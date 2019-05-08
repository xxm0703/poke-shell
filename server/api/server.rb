# frozen_string_literal: true

require 'sinatra'
require 'active_record'
require 'rubygems'
require 'json'

current_dir = File.dirname(__FILE__)
Dir["#{current_dir}/models/*.rb"].each { |file| require file }

ActiveRecord::Base.establish_connection(
  adapter: 'postgresql',
  database: 'development',
  host: 'localhost',
  username: 'postgres',
  password: 'postgres'
)

enable :sessions

before do
  s_rd_pipe, a_wr_pipe = IO.pipe
  a_rd_pipe, s_wr_pipe = IO.pipe
  `#{File.join(current_dir, '/../bin/')}start_game #{s_rd_pipe} #{s_wr_pipe}`
  s_rd_pipe.close
  s_wr_pipe.close

  content_type :json
end

helpers do
  def generate_token(user)
    (user.username + user.password).hash
  end

  # Cheaty way of checking
  def check_encoding(str)
    str[/[A-Za-z0-9_]+/] == str
  end
end

# TODO: permit only some params
post '/register' do
  user = User.new(params)

  unless check_encoding(user.password) && check_encoding(user.username)
    status 411
    return { status: 411,
             message: 'Username and password should use only letters, digits and underscore' }.to_json
  end

  if user.save!
    user.update(id: generate_token(user))
    return { 'status': 0, 'message': 'Success' }.to_json
  end
rescue ActiveRecord::RecordNotUnique
  status 422
  { 'status': 422, 'message': 'Username already taken' }.to_json
rescue Exception
  status 400
  { 'status': 400, 'message': user.errors.to_a }.to_json
end

post '/log' do
  user = User.find_by username: params[:username]
  if user.nil? == true || user.password != params[:password]
    status 408
    { 'status': 408, 'message': 'Username or password, not correct' }.to_json
  else
    { 'status': 0, 'message': 'Success', 'session_id': user.id }.to_json
  end
end

get '/join_table' do
  token = params['token']

  if token.nil? || User.find(token).nil?
    status 420
    { status: 420, message: 'Authentication error' } if room.nil?
  end

  user = User.find(token)

  if user.room_id.nil?
    room = Room.find_by(full: false)

    room = Room.new if room.nil?
    room.entered += 1
    room.full = true if room.entered == room.capacity
    room.save
    user.room = room
    user.save
  end

  # Just for testing
  until Room.find(room.id).full
    puts Room.find(room.id).entered.to_s + user.username
  end

  { status: 0, room_id: room.id, 'people': User
    .where(room_id: room.id)
    .map { |u| { 'display_name': u.display_name } } }.to_json
end

get '/exit_table' do
  user = User.find(params[:token])
  room = user.room
  { status: 405, message: 'You are not in a room' } if room.nil?
  room.update(entered: room.entered - 1)

  room.delete if room.entered.zero?

  user.update(room_id: nil)
  { 'status': 0, 'message': 'Success' }.to_json
end

$tmp = 5

get '/' do
  user = User.find(params[:token])
  room = user.room
  $tmp += 1
  { users: room.users, tmp: $tmp }.to_json
end

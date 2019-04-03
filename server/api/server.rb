# frozen_string_literal: true

require 'sinatra'
require 'active_record'
# require_relative 'cards'
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
end

# TODO: permit only some params
post '/register' do
  user = User.new(params)
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
    status 401
    return token.to_json
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
  until Room.find(room.id).entered == 2
    puts Room.find(room.id).entered.to_s + user.username
  end

  { 'room_id': room.id, 'people': User
    .where(room_id: room.id)
    .map { |u| { 'display_name': u.display_name } } }.to_json
end

get '/exit_table' do
  user = User.find(params[:token])
  room = user.room
  room.update(entered: room.entered - 1)
  user.update(room_id: nil)
end

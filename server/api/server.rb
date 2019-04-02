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
# To make instance
@@connections = {}
@@rooms = {}

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

  def log(user)
    session['token'] = generate_token(user)
    @@connections[session['token']] = user.id
    session['token']
  end
end

# TODO: permit only some params
post '/register' do
  user = User.new(params)
  if user.save!
    { 'status': 0, 'message': 'Success' }.to_json
  end
rescue ActiveRecord::RecordNotUnique
  { 'status': 422, 'message': 'Username already taken' }.to_json
rescue Exception
  { 'status': 400, 'message': 'Something went wrong with your registration' }.to_json
end

post '/log' do
  user = User.find_by username: params[:username]
  if user.nil? == true || user.password != params[:password]
    # To remove debug message
    { 'status': 408, 'message': 'Username or password, not correct', params[:password]=> params[:username] }.to_json
  else
    token = log(user)
    { 'status': 0, 'message': 'Success', 'session_id': token }.to_json
  end
end

get '/join_table' do
  token = params['token']

  if token.nil? || @@connections[token].nil?
    status 401
    return token.to_json
  end
  values = @@rooms.values
  if values.empty? or values[-1].size == 5
    room_id = rand.hash
    @@rooms[room_id] = [] if @@rooms[room_id].nil?
  else
    room_id = @@rooms.keys[-1]
  end
  @@rooms[room_id].push session[:token]
  session[:roomId] = room_id
  status 200
  session.to_json
end

get '/' do
 @link = request.ip.hash.to_s
 session['counter'] ||= 0
 session['counter'] += 1
 @counter = session['counter']
 @@connections.to_json
end

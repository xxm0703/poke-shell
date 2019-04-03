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
$rooms = []

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

  if Room.find_by(player_id: user).nil?
    last_room = Room.last
    room = last_room.nil? 
  end

end

get '/' do
 @link = request.ip.hash.to_s
 session['counter'] ||= 0
 session['counter'] += 1
 @counter = session['counter']
 $connections.to_json
end

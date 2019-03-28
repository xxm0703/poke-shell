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
   session['username'] = user.username
 end
end

# TODO: permit only some params
post '/register' do
 begin
  user = User.new(params)
  if user.save!
   status 201
   log(user)
  end
 rescue ActiveRecord::RecordNotUnique
  status 422
  {'error': 'username already taken'}.to_json
 rescue Exception
  status 400
  {'error': 'Something went wrong with your registration'}.to_json
 end
end

post '/log' do
  user = User.find_by username: params[:username]
  if user.nil? == true or user.password != params[:password]
    {'error': "Username or password, not correct", params[:password]=> params[:username]}.to_json
  else
    log(user)
    session.to_json
  end
end

get '/join_table' do
  token = params['token']

  if(token.nil? or @@connections[token].nil?)
    status 401
    return token.to_json
  end
  values = @@rooms.values
  if values.empty? or values[-1].size == 5
    room_id = rand.hash
    if @@rooms[room_id].nil?
      @@rooms[room_id] = []
    end
  else
    room_id = @@rooms.keys[-1]
  end
  @@rooms[room_id].push session[:token]
  session[:roomId] = room_id
  status 200
  session.to_json
end

get '/' do
 @link = generate_token(request.ip).to_s
 session['counter'] ||= 0
 session['counter'] += 1
 @counter = session['counter']
 @@connections.to_json
end

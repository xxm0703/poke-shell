# frozen_string_literal: true

require 'sinatra'
require 'active_record'
require 'rubygems'
require 'json'

current_dir = File.dirname(__FILE__)
Dir["#{current_dir}/models/*.rb"].each { |file| require file }
require "#{current_dir}/../game_engine/src/table.rb"

ActiveRecord::Base.establish_connection(
  adapter: 'postgresql',
  database: 'development',
  host: 'localhost',
  username: 'postgres',
  password: 'postgres'
)

enable :sessions

$games = Hash.new { |h, k| h[k] = Game.new }
before do
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
  else
    room = user.room
  end

  $games[room.id] << Player.new(user.id, user.balance)
  puts $games.to_s

  { status: 0, room_id: room.id, 'people': User
    .where(room_id: room.id)
    .map { |u| { 'display_name': u.display_name } } }.to_json
end

get '/exit_table' do
  user = User.find(params[:token])
  room = user.room
  { status: 405, message: 'You are not in a room' } if room.nil?
  room.update(entered: room.entered - 1)

  $games[room.id].players.delete_if { |u| u.id == user.id }

  if room.entered.zero?
    room.delete
    $games[room.id] = Game.new
  end

  user.update(room_id: nil)
  { 'status': 0, 'message': 'Success' }.to_json
end

get '/deal' do
  user = User.find(params[:token])
  game = $games[user.room.id]
  player = game.find params[:token]

  raise Exception if player.nil?

  return { status: 0, hand: player.hand, token: user.id }.to_json unless player.hand.empty?

  player.deal_cards game.deck.deal
  { status: 0, hand: player.hand, token: user.id }.to_json
end

get '/bet' do
  user = User.find(params[:token])
  game = $games[user.room.id]
  player = game.find params[:token]

  unless params[:bet].nil?
    bet = params[:bet].to_i
    raise ArgumentError if bet < game.current_bet

    game.current_bet = bet
    player.current_bet = bet
  end
end

get '/flop' do
  user = User.find(params[:token])
  game = $games[user.room.id]
  player = game.find params[:token]

  game.table ||= game.deck.flop

  { status: 0, table: game.table, token: user.id }.to_json
end

get '/turn' do
  user = User.find(params[:token])
  game = $games[user.room.id]
  player = game.find params[:token]

  if game.table.size < 3
    { status: 403, message: 'Wrong order of requests' }
  else
    game.table << game.deck.turn if game.table.size < 4
    { status: 0, table: game.table, token: user.id }.to_json
  end
end

get '/fold' do
  user = User.find(params[:token])
  game = $games[user.room.id]
  player = game.find params[:token]

  game.whole_pot += player.current_pot
  player.pay_pot
  user.balance = player.balance
  user.save!
  game.delete player
end

get '/' do
  user = User.find(params[:token])
  room = user.room
  $tmp += 1
  { users: room.users, tmp: $tmp }.to_json
end

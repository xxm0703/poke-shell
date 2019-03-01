# frozen_string_literal: true

require 'sinatra'
require 'active_record'
require_relative 'cards'
require 'rubygems'
require 'json'

current_dir = File.dirname(__FILE__)
Dir["#{current_dir}/models/*.rb"].each { |file| require file }

ActiveRecord::Base.establish_connection(
  { :adapter => 'postgresql',
    :database => 'development',
    :host => 'localhost',
    :username => 'postgres',
    :password => "postgres" }
  )

enable :sessions
connections = {}

s_rd_pipe, a_wr_pipe = IO.pipe
a_rd_pipe, s_wr_pipe = IO.pipe
`#{File.join(current_dir, '/../bin/')}start_game #{s_rd_pipe} #{s_wr_pipe}`
s_rd_pipe.close
s_wr_pipe.close

helpers do
  def generate_token(user)
    (user.username + user.password).hash
  end
end

#TODO permit only some params
post '/register' do
  begin
    user = User.new(params)
    if user.save!
      status 201
      session["token"] = generate_token(user)
    end
  # rescue Exception
  #   status 422
  end

end

get '/new' do
  token = generate_token(request.ip)
  connections[token] = request.ip
  "#{generate_token(request.ip)}  #{session['counter']}"
end

get '/join_table' do
	d = Deck.new()
	"#{d.deal.to_s}  #{Random.rand}"
end

get '/' do
  @link = generate_token(request.ip).to_s
  session['counter'] ||= 0
  session['counter'] += 1
  @counter = session['counter']
  haml :index
end

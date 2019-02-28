# frozen_string_literal: true

require 'sinatra'
require_relative 'cards'
require 'rubygems'

current_dir = File.dirname(__FILE__)

enable :sessions
connections = {}

s_rd_pipe, a_wr_pipe = IO.pipe
a_rd_pipe, s_wr_pipe = IO.pipe
`#{File.join(current_dir, '/../bin/')}start_game #{s_rd_pipe} #{s_wr_pipe}`
s_rd_pipe.close
s_wr_pipe.close

helpers do
  def generate_token(ip)
    ip.hash
  end
end

get '/new' do
  token = generate_token(request.ip)
  connections[token] = request.ip
  "#{generate_token(request.ip)}  #{session['counter']}"
end

get '/join_table' do
	d = new Deck
	"#{d.deal}"
end

get '/' do
  @link = generate_token(request.ip).to_s
  session['counter'] ||= 0
  session['counter'] += 1
  @counter = session['counter']
  haml :index
end

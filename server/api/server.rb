require "sinatra"
require 'rubygems'

current_dir = File.dirname(__FILE__)

enable :sessions

s_rd_pipe, a_wr_pipe = IO.pipe
a_rd_pipe, s_wr_pipe = IO.pipe
puts current_dir
`#{File.join(current_dir, '/../bin/')}start_game #{s_rd_pipe} #{s_wr_pipe}`
connections = {}

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

get '/' do

	@link = "#{generate_token(request.ip)}"
	session['counter'] ||= 0
	session['counter'] += 1
	@counter = session['counter']
	haml :index
end

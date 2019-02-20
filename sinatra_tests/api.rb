require "sinatra"
require 'rubygems'
require 'active_record'
require_relative "card_deck"

current_dir = Dir.pwd
Dir["#{current_dir}/models/*.rb"].each { |file| require file }

get '/' do
	@link = "click me!"
	haml :index
end

get '/greet/:name' do
  name = params[:name]
  User.create(:username => name, :password => "123456")
	"Hello, Sinatra #{name}"
end

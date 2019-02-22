require "sinatra"
require 'rubygems'
require 'active_record'
require_relative "card_deck"

current_dir = Dir.pwd
Dir["#{current_dir}/models/*.rb"].each { |file| require file }

ActiveRecord::Base.establish_connection(
 { :adapter => 'postgresql',
   :database => 'development',
   :host => 'localhost',
   :username => 'postgres',
   :password => "martin20" }
)

get '/' do
	@link = "click me!"
	haml :index
end

get '/greet/:name' do
  name = params[:name]
  u = User.new(:username => name, :password => "123456")
	u.save!
	"Hello, Sinatra #{name}"
end

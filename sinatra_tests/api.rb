require "sinatra"
require 'rubygems'
require 'active_record'
require_relative "card_deck"

enable :session

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

#TODO permit only some params
post '/register' do
  "#{params[:credentials]}"
  user = User.new(params)
  if user.save!
    session['token'] = user.id.hash
    status 201
  else
    "Hello"
    status 422
  end

end

get '/greet/:name' do
  name = params[:name]
	"Hello, Sinatra #{name}"
end

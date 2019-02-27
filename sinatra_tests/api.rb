require "sinatra"
require 'rubygems'
require 'active_record'
require_relative "card_deck"

enable :session

current_dir = File.join(File.dirname(__FILE__), '../../')

# ActiveRecord::Base.establish_connection(
#  { :adapter => 'postgresql',
#    :database => 'development',
#    :host => 'localhost',
#    :username => 'postgres',
#    :password => "martin20" }
# )

get '/' do
	@link = "click me!"
	haml :index
end

#TODO permit only some params
post '/register' do
  session["token"] = "1234"
  status 422
  begin
    user = User.new(params)
    if user.save!
      session['token'] = user.id.hash
      status 201
    end
  rescue Exception
    status 422
  end

end

get '/greet/:name' do
  name = params[:name]
	"Hello, Sinatra #{name}"
end

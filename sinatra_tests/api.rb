require "sinatra"
require_relative "card_deck"

get '/' do
	@link = "click me!"
	haml :index
end

get '/greet/:name' do
	"Hello, Sinatra #{params[:name]}"
end

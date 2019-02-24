require "sinatra"
require 'rubygems'

enable :session

get '/' do
	@link = "click me!"
	haml :index
end


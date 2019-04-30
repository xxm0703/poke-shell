module Deck
	require_relative "card.rb"

	SUITS = ['S', 'H', 'D', 'C']
	RANKS = ['A', 'K', 'Q', 'J', '10', '9', '8', '7', '6', '5', '4', '3', '2']

	class Deck
		def initialize()
			@deck = []
			SUITS.each do |s|
				RANKS.each do |r|
					@deck.push Card.new(s,r)
				end
			end
		end

		def deal

		end

		def flop

		end

		def turn

		end

		def river
			
		end

	end
end
Deck::Deck.new()

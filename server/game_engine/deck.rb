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

		def deal(players_count)
			@deck.shuffle!
			dealed = Array.new(players_count) {Array.new(2)}

			(0...2).each { |i| (0...players_count).each { |j| dealed[j][i] = @deck.pop }}
		end

		def flop
			clear
			@deck.pop(3)
		end

		def turn
			clear
			@deck.pop
		end

		def river
			turn
		end

private

		def clear
			@deck.pop
		end
	end
end

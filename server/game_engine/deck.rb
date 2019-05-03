module Deck
	require_relative "card.rb"

	SUITS = ['S', 'H', 'D', 'C']
	RANKS = ['A', 'K', 'Q', 'J', '10', '9', '8', '7', '6', '5', '4', '3', '2']

	class Deck
		def initialize()
			@deck = []
			@deck = RANKS.product(SUITS)
			.map { |rank, suit| Card.new suit, rank }
		end

		def deal(players_count)
			@deck.shuffle!
			dealed = Array.new(players_count) {Array.new(2)}

			(0...2).each { |i| (0...players_count).each { |j| dealed[j][i] = @deck.pop }}
			return dealed
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

# a = Deck::Deck.new
# puts a.deal(2)

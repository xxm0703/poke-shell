module Poker
	require_relative "deck.rb"
	include Deck

	def Poker.high_card(best, current)
		if best.class == Array || current.class == Array
			best = best[high_card(best[0], best[1])]
			current = current[high_card(current[0], current[1])]
		end

		best_index = RANKS.index best[0..-2]
		current_index = RANKS.index current[0..-2]

		if best_index < current_index
			return 0
		elsif best_index > current_index
			return 1
		else
			return -1
		end

	end

	def check_combination

	end
end

puts Poker.high_card(['10S', 'KH'], ['AS', '8C'])

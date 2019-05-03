module Poker
	require_relative "deck.rb"
	include Deck

	def Poker.get_rank(cards)
		cards.map { |e| e[0..-2] }
	end

	def Poker.high_card(best, current)
		if best.class == Array || current.class == Array
			best = best[high_card(best[0], best[1])]
			current = current[high_card(current[0], current[1])]
		end

		best_index = RANKS.index best
		current_index = RANKS.index current

		if best_index < current_index
			return 0
		elsif best_index > current_index
			return 1
		else
			return -1
		end

	end

	def Poker.pair_card(best, current)
		best = get_rank(best)
		current = get_rank(current)
		if best.uniq.length == 1 || current.uniq.length == 1
			if best.uniq.length != 1
				return 1
			elsif current.uniq.length != 1
				return 0
			else
				return high_card(best, current)
			end
		end
		return -1
	end

	def check_combination
		get_rank(best)
		get_rank(current)
	end
end

puts Poker.pair_card(['10S', 'JH'], ['9S', '9C'])

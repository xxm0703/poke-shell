module Poker
	require_relative "deck.rb"
	include Deck

	def Poker.get_rank(cards)
		cards.map { |e| e[0..-2] }
	end

	def Poker.higher_card(f, s)
		best_index = RANKS.index f
		current_index = RANKS.index s

		best_index < current_index ? f : s
	end

	def Poker.high_card(best, current)

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
		best = get_rank(best).reduce('2C', &higher_card)
		current = get_rank(current).reduce('2C', &higher_card)

		best = get_rank(best)
		current = get_rank(current)
		if best.uniq.length != best.length || current.uniq.length != current.length
			if best.uniq.length == best.length
				return 1
			elsif current.uniq.length == current.length
				return 0
			else
				return high_card(best, current)
			end
		end
		return -1
	end

	def check_combination
		best =
		get_rank(best)
		get_rank(current)
	end
end

puts Poker.pair_card(['10S', 'JH'], ['9S', '9C'])

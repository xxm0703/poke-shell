class Card
	SUITS = ['S', 'H', 'D', 'C']
	RANKS = ['A', 'K', 'Q', 'J', '10', '9', '8', '7', '6', '5', '4', '3', '2']

	attr_reader :rank

	def initialize(*args)
		unless args.length == 1
			@suit, @rank = args 
		else
			@suit = args[0][-1..-1]
			@rank = args[0][0..-2]
		end
	end	

	def to_s
		@rank + @suit
	end

	def higher_card(other)
		best_index = RANKS.index @rank
		current_index = RANKS.index other.rank

		best_index < current_index ? self : other
	end
end

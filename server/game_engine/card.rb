class Card
	def initialize(suit, rank)
		@rank = rank
		@suit = suit
	end

	def to_s
		@rank + @suit
	end
end

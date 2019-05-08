# frozen_string_literal: true

class Card
  SUITS = %w[S H D C].freeze
  RANKS = %w[A K Q J 10 9 8 7 6 5 4 3 2].freeze

  attr_reader :rank, :suit

  def initialize(*args)
    if args.length == 1
      @suit = args[0][-1..-1]
      @rank = args[0][0..-2]
    else
      @rank, @suit = args
     end
  end

  def to_s
    @rank + @suit
  end

  def ==(other)
    @rank == other.rank &&
      @suit == other.suit
  end

  def <=>(other)
    best_index = RANKS.index @rank
    current_index = RANKS.index other.rank

    best_index < current_index ? 1 :
    best_index == current_index ? 0 : -1
  end

  def higher_card(other)
    best_index = RANKS.index @rank
    current_index = RANKS.index other.rank

    best_index < current_index ? self : other
  end
end

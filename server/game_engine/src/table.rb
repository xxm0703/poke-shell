# frozen_string_literal: true

# Stores the strongest combination
class Combination
  attr_reader :combination, :rating

  def initialize(combination, rating)
    @combination = combination
    @rating = rating
  end

  def <=>(other)
    if @rating < other.rating
      -1
    elsif @rating > other.rating
      1
    else
      0
    end
  end

  def ==(other)
    @rating == other.rating &&
      @combination == other.combination
  end

  def to_s
    @combination.to_s + ' ' + @rating.to_s
  end
end

# Representation of one player
class Player
  attr_accessor :combination
  attr_reader :id

  def initialize(id, combination)
    @id = id
    @combination = combination
    @hand = []
  end

  def deal_cards(cards)
    @hand = cards
  end
end

# Represents a poker table
class Table
  attr_accessor :players

  def initialize
    @pot = 0
    @players = []
  end

  def <<(player)
    @players << player
  end
end

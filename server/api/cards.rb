# frozen_string_literal: true

class Card
  def initialize(suit, rank)
    @suit = suit
    @rank = rank
  end

  def beats(other_card)
    @rank > other_card.rank
  end
end

class Deck
  @suits = %w[Spades Hearths Diamonds Clubs]
  @ranks = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
  def initialize
    @suits.each do |suit|
      @ranks.each do |rank|
        @cards << Card(suit, rank)
      end
    end
  end

  def self.deal
    @cards[Random.rand]
  end
end

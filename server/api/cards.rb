# frozen_string_literal: true

class Card
  def initialize(suit, rank)
    @suit = suit
    @rank = rank
  end

  def beats(other_card)
    @rank > other_card.rank
  end

  def to_s
    "#{@suit} #{@rank}"
  end
end

class Deck
    def initialize
        @ranks = 2..14
        @suits = %w[Spades Hearths Diamonds Clubs]
        @cards = []
        @suits.each do |suit|
            @ranks.each do |rank|
                @cards.push Card.new(suit, rank)
            end
        end
    end

    def deal
        @cards[Random.rand*52]
    end
end

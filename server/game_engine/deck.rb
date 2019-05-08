# frozen_string_literal: true

module Deck
  require_relative 'card.rb'

  class Deck
    def initialize
      @deck = []
      @deck = RANKS.product(SUITS)
                   .map { |rank, suit| Card.new suit, rank }
    end

    def deal(players_count)
      @deck.shuffle!
      dealed = Array.new(players_count) { Array.new(2) }

      (0...2).each { |i| (0...players_count).each { |j| dealed[j][i] = @deck.pop } }
      dealed
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

  class Hand
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

    def to_s
      @combination.to_s + ' ' + @rating.to_s
    end
  end
end

# a = Deck::Deck.new
# puts a.deal(2)

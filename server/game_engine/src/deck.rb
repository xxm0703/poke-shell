# frozen_string_literal: true

require_relative 'card.rb'

# The deck of cards all 52 of them
class Deck
  attr_reader :deck

  def initialize
    @deck = []
    @deck = Card::RANKS.product(Card::SUITS)
                       .map { |rank, suit| Card.new rank, suit }

    @deck.shuffle!
  end

  def deal(players_count)
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

  def ==(other)
    @deck.zip(other.deck)
         .each { |e| return false if e[0] != e[1] }

    true
  end

  private

  def clear
    @deck.pop
  end
end

# a = Deck::Deck.new
# puts a.deal(2)

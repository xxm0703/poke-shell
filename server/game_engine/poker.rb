# frozen_string_literal: true

module Poker
  require_relative 'deck.rb'

  WEAKEST = Card.new '2C'
  STRONGEST = Card.new 'AS'

  def self.get_ranks(cards)
    cards.map(&:rank)
  end

  def self.high_card(best, current)
    best = best.reduce(WEAKEST, :higher_card)
    current = current.reduce(WEAKEST, :higher_card)

    best_index = Card::RANKS.index best.rank
    current_index = Card::RANKS.index current.rank

    return 0 if best_index < current_index

    return 1 if best_index > current_index

    -1
  end

  def self.one_pair(cards)
    # puts find_duplicates(cards)
    return true if find_duplicates(cards).length == 1

    false
  end

  def self.two_pair(cards); end

  def check_combination
    # TODO
  end

  def self.find_duplicates(cards)
    ranks = get_ranks(cards)
    duplicates = ranks - ranks.uniq
    puts ranks - ranks.uniq
    duplicates
  end
end

puts Poker.one_pair([Card.new('JS'), Card.new('JH')])

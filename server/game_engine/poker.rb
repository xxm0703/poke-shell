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
    find_duplicates(cards).each_value { |v| return v if v.length == 2 }

    nil
  end

  def self.two_pair(cards)
    f_pair = one_pair cards
    return nil if f_pair.nil?

    f_pair.each { |e| cards.delete_at e }

    s_pair = one_pair cards
    return nil if s_pair.nil?

    f_pair + s_pair
  end

  def self.tree_kind(cards)
    find_duplicates(cards).each_value { |v| return v if v.length == 3 }

    nil
  end

  def self.straight(cards)
    ranks = get_ranks(cards)
    sequence = []
    Card::RANKS.each do |e|
      ranks.include?(e) ? sequence << ranks.index(e) : sequence.clear
      return sequence.sort.reverse if sequence.length == 5
    end
  end

  def check_combination
    # TODO
  end

  def self.find_duplicates(cards)
    ranks = get_ranks(cards)
    duplicates = Hash.new { [] }
    ranks.each_with_index { |e, i| duplicates[e] = duplicates[e].unshift i }
    duplicates
  end
end

puts Poker.straight([Card.new('10S'), Card.new('JS'), Card.new('QH'), Card.new('KC'), Card.new('AS'), Card.new('4H')]).to_s

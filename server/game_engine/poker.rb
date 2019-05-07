# frozen_string_literal: true

module Poker
  require_relative 'deck.rb'

  WEAKEST = Card.new '2C'
  STRONGEST = Card.new 'AS'

  def self.get_ranks(cards)
    cards.map(&:rank)
  end

  def self.get_suits(cards)
    cards.map(&:suit)
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

  def self.pair(cards, amount)
    find_duplicates(get_ranks(cards)).each_value { |v| return v if v.length == amount }

    nil
  end

  def self.one_pair(cards)
    pair(cards, 2)
  end

  def self.two_pair(cards)
    f_pair = one_pair cards
    return nil if f_pair.nil?

    f_pair.each { |e| cards.delete_at e }

    s_pair = one_pair cards
    return nil if s_pair.nil?

    (f_pair + s_pair).sort.reverse
  end

  def self.three_kind(cards)
    pair(cards, 3)
  end

  # Possible breach (not always the best combination)
  def self.straight(cards)
    ranks = get_ranks(cards)
    sequence = []
    Card::RANKS.each do |e|
      ranks.include?(e) ? sequence << ranks.index(e) : sequence.clear
      return sequence.sort.reverse if sequence.length == 5
    end
  end

  # Possible breach (not always the best combination)
  def self.flush(cards)
    find_duplicates(get_suits(cards)).each_value { |v| return v if v.length >= 5 }

    nil
  end

  def self.full_house(cards)
    pair = one_pair cards
    return nil if pair.nil?

    pair.each { |e| cards.delete_at e }

    kind = three_kind cards
    return nil if kind.nil?

    (pair + kind).sort.reverse
  end

  def check_combination
    # TODO
  end

  def self.find_duplicates(set)
    duplicates = Hash.new { [] }
    set.each_with_index { |e, i| duplicates[e] = duplicates[e].unshift i }
    duplicates
  end
end

puts Poker.full_house([Card.new('JC'), Card.new('JH'), Card.new('AS'), Card.new('KS'), Card.new('AS'), Card.new('JS')]).to_s

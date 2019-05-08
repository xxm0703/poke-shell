# frozen_string_literal: true

# This is the poker module
module Poker
  require_relative 'deck.rb'
  # include Deck

  WEAKEST = Card.new '2C'
  STRONGEST = Card.new 'AS'

  HAND_STRENGTH = %i[
    royal_flush
    straight_flush
    four_kind
    full_house
    flush
    straight
    three_kind
    two_pair
    one_pair
  ].freeze

  def self.get_ranks(cards)
    cards.map(&:rank)
  end

  def self.get_suits(cards)
    cards.map(&:suit)
  end

  def self.pair(cards, amount)
    find_duplicates(get_ranks(cards)).each_value { |v| return v if v.length == amount }

    nil
  end

  def self.one_pair(cards)
    pair(cards, 2)
  end

  def self.two_pair(cards)
    cards_copy = cards.dup
    f_pair = one_pair cards
    return nil if f_pair.nil?

    f_pair.each { |e| cards_copy.delete_at e }

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

    Card::RANKS.cycle(2) do |e|
      sequence.clear if sequence.length > 1 && e.eql?('K')

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
    cards_copy = cards.dup
    pair = one_pair cards
    return nil if pair.nil?

    pair.each { |e| cards_copy.delete_at e }

    kind = three_kind cards
    return nil if kind.nil?

    (pair + kind).sort.reverse
  end

  def self.four_kind(cards)
    pair(cards, 4)
  end

  # Possible breach (not always the best combination)
  def self.straight_flush(cards)
    f = flush(cards)
    s = straight(cards)

    return nil if f.nil? || s.nil?

    return f if (f - s).empty?

    nil
  end

  def self.royal_flush(cards)
    sf = straight_flush(cards)

    return sf if get_ranks(cards).include?('A') && !sf.nil?

    nil
  end

  def self.eval_combination
    a = [Card.new('JC'), Card.new('QS'), Card.new('JS'), Card.new('AS'), Card.new('JS'), Card.new('JS')]

    HAND_STRENGTH.each_with_index do |f, i|
      tmp = Poker.send(f, a)

      return Deck::Hand.new(tmp, (10 - i)) unless tmp.nil?

    end
  end

  def self.find_duplicates(set)
    duplicates = Hash.new { [] }
    set.each_with_index { |e, i| duplicates[e] = duplicates[e].unshift i }
    duplicates
  end
end
puts Poker.eval_combination
# puts Poker.royal_flush(a).to_s
# puts Poker.full_house(a).to_s
# puts Poker.two_pair(a).to_s
# puts a

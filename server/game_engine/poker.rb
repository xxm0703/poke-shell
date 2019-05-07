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

  def self.one_pair(cards)
    find_duplicates(get_ranks(cards)).each_value { |v| return v if v.length == 2 }

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
    find_duplicates(get_ranks(cards)).each_value { |v| return v if v.length == 3 }

    nil
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
  

  def check_combination
    # TODO
  end

  def self.find_duplicates(set)
    duplicates = Hash.new { [] }
    set.each_with_index { |e, i| duplicates[e] = duplicates[e].unshift i }
    duplicates
  end
end

puts Poker.flush([Card.new('10C'), Card.new('JH'), Card.new('QS'), Card.new('KS'), Card.new('AS'), Card.new('4S')]).to_s

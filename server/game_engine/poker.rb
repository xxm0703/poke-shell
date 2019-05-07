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

  def self.pair_card(best, current)
    best_ranks = get_ranks(best)
    current_ranks = get_ranks(current)

    if best_ranks.uniq.length != best_ranks.length ||
       current_ranks.uniq.length != current_ranks.length

      return 1 if best_ranks.uniq.length == best_ranks.length

      return 0 if current_ranks.uniq.length == current_ranks.length

      return high_card(best, current)

	end
    -1
  end

  def check_combination
    # TODO
  end

private

  def find_pair(cards)
	ranks = get_ranks(cards)
	duplicate = ranks - ranks.uniq
	cards.select { |e| e.rank == duplicate[0] }
  end

end

puts Poker.pair_card([Card.new('JS'), Card.new('JH')],
                     [Card.new('AS'), Card.new('9C')])

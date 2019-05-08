# frozen_string_literal: true

require_relative '../src/poker.rb'
require 'test/unit'

class TestPoker < Test::Unit::TestCase
  def setup
    # @deck1 = Deck.new
    # @deck2 = Deck.new
  end

  def test_pair
    hand = [Card.new('JC'), Card.new('QS'), Card.new('JS'), Card.new('AS'), Card.new('4S'), Card.new('&S')]
    assert_equal([2, 0], Poker.one_pair(hand))
    hand[0] = Card.new '9D'
    assert_nil(Poker.one_pair(hand))
  end

  def test_two_pair
    hand = [Card.new('JC'), Card.new('QS'), Card.new('JS'), Card.new('7S'), Card.new('4S'), Card.new('7S')]
    assert_equal([5, 3, 2, 0], Poker.two_pair(hand))
    hand[0] = Card.new '9D'
    assert_nil(Poker.two_pair(hand))
  end

  def test_three_kind
    hand = [Card.new('JC'), Card.new('QS'), Card.new('JS'), Card.new('7S'), Card.new('4S'), Card.new('JD')]
    assert_equal([5, 2, 0], Poker.three_kind(hand))
    hand[0] = Card.new '9D'
    assert_nil(Poker.three_kind(hand))
  end

  def test_straight
    hand = [Card.new('JC'), Card.new('QS'), Card.new('KS'), Card.new('AS'), Card.new('10S'), Card.new('3D')]
    assert_equal([4, 3, 2, 1, 0], Poker.straight(hand))
    hand[0] = Card.new '9D'
    assert_nil(Poker.straight(hand))
  end

  def test_flush
    hand = [Card.new('2S'), Card.new('QS'), Card.new('JS'), Card.new('7S'), Card.new('4S'), Card.new('JD')]
    assert_equal([4, 3, 2, 1, 0], Poker.flush(hand))
    hand[0] = Card.new '9D'
    assert_nil(Poker.flush(hand))
  end

  def test_full_house
    hand = [Card.new('JC'), Card.new('7S'), Card.new('JS'), Card.new('7C'), Card.new('4S'), Card.new('7D')]
    assert_equal([5, 3, 2, 1, 0], Poker.full_house(hand))
    hand[0] = Card.new '9D'
    assert_nil(Poker.full_house(hand))
  end

  def test_four_kind
    hand = [Card.new('JC'), Card.new('QS'), Card.new('JS'), Card.new('7S'), Card.new('JH'), Card.new('JD')]
    assert_equal([5, 4, 2, 0], Poker.four_kind(hand))
    hand[0] = Card.new '9D'
    assert_nil(Poker.four_kind(hand))
  end

  def test_eval_combination
    hand = [Card.new('2S'), Card.new('QS'), Card.new('JS'), Card.new('7S'), Card.new('4S'), Card.new('JD')]
    assert_equal(Combination.new([4, 3, 2, 1, 0], 6), Poker.eval_combination(hand))
  end
end

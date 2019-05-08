# frozen_string_literal: true

require_relative '../src/deck.rb'
require 'test/unit'

class TestDeck < Test::Unit::TestCase
  def setup
    @deck1 = Deck.new
    @deck2 = Deck.new
  end

  def test_initialization
    assert_not_equal(Deck.new, @deck1)
    assert_not_equal(@deck2, @deck1)
  end

  def test_deal
    assert_not_equal(@deck1.deal(5), @deck2.deal(5))
  end

  def test_flop
    assert_not_equal(@deck1.flop, @deck2.flop)
    assert_equal(3, @deck1.flop.length)
  end

  def test_turn
    assert_not_equal(@deck1.turn, @deck2.turn)
    assert_instance_of(Card, @deck1.turn)
  end
end

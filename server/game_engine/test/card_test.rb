# frozen_string_literal: true

require_relative '../src/card.rb'
require 'test/unit'

class TestCard < Test::Unit::TestCase
  def setup
    @card1 = Card.new '10C'
    @card2 = Card.new('J', 'S')
  end

  def test_initialization
    assert_equal('S', @card2.suit)
    assert_equal('10', @card1.rank)
    assert_equal('J', @card2.rank)
  end

  def test_to_s
    assert_equal('10C', @card1.to_s)
    assert_equal('JS', @card2.to_s)
  end

  def test_comparison
    assert_equal(1, @card2 <=> @card1)
    assert_equal(0, @card2 <=> Card.new('JH'))

    assert_equal(@card2, @card2.higher_card(@card1))

    assert_equal(Card.new('10C'), @card1)
  end
end

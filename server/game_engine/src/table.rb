# frozen_string_literal: true

require_relative './deck.rb'

# Stores the strongest combination
class Combination
  attr_reader :combination, :rating

  def initialize(combination, rating)
    @combination = combination
    @rating = rating
  end

  def <=>(other)
    if @rating < other.rating
      -1
    elsif @rating > other.rating
      1
    else
      0
    end
  end

  def ==(other)
    @rating == other.rating &&
      @combination == other.combination
  end

  def to_s
    @combination.to_s + ' ' + @rating.to_s
  end
end

# Representation of one player
class Player
  attr_accessor :combination
  attr_reader :id, :hand

  def initialize(id, balance)
    @id = id
    @balance = balance
    @current_pot = 0
    @combination = nil
    @hand = []
  end

  def ==(other)
    @id == other.id
  end

  def pay_pot
    @balance = balance - @current_pot
    @current_pot = 0
  end

  def deal_cards(cards)
    @hand = cards
  end
end

# Represents a poker table
class Game
  attr_accessor :players, :deck, :current_bet, :whole_pot

  def initialize
    @deck = Deck.new
    @whole_pot = 0
    @current_bet = 0
    @players = []
  end

  def player_pay(player_id)
    @players[@players.index player_id].current_pot = @current_bet
  end

  def find(token)
    index = @players.map(&:id).find_index(token.to_i)
    index.nil? ? nil : @players[index]
  end

  def <<(player)
    @players << player unless @players.include? player
    puts @players.to_s
  end
end

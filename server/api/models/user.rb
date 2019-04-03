class User < ActiveRecord::Base
    belongs_to :room
    validates :password, length: { in: 6..20 }
    validates :password, confirmation: true
end

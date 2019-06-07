class User < ActiveRecord::Base
    belongs_to :room
    validates :password, length: { in: 6..100 }
end

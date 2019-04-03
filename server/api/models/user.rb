class User < ActiveRecord::Base
    validates :password, length: { in: 6..20 }
    validates :password, confirmation: true
end

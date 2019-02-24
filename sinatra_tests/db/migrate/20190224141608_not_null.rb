class NotNull < ActiveRecord::Migration[5.2]
  def change
    change_column_null :users, :username, true
    change_column_null :users, :password, true
  end
end

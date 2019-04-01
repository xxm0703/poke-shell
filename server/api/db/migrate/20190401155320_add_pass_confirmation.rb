class AddPassConfirmation < ActiveRecord::Migration[5.2]
  def change
    add_column :users, :display_name, :string, :null => false
    add_column :users, :password_confirmation, :string, :null => false
  end
end

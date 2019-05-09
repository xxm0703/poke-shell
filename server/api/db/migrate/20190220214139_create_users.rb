class CreateUsers < ActiveRecord::Migration[5.2]
  def change
    create_table :users do |t|
      t.belongs_to :room
      t.string :username, :null => false
      t.string :password, :null => false
      t.string :display_name, :null => false
      t.integer :balance, :default => 0
      t.timestamps null: false
    end
  end
end

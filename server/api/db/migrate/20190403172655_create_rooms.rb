class CreateRooms < ActiveRecord::Migration[5.2]
  def change
    create_table :rooms do |t|
      t.boolean :pending, :default => true
      t.integer :entered
      t.integer :capacity, :default => 5
      t.boolean :full, :default => false
      t.timestamps
    end
  end
end

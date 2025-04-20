🛒 Online Shopping Cart System – C++
📌 Overview
This C++ program implements a console-based online shopping cart system. It allows users to:

• Log in with credentials

• Browse items categorized into predefined categories (Clothes, Food, Cosmetics, Electronics, Books)

• Add items to a cart

• Undo the last added item

• View cart contents

• Checkout with or without cash on delivery

The program uses various data structures like:

• Doubly linked lists (for item management in categories)

• Stacks (to implement undo functionality)

• Queues (to simulate a checkout line)

💡 Features
👤 User Login (with basic email validation)

🧺 Category-based shopping (Clothes, Food, Cosmetics, Electronics, Books)

➕ Add items to cart

↩️ Undo last added item

👀 View current cart

💳 Checkout with Cash on Delivery or Bank Transfer

🧮 Total bill calculation

🪜 Uses Linked List, Stack, Queue, and Hash Map

🔍 Example Run
text
Copy
Edit
Login:
Enter username: ali123
Enter email: ali@example.com
Enter password: *****
Login successful!

*************** Menu ***************
1. Add item to cart
2. Undo last action
3. View cart
4. Checkout
5. Exit

Enter your choice: 1

Enter the category (Clothes, Food, Cosmetics, Electronics, Books): Food
Enter the item name: Apple
Enter the quantity: 5
Added 5 x Apple to your cart.
Do you want to add more items? (y/n): n

*************** Menu ***************
Enter your choice: 3

Cart in Food category:
- Apple | Price: Rs.15 | Quantity: 5

*************** Menu ***************
Enter your choice: 4

Checkout for ali123:
Do you want Cash on Delivery? (y/n): y
Enter your contact number: 0312xxxxxxx
Enter your delivery address: House #12, Karachi
ali123 has been added to the checkout queue.

Cart in Food category:
- Apple | Price: Rs.15 | Quantity: 5

Total amount: Rs. 75

*******************************Thank you for your purchase ali123**********************************
🧱 Data Structures Used

Structure	                      Purpose
Doubly Linked List              Store category items and quantities
unordered_map                   Fast lookup of items by name
stack                          	Undo last action in cart
queue                          	Checkout line simulation

#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

              // Node structure for a doubly linked list
 
 struct Node {
    string itemName;
    double price;
    int quantity;
    Node* prev;
    Node* next;

    Node(const string& name, double p, int qty = 0)
        : itemName(name), price(p), quantity(qty), prev(nullptr), next(nullptr) {}
};

             // CategoryList class to manage each category's linked list

class CategoryList {
private:
    Node* head;
    Node* tail;
    string category;
    unordered_map<string, Node*> itemMap;

public:
    CategoryList(const string& cat) : head(nullptr), tail(nullptr), category(cat) {}

    void addPredefinedItem(const string& itemName, double price) {
        Node* newNode = new Node(itemName, price, 0);
        itemMap[itemName] = newNode;
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
                                           // Function to display items

    void displayItems() const {
        cout << "\nItems in " << category << " category:\n";
        Node* current = head;
        while (current) {
            cout << "- " << current->itemName << " | Price: Rs." << current->price << "\n";
            current = current->next;
        }
    }
                           //  Function to view cart
						        
        void viewCart() const {
        cout << "\nCart in " << category << " category:\n";
        Node* current = head;
        bool hasItems = false;
        while (current) {
            if (current->quantity > 0) {
                cout << "- " << current->itemName << " | Price: Rs." << current->price
                     << " | Quantity: " << current->quantity << "\n";
                hasItems = true;
            }
            current = current->next;
        }
        if (!hasItems) {
            cout << "No items in this category.\n";
        }
    }

                       // function to check if items are avilable in the cart
                       
    bool addItemToCart(const string& itemName, int quantity) {
        if (itemMap.find(itemName) == itemMap.end()) {
            cout << "Item '" << itemName << "' not found in " << category << " category.\n";
            return false;
        }
        Node* item = itemMap[itemName];
        item->quantity += quantity;
        cout << "Added " << quantity << " x " << itemName << " to your cart.\n";
        return true;
    }

    bool removeItemFromCart(const string& itemName) {
        if (itemMap.find(itemName) == itemMap.end() || itemMap[itemName]->quantity == 0) {
            cout << "Item not found in your cart.\n";
            return false;
        }
        itemMap[itemName]->quantity = 0;
        cout << "Removed " << itemName << " from your cart.\n";
        return true;
    }
                      // function to calculate  total price
    double calculateTotal() const {
        double total = 0.0;
        Node* current = head;
        while (current) {
            total += current->price * current->quantity;
            current = current->next;
        }
        return total;
    }

    // Public getter to view the cart for each category
    Node* getHead() const {
        return head;
    }
};

// ShoppingCart class that manages the different category lists
class ShoppingCart {
private:
    CategoryList clothesList;
    CategoryList foodList;
    CategoryList cosmeticsList;
    CategoryList electronicsList;
    CategoryList booksList;
    stack<pair<string, string>> undoStack;  // Stack to track actions for undo
    queue<string> checkoutQueue;           // Queue to track customers
    bool itemsDisplayed;                   // Flag to track if items have been displayed

public:
    string username; // to store username entered during login
    string email;    // to store email ID entered during login
    string password; // to store password entered during login

    ShoppingCart() : clothesList("Clothes"), foodList("Food"), cosmeticsList("Cosmetics"), electronicsList("Electronics"), booksList("Books"), itemsDisplayed(false) {
        clothesList.addPredefinedItem("T-Shirt", 500);
        clothesList.addPredefinedItem("Jeans", 800);
        foodList.addPredefinedItem("Apple", 15);
        foodList.addPredefinedItem("Bread", 100);
        cosmeticsList.addPredefinedItem("Lipstick", 300);
        cosmeticsList.addPredefinedItem("Perfume", 1500);
        electronicsList.addPredefinedItem("Laptop", 30000);
        electronicsList.addPredefinedItem("Smartphone", 25000);
        booksList.addPredefinedItem("Book 1", 700);
        booksList.addPredefinedItem("Book 2", 260);
    }

    void displayAllItemsOnce() {
        if (!itemsDisplayed) {
            clothesList.displayItems();
            foodList.displayItems();
            cosmeticsList.displayItems();
            electronicsList.displayItems();
            booksList.displayItems();
            itemsDisplayed = true;
        }
    }

    void addItemToCart() {
        string category, itemName;
        int quantity;
        cout << "\nEnter the category (Clothes, Food, Cosmetics, Electronics, Books): ";
        cin >> category;
        cout << "Enter the item name: ";
        cin >> ws; // to handle whitespace before item name
        getline(cin, itemName);
        cout << "Enter the quantity: ";
        cin >> quantity;

        bool itemAdded = false;
        if (category == "Clothes") {
            itemAdded = clothesList.addItemToCart(itemName, quantity);
        } else if (category == "Food") {
            itemAdded = foodList.addItemToCart(itemName, quantity);
        } else if (category == "Cosmetics") {
            itemAdded = cosmeticsList.addItemToCart(itemName, quantity);
        } else if (category == "Electronics") {
            itemAdded = electronicsList.addItemToCart(itemName, quantity);
        } else if (category == "Books") {
            itemAdded = booksList.addItemToCart(itemName, quantity);
        } else {
            cout << "Invalid category.\n";
        }

        if (itemAdded) {
            undoStack.push({category, itemName});  // Push the action to the stack for undo functionality
        }

        // Ask if the user wants to add more items
        char addMore;
        cout << "Do you want to add more items? (y/n): ";
        cin >> addMore;
        if (addMore == 'y' || addMore == 'Y') {
            addItemToCart(); // Call the function recursively to add more items
        }
    }

    void undoLastAction() {
        if (undoStack.empty()) {
            cout << "No actions to undo.\n";
            return;
        }

        pair<string, string> lastAction = undoStack.top();
        undoStack.pop();
        string category = lastAction.first;
        string itemName = lastAction.second;

        if (category == "Clothes") {
            clothesList.removeItemFromCart(itemName);
        } else if (category == "Food") {
            foodList.removeItemFromCart(itemName);
        } else if (category == "Cosmetics") {
            cosmeticsList.removeItemFromCart(itemName);
        } else if (category == "Electronics") {
            electronicsList.removeItemFromCart(itemName);
        } else if (category == "Books") {
            booksList.removeItemFromCart(itemName);
        }

        cout << "Undid the last action: Removed " << itemName << " from the cart.\n";

        // After undo, update and display the cart items
        displayCartItems();
    }

    void checkout() {
        // Use the username already entered during login
        cout << "Checkout for " << username << ":\n";
        
        // Ask if user wants Cash on Delivery
        char cashOnDelivery;
        cout << "Do you want Cash on Delivery? (y/n): ";
        cin >> cashOnDelivery;

        string bankAccount;
        if (cashOnDelivery == 'n' || cashOnDelivery == 'N') {
            cout << "Enter your bank account details: ";
            cin >> ws; // to handle whitespace before input
            getline(cin, bankAccount);
        }

        // Ask for the user's contact number and delivery address
        string contactNumber, address;
        cout << "Enter your contact number: ";
        cin >> ws; // to handle leading whitespace
        getline(cin, contactNumber);
        cout << "Enter your delivery address: ";
        getline(cin, address);
        
        // Process checkout queue
        checkoutQueue.push(username);
        cout << username << " has been added to the checkout queue.\n";
        
        // Display cart and calculate total
        clothesList.viewCart();
        foodList.viewCart();
        cosmeticsList.viewCart();
        electronicsList.viewCart();
        booksList.viewCart();
        
        double total = clothesList.calculateTotal() + foodList.calculateTotal() + cosmeticsList.calculateTotal() +
                       electronicsList.calculateTotal() + booksList.calculateTotal();
        cout << "Total amount: Rs. " << total << "\n";
        cout<<endl;
        cout << "      *******************************Thank you for your purchase   "<< username<<"********************************** "<< "!\n";
    }

    void displayCartItems() const {
        clothesList.viewCart();
        foodList.viewCart();
        cosmeticsList.viewCart();
        electronicsList.viewCart();
        booksList.viewCart();
    }

    // Function to handle user login

void userLogin() {
    cout << "Login:\n\n";
    cout << "Enter username: ";
    cin >> username;

    bool validEmail = false;
    do {
        cout << "Enter email: ";
        cin >> email;

        // Check if the email contains an "@" symbol
        if (email.find('@') != string::npos) {
            validEmail = true;
        } else {
            cout << "Invalid email address. Please enter a valid email address.\n";
        }
    } while (!validEmail);

    cout << "Enter password: ";
    cin >> password;
    cout << "Login successful!\n";
}

};

int main() {
    ShoppingCart cart;
    cout<<endl;
     cout << "                            *********************************************" << endl;
    cout << "                                                 WELCOME            " << endl;
    cout << endl;
    cout << "                                                  TO THE                 " << endl;
    cout << endl;
    cout << "                                              ONLINE SHOPPING              " << endl;
    cout << endl;
    cout << "                                                CART SYSTEM            " << endl;
    cout <<  endl;
    cout << endl;
    cout << "                              **********************************************" << endl;

    cout<<endl;
    cout<< "login to the shopping cart"<<endl;
    cart.userLogin();
     cout << "Access granted!" << endl;
    cout<<endl;
    cout<<"                **************** Available categories in the shopping cart system ****************           "<<endl;

    // Display categories, items, and prices once after login
    cart.displayAllItemsOnce();
    
    

    while (true) {
        int choice;
        cout << "\n                                  *************** Menu ***************\n";
        cout << "1. Add item to cart\n";
        cout << "2. Undo last action\n";
        cout << "3. View cart\n";
        cout << "4. Checkout\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cart.addItemToCart();
                break;
            case 2:
                cart.undoLastAction();
                break;
            case 3:
                cart.displayCartItems();
                break;
            case 4:
                cart.checkout();
                return 0;  // End the program after checkout
            case 5:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

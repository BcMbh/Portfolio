#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <functional>

using namespace std;

//Structure for menu
struct MenuItem {
    int id;
    char name[50];
    double price;
};

struct Node {
    MenuItem item;
    int quantity;
    Node* next;
};

class Customer {
private:
    Node* cart;

public:
    Customer() : cart(nullptr) {}

    void addToCart(const MenuItem& menuItem, int quantity) {
        Node* newNode = new Node;
        newNode->item = menuItem;
        newNode->quantity = quantity;
        newNode->next = cart;
        cart = newNode;

        cout << "Item \"" << menuItem.name << "\" added to your cart successfully.\n";
    }

    void editCartItem(const char itemName[], int& newQuantity) {
        Node* current = cart;

        // Convert user input to lowercase for case-insensitive comparison
        string userInput = itemName;
        transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);

        while (current != nullptr) {
            // Convert cart item name to lowercase for case-insensitive comparison
            string cartItemName = current->item.name;
            transform(cartItemName.begin(), cartItemName.end(), cartItemName.begin(), ::tolower);

            if (cartItemName == userInput) {
                cout << "Enter new quantity for item " << current->item.name << ": ";
                cin >> newQuantity;
                current->quantity = newQuantity;
                cout << "Quantity for item " << current->item.name << " updated successfully.\n";
                return;
            }
            current = current->next;
        }

        cout << "Item " << itemName << " not found in your cart.\n";
    }

    void deleteCartItem(const char itemName[]) {
    Node* current = cart;
    Node* prev = nullptr;

    // Convert user input to lowercase and remove spaces
    string userInput = itemName;
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
    userInput.erase(remove_if(userInput.begin(), userInput.end(), ::isspace), userInput.end());

    while (current != nullptr) {
        // Convert cart item name to lowercase and remove spaces
        string cartItemName = current->item.name;
        transform(cartItemName.begin(), cartItemName.end(), cartItemName.begin(), ::tolower);
        cartItemName.erase(remove_if(cartItemName.begin(), cartItemName.end(), ::isspace), cartItemName.end());

        if (cartItemName == userInput) {
            if (prev == nullptr) {
                cart = current->next;
            } else {
                prev->next = current->next;
            }

            delete current;
            cout << "Item '" << itemName << "' deleted from your cart successfully.\n";
            return;
        }

        prev = current;
        current = current->next;
    }

    cout << "Item '" << itemName << "' not found in your cart.\n";
    }


    void displayCart() const {
    if (isEmptyCart()) {
        cout << "Your cart is empty.\n";
    } else {
        Node* current = cart;
        double overallTotal = 0.0;

        cout << "Items in your cart:\n";
        cout << "------------------------------------------\n";

        while (current != nullptr) {
            double itemTotal = current->item.price * current->quantity;
            overallTotal += itemTotal;

            cout << setw(20) << left << current->item.name
                << " x " << current->quantity
                << " - $" << fixed << setprecision(2) << itemTotal << "\n";

            current = current->next;
        }

        cout << "------------------------------------------\n";
        cout <<  left << "Total(RM) including delivery fee" << " - RM" << fixed << setprecision(2) << overallTotal+5 << "\n";
        cout << "------------------------------------------\n";
    }
    }


    double calculateTotal() const {
        Node* current = cart;
        double total = 0;

        while (current != nullptr) {
            total += current->item.price * current->quantity;
            current = current->next;
        }

        // Add delivery fee
        total += 5.0;

        return total;
    }

    bool isEmptyCart() const {
        return cart == nullptr;
    }

    void sortCartByName() {
        if (!cart || !cart->next){
            cout<<"No item in cart to sort.."<<endl;
            return;
        } //No sort if no item in cart

        Node* current;
        Node* index;
        MenuItem tempItem;
        int tempQuantity;

        for (current = cart; current != nullptr; current = current->next) {
            for (index = current->next; index != nullptr; index = index->next) {
                if (strcmp(current->item.name, index->item.name) > 0) {
                    tempItem = current->item;
                    tempQuantity = current->quantity;

                    current->item = index->item;
                    current->quantity = index->quantity;

                    index->item = tempItem;
                    index->quantity = tempQuantity;
                }
            }
        }
        cout << "Cart sorted by item name successfully.\n";
    }

    ~Customer() {
        while (cart != nullptr) {
            Node* temp = cart;
            cart = cart->next;
            delete temp;
        }
    }
};

//only cout outline
void printMenu() {
    cout << "------------------------------------------\n";
    cout << "\t****Deli Res Menu****\n";
    cout << "------------------------------------------\n";
    cout << left << setw(28) << "Item:" << "\tPrice(RM):\n";
    cout << "------------------------------------------\n";
}

//this only the menu item
void displayMenu(const MenuItem menu[], int menuSize) {
    for (int i = 0; i < menuSize; i++) {
        cout << left << menu[i].id << ". " << setw(25) << menu[i].name << "\t$" << menu[i].price << "\n";
    }
    cout << "------------------------------------------\n";
    cout << "*Delivery Fee RM5 will be included when checkout.\n\n";
}

int main() {
    //this is the default menu item
    MenuItem menu[] = {{1, "Burger", 6.69}, {2, "Pizza", 12.69}, {3, "Salad", 4.69}, {4, "Shawarma", 10.69}, {5, "Maggie Goreng", 5.69}, {6, "Nasi Lemak", 4.69},
    {7, "Milo", 2.69}, {8, "Nescafe", 3.69}, {9, "Teh Tarik", 1.69}, {10, "Limau Ais", 0.69}};
    const int menuSize = sizeof(menu) / sizeof(menu[0]);

    Customer customer;

    int choice;
    char itemName[50];
    double itemPrice;
    int quantity;
    bool itemFound = false;
    string userInput;
    double total = 0;

    do {
        printMenu();
        displayMenu(menu, menuSize);

        cout << "Menu Options:\n";
        cout << "1. Search Item in Menu\n";
        cout << "2. Add Item to Cart\n";
        cout << "3. Edit Item in Cart\n";
        cout << "4. Delete Item from Cart\n";
        cout << "5. Display Cart\n";
        cout << "6. Sort Cart by Item Name\n";
        cout << "7. Checkout (Immediate) \n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Search Item in Menu
                cout << "Enter item name to search in the menu: ";
                cin.ignore();
                cin.getline(itemName, sizeof(itemName));

                // Convert the item names and user input to lowercase and remove spaces
                userInput = itemName;
                transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
                userInput.erase(remove_if(userInput.begin(), userInput.end(), ::isspace), userInput.end());

                itemFound = false;
                for (int i = 0; i < menuSize; ++i) {
                    // Convert the menu item names to lowercase and remove spaces
                    string menuItemName = menu[i].name;
                    transform(menuItemName.begin(), menuItemName.end(), menuItemName.begin(), ::tolower);
                    menuItemName.erase(remove_if(menuItemName.begin(), menuItemName.end(), ::isspace), menuItemName.end());

                    if (menuItemName == userInput) {
                        cout << "Item found in the menu: " << menu[i].name << " - $" << menu[i].price << "\n";
                        itemFound = true;

                        int addToCartChoice;
                        cout << "Do you want to add this item to your cart? (Enter 1 for Yes, enter 2 for No): ";
                        cin >> addToCartChoice;

                        if (addToCartChoice == 1) {
                            MenuItem newItem = menu[i];
                            cout << "Enter quantity: ";
                            cin >> quantity;
                            customer.addToCart(newItem, quantity);
                        } else if (addToCartChoice == 2) {
                            cout << "Item not added to your cart.\n";
                        } else {
                            cout << "Invalid choice. Item not added to your cart.\n";
                        }

                        break;
                    }
                }

                if (!itemFound) {
                    cout << "Item '"<<userInput<<"' not found in the menu.\n";
                }
                break;

            case 2:
                // Add Item to Cart
                int selectedId;
                cout << "Enter item ID to add to your cart: ";
                cin >> selectedId;

                itemFound = false;
                for (int i = 0; i < menuSize; ++i) {
                    if (menu[i].id == selectedId) {
                        itemFound = true;
                        MenuItem newItem = menu[i];
                        cout << "Enter quantity: ";
                        cin >> quantity;

                        customer.addToCart(newItem, quantity);
                        break;
                    }
                }

                if (!itemFound) {
                    cout << "Item not found in the menu.\n";
                }
                break;

            case 3:
                // Edit Item in Cart
                cout << "Enter item name in your cart to edit: ";
                cin.ignore();
                cin.getline(itemName, sizeof(itemName));

                int newQuantity;
                customer.editCartItem(itemName, newQuantity);
                break;

            case 4:
                // Delete Item from Cart
                cout << "Enter item name in your cart to delete: ";
                cin.ignore();
                cin.getline(itemName, sizeof(itemName));

                customer.deleteCartItem(itemName);
                break;

            case 5:
                // Display Cart
                customer.displayCart();
                break;

            case 6:
                // Sort Cart by Item Name
                customer.sortCartByName();
                break;

            case 7:
                // Checkout
                if (customer.isEmptyCart()) {
                    cout << "Fail to checkout. Your cart is empty.\n";
                } else {
                    cout << "Enter your address for delivery: ";
                    cin.ignore();
                    string userAddress;
                    getline(cin, userAddress);

                    cout << "Checking out...\n";
                    total = customer.calculateTotal();
                    cout << "Total amount: $" << total << "\n";
                    cout << "Thank you for your order! Our rider will deliver to: " << userAddress << "\n";
                    choice = 0;
                }
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

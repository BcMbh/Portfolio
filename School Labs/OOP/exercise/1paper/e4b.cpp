#include <iostream>
using namespace std;

class House {
    protected:
        int id;
        float price;
    public:
        void set() {
            id = 111;
            price = 355000;
        }
        virtual void display() { // (i) Declare a virtual function display()
            cout << "House Record:" << endl;
            cout << "House ID : " << id << endl;
            cout << "Price : RM " << price << endl;
        }
};

class Bungalow : public House {
    private:
        string name = "Elegant";
        float tax = 0.12, total;
    public:
        void calculate() {
            total = price + (tax * price);
        }
        void display() override { // Override the virtual function display()
            cout << "Bungalow Record:" << endl;
            cout << "House name : " << name << endl;
            cout << "House ID : " << id << endl;
            cout << "Price : RM " << price << endl;
            cout << "Total : RM " << total << endl;
        }
};

int main() {
    House *h; // (ii) Declare a pointer object called h for class House
    h = new House; // (iii) Use the pointer object h to assign by a new dynamic object of House class
    Bungalow *b; // (iv) Declare a pointer object called b for class Bungalow
    b = new Bungalow; // (v) Use the pointer object h to assign by a new dynamic object of Bungalow class
    b->set(); // (vi) Use an arrow pointer to call function set() by b object
    b->calculate(); // (vii) Use an arrow pointer to call function calculate() by b object
    h = b; // (viii) Write a code to assign object b to object h
    h->display(); // (ix) Use an arrow pointer to call function display() by h object
    b->display(); // (x) Use an arrow pointer to call function display() by b object

    // Clean up
    delete h; // This is safe because h points to a Bungalow object due to polymorphism
    return 0;
}

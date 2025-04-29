#include<iostream>
using namespace std;

class Cake {
private:
    string type;
    float quantity;
public:
    void Purchase(string t, float q) {
        type = t;
        quantity = q;
    }
    string getType() {
        return type;
    }
    int getQuantity() { 
        return quantity;
    }
};

int main() {
    Cake *ck;
    int noCake, i;
    int qty; 
    string cakeType; 
    
    cout << "Enter how many types of cake: ";
    cin >> noCake;
    
    ck = new Cake[noCake]; 
    
    for (i = 0; i < noCake; i++) {
        cout << "\nEnter type of cake <fondant, sponge, meringue>: ";
        cin >> cakeType;
        cout << "Enter quantity: ";
        cin >> qty;
        ck[i].Purchase(cakeType, qty); 
    }
    
    cout << "\nYou have purchased: " << endl;
    for (i = 0; i < noCake; i++) {
        cout << ck[i].getQuantity() << " of " << ck[i].getType() << " cake(s)" << endl; // Q2b(iii) Display quantity and type
    }
    
    return 0;
}

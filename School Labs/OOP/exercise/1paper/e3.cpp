#include <iostream>
#include <iomanip>
using namespace std;

class fruit {
    private:
        string name;
        float weight, price, payment;

    public:
        static int count;

        fruit() {
            cout << "Welcome to the Fruit Record System" << endl;
        }

        ~fruit() {
            cout << "Thank you" << endl;
        }

        fruit(const fruit &f) {
            count++;
            cout << "Record " << count<<endl;
            weight = f.weight;
            price = f.price;
            payment = f.payment;
        }

        void get_data() {
            cout << "Enter fruit name: ";   cin >> name;
            cout << "Enter fruit weight: "; cin >> weight;
            cout << "Enter fruit price: ";  cin >> price;
        }

        void calculate() {
            payment = weight * price;
        }

        void display() {
            cout << "Fruit Name: " << name << endl;
            cout << "Total Payment: RM" << fixed << setprecision(2) << payment << endl;
        }

        friend void summary(fruit f);
};

int fruit::count = 0;

void summary(fruit f) {
    f.get_data();
    f.calculate();
    f.display();
}

class organic_fruit : public fruit {
    public:
        friend void summary(fruit f);
};

int main() {
    fruit f;
    int i = 0;
    do {
        summary(f);
        i++;
    } while (i < 2);

    return 0;
}

#include <iostream>
#include <iomanip>
using namespace std;

class Calculate {
private:
    int total;
    float price_per_cm;
public:
    Calculate(int ttl) : total(ttl), price_per_cm(2.00) {} // Constructor

    void Display() {
        cout << "Perimeter (cm) : " << total << endl;
        cout << "Ribbon price per cm (RM) : " << fixed << setprecision(2) << price_per_cm << endl;
        cout << "Total ribbon price (RM) : " << fixed << setprecision(2) << total * price_per_cm << endl;
    }
};

class Trapezium {
private:
    int perimeter;
public:
    // Default constructor
    Trapezium() : perimeter(0) {}

    // Parameterized constructor
    Trapezium(int p) : perimeter(p) {}

    void SetPerimeter() {
        cout << "Enter trapezium perimeter: ";
        cin >> perimeter;
    }

    // Overloaded operator+ to add perimeters of two Trapezium objects
    Trapezium operator+(const Trapezium& other) const {
        return Trapezium(perimeter + other.perimeter); // Return new Trapezium with summed perimeter
    }

    int getPerimeter() const {
        return perimeter; // Return the perimeter of the current object
    }
};

int main() {
    Trapezium A, B;

    A.SetPerimeter();
    B.SetPerimeter();

    Trapezium sumTrapezium = A + B;
    
    // Create a Calculate object named C with the perimeter of sumTrapezium
    Calculate C(sumTrapezium.getPerimeter());

    C.Display();

    return 0;
}

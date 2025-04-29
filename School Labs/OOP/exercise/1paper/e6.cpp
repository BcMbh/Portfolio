#include<iostream>
using namespace std;

class TempConvert {
private:
    float celsius, fahrenheit;

public:
    TempConvert(){ 
        cout << " Celsius = " << celsius << " Fahrenheit = " << fahrenheit << endl;
    }

    void Input() {
        cout << "\nEnter temperature in Celsius: ";
        cin >> celsius;
    }

    friend float convert(TempConvert&); // Declare convert as a friend function

    void Display(float tempF) {
        cout << celsius << " Celsius = " << tempF << " Fahrenheit." << endl;
    }

    ~TempConvert() {
        cout << "End of conversion." << endl;
    }
};

float convert(TempConvert& temp) { // Define convert as an external friend function
    temp.fahrenheit = temp.celsius * 1.8 + 32;
    return temp.fahrenheit;
}

int main() {
    TempConvert temp; 
    float tempF;
    temp.Input();
    tempF = convert(temp); // Call the friend function convert
    temp.Display(tempF);
    return 0;
}

#include <iostream>
using namespace std;

class Photograph {
private:
    int request;
    float sale;

public:
    float Payment();

    void setSale(float Sal) { 
        sale = Sal; 
    }

    void setRequest(int Req) { 
        request = Req; 
    }

    float getSale() const { 
        return sale; 
    }

    int getRequest() const { 
        return request; 
    }
};

float Photograph::Payment() {
    return sale * request;
}

int main() {
    Photograph Convo;
    Convo.setSale(58.72);
    Convo.setRequest(5);
    cout << "The special sale given is " << Convo.getSale() << endl; // Accessing sale through a getter method
    cout << "The total payment is: " << Convo.Payment() << endl;
    return 0;
}

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

float kineticEnergy(float, float);

int main()
{
    float energy,mass,velocity;

    cout<<"Enter an object's mass and velocity as required....\n"<<endl;
    cout<<"Mass in kilograms: "<<mass<<endl;
    cout<<"Mass in kilograms: "<<velocity<<endl;

    energy = kineticEnergy(mass, velocity);
  
    cout << "The kinetic energy of this object is: \n";
    cout << fixed << setprecision(2) << energy;
    cout << "joules\n";
}

float kineticEnergy(float m, float v){
    float ke;

    ke=(1/2) * m * pow(v,2);

    return ke;    
}
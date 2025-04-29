#include <iostream>
#include <iomanip>

using namespace std;

int main() 
{
    char *ptr = "Data Structure and Algorithm";
    cout << *ptr;
    ptr += 5;
    cout << *ptr;
    cout << *(ptr + 14) << endl;

}
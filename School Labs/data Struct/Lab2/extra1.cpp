#include <iostream>
#include <iomanip>

using namespace std;

int main() 
{
    int arr[5] = {1,2,3,4,5}, a, b, *ptr;
    ptr = arr;
    a = *ptr + 10;
    ptr += 2;
    b = *ptr - 5;
    cout << *ptr << "\n" << a << "\n" << b << endl;
}
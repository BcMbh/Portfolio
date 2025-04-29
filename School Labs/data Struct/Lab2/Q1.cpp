#include <iostream>
#include <iomanip>

using namespace std;

struct employee {
    string name;
    float salary;
};

int main() {
    int n_employee;
    cout << "Enter number of employees: ";
    cin >> n_employee;

    employee* e = new employee[n_employee];

    for (int i = 0; i < n_employee; i++) {
        cout << "Enter Name: ";
        cin >> e[i].name;
        cout << "Enter Salary: ";
        cin >> e[i].salary;
    }

}

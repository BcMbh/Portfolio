#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

class Guard_House {
protected:
    string id;
    float hour, salary, net_salary, bonus, payment;

public:
    Guard_House() {
        cout << "Welcome to Guard House Salary System" << endl;
        id = "Invalid";
    }
    ~Guard_House() {
        cout << "Thank you" << endl;
    }

    virtual void set_Data(string ID, float extra_hour = 0) {
        id = ID;
        hour = extra_hour;
    }

    string getid() { return id; }
    float getbonus() { return bonus; }
    float getpayment() { return payment; }
    float getnetsalary() { return net_salary; }

    void display() {
        cout << "ID: " << id << endl;
        cout << "Bonus: RM" << bonus << endl;
        cout << "Payment: RM" << payment << endl;
        cout << "Net Salary: RM" << net_salary << endl;
    }
};

class normal_Hour : public Guard_House {
private:
    float salary = 1200;

public:
    void set_Data(string ID) {
        id = ID;
    }
    void cal_net_salary() {
        bonus = salary * 1.2;
        net_salary = salary + bonus;
    }
};

class shift_Hour : public Guard_House {
protected:
    float salary = 850;

public:
    void set_Data(string ID, float extra_hour) {
        id = ID;
        hour = extra_hour;
    }
    void cal_net_salary() {
        bonus = salary * 1.2;
        payment = hour * 55;
        net_salary = salary + bonus + payment;
    }
};

class contract : public shift_Hour {
public:
    void repeat() {
        shift_Hour::set_Data(id, hour);
        shift_Hour::cal_net_salary();
    }
};

int main() {
    string ID, type;
    float extra_Hour;

    for (int i = 0; i < 3; i++) {
        cout << "Enter your ID: ";   
        cin >> ID;
        cout << "Type of working (Normal or Shift or Contract): ";   
        cin >> type;

        if (type == "Normal") {
            normal_Hour nh;
            nh.set_Data(ID);
            nh.cal_net_salary();
            cout << "ID: " << nh.getid() << endl;
            cout << "Bonus: RM" << nh.getbonus() << endl;
            cout << "Net Salary: RM" << nh.getnetsalary() << endl;
        } else if (type == "Shift") {
            cout << "Enter extra hours worked: ";
            cin >> extra_Hour;
            shift_Hour sh;
            sh.set_Data(ID, extra_Hour);
            sh.cal_net_salary();
            sh.display();
        } else if (type == "Contract") {
            cout << "Enter extra hours worked: ";
            cin >> extra_Hour;
            contract c;
            c.set_Data(ID, extra_Hour);
            c.repeat();
            c.display();
        } else {
            cout << "Invalid type of working." << endl;
        }
    }

    return 0;
}

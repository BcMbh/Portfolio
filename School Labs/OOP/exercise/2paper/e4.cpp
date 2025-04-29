#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int SIZE = 5; 

class Shoes {
protected:
    string type;
    string material;

public:
    void setShoes(string t, string m) {
        type = t;
        material = m;
    }
    virtual void setSales() = 0; 
};

class DesignerShoes : public Shoes {
private:
    string name;
    string month[SIZE];
    float sales[SIZE];
    float total;

public:
    DesignerShoes(string n, string t, string m) {
        name = n;
        setShoes(t, m);
        string months[SIZE] = {"Jan", "Feb", "Mar", "Apr", "May"};
        for (int i = 0; i < SIZE; ++i) {
            month[i] = months[i];
        }
        total = 0;
    }

    void setSales() override {
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "       Sales Data Entry for " << name << " " << type << " wear shoes" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

        for (int i = 0; i < SIZE; ++i) {
            cout << "Enter month " << month[i] << " sales: ";cin >> sales[i];
            total += sales[i];
        }
        cout << endl;
    }

    void display() const {
        cout << setw(20) << left << name << setw(12) << left << type
             << setw(12) << left << material << setw(18) << right << fixed << setprecision(2) << total
             << setw(14) << right << fixed << setprecision(2) << total / SIZE << endl;
    }

    friend float Average(DesignerShoes& ds);
};

float Average(DesignerShoes& ds) {
    return ds.total / SIZE;
}

int main() {
    DesignerShoes* p = new DesignerShoes("Bedazzled-Stone101", "Evening", "Synthetic");
    p->setSales();
    DesignerShoes* q = new DesignerShoes("Summer", "Casual", "Cotton");
    q->setSales();
    DesignerShoes* r = new DesignerShoes("BeautifulDay", "Casual", "Leather");
    r->setSales();

    cout << "-------------------------------------------------------------------------" << endl;
    cout << "                           Summary Report" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << setw(20) << left << "Name" << setw(12) << left << "Type" << setw(12) << left << "Material"
         << setw(18) << right << "Total Sales(RM)" << setw(14) << right << "Average(RM)" << endl;
    cout << setw(20) << left << "----" << setw(12) << left << "----" << setw(12) << left << "-------"
         << setw(18) << right << "--------------" << setw(14) << right << "----------" << endl;

    p->display();
    q->display();
    r->display();

    delete p;
    delete q;
    delete r;

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

struct Person{
    char name[50];
    int flavor;
};

class ADTqueue{
private:
    Person queue[10];
    int head, tail;
public:
    ADTqueue(){
        tail = -1;
        head = 0;
    }

    bool empty(){
        return head == tail + 1;
    }

    bool full(){
        return tail == 9;
    }

    void append(Person p) {
        if (!full()){
            tail++;
            queue[tail] = p;
        }else{
            cout << "Queue is Full" << endl;
        }
    }

    Person serve(){
        if (!empty()){
            Person p = queue[head];
            head++;
            return p;
        }else{
            cout << "Queue is Empty" << endl;
            return {};
        }
    }
};

void analyzeFlavor(int flavor){
    switch(flavor){
        case 1:
            cout << "Sensitive and often daydreaming about past and future." << endl;
            break;
        case 2:
            cout << "Friendly, easygoing and has many friends." << endl;
            break;
        case 3:
            cout << "Affectionate, giving, loving and very understanding." << endl;
            break;
        case 4:
            cout << "Negotiator and will do anything to avoid open conflict." << endl;
            break;
        default:
            cout << "Input Error." << endl;
    }
}


int main() 
{
    Person p;
    ADTqueue q;

    cout<<"Do you know that the flavor of ice cream can reveal one's personality?"<<endl;
    
    for (int i = 0; i < 2; i++)
    {
        cout<<"Enter Name: ";
        cin>>p.name;
        cout<<"Enter favourite flavour:\n (1=chocolate 2=vanilla 3=strawberry 4=mixed flavor)"<<endl;
        cin>>p.flavor;

        q.append(p);

    }
    
    while (!q.empty()) {
        Person served = q.serve();
        cout<<served.name<<"   ";
        analyzeFlavor(served.flavor);
    }

}
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    string name;
    char flavour, again;
    int quantity;
    float price, itemPrice, total;

    cout<<"Welcome to IceCream\n";
    cout<<"IceCream Flavour\n";
    cout<<"[C] Chocolate\n";
    cout<<"[V] vanilla\n";
    cout<<"[S] straberry\n";

    cout<<"enter Name:\n";
    cin>>name;
    do
    {
        cout<<"enetr flavour:\n";
        cin>> flavour;

        while (flavour != 'C'&& flavour != 'V'&& flavour != 'S')
        {
            cout<<"Incorrect flavour,Please re-enter flavour:"<<endl;
            cin>>flavour;
        }

        cout<<"eneter quantity\t:";
        cin>>quantity;

        switch (flavour)
        {
        case 'C':
            price=3.50;
            break;
        case 'V':
            price =3;
            break;
        case 'S':
            price=2.5;
            break;
        }

        itemPrice=price*quantity;
        total=itemPrice;

        cout<<"Do you want more?"<<endl;
        cin>> again;
        cout<<endl;
        
    } while (again=='Y'|| again=='y');
    
cout<<"**************Reciept****************"<<endl;
cout<<"Name\t:"<<endl;
cout<<"toatal Price\t: RM"<<total<<fixed<<setprecision(2)<<endl;

}
#include <iostream>
#include<iomanip>
using namespace std;

class strawberry{
    private:
    string selection;
    double price;
    public:
    void displayMenu()
    {
        cout<<"[1]Strawberry & Nutellla Crepe\tPrice\tRm10.00"<<endl;
        cout<<"[2]Strawberry & Chocolate Crepe\tPrice\tRm12.00"<<endl;
        cout<<"[3]Strawberry Waffle with Custard\tPrice\tRm13.00"<<endl;
        cout<<"[4]Strawberry Smoothie\tPrice\tRm10.00"<<endl;
        cout<<"[5]Strawberry & Country Cream\tPrice\tRm13.00"<<endl;

    }
    void purchase(){
        int s;
        cout<<"\n Enter your choice based on the number"<<endl;
        cin>>s;
        if(s==1){
            selection ="Strawberry & Nutella Crepe";
            price = 10;
        } else if(s==2){
            selection ="Strawberry & Chocolate Crepe";
            price = 12;
        }else if(s==3){
            selection =" Strawberry Waffle with Custard ";
            price = 13.4;
        }else if(s==4){
            selection =" Strawberry Smoothie";
            price = 10;
        }else if(s==5){
            selection ="Strawberry & Country Cream";
            price = 13;
        }else
            selection = "Not available";
            price = 0;
        
    }
    double getPrice(){return price;}
    string getSelection(){return selection;}
};

class Customer
{
    private:
    string strawSelect, name;
    double payment;
    strawberry st;

    public:
    void setData()
    {
        cout<<"+++++++++++++++++++++++++"<<endl;
        cout<<"Tuity fruity. Strawberry"<<endl;
        cout<<"+++++++++++++++++++++++++"<<endl;

        cout<<"Enter name\t:"<<endl;
        getline(cin,name);
        getOrder();

    }

    void getOrder()
    {
        st.displayMenu();
        st.purchase();
        payment=st.getPrice();
        strawSelect=st.getSelection();
    }

    void displayDetails()
    {
        cout<<"+++++++++++++++++++++++++"<<endl;
        cout<<name<<"Your Purchase Details"<<endl;
        cout<<"+++++++++++++++++++++++++"<<endl;
        cout<<"Slection\t\t:"<<strawSelect<<endl;
        cout<<"payment to be made\t:RM"<<fixed<<setprecision(2)<<payment<<endl;
    }
};

int main()
{
    Customer c;
    c.setData();
    c.displayDetails();
    return 0;
}
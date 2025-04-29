#include <iostream>
#include <limits>
using namespace std;
//initialize constant global variable
const int ITEM=3;
 
class BeanBag
{
    //private data members
    string name; int stock[ITEM];
    public:
        void latest_BeanBagstock()
        {
            //display header
            cout<<"---------------------"<<endl;
            cout<<"#Current# Ready stocks Checking..."<<endl;
            cout<<"---------------------"<<endl;
            //display code name
            cout<<"Code Tracing\t"<<name<<"<<"<<endl;
            //loop to display elements of array in reversed order
            for(int i=0;i<ITEM;i++)
            {
                cout<<"Group "<<i+1<<"production:\t"<<stock[ITEM-(i+1)]<<"item(s) ready"<<endl;
            }
        }
        //function to print details and initialize stock values
        void beanBag_Details(int* bb)//pointer variable as argument
        {
            //print header
            cout<<"##############################"<<endl;
            cout<<"Stock Checking"<<endl;
            cout<<"-----------------------------"<<endl;
            //get user input for name
            cout<<"Enter Bean Bag Chair Code:"<<endl;
            getline(cin,name);
            //loop to initilize array with pointer argument
            for(int i=0;i<ITEM;i++)
            {
                stock[i]= bb[i];
            }
        }
}ready;//declare global object

void stockUpdate()
{
    int *arr;

    cout<<"-----------------------------"<<endl;
    cout<<"Stocks ready for the month"<<endl;
    cout<<"-----------------------------"<<endl;

    arr=new int[ITEM];
    for(int i=0;i<ITEM;i++)
    {
        cout<<"Ready stock from group "<<ITEM-i<<":";
        cin>>*(arr+i);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    //update values to global object
    ready.beanBag_Details(arr);
    //display updated details
    ready.latest_BeanBagstock();
    delete [] arr;
}

int main() {
    BeanBag BBag;
    int val[ITEM]={9,7,5};

    cout<<"Cosy Bean Bag Chair Sdn Bhd."<<endl;
    //initialize value
    BBag.beanBag_Details(val);
    //display stock
    BBag.latest_BeanBagstock();
    //user update stock
    stockUpdate();
    
    return 0;
}
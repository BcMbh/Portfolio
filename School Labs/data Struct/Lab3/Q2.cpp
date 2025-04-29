#include <iostream>
#include <iomanip>
#include <stack>

using namespace std;

int main() 
{
    stack<int> st;
    int num,even,odd;

    cout<<"Key in ten numbers: ";
    while (st.size()<10)
    {
        cin>>num;
        st.push(num);
    }

    cout<<"Numbers entered are: ";
    while (!st.empty())
    {
        cout<< st.top()<<" ";
        if (st.top()%2==0)
           even=st.top();
        else
            odd=st.top();
        
        st.pop();
    }
    cout<<"\nThere are "<<even<<" even numbers and "<<odd<<" odd numbers";
    
    

}
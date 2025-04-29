#include <iostream>
#include <iomanip>
#include <stack>

using namespace std;

int main() 
{
    stack<string> st;
    string chars;

    cout<<"Key in five characters: ";
    while (st.size()<5)
    {
        cin>>chars;
        st.push(chars);
    }

    cout<<"The reverse order is: ";
    while (!st.empty())
    {
        cout<< st.top()<<" ";
        st.pop();
    }
    
    

}
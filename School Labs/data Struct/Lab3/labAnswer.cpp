#include<iostream>
using namespace std;

class ADTstack
{
    private:
    char stack[10];
    int topstack;

    public:
    ADTstack()
    {
        topstack = -1;
    }
    int empty()
    {
        if(topstack==-1)
        return 1;
        else
        return 0;
    }
    int full()
    {
        if(topstack>=5)
        return 1;
        else
        return 0;
    }
    void push(char a)
    {
        if (!full())
        {
            topstack++;
            stack[topstack] = a;
        }
        else
        {
            cout<<"Stack is Full"<<endl;
        }
    }
    char pop()
    {
        char a;
        if(!empty())
        {
            a = stack[topstack];
            topstack--;
            return a;
        }
        else
        {
            cout<<"Stack is Empty"<<endl;
            return '\0'; 
        }
    }
};
int main()
{
    ADTstack st;
    char chars;

    cout<<"Key in five characters: ";
    for (int i = 0; i < 5; i++) 
    {
        cin>>chars;
        st.push(chars);
    }

    cout<<"The reverse order is: ";
    while (!st.empty())
    {
        cout<< st.pop()<<" ";
    }
}
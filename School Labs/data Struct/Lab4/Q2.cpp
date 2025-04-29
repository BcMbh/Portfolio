#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

int x,y,z;

class Queue
{
    private:
    int queue[10];
    int head,tail;

    public:
    Queue()
    {
        tail = -1;
        head = 0;
    }

    int empty(){
        if(head == tail+1)
        return 1;
        else
        return 0;
    }

    int full(){
        if(tail == 10)
        return 1;
        else
        return 0;
    }

    void append(int num)
    {
        if (!full()){
            tail++;
            queue[tail] = num;
        }else {
            cout<<"Queue is Full"<<endl;
        }
    }

    int serve(){
        int num;
        if(!empty()){
            num = queue[head];
            head++;
            return num;
        }else{
            cout<<"Queue is Empty"<<endl;
            return 0;
        }
    }
};



int main() 
{
    Queue q;
    x = 2;
    y = 4;
    z = 6;
    q.append (8);
    q.append(x-y);
    q.append(z);
    y += q.serve();
    q.append(x+z);
    z = q.serve () - 4;
    q.append(z);
    q.append (3);
    x -= q.serve();
    q.append(x);
    cout<<"Elements in the queue are :";
    while(!q.empty())
    {
        cout<<q.serve()<<endl;
    }
}
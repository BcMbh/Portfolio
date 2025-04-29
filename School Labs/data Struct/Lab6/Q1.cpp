#include <iostream>
#include <iomanip>

using namespace std;

struct node
{
    int data;
    node *next;

};

class ADTqueue
{
private:
    node *front, *rear;
public:
    ADTqueue(){
        front=rear=NULL;
    }

    void append(int num){
        node *newNode = new node;
        newNode->data = num;
        newNode->next = NULL;
        if (rear == NULL)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void traverse(){
        node *temp;
        temp= front;
        while (temp!=NULL)
        {
            cout<<temp->data<<" ";
            temp=temp->next;
        }  
    }

    int empty(){
        if (front==NULL)
            return 1;
        else
            return 0;
    }

    int serve(){
        if (!empty())
        {
            node *temp;
            temp=front;
            int num;
            num=front->data;
            front = front->next;
            delete temp;
            if(front==NULL)
                 rear=NULL;
                return num;
        }else{
            cout<<"Queue is empty\n";
            exit(1);
        }
        
    }
}q;


int main() 
{
    int numData,num,sum;
    ADTqueue();

    cout<<"How many intigers to append into queue?";
    cin>>numData;

    for (int i = 0; i < numData; i++)
    {
        cout<<"Enter intiger "<<i+1<<" to append into queue: ";
        cin>>num;
        q.append(num);
    }
    cout<<"\n Integers that are append into the queue\n";
    q.traverse();

    cout<<"\nThe sum are: \n";
    while (!q.empty())
    {
        sum=sum+q.serve();
        cout<<sum<<endl;
        return 0;
    }
    
    
}
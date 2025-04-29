#include <iostream>
using namespace std;

struct node {
    int data;
    node* next;
};

int main() {
    node* head = new node;
    node* temp = head;
    int num;

    cout << "Enter Data 1: ";
    cin >> head->data;
    head->next = nullptr;

    for (int i = 2; i < 6; i++) {
        cout << "Enter Data " << i << " : ";
        cin >> num;
        temp->next = new node;
        temp = temp->next;
        temp->data = num;
        temp->next = nullptr;
        
    }

    temp = head;
    head = head->next;
    temp->next = NULL;
    delete temp;


    if (head!=NULL && head->next!=NULL)
    {
        temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        
        node *lastNode=temp->next;
        temp->next = NULL;
        delete lastNode; 
        
    }
    
    temp = head;
    cout << "Element after deleting the first node: ";
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << "\nData to search: ";
    cin >> num;
    temp = head;
    while (temp != NULL) {
        if (temp->data == num) {
            cout << "Data found";
            break;
        }
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Data not found";
    }

    return 0;
}
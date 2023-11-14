#include <iostream>
#include <fstream>
#include <cstdlib> 

using namespace std;


struct Node 
{
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};


Node* insertAtFront(Node* head, int value) 
{
    Node* newNode = new Node(value);
    newNode->next = head;
    return newNode;
}


void displayList(Node* head) 
{
    Node* current = head;
    while (current != nullptr) 
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}


Node* mergeSort(Node* head);

Node* merge(Node* left, Node* right);

int main() 
{
    
    
    srand(static_cast<unsigned>(time(0)));

    ofstream outputFile("random_numbers.txt");
    if (!outputFile) 
    {
        cout << "Error creating the file." << endl;
        return 1;
    }

    for (int i = 0; i < 21; i++) 
    {
        int randomNumber = rand() % 501 - 250;
        outputFile << randomNumber << " ";
    }

    outputFile.close();

   


    ifstream inputFile("random_numbers.txt");
    if (!inputFile) 
    {
        cout << "Error opening the file." << endl;
        return 1;
    }

    

    Node* head = nullptr;
    int value;
    for (int i = 0; i < 21; ++i) 
    {
        inputFile >> value;
        head = insertAtFront(head, value);
    }

   
    cout << "List before sorting: ";
    displayList(head);

   
    head = mergeSort(head);

    
    cout << "List after sorting: ";
    displayList(head);

    
    Node* current = head;
    while (current != nullptr) 
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}

Node* mergeSort(Node* head) 
{
    if (head == nullptr || head->next == nullptr) {
        return head;
    }


    Node* slow = head;
    Node* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) 
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* left = head;
    Node* right = slow->next;
    slow->next = nullptr;


    left = mergeSort(left);
    right = mergeSort(right);


    return merge(left, right);
}



Node* merge(Node* left, Node* right) 
{
    Node* result = nullptr;

    if (left == nullptr) 
    {
        return right;
    }
    if (right == nullptr) 
    {
        return left;
    }

    if (left->data <= right->data) 
    {
        result = left;
        result->next = merge(left->next, right);
    }
    else
    {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}
#include <iostream>
using namespace std;

class Node
{
public:
    int nodevalue; // Integer value stored in the node
    Node* next;    // Pointer to the next node in the linked list
    Node* prev;    // Pointer to the previous node in the linked list
};

// Function to swap two integer values
void swap(int* x, int* y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

// Function to find the last node in a linked list
Node* lastNode(Node* root)
{
    // Traverse the linked list until the last node is reached
    while (root && root->next)
        root = root->next;
    return root;
}

// Function to partition the linked list around a pivot element
Node* partition(Node* l, Node* h)
{
    // Select the pivot element as the value of the last node
    int x = h->nodevalue;

    // Initialize a pointer 'i' to the previous node of the low pointer
    Node* i = l->prev;

    // Iterate through the linked list from 'l' to 'h'
    for (Node* j = l; j != h; j = j->next)
    {
        // If the current node's value is less than or equal to the pivot
        if (j->nodevalue <= x)
        {
            // Move 'i' to the next node
            i = (i == NULL) ? l : i->next;

            // Swap the values of 'i' and 'j'
            swap(&(i->nodevalue), &(j->nodevalue));
        }
    }
    // Move 'i' to the next node and swap its value with the pivot value
    i = (i == NULL) ? l : i->next;
    swap(&(i->nodevalue), &(h->nodevalue));
    return i;
}

// Function to recursively sort the linked list using quicksort algorithm
void sort(Node* l, Node* h)
{
    // Base case: if 'h' is not NULL and 'l' is not equal to 'h' and 'l' is not the next of 'h'
    if (h != NULL && l != h && l != h->next)
    {
        // Partition the linked list around the pivot and get the pivot node
        Node* p = partition(l, h);

        // Recursively sort the elements before and after the pivot
        sort(l, p->prev);
        sort(p->next, h);
    }
}

// Function to initiate quicksort on the linked list
void quickSort(Node* head)
{
    // Find the last node of the linked list
    Node* h = lastNode(head);

    // Sort the linked list using quicksort algorithm
    sort(head, h);
}

// Function to print the elements of the linked list
void printList(Node* head)
{
    // Traverse the linked list and print each node's value
    while (head)
    {
        cout << head->nodevalue << " ";
        head = head->next;
    }
    cout << endl;
}

// Function to insert a new node at the beginning of the linked list
void Insert(Node** head_ref, int new_nodevalue)
{
    // Allocate memory for a new node
    Node* new_node = new Node;

    // Set the value of the new node
    new_node->nodevalue = new_nodevalue;

    // Set the previous pointer of the new node to NULL
    new_node->prev = NULL;

    // Set the next pointer of the new node to the current head of the linked list
    new_node->next = (*head_ref);

    // If the linked list is not empty, set the previous pointer of the current head to the new node
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;

    // Update the head of the linked list to point to the new node
    (*head_ref) = new_node;
}

int main()
{
    Node* a = NULL;

    // Insert elements into the linked list
    Insert(&a, 50);
    Insert(&a, 1001);
    Insert(&a, 290);
    Insert(&a, 23891);
    Insert(&a, 4492);
    Insert(&a, 4221);
    Insert(&a, 3423);
    Insert(&a, 939);
    Insert(&a, 8658);
    Insert(&a, 1212);
    Insert(&a, 198);

    cout << "Unsorted \n";
    printList(a);

    // Sort the linked list using quicksort algorithm
    quickSort(a);

    cout << "Sorted \n";
    printList(a);

    return 0;
}

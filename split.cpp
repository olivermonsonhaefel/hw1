/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */
void tempIterator(Node*& t);

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE
      // Take the first item of the list, add it to either odds or evens, the call the list again without the first item
    if(in == nullptr) {
      return;
    }
    if(in->value % 2 == 0) {
      if(evens == nullptr) {
        evens = new Node(in->value, nullptr);
      }
      else {
        Node* temp = evens;
        /*
        while(temp->next != nullptr) {
          temp = temp->next;
        }
        */
        tempIterator(temp);
        temp->next = new Node(in->value, nullptr);
      }
    }
    else {
      if(odds == nullptr) {
        odds = new Node(in->value, nullptr);
      }
      else {
        Node* temp = odds;
        /*
        while(temp->next != nullptr) {
          temp = temp->next;
        }
        */
        tempIterator(temp);
        temp->next = new Node(in->value, nullptr);
      }
    }
    Node* temp2 = in;
    in = in->next;
    delete temp2;
    split(in, odds, evens);
}

/* If you needed a helper function, write it here */
void tempIterator(Node*& t) {
  if(t->next != nullptr) {
    t = t->next;
    tempIterator(t);
  }
}
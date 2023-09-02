#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
    clear();
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
    Node* newNode = new Node(ndata);
    Node* last = walk(head_, length_);
    last->next = newNode;
    newNode->next = head_;
    length_++;
}


/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 * 
 */
void Chain::swap(int i, int j)
{
    //pointers for i
    Node* node1 = walk(head_, i);
    Node* node1Back = walk(node1, 1);
    Node* node1Front = walk(head_, i-1);

    //pointers for j
    Node* node2 = walk(head_, j);
    Node* node2Back = walk(node2, 1);
    Node* node2Front = walk(head_, j-1);

    if (node2Back != node1 || node1Back != node2) {
        //put node2 between node1Front and node1Back
        node1Front->next = node2;
        node2->next = node1Back;

        //put node1 between node2Front and node2Back
        node2Front->next = node1;
        node1->next = node2Back;

    }

    if (node1Back == node2) {
        node1Front->next = node2;

        node2->next = node1;

        node1->next = node2Back;
    } 

    if (node2Back == node1) {
        node2Front->next = node1;

        node1->next = node2;

        node2->next = node1Back;
    }

}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
    if (!head_) return;

    if (!head_->next) return;

    for (int i = length_; i > length_ / 2; i--) {
        
        swap(length_-i + 1, i);
    }

}

/*
* Modifies the current chain by "rotating" every k nodes by one position.
* In every k node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/
void Chain::rotate(int k)
{    
    if (k == 1 || k > length_) return;

    for (int i = k; i > 1; i--) {
         for (int j = 0; j < length_ / k; j++) {
             swap(i + k * j, 1 + k * j);
         }
    }
}

/**
 * Destroys ALL dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
    Node *curr = head_;
    Node *next;

    for (int i = 0; i <= length_; i++) {
        
        next = curr->next;
        delete curr;
        curr = next;

    }
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
    width_ = other.width_;
    height_ = other.height_;

    head_ = new Node();
    head_->next = head_;

    Node* current_cursor = head_;
    Node* other_cursor = other.head_->next;

    while (other_cursor != other.head_) {
        Node* new_node = new Node(other_cursor->data);
        current_cursor->next = new_node;
        current_cursor = current_cursor->next;
        other_cursor = other_cursor->next;
    }

    current_cursor->next = head_;

    length_ = other.length_;

}

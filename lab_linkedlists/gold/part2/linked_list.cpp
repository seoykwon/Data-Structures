// linked_list.cc -- functions for linked_list lab (cs221)

#include "linked_list.h"

#define ITERATIVE 0

/**
 * Inserts a new Node (with key=newKey) at the head of the linked_list.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 * PRE: newKey is the value for the key in the new Node
 * POST: the new Node is now the head of the linked_list
 */
void insert(Node *&head, int newKey)
{
  head = new Node(newKey, head);
}

/**
 * Print the keys of a linked_list in order, from head to tail
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 */
void print(Node *head)
{
  std::cout << "[";
  for (Node *curr = head; curr != NULL; curr = curr->next)
  {
    std::cout << curr->key;
    if (curr->next != NULL)
      std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

/**
 * Returns the size (number of Nodes) of the linked_list
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 */
int size(Node *head)
{
  if (!head)
    return 0;
  return 1 + size(head->next);
}

/**
 * Copies the keys in a linked list to a vector.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 * POST: a new vector<int> containing the keys in the correct order has been returned.
 */
std::vector<int> to_vector(Node *head)
{
  std::vector<int> result;
  for (Node *curr = head; curr != NULL; curr = curr->next)
  {
    result.push_back(curr->key);
  }
  return result;
}

/**
 * Delete the last Node in the linked_list
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty)
 * POST: the last Node of the linked_list has been removed
 * POST: if the linked_list is now empty, head has been changed
 * POST: else head remains the first Node in the linked_list
 */
void delete_last_element(Node *&head)
{
  // ******** WRITE YOUR CODE HERE ********
  if (!head)
    return;
#if ITERATIVE
  // iterative solution
  Node *second_last = NULL;
  Node *last = head;

  while (last->next)
  {
    second_last = last;
    last = last->next;
  }

  if (second_last)
    second_last->next = NULL;
  else
    head = NULL;
  delete last;
#else
  // recursive solution
  if (!head->next)
  {
    delete head;
    head = NULL;
  }
  else
  {
    delete_last_element(head->next);
  }
#endif
}

/**
 * Removes an existing Node (with key=oldKey) from the linked_list.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 * PRE: oldKey is the value of the key in the Node to be removed
 * PRE: if no Node with key=oldKey exists, the linked_list has not changed
 * POST: if a Node with key=oldKey was found, then it was deleted
 * POST: other Nodes with key=oldKey might still be in the linked_list
 * POST: head is the new first Node of the linked_list, if updated
 */
void remove(Node *&head, int oldKey)
{
  // ******** WRITE YOUR CODE HERE ********
  if (!head)
    return;
#if ITERATIVE
  // iterative solution
  Node *prev = NULL;
  Node *curr = head;

  while (curr && curr->key != oldKey)
  {
    prev = curr;
    curr = curr->next;
  }

  if (curr) // oldKey found in list
  {
    if (prev) { // curr is not head
      prev->next = curr->next;
    } else {
      head = head->next;
    }

    delete curr;
  }
#else
  // recursive solution
  if (head->key == oldKey)
  {
    Node *temp = head;
    head = head->next;
    delete temp;
  }
  else
  {
    remove(head->next, oldKey);
  }
#endif
}

/**
 * Insert a new Node (with key=newKey) after an existing Node (with key=oldKey)
 * If there is no existing Node with key=oldKey, then no action.
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty)
 * PRE: oldKey is the value to look for (in the key of an existing Node)
 * PRE: newKey is the value of the key in the new Node (that might be inserted)
 * POST: if no Node with key=oldKey was found, then the linked_list has not changed
 * POST: else a new Node (with key=newKey) is right after the Node with key = oldKey.
 */
void insert_after(Node *head, int oldKey, int newKey)
{
  // ******** WRITE YOUR CODE HERE ********
  if (!head)
    return;
#if ITERATIVE
  // iterative solution
  Node* curr = head;

  while (curr && curr->key != oldKey) {
    curr = curr->next;
  }

  if (curr) {
    curr->next = new Node(newKey, curr->next);
  }
#else
  // recursive solution
  if (head->key == oldKey)
  {
    head->next = new Node(newKey, head->next);
  }
  else
  {
    insert_after(head->next, oldKey, newKey);
  }
#endif
}

/**
 * Create a new linked_list by merging two existing linked_lists.
 * PRE: list1 is the first Node in a linked_list (if NULL, then it is empty)
 * PRE: list2 is the first Node in another linked_list (if NULL, then it is empty)
 * POST: A new linked_list is returned that contains new Nodes with the keys from
 * the Nodes in list1 and list2, starting with the key of the first Node of list1,
 * then the key of the first Node of list2, etc.
 * When one list is exhausted, the remaining keys come from the other list.
 * For example: [1, 2] and [3, 4, 5] would return [1, 3, 2, 4, 5]
 */
Node *interleave(Node *list1, Node *list2)
{
  // ******** WRITE YOUR CODE HERE ********
  if (!list1 && !list2)
    return NULL;

  // swap lists so that list1 is always not NULL
  if (!list1)
  {
    list1 = list2;
    list2 = NULL;
  }
#if ITERATIVE
  // iterative solution
  Node* head = NULL;
  Node* tail = NULL;

  while (list1) {
    Node* curr = new Node(*list1);

    if (!head) {
      head = curr;
    } else {
      tail->next = curr;
    }

    tail = curr;

    if (list2) { // swap to interleave
      Node* tmp = list1->next;
      list1 = list2;
      list2 = tmp;
    } else {
      list1 = list1->next;
    }
  }
#else
  // recursive solution
  Node *head = new Node(*list1);
  head->next = interleave(list2, list1->next);
#endif
  return head;
}

#pragma once

/// @brief Node structure for LinkedList 
typedef struct LinkedListNode {
    struct LinkedListNode* prev;
    struct LinkedListNode* next;
    int node_content;
} LinkedListNode;

/// @brief LinkedList master structure
typedef struct LinkedList {
    LinkedListNode* head;
    LinkedListNode* tail;
    int len;
} LinkedList;

/// @brief Creates a new instance of the LinkedList structure
/// @return empty LinkedList 
LinkedList linkedlist_new();

/// @brief Frees the entire LinkedList from memory
/// @param[inout] l 
void linkedlist_free(LinkedList* l);

/// @brief Checks and returns the stored length value from the LinkedList
/// @param l 
/// @return LinkedList length
int linkedlist_len(const LinkedList* l); 

/// @brief Pushes a new node to the end of the LinkedList 
/// @param[inout] l 
/// @param value 
void linkedlist_pushtail(LinkedList* l, int value);

/// @brief Pushes a new node to the beginning of the LinkedList
/// @param[inout] l 
/// @param value 
void linkedlist_pushhead(LinkedList* l, int value);

/// @brief Inserts a new node after an existing node within the LinkedList
/// @param[inout] l 
/// @param[inout] n 
/// @param value 
void linkedlist_insertafter(LinkedList* l, LinkedListNode* n, int value);    

/// @brief Inserts a new node before an existing node within the LinkedList
/// @param[inout] l 
/// @param[inout] n 
/// @param value 
void linkedlist_insertbefore(LinkedList* l, LinkedListNode* n, int value);

/// @brief Finds a node at a specified index within the LinkedList
/// @param l 
/// @param idx 
/// @return NULL if node does not exist; Node if existant 
LinkedListNode* linkedlist_findnodeat(LinkedList* l, int idx);
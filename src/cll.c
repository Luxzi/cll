#include "cll.h"
#include <stdio.h>
#include <stdlib.h>

/// @brief Creates a new instance of the LinkedList structure
/// @return empty LinkedList 
LinkedList linkedlist_new() {
  return (LinkedList) {.head = NULL, .tail = NULL, .len = 0};
}

/// @brief Frees the entire LinkedList from memory
/// @param[inout] l 
void linkedlist_free(LinkedList* l) {
    LinkedListNode* cursor = l->head;

    while (cursor != NULL) {
        LinkedListNode* tmp = cursor;
        cursor = cursor->next;
        free(tmp);
    }

    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
};

/// @brief Checks and returns the stored length value from the LinkedList
/// @param l 
/// @return LinkedList length
int linkedlist_len(const LinkedList* l) {
    return l->len;
};

/// @brief Pushes a new node to the end of the LinkedList 
/// @param[inout] l 
/// @param value 
void linkedlist_pushtail(LinkedList* l, int value) {
        LinkedListNode* n = malloc(sizeof(LinkedListNode));
        n->prev = NULL;
        n->next = NULL;
        n->node_content = value;
        l->len += 1;

        if (l->tail == NULL) {
            l->head = n;
            l->tail = l->head;
            return;
        }

        l->tail->next = n;
        n->prev = l->tail;
        l->tail = n;
        return;
};

/// @brief Pushes a new node to the beginning of the LinkedList
/// @param[inout] l 
/// @param value 
void linkedlist_pushhead(LinkedList* l, int value) {
        LinkedListNode* n = malloc(sizeof(LinkedListNode));
        n->prev = NULL;
        n->next = NULL;
        n->node_content = value;
        l->len += 1;

        if (l->head == NULL) {
            l->head = n;
            l->tail = l->head;
            return;
        }

        n->next = l->head;
        l->head->prev = n;
        l->head = n;
        return;
};

/// @brief Inserts a new node after an existing node within the LinkedList
/// @param[inout] l 
/// @param[inout] n 
/// @param value 
void linkedlist_insertafter(LinkedList* l, LinkedListNode* n, int value) {    
    if (n->next == NULL) {
        linkedlist_pushtail(l, value);
    }

    LinkedListNode* insert = malloc(sizeof(LinkedListNode));
    insert->prev = n;
    insert->next = n->next;
    insert->node_content = value;
    n->next->prev = insert;
    n->next = insert;
    l->len += 1;
}

/// @brief Inserts a new node before an existing node within the LinkedList
/// @param[inout] l 
/// @param[inout] n 
/// @param value 
void linkedlist_insertbefore(LinkedList* l, LinkedListNode* n, int value) {
    if (n->prev == NULL) {
        linkedlist_pushhead(l, value);
    }

    linkedlist_insertafter(l, n->prev, value);
}

/// @brief Finds a node at a specified index within the LinkedList
/// @param l 
/// @param idx 
/// @return NULL if node does not exist; Node if existant 
LinkedListNode* linkedlist_findnodeat(LinkedList* l, int idx) {
    if (idx > l->len) {
        return NULL;
    }

    LinkedListNode* cursor = l->head;
    int localidx = idx;

    while (cursor != NULL && localidx != 0) {
        cursor = cursor->next;
        localidx -= 1;
    }

    return cursor;
}
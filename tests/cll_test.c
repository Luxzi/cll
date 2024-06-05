#include <cll.h>
#include <unity.h>
#include <time.h>
#include <Windows.h>
#include "log.h"

void setUp(void) {};
void tearDown(void) {};

void populateList(void) {
    LinkedList testlist = linkedlist_new();

    for (int i = 0; i < 10; i++) {
        linkedlist_pushtail(&testlist, i);
    }   

    int i = 0;
    for (LinkedListNode* current = testlist.head; current != NULL; current = current->next, i++) {
        TEST_ASSERT(current->node_content == i);
    }

    log_debug("PUSH_TAIL: Populated linked list from tail with %d node(s)", testlist.len);
    TEST_ASSERT(i == 10);    
    linkedlist_free(&testlist);

    for (int i = 9; i >= 0; i--) {
        linkedlist_pushhead(&testlist, i);
    }   

    i = 0;
    for (LinkedListNode* current = testlist.head; current != NULL; current = current->next, i++) {
        TEST_ASSERT(current->node_content == i);
    }

    TEST_ASSERT(i == 10);    
    log_debug("PUSH_HEAD: Populated linked list from head with %d node(s)", testlist.len);
    linkedlist_free(&testlist);
}

void validateLength(void) {
    LinkedList testlist = linkedlist_new();

    for (int i = 0; i < 10; i++) {
        linkedlist_pushtail(&testlist, i);
    }   

    int i = 0;
    for (LinkedListNode* current = testlist.head; current != NULL; current = current->next, i++);

    log_debug("Linked list length recalculated: (NEW) %d (OLD) %d", i, testlist.len);
    TEST_ASSERT(i == testlist.len);
    linkedlist_free(&testlist);
}

void insertBefore(void) {
    LinkedList testlist = linkedlist_new();
    
    for (int i = 0; i < 10; i++) {
        linkedlist_pushtail(&testlist, i);
    }  

    int insertpoint = (testlist.len / 2);
    LinkedListNode* basenode = linkedlist_findnodeat(&testlist, insertpoint);
    linkedlist_insertbefore(&testlist, basenode, INT_MAX);
    LinkedListNode* newnode =  linkedlist_findnodeat(&testlist, insertpoint);

    log_debug("Appended new node before index %d", insertpoint);
    TEST_ASSERT(newnode->node_content == INT_MAX);
    TEST_ASSERT(newnode->next != NULL);
    linkedlist_free(&testlist);
}

void insertAfter(void) {
    LinkedList testlist = linkedlist_new();
    
    for (int i = 0; i < 10; i++) {
        linkedlist_pushtail(&testlist, i);
    }  

    int insertpoint = (testlist.len / 2);
    LinkedListNode* basenode = linkedlist_findnodeat(&testlist, insertpoint);
    linkedlist_insertafter(&testlist, basenode, INT_MAX);

    log_debug("Appended new node after index %d", insertpoint);
    LinkedListNode* newnode = linkedlist_findnodeat(&testlist, insertpoint+1);

    TEST_ASSERT(newnode->node_content == INT_MAX);
    TEST_ASSERT(newnode->prev != NULL);
    linkedlist_free(&testlist);
}

void findNodeAt(void) {
    LinkedList testlist = linkedlist_new();

    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            linkedlist_pushtail(&testlist, INT_MAX);
            continue;
        }

        linkedlist_pushtail(&testlist, i);
    }   

    log_debug("Set node 5 to INT_MAX");
    TEST_ASSERT(linkedlist_findnodeat(&testlist, 5)->node_content == INT_MAX);
    linkedlist_free(&testlist);
}

double get_time() {
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (double)t.QuadPart/(double)f.QuadPart;
}

void benchmarkList(void) {
    int nodes = 1 << 10;

    double begin = get_time();

    LinkedList testlist = linkedlist_new();
    
    for (int i = 0; i < nodes; i++) {
        linkedlist_pushtail(&testlist, i);
    }  

    LinkedListNode* cursor = testlist.head;
    int local_len = 0;
    while (cursor != NULL && local_len != testlist.len) {
        cursor = cursor->next;
        local_len += 1;
    }

    TEST_ASSERT(local_len == testlist.len);

    double end = get_time();

    log_debug("Added %d node(s) to linked list in %f second(s)", nodes, (end-begin)*1000);
    TEST_ASSERT(testlist.len == nodes);
    linkedlist_free(&testlist);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(populateList);
    RUN_TEST(validateLength);
    RUN_TEST(insertBefore);
    RUN_TEST(insertAfter);
    RUN_TEST(findNodeAt);
    RUN_TEST(benchmarkList);
    return UNITY_END();
}
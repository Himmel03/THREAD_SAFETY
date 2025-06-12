#pragma once

#include <windows.h>  // CRITICAL_SECTION 정의
#include <stdbool.h>  // C에서 bool 사용을 위한 헤더

typedef int Key;
typedef char* Value;

typedef struct {
    Key key;
    Value value;
    int value_size;
} Item;

typedef struct node_t {
    Item item;
    struct node_t* next;
} Node;

typedef struct {
    bool success;
    Item item;
} Reply;

typedef struct {
    Node* head;
    Node* tail;
    CRITICAL_SECTION lock; // Windows thread-safe
} Queue;

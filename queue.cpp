#include <windows.h>
#include <cstring>
#include "queue.h"
#include "qtype.h"

static Value deepcopy(Value value, int size) {
    Value new_val = new char[size];
    memcpy(new_val, value, size);
    return new_val;
}

Node* nalloc(Item item) {
    Node* node = new Node;
    node->item.key = item.key;
    node->item.value_size = item.value_size;
    node->item.value = deepcopy(item.value, item.value_size);
    node->next = nullptr;
    return node;
}

void nfree(Node* node) {
    if (node) {
        delete[] node->item.value;
        delete node;
    }
}

Node* nclone(Node* node) {
    if (!node) return nullptr;
    return nalloc(node->item);
}

Node* nalloc(Item item) {
    Node* node = new Node;
    node->item.key = item.key;
    node->item.value_size = item.value_size;
    node->item.value = deepcopy(item.value, item.value_size);
    node->next = nullptr;
    return node;
}

void nfree(Node* node) {
    if (node) {
        delete[] node->item.value;
        delete node;
    }
}

Node* nclone(Node* node) {
    if (!node) return nullptr;
    return nalloc(node->item);
}


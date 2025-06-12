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

Queue* init(void) {
    Queue* q = new Queue;
    q->head = q->tail = nullptr;
    InitializeCriticalSection(&q->lock);
    return q;
}

void release(Queue* queue) {
    EnterCriticalSection(&queue->lock);
    Node* cur = queue->head;
    while (cur) {
        Node* next = cur->next;
        nfree(cur);
        cur = next;
    }
    LeaveCriticalSection(&queue->lock);
    DeleteCriticalSection(&queue->lock);
    delete queue;
}

Reply enqueue(Queue* queue, Item item) {
    Reply reply = { false, {} };
    EnterCriticalSection(&queue->lock);

    Node* prev = nullptr;
    Node* cur = queue->head;

    while (cur) {
        if (cur->item.key == item.key) {
            // 기존 노드의 value를 새로운 value로 깊은 복사하여 교체
            delete[] cur->item.value;
            cur->item.value = deepcopy(item.value, item.value_size);
            cur->item.value_size = item.value_size;

            reply.success = true;
            reply.item = cur->item;
            LeaveCriticalSection(&queue->lock);
            return reply;
        }
        if (cur->item.key > item.key) {
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    Node* new_node = nalloc(item);

    if (!prev) {
        new_node->next = queue->head;
        queue->head = new_node;
        if (!queue->tail) queue->tail = new_node;
    }
    else {
        new_node->next = prev->next;
        prev->next = new_node;
        if (!new_node->next) queue->tail = new_node;
    }

    reply.success = true;
    reply.item = new_node->item;
    LeaveCriticalSection(&queue->lock);
    return reply;
}

Reply dequeue(Queue* queue) {
    Reply reply = { false, {} };

    EnterCriticalSection(&queue->lock);

    if (!queue->head) {
        LeaveCriticalSection(&queue->lock);
        return reply;
    }

    Node* node = queue->head;
    queue->head = node->next;
    if (!queue->head) queue->tail = nullptr;

    reply.success = true;
    reply.item.key = node->item.key;
    reply.item.value_size = node->item.value_size;
    reply.item.value = deepcopy(node->item.value, node->item.value_size);

    nfree(node);
    LeaveCriticalSection(&queue->lock);
    return reply;
}

Queue* range(Queue* queue, Key start, Key end) {
    Queue* new_q = init();
    EnterCriticalSection(&queue->lock);

    Node* cur = queue->head;
    while (cur) {
        if (cur->item.key >= start && cur->item.key <= end) {
            Item cloned = {
                .key = cur->item.key,
                .value = deepcopy(cur->item.value, cur->item.value_size),
                .value_size = cur->item.value_size
            };
            enqueue(new_q, cloned);
        }
        cur = cur->next;
    }

    LeaveCriticalSection(&queue->lock);
    return new_q;
}


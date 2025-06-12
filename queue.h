#pragma once

#include "qtype.h"

// 큐 초기화 및 해제
Queue* init(void);
void release(Queue* queue);

// 노드 관련 함수
Node* nalloc(Item item);
void nfree(Node* node);
Node* nclone(Node* node);

// 큐 연산 함수
Reply enqueue(Queue* queue, Item item);
Reply dequeue(Queue* queue);
Queue* range(Queue* queue, Key start, Key end);

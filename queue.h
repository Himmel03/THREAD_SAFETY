#pragma once

#include "qtype.h"

#ifdef __cplusplus
extern "C" {
#endif

	// ť �ʱ�ȭ �� ����
	Queue* init(void);
	void release(Queue* queue);

	// ��� ���� �Լ�
	Node* nalloc(Item item);
	void nfree(Node* node);
	Node* nclone(Node* node);

	// ť ���� �Լ�
	Reply enqueue(Queue* queue, Item item);
	Reply dequeue(Queue* queue);
	Queue* range(Queue* queue, Key start, Key end);

#ifdef __cplusplus
}
#endif

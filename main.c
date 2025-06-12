#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "qtype.h"

Item create_item(Key key, const char* str) {
    Item item;
    item.key = key;
    item.value_size = (int)strlen(str) + 1;
    item.value = (char*)malloc(item.value_size);
    memcpy(item.value, str, item.value_size);
    return item;
}

void free_item(Item item) {
    free(item.value);
}

int main() {
    Queue* q = init();

    Item a = create_item(10, "banana");
    Item b = create_item(20, "apple");

    enqueue(q, a);
    enqueue(q, b);

    free_item(a);
    free_item(b);

    Reply r = dequeue(q);
    if (r.success) {
        printf("Dequeued: key = %d, value = %s\n", r.item.key, r.item.value);
        free(r.item.value);
    }

    release(q);
    return 0;
}

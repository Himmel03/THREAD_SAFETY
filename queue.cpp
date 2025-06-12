#include <windows.h>
#include <cstring>
#include "queue.h"
#include "qtype.h"

static Value deepcopy(Value value, int size) {
    Value new_val = new char[size];
    memcpy(new_val, value, size);
    return new_val;
}

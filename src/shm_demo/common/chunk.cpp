#include "../include/chunk.hpp"

#include <cstddef>
#include <cstring>

bool make_chunk(const char *str, chunk &out) {
    const size_t len = strlen(str);

    if (len >= PAYLOAD_SIZE) return false;

    strcpy(reinterpret_cast<char*>(out.data), str);
    out.size = len;
    return true;
}

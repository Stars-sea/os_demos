#pragma once

#include <cstddef>
#include <cstdint>

constexpr size_t PAYLOAD_SIZE = 256;

/**
 * 内容分块
 */
struct chunk {
    uint8_t size;
    uint8_t data[PAYLOAD_SIZE];
};

bool make_chunk(const char* str, chunk& out);

#pragma once

#include "shared_mem.hpp"
#include <cstddef>
#include <string>
#include <atomic>
#include <sys/types.h>

struct chunk;

/**
 * SPSC 共享内存环形缓冲区
 */
class shared_buffer {
private:
    struct header {
        static_assert(std::atomic<int>::is_always_lock_free,
                      "std::atomic<int> must be lock-free for cross-process use");
        std::atomic<int> in;
        std::atomic<int> out;
    };

    shared_mem _mem;

    int _capacity;

    const header* chead() const;
    header* head();
    chunk* at(int id);

    static size_t calc_size(int capacity);

public:
    shared_buffer(std::string name, bool own, int capacity);

    const std::string& name() const;
    bool is_own() const;

    bool empty() const;
    int length() const;
    int capacity() const;

    bool read(chunk& out);
    bool write(const chunk& in);
};

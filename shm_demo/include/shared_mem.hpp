#pragma once

#include <string>

/**
 * 封装共享内存，使用 RAII 保证内存安全
 */
class shared_mem {
private:
    std::string _name;
    int fd = -1;
    size_t _size;
    bool _own;
    char* _data = nullptr;

public:
    shared_mem(const shared_mem&) = delete;
    shared_mem& operator=(const shared_mem&) = delete;

    shared_mem(std::string name, bool own, size_t size);

    ~shared_mem();

    const std::string& name() const;

    size_t size() const;

    bool is_own() const;

    char* data();
    const char* cdata() const;
};

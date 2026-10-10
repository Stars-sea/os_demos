#include "../include/shared_mem.hpp"

#include <cerrno>
#include <cstddef>
#include <fcntl.h>
#include <system_error>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>


shared_mem::shared_mem(
    std::string name,
    bool own,
    size_t size
) : _name(std::move(name)), _size(size), _own(own) {
    auto fail = [&](int e) -> void {
        if (fd >= 0) close(fd);
        if (_own) shm_unlink(_name.c_str());
        throw std::system_error{e, std::generic_category()};
    };

    int oflag = _own ? (O_CREAT | O_RDWR | O_EXCL) : O_RDWR;
    fd = shm_open(_name.c_str(), oflag, 0666);
    if (fd < 0) throw std::system_error{errno, std::generic_category()};

    struct stat st{};
    if (fstat(fd, &st) < 0) fail(errno);

    if (_own) {
        if (ftruncate(fd, size) < 0) fail(errno);
        _size = size;
    } else {
        _size = static_cast<size_t>(st.st_size);
    }

    _data = reinterpret_cast<char*>(
        mmap(nullptr, _size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0));
    if (_data == MAP_FAILED) fail(errno);
}

shared_mem::~shared_mem() {
    if (_data != nullptr) {
        munmap(_data, _size);
        _data = nullptr;
    }

    if (fd >= 0) close(fd);
    if (_own)
        shm_unlink(_name.c_str());
}

const std::string& shared_mem::name() const { return _name; }

size_t shared_mem::size() const { return _size; }

bool shared_mem::is_own() const { return _own; }

char* shared_mem::data() { return _data; }

const char* shared_mem::cdata() const { return _data; }

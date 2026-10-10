#include "../include/shared_buffer.hpp"
#include "../include/chunk.hpp"

size_t shared_buffer::calc_size(int capacity) {
    if (capacity <= 0) throw std::exception{};
    return sizeof(header) + static_cast<size_t>(capacity) * sizeof(chunk);
}

shared_buffer::shared_buffer(
    std::string name,
    bool own,
    int capacity
) : _mem(std::move(name), own, calc_size(capacity)), _capacity(capacity) {
    if (own) {
        new (_mem.data()) header{};
    }
}

const std::string& shared_buffer::name() const { return _mem.name(); }

bool shared_buffer::is_own() const { return _mem.is_own(); }

bool shared_buffer::empty() const {
    const header* h = chead();
    int i = h->in.load(std::memory_order_acquire);
    int o = h->out.load(std::memory_order_acquire);
    return i == o;
}

int shared_buffer::length() const {
    const header* h = chead();
    int i = h->in.load(std::memory_order_acquire);
    int o = h->out.load(std::memory_order_acquire);

    if (o == i) return 0;
    if (o < i) return i - o;
    return _capacity - o + i;
}

int shared_buffer::capacity() const { return _capacity; }

bool shared_buffer::read(chunk &out) {
    header* h = head();
    int o = h->out.load(std::memory_order_relaxed);
    if (o == h->in.load(std::memory_order_acquire)) return false;
    out = *at(o);
    h->out.store((o + 1) % _capacity, std::memory_order_release);
    return true;
}

bool shared_buffer::write(const chunk &in) {
    header* h = head();
    int i = h->in.load(std::memory_order_relaxed);
    int next = (i + 1) % _capacity;
    if (next == h->out.load(std::memory_order_acquire)) return false;
    *at(i) = in;
    h->in.store(next, std::memory_order_release);
    return true;
}

const shared_buffer::header* shared_buffer::chead() const {
    return reinterpret_cast<const header*>(_mem.cdata());
}

shared_buffer::header* shared_buffer::head() {
    return reinterpret_cast<header*>(_mem.data());
}

chunk* shared_buffer::at(int id) {
    char* base = _mem.data() + sizeof(header);
    return reinterpret_cast<chunk*>(base) + id;
}

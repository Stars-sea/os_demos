#include "include/shared_buffer.hpp"
#include "include/chunk.hpp"

#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main() {
    shared_buffer buf{"/shm_demo", false, 10};

    while (true) {
        chunk msg_chunk{};
        if (buf.read(msg_chunk)) {
            if (msg_chunk.size == 1 && msg_chunk.data[0] == 'q')
                break;
            std::cout << "[consumer] -> " << msg_chunk.data << std::endl;
        }

        std::this_thread::sleep_for(10ms);
    }
}

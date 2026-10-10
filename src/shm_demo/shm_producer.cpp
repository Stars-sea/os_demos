#include "include/shared_buffer.hpp"
#include "include/chunk.hpp"

#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std::chrono_literals;

volatile sig_atomic_t g_running = 1;

// Ctrl-C 不会析构 C++ 对象, 处理信号保证析构正常执行
void handleSIGINT(int) {
    g_running = 0;
}

int main(int argc, const char* argv[]) {
    signal(SIGINT, handleSIGINT);

    shared_buffer buf{"/shm_demo", true, 10};

    if (argc > 1 && strcmp(argv[1], "with_consumer") == 0) {
        pid_t pid = fork();
        if (pid < 0) {
            std::cerr << "[producer] Failed to start consumer process" << std::endl;
        } else if (pid == 0) {
            execl("./shm_consumer", "shm_consumer", nullptr);
            execl("./bin/shm_consumer", "shm_consumer", nullptr);
            std::cerr << "[producer] Failed to find consumer process" << std::endl;
            return -1;
        }
    }

    std::string msg = "";
    chunk msg_chunk{};
    while (g_running) {
        std::cout << "[producer] <- ";
        std::getline(std::cin, msg);
        if (msg == "q") break;

        if (!make_chunk(msg.c_str(), msg_chunk)) {
            std::cout << "failed to make chunk, ignoring..." << std::endl;
            continue;
        }

        if (!buf.write(msg_chunk)) {
            std::cout << "failed to write chunk, skipped..." << std::endl;
        }
        std::this_thread::sleep_for(50ms);
    }

    make_chunk("q", msg_chunk);
    buf.write(msg_chunk);
    if (wait(nullptr) == -1)
        std::this_thread::sleep_for(1s);
}

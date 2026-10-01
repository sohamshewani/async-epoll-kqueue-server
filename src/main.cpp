#include <iostream>
#include "include/config.h"
#include "include/event_loop.h"

int main(int argc, char *argv[]) {
    std::cout << "Async Epoll Kqueue Server Starting..." << std::endl;
    EventLoop loop;
    Config config(argc, argv);
    ConnectionPool pool(&loop, &config);
    Session session(&loop, &pool);
    loop.loop();
    return 0;
}
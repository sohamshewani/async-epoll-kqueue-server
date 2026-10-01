#pragma once

#ifndef EVENT_LOOP_H_
#define EVENT_LOOP_H_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "session.h"
#include "config.h"

// EventLoop class manages event handling
class EventLoop {
public:
    EventLoop(const Config& config);
    ~EventLoop();
    void start();

private:
    void loop();
    void handleRead(int fd);
    void handleWrite(int fd);
    void handleError(int fd);

    Config config_;  // Configuration data
    std::unordered_map<int, Session*> fd_to_session_; // FD to Session mapping
    std::vector<epoll_event> events_; // Events to handle
    int epoll_fd_;
};

#endif // EVENT_LOOP_H_

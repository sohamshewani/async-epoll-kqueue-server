#include "event_loop.h"
#include "session.h"
#include <sys/eventfd.h>

EventLoop::EventLoop(const Config& config) : config_(config), epoll_fd_(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC)) {
    if (epoll_fd_ == -1) {
        perror("eventfd");
        exit(EXIT_FAILURE);
    }
    events_.resize(MAX_EVENTS);
    epoll_fd_ = epoll_create1(0);
    if (epoll_fd_ == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }
}

EventLoop::~EventLoop() {
    close(epoll_fd_);
    close(epoll_fd_);
}

void EventLoop::start() {
    loop();
}

void EventLoop::loop() {
    int nfds = epoll_wait(epoll_fd_, events_.data(), MAX_EVENTS, -1);
    if (nfds == -1) {
        perror("epoll_wait");
        return;
    }
    for (int i = 0; i < nfds; ++i) {
        int fd = events_[i].data.fd;
        switch (events_[i].events) {
            case EPOLLIN:
                handleRead(fd);
                break;
            case EPOLLOUT:
                handleWrite(fd);
                break;
            case EPOLLERR:
                handleError(fd);
                break;
            default:
                break;
        }
    }
}

void EventLoop::handleRead(int fd) {
    // Handle read event
    if (fd_to_session_.find(fd) == fd_to_session_.end()) {
        std::cerr << "Error: No session for fd: " << fd << std::endl;
        return;
    }
    fd_to_session_[fd]->handleRead();
}

void EventLoop::handleWrite(int fd) {
    // Handle write event
    if (fd_to_session_.find(fd) == fd_to_session_.end()) {
        std::cerr << "Error: No session for fd: " << fd << std::endl;
        return;
    }
    fd_to_session_[fd]->handleWrite();
}

void EventLoop::handleError(int fd) {
    // Handle error event
    if (fd_to_session_.find(fd) == fd_to_session_.end()) {
        std::cerr << "Error: No session for fd: " << fd << std::endl;
        return;
    }
    fd_to_session_[fd]->handleError();
}

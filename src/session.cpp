#include "session.h"

Session::Session(int fd, const Config& config) : fd_(fd), config_(config) {
}

Session::~Session() {
    close(fd_);
}

void Session::handleRead() {
    // Handle read event
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(fd_, buffer, BUFFER_SIZE);
    if (bytes_read == -1) {
        perror("read");
        return;
    }
    // Process the read data
}

void Session::handleWrite() {
    // Handle write event
    std::string data = "Hello, World!";
    ssize_t bytes_written = write(fd_, data.c_str(), data.size());
    if (bytes_written == -1) {
        perror("write");
        return;
    }
}

void Session::handleError() {
    // Handle error event
    std::cerr << "Error in session: " << fd_ << std::endl;
}

#pragma once

#ifndef SESSION_H_
#define SESSION_H_

#include <iostream>
#include <string>

// Session class for handling network connections
class Session {
public:
    Session(int fd, const Config& config);
    ~Session();
    void handleRead();
    void handleWrite();

private:
    int fd_; // File descriptor for the connection
    Config config_; // Configuration data
};

#endif // SESSION_H_

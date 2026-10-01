#pragma once

#ifndef CONNECTION_POOL_H_
#define CONNECTION_POOL_H_

#include <unordered_map>
#include <vector>
#include <iostream>
#include <mutex>

#include "session.h"
#include "config.h"

// ConnectionPool manages a pool of active connections
class ConnectionPool {
public:
    ConnectionPool(const Config& config);
    ~ConnectionPool();
    Session* getNewSession();
    void releaseSession(Session* session);

private:
    Config config_; // Configuration data
    std::vector<Session*> available_; // Free sessions
    std::unordered_map<int, Session*> inUse_; // Sessions in use
    std::mutex mutex_;
};

#endif // CONNECTION_POOL_H_

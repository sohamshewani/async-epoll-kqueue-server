#include "connection_pool.h"
#include <iostream>

ConnectionPool::ConnectionPool(const Config& config) : config_(config), available_(CONN_POOL_SIZE), mutex_() {
    for (int i = 0; i < available_.size(); ++i) {
        available_[i] = new Session(i, config_);
    }
}

ConnectionPool::~ConnectionPool() {
    for (Session* session : available_) {
        delete session;
    }
}

Session* ConnectionPool::getNewSession() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!available_.empty()) {
        Session* session = available_.back();
        available_.pop_back();
        return session;
    }
    return nullptr;
}

void ConnectionPool::releaseSession(Session* session) {
    std::lock_guard<std::mutex> lock(mutex_);
    available_.push_back(session);
}

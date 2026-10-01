#pragma once

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <vector>

// Configuration constants
const int DEFAULT_PORT = 8080;
const int MAX_EVENTS = 1024;
const int CONN_POOL_SIZE = 100;
const int BUFFER_SIZE = 1024;

// Configuration structure
struct Config {
    std::string ip;
    int port = DEFAULT_PORT;
    std::vector<std::string> addresses;
};

#endif // CONFIG_H_

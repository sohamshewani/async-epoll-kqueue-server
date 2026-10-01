CC := g++
CFLAGS := -std=c++11 -Wall -Wextra -pedantic -g
SRCS := $(shell find src -name '*.cpp')
HDRS := $(shell find include -name '*.h')
OBJS := $(SRCS:.cpp=.o)
TARGET := async-epoll-kqueue-server

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

test_unit:
	make -C tests test

test_integration:
	make -C tests test_integration

clean:
	rm -f $(OBJS) $(TARGET)

clean_tests:
	make -C tests clean

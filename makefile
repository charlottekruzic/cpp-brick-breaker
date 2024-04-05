CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lSDL2

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = simple_window

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

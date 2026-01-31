CC  = gcc
CXX = g++

CFLAGS   = -O2
CXXFLAGS = -O3

C_SRCS = main.c GameCore.c alphabeta.c negamax.c evaluation.c random.c helpers.c 
C_OBJS = $(C_SRCS:.c=.o)

CPP_SRCS = Position.cpp Solver.cpp connect4_wrapper.cpp
CPP_OBJS = $(CPP_SRCS:.cpp=.o)

all: connect4_bot

connect4_bot: $(C_OBJS) libconnect4.a
	$(CC) $(C_OBJS) -L. -lconnect4 -lstdc++ -o $@

libconnect4.a: $(CPP_OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o *.a connect4_bot

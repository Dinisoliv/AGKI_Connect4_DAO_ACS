CC  = gcc
CXX = g++
AR  = ar

CFLAGS   = -O2 -std=c11
CXXFLAGS = -O3 -std=c++17

# C sources (your bot)
C_SRCS = main.c GameCore.c alphabeta.c negamax.c evaluation.c helpers.c random.c
C_OBJS = $(C_SRCS:.c=.o)

# C++ sources (solver + wrapper)
CPP_SRCS = Solver.cpp connect4_wrapper.cpp
CPP_OBJS = $(CPP_SRCS:.cpp=.o)

TARGET = connect4

all: $(TARGET)

$(TARGET): $(C_OBJS) libconnect4.a
	$(CC) $(C_OBJS) -L. -lconnect4 -lstdc++ -o $(TARGET)

libconnect4.a: $(CPP_OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o *.a $(TARGET)

# ─────────────────────────────────────────────
# Toolchain
# ─────────────────────────────────────────────
CC  = gcc
CXX = g++
AR  = ar

# ─────────────────────────────────────────────
# Flags
# ─────────────────────────────────────────────
CFLAGS   = -O2 -std=c11 -Wall -Wextra -D_POSIX_C_SOURCE=199309L
CXXFLAGS = -O3 -std=c++17 -Wall -Wextra
LDFLAGS  = -lstdc++

# ─────────────────────────────────────────────
# Sources
# ─────────────────────────────────────────────

# C sources (your engine)
C_SRCS = \
	main.c \
	GameCore.c \
	alphabeta.c \
	negamax.c \
	evaluation.c \
	random.c \
	helpers.c \
	alphabeta_tt.c \
	iterative.c

C_OBJS = $(C_SRCS:.c=.o)

# C++ sources (PascalPons solver + wrapper)
CPP_SRCS = \
	Solver.cpp \
	connect4_wrapper.cpp

CPP_OBJS = $(CPP_SRCS:.cpp=.o)

# Output
TARGET = connect4_bot
LIB    = libconnect4.a

# ─────────────────────────────────────────────
# Build rules
# ─────────────────────────────────────────────

all: $(TARGET)

$(TARGET): $(C_OBJS) $(LIB)
	$(CC) $(C_OBJS) -L. -lconnect4 $(LDFLAGS) -o $@

$(LIB): $(CPP_OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o *.a $(TARGET)

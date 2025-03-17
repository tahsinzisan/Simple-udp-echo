all: main

CXX = clang++
CXXFLAGS = -g -Wall -Werror

SRCS = $(wildcard src/*.cpp)
OBJFILES = $(SRCS:.cpp=.o)

main: $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(OBJFILES) -o $@

main-debug: $(OBJFILES)
	$(CXX) $(CXXFLAGS) -O0 $(OBJFILES) -o $@

clean:
	rm -f main main-debug $(OBJFILES)

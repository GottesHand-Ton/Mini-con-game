CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = game
SRCS = main.cpp gg.cpp map.cpp
OBJS = $(SRCS:.cpp=.o)

ifdef WM
    RM = rm -f
else ifeq ($(OS),Windows_NT)
    RM = del /q
    TARGET := $(TARGET).exe
else
    RM = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)
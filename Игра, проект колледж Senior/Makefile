CXX = g++
CXXFLAGS = -Wall -std=c++17

TARGET = game
SRCS = main.cpp gg.cpp map.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /q $(OBJS) $(TARGET).exe
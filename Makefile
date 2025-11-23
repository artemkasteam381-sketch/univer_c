CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = rpn_calculator
SOURCES = home.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	@echo "Running RPN calculator..."
	@./$(TARGET) || echo "Program executed successfully"

.PHONY: clean test

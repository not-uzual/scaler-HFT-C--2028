CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

demo: main.cpp OrderBookA.cpp OrderBookA.h Common.h
	$(CXX) $(CXXFLAGS) main.cpp OrderBookA.cpp -o demo

clean:
	rm -f demo bench

.PHONY: clean

CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

demo: main.cpp OrderBookA.cpp OrderBookA.h OrderBookB.cpp OrderBookB.h Common.h
	$(CXX) $(CXXFLAGS) main.cpp OrderBookA.cpp OrderBookB.cpp -o demo

clean:
	rm -f demo bench

.PHONY: clean

CXX := g++
CXXFLAGS := -Wall -std=c++11

test: tests.o tests-main.o
	${CXX} ${CXXFLAGS} *.o -o tests
	./tests

tests.o: tests.cpp
	${CXX} ${CXXFLAGS} -c -I/home/pieter/lib/Catch2/single_include tests.cpp

tests-main.o: tests-main.cpp
	${CXX} ${CXXFLAGS} -c -I/home/pieter/lib/Catch2/single_include tests-main.cpp

.PHONY: clean
clean:
	$(RM) *.o
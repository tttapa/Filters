CXX := g++
CXXFLAGS := -Wall -std=c++11

export: all
	./Spectrum

all: Spectrum.o AudioFile.o
	${CXX} ${CXXFLAGS} *.o -fopenmp -o Spectrum

Spectrum.o: Spectrum.cpp
	${CXX} ${CXXFLAGS} -fopenmp -c Spectrum.cpp

AudioFile.o: AudioFile.cpp
	${CXX} ${CXXFLAGS} -c AudioFile.cpp

.PHONY: clean
clean:
	$(RM) *.o
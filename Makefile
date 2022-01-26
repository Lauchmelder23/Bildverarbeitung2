CC = g++
CCFLAGS = -std=c++14 -Wall

all: bin/imageviewer bin/smooth bin/edgedetect

rebuild: clean all

%.o: %.cpp bild.hpp
	$(CC) -c $< -o $@ $(CCFLAGS)

bin/%: %.o bild.o
	@mkdir -p $(@D)
	$(CC) $^ -o $@

clean:
	@rm -rf bin


CC = g++
CCFLAGS = -std=c++14 -Wall

all: bin/imageviewer bin/smooth bin/edgedetect

imageviewer: bin/imageviewer
smooth: bin/smooth
edgedetect: bin/edgedetect

%.o: src/%.cpp include/bild.hpp
	@mkdir -p $(@D)
	$(CC) -Iinclude -c $< -o $@ $(CCFLAGS)

bin/%: %.o bild.o
	@mkdir -p $(@D)
	$(CC) $^ -o $@

clean:
	@rm -rf bin 
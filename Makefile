default: imageviewer smooth edgedetect

imageviewer: folder src/Bild.cpp src/ImageViewer.cpp
	clang++ -o build/imageviewer src/Bild.cpp src/ImageViewer.cpp -I include -std=c++14 -Weverything -Wno-c++98-compat

smooth: folder src/Bild.cpp src/Smooth.cpp
	clang++ -o build/smooth src/Bild.cpp src/Smooth.cpp -I include -std=c++14 -Weverything -Wno-c++98-compat

edgedetect: folder src/Bild.cpp src/EdgeDetect.cpp
	clang++ -o build/edetect src/Bild.cpp src/EdgeDetect.cpp -I include -std=c++14 -Weverything -Wno-c++98-compat

folder:
	mkdir -p build

clean:
	rm -rf build

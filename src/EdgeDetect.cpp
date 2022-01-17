/**
 * Reads a PGM file and performs edge detection, then writes the result to disk
 */
#include <iostream>
#include "Bild.hpp"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Usage: edetect <pgm file>" << std::endl;
        return 0;
    }
    std::string filename = argv[1];

    // Load file
    std::ifstream file(filename);
    if(!file.good())
    {
        std::cerr << "Failed to open file" << std::endl;
        return -1;
    }

    // Create image
    Bild image;
    try 
    {
        file >> image;
    } 
    catch(const std::runtime_error& err)
    {
        std::cerr << err.what() << std::endl;
        file.close();
        return -1;
    }

    file.close();

    // Print image
    image = image.Kantenbild();

    filename.insert(filename.find('.'), "_modified");
    std::ofstream outFile(filename);
    outFile << image;
    outFile.close();

    return 0;
}

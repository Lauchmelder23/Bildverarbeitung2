/**
 * Displays a given PGM image in the console using ASCII characters
 */
#include <iostream>
#include "Bild.hpp"

int main(int argc, char** argv)
{
    // If there are no additional arguments print usage info
    if(argc < 2)
    {
        std::cout << "Usage: imageviewer <pgm file>" << std::endl;
        return 0;
    }

    // Load file
    std::ifstream file(argv[1]);
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
    std::cout << image << std::endl;
    return 0;
}

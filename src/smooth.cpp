/**
 * Reads a PGM image and smooths it by some amount, then writes it back to disk
 */
#include <iostream>
#include "bild.hpp"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Usage: smooth <pgm file>" << std::endl;
        return 0;
    }
    std::string filename = argv[1];

    uint16_t smoothing;
    std::cout << "Wie oft soll das Bild geglaettet werden? ";
    std::cin >> smoothing;

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
    for(uint8_t i = 0; i < smoothing; i++)
        image = image.Geglaettet();

    filename.insert(filename.find('.'), "_modified");
    std::ofstream outFile(filename);
    outFile << image;
    outFile.close();

    return 0;
}

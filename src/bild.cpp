#include "bild.hpp"

#include <iostream>
#include <sstream>

std::ifstream& operator>>(std::ifstream& file, Bild& image)
{
    std::string lineContent;

    // First line should contain "P2"
    std::getline(file, lineContent);
    if(lineContent[0] != 'P' || lineContent[1] != '2')
    {
        throw std::runtime_error("Missing/Wrong PGM magic number.");
    }

    // The second line contains an image description
    std::getline(file, lineContent);
    std::string::iterator it;
    for(it = lineContent.begin(); it != lineContent.end(); it++)    // Flush out any leading spaces to get the description
    {
        if(*it != ' ' && *it != '#')    // Break from loop if the iterator reached a character that isnt '#' or ' '
            break;
    }

    image.description = std::string(it, lineContent.end() - 1);   // Store the description (and cut off the newline)

    // The third line contains the image dimensions
    file >> image.width >> image.height;
    std::getline(file, lineContent); 

    // The fourth line contains the max brightness value
    std::getline(file, lineContent);    // Do nothing with it

    // The remaining file contains image data
    uint16_t pixelValue = 0;
    while(std::getline(file, lineContent))  // Loop through remaining lines
    {
        std::stringstream ss(lineContent);
        while(ss >> pixelValue)     // Loop through numbers in the line
        {
            image.pixels.push_back(static_cast<uint8_t>(pixelValue)); // Write pixel into the array
        }
    }

    // Check if vector size matches image dimensions
    if(image.pixels.size() != static_cast<size_t>(image.width) * image.height)
    {
        throw std::runtime_error(
            "Amount of image data doesn't match image dimensions. Expected " + 
            std::to_string(image.width * image.height) + 
            " pixels, got " + std::to_string(image.pixels.size()) + 
            " pixels instead."
        );
    }

    return file;
}

std::ofstream& operator<<(std::ofstream& file, const Bild& image)
{
    file << "P2" << std::endl;                                  // Write magic number to file
    file << "# " << image.description << std::endl;             // Write image description
    file << image.width << " " << image.height << std::endl;    // Write image dimensions
    file << 255 << std::endl;                                   // Write max brightness value

    // Write pixel data
    std::string line;
    for(uint8_t pixel : image.pixels)
    {
        uint32_t value = static_cast<uint32_t>(pixel);
        if(line.size() + std::to_string(value).length() > 70)
        {
            file << line << std::endl;
            line.clear();
        }

        line += std::to_string(value) + " ";
    }

    file << line << std::endl;

    return file;
}

std::ostream& operator<<(std::ostream& os, const Bild& image)
{
    std::string asciiBrightnessMap(".'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$");

    for(uint16_t y = 0; y < image.height; y++)
    {
        std::stringstream lineBuffer;
        for(uint16_t x = 0; x < image.width; x++)
        {
            uint8_t brightness = image.pixels[y * image.width + x];

            // Map the pixel brightness (which is in the interval [0, 255]) to the ascii chart length
            uint8_t asciiMapIndex = static_cast<uint8_t>(brightness * (asciiBrightnessMap.length() - 1) / 255);
            lineBuffer << asciiBrightnessMap[asciiMapIndex];
        }
        
        std::cout << lineBuffer.str() << std::endl;
    }

    return os;
}

Bild Bild::Geglaettet() const
{
    // Create new image and copy metadata
    Bild smoothedImage;
    smoothedImage.width = width;
    smoothedImage.height = height;
    smoothedImage.description = description + " smoothed";
    smoothedImage.pixels.resize(pixels.size()); // Resize the pixel array to match the image dimensions

    // Apply smoothing
    for(uint32_t y = 0; y < smoothedImage.height; y++)
    {
        for(uint32_t x = 0; x < smoothedImage.width; x++)
        {
            // If this is a border pixel just copy it from the original
            if(y == 0 || x == 0 || y == smoothedImage.height - 1 || x == smoothedImage.width - 1) 
            {
                smoothedImage.pixels[y * smoothedImage.width + x] = pixels[y * smoothedImage.width + x];
                continue;
            }

            // Else, make this pixel the average of its 4 neighbours
            uint32_t sumOfPixels = 
                pixels[(y - 1) * smoothedImage.width + (x + 0)] +
                pixels[(y + 1) * smoothedImage.width + (x + 0)] +
                pixels[(y + 0) * smoothedImage.width + (x - 1)] +
                pixels[(y + 0) * smoothedImage.width + (x + 1)] +
                4 * pixels[y * smoothedImage.width + x];

            smoothedImage.pixels[y * smoothedImage.width + x] = static_cast<uint8_t>(sumOfPixels / 8);
        }
    }

    return smoothedImage;
}

Bild Bild::Kantenbild() const
{
    // Create new image and copy metadata
    Bild modifiedImage;
    modifiedImage.width = width;
    modifiedImage.height = height;
    modifiedImage.description = description + " edged";
    modifiedImage.pixels.resize(pixels.size()); // Resize the pixel array to match the image dimensions

    // Apply edge detection
    for(uint32_t y = 0; y < modifiedImage.height; y++)
    {
        for(uint32_t x = 0; x < modifiedImage.width; x++)
        {
            // If this is a border pixel set its brightness to 0
            if(y == 0 || x == 0 || y == modifiedImage.height - 1 || x == modifiedImage.width - 1) 
            {
                modifiedImage.pixels[y * modifiedImage.width + x] = 0;
                continue;
            }

            // Else, apply the formula to calculate pixel brightness
            int32_t sumOfPixels = 
                pixels[(y - 1) * modifiedImage.width + (x + 0)] +
                pixels[(y + 1) * modifiedImage.width + (x + 0)] +
                pixels[(y + 0) * modifiedImage.width + (x - 1)] +
                pixels[(y + 0) * modifiedImage.width + (x + 1)] -
                4 * pixels[y * modifiedImage.width + x];

            if(sumOfPixels < 0)
                sumOfPixels = 0;

            modifiedImage.pixels[y * modifiedImage.width + x] = static_cast<uint8_t>(sumOfPixels / 8);
        }
    }

    return modifiedImage;
}

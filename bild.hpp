#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

/**
 * @brief Stores PGM image data
 * 
 * This class can read and write PGM images, perform smoothing and 
 * edge detection on them and display them in the console as ASCII art
 */
class Bild
{
public:
    // ASCII characters used when printing the image to stdout
    static const std::string asciiBrightnessMap;

public:
    /**
     * @brief Creates a new empty picture.
     * 
     * The created picture has no dimensions and contains no pixel data.
     */
    Bild() = default;

    /**
     * @brief Construct a new empty picture with meta data
     * 
     * The pixel buffer will be empty, but the meta data (width, height, description)
     * will be set, and the pixel buffer will be resized to match the dimensions
     * 
     * @param width Width of the image
     * @param height Height of the image
     * @param description Description of the image
     */
    Bild(uint32_t width, uint32_t height, const std::string& description);

    /**
     * @brief Copy an image
     * 
     * The copy will copy the image data from the original image to a new buffer
     * 
     * @param other The image to copy from
     */
    Bild(const Bild& other) = default;

    /**
     * @brief Load an image
     * 
     * Reads a file containing image data and populates the pixel array
     * 
     * @param file (Valid) filestream containing image data
     * @param image The image object to store the data in
     * @return The modified filestream
     */
    friend std::ifstream& operator>>(std::ifstream& file, Bild& image);

    /**
     * @brief Save an image
     * 
     * Writes the stored image data into a file, overwriting any contents in it
     * 
     * @param file (Valid) filestream to store the image in
     * @param image The image object to get the data from
     * @return The modified filestream
     */
    friend std::ofstream& operator<<(std::ofstream& file, const Bild& image);

    /**
     * @brief Renders the image to the console
     * 
     * Draws the image in the console using ascii characters.
     * Das war zwar in der Aufgabe nicht verlangt aber ich wollte gern die Bilder sehen
     * 
     * @param os Output stream to draw to
     * @param image Image to draw
     * @return The modified output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Bild& image);

    /**
     * @brief Applies smoothing to an image, effectively blurring it
     * 
     * @return The blurred image 
     */
    Bild Geglaettet() const;

    /**
     * @brief Performs edge detection on the image
     * 
     * @return An image with only the edges found in the original 
     */
    Bild Kantenbild() const;

private:
    uint32_t width {};
    uint32_t height {};
    std::string description;
    std::vector<uint8_t> pixels;
};

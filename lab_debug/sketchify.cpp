#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
HSLAPixel* myFavoriteColor(double saturation) {
 /* HSLAPixel pixel(128, saturation, 0.5);  // Green (hue = 128) is my favorite color!
    return &pixel; */
    HSLAPixel* pixel = new HSLAPixel(128, saturation, 0.5);
    return pixel;  // ======== BUG #03 FIXED ========
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
 /* PNG* original = NULL; */
    PNG* original = new PNG();  // ======== BUG #01 FIXED ========

    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();

    // Create out.png
 /* PNG* output;
    setupOutput(width, height); */
    PNG* output = setupOutput(width, height);  // ======== BUG #02 FIXED ========

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor(0.5);

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
 /* for (unsigned y = 1; 0 < y < height; y++)
        for (unsigned x = 1; 0 < x < width; x++) { */
    for (unsigned y = 1; y < height; y++)
        for (unsigned x = 1; x < width; x++) {  // ======== BUG #04 FIXED ========
            // Calculate the pixel difference
            HSLAPixel* prev = original->getPixel(x - 1, y - 1);
            HSLAPixel* curr = original->getPixel(x, y);
            double diff = std::fabs(curr->h - prev->h);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
         /* HSLAPixel* currOutPixel = (*output).getPixel(x, y);
            if (diff > 20) currOutPixel = myPixel; */
            HSLAPixel* currOutPixel = output->getPixel(x, y);
            if (diff > 20) *currOutPixel = *myPixel;  // ======== BUG #05 FIXED ========
        }

    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}

#include <string>
#include "cs225/PNG.h"


void rotate(std::string inputFile, std::string outputFile) {
	cs225::PNG inputImage, outputImage;
	cs225::HSLAPixel *inputPixel, *outputPixel;
	unsigned width, height;
	
	inputImage.readFromFile( inputFile );
	width = inputImage.width(), height = inputImage.height();
	outputImage.resize( width, height );
	
	for (unsigned x = 0; x < width; x++)
		for (unsigned y = 0; y < height; y++) {
			inputPixel = inputImage.getPixel( x, y );
			outputPixel = outputImage.getPixel( width - 1 - x, height - 1 - y );
			*outputPixel = *inputPixel;
		}
	
	outputImage.writeToFile( outputFile );
}

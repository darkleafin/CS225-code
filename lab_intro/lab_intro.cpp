#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "lab_intro.h"

using namespace cs225;

#include <signal.h>

/**
 * Returns 1 if a double is positive, 0 for zero, and -1 for negative.
 * 
 * A double with its absolute value no larger than the tolerance
 * threshold is regarded to be zero.
 * 
 * @param val The input value.
 * @param eps The tolerance threshold.
 */
int dcmp(double val, double eps = 1e-8) {return val < -eps ? -1 : (int)(val > eps);}


/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @param image A PNG object which holds the image data to be modified.
 * 
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
    /// This function is already written for you so you can see how to
    /// interact with our PNG class.
    for (unsigned x = 0; x < image.width(); x++)
        for (unsigned y = 0; y < image.height(); y++) {
            HSLAPixel *pixel = image.getPixel(x, y);

            // `pixel` is a pointer to the memory stored inside of the PNG `image`,
            // which means you're changing the image directly.  No need to `set`
            // the pixel since you're directly changing the memory of the image.
            pixel->s = 0;
        }

    return image;
}


/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 200 pixels away, the luminance will always 0.
 *
 * The modified PNG is then returned.
 *
 * @param image   A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
    for (unsigned x = 0; x < image.width(); x++)
        for (unsigned y = 0; y < image.height(); y++) {
            HSLAPixel *pixel = image.getPixel(x, y);
            
            double dist = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));  // calculate the distance
            pixel->l *= max(1. - 0.005 * dist, 0.);  // scale the luminance of the pixel
        }
    
    return image;
}


/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
    static const double hue_io = 11.;
    static const double hue_ib = 216.;

    for (unsigned x = 0; x < image.width(); x++)
        for (unsigned y = 0; y < image.height(); y++) {
            HSLAPixel *pixel = image.getPixel(x, y);
            
            double dist_io = abs(pixel->h - hue_io);
            double dist_ib = abs(pixel->h - hue_ib);  // calculate the hue distance
            dist_io = min(dist_io, 360. - dist_io);
            dist_ib = min(dist_ib, 360. - dist_ib);  // distance could be obtained from two directions
            pixel->h = -1 == dcmp(dist_io - dist_ib) ? hue_io : hue_ib;  // determine the illinify'd hue
        }
    
    return image;
}


/**
* Returns an image that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs.
* @param secondImage The second of the two PNGs.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
    unsigned width = min(firstImage.width(), secondImage.width());
    unsigned height = min(firstImage.height(), secondImage.height());

    for (unsigned x = 0; x < width; x++)
        for (unsigned y = 0; y < height; y++) {
            HSLAPixel *pixel = secondImage.getPixel(x, y);
            
            if (dcmp(pixel->l - 1.) >= 0) {  // if luminance of the pixel on second image is 1
                pixel = firstImage.getPixel(x, y);
                pixel->l = min(pixel->l + 0.2, 1.);  // increase the pixel on the first image by 0.2, with maximum 1
            }
        }

    return firstImage;
}

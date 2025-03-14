#ifndef STEGANOGRAPHY_PIXELCOLOR_H
#define STEGANOGRAPHY_PIXELCOLOR_H


class PixelColor {
public:
    PixelColor(const PixelColor& t)
    {
        red = t.red;
        green = t.green;
        blue = t.blue;
        alpha = t.alpha;
    }
    unsigned char red, green, blue, alpha;

    PixelColor() : red(0), green(0), blue(0), alpha(0) { }

    PixelColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : red(r), green(g), blue(b), alpha(a) { }
};

#endif //STEGANOGRAPHY_PIXELCOLOR_H

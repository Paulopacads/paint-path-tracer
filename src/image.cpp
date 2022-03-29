#include <math.h>
#include <stdio.h>
#include <iostream>

#include "image.hpp"

inline double clamp(double x)
{
    return x < 0 ? 0 : x > 1 ? 1 : x;
}

inline int toInt(double n)
{
    int res = int(pow(clamp(n), 1 / 2.2) * 255 + .5);
    if (res > 255)
        std::cout << res << '\n';
    return res;
}

Image::Image(int width, int height)
    : width(width)
    , height(height)
    , pixels(new Vector3[width * height])
{
    for (int i = 0; i < width * height; ++i)
        this->pixels[i] = Vector3();
}

void Image::setPixel(int x, int y, Vector3 pixel)
{
    this->pixels[y * width + x] = pixel;
}

Vector3 Image::getPixel(int x, int y)
{
    return this->pixels[y * width + x];
}

int Image::save(std::string filename)
{
    FILE *file = std::fopen(filename.append(".ppm").c_str(), "w");
    std::fprintf(file, "P3\n%d %d\n%d\n", width, height, 255);
    for (int i = 0; i < width * height; ++i)
        std::fprintf(file, "%d %d %d ", toInt(pixels[i].x), toInt(pixels[i].y),
                     toInt(pixels[i].z));
    fclose(file);
    return 0;
}

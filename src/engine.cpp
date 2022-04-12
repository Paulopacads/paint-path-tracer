#include <iostream>
#include <math.h>

#include "engine.hpp"

Image raytrace(Scene scene, int width, int height, int spp)
{
    Image image = Image(width, height);

    Vector3 fakeplancenter = scene.camera.center + scene.camera.direction;
    double fakeplanwidth = 2 * tan(M_PI * scene.camera.betaFOV / 360);
    double fakeplanheight = 2 * tan(M_PI * scene.camera.alphaFOV / 360);

    Vector3 plancenter =
        scene.camera.center + scene.camera.direction * scene.camera.distance;
    double planwidth = fakeplanwidth * scene.camera.distance;
    double planheight = fakeplanheight * scene.camera.distance;

    Vector3 fakeplantopleft = fakeplancenter
        + scene.camera.up * fakeplanheight / 2
        - scene.camera.right * fakeplanwidth / 2;

    Vector3 plantopleft = plancenter + scene.camera.up * planheight / 2
        - scene.camera.right * planwidth / 2;

    for (int j = 0; j < height; ++j)
        for (int i = 0; i < width; ++i)
        {
            fprintf(stdout, "\rRendering, %5.2f%%",
                    100. * (j * width + i) / (width * height));

            Vector3 fakeorigin = fakeplantopleft
                + scene.camera.right * fakeplanwidth * (i + .5) / width
                - scene.camera.up * fakeplanheight * (j + .5) / height;

            Vector3 origin = plantopleft
                + scene.camera.right * planwidth * (i + .5) / width
                - scene.camera.up * planheight * (j + .5) / height;

            Vector3 vector = (fakeorigin - scene.camera.center).norm();

            Vector3 color = scene.castRay(origin, vector, 5);
            for (int s = 1; s < spp; ++s)
            {
                double ns = s + 1;
                color = color * (s / ns) + scene.castRay(origin, vector, 5) / ns;
            }
            image.setPixel(i, j, color);
        }
    return image;
}

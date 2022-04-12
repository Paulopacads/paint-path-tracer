#include <iostream>
#include <math.h>

#include "engine.hpp"

Image raytrace(Scene scene, int width, int height, int spp, int halton)
{
    Image image = Image(width, height);

    Halton *gen1 = new Halton();
    Halton *gen2 = new Halton();

    gen1->init(0, halton);
    gen2->init(0, halton);

    double fakeplanwidth = 2 * tan(M_PI * scene.camera.betaFOV / 360);
    double fakeplanheight = 2 * tan(M_PI * scene.camera.alphaFOV / 360);

    Vector3 plancenter =
        scene.camera.center + scene.camera.direction * scene.camera.distance;
    double planwidth = fakeplanwidth * scene.camera.distance;
    double planheight = fakeplanheight * scene.camera.distance;

    Vector3 plantopleft = plancenter + scene.camera.up * planheight / 2
        - scene.camera.right * planwidth / 2;

#pragma omp parallel for schedule(dynamic) firstprivate(gen1, gen2)
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            fprintf(stdout, "\rRendering, %5.2f%%", 100. * (j * width + i) / (height * width));
            Vector3 origin = plantopleft
                + scene.camera.right * planwidth * (i + .5) / width
                - scene.camera.up * planheight * (j + .5) / height;

            Vector3 vector = (origin - scene.camera.center).norm();

            Vector3 color = scene.castRay(origin, vector, 5, gen1, gen2);
            for (int s = 1; s < spp; ++s)
            {
                double ns = s + 1;
                color = color * (s / ns)
                    + scene.castRay(origin, vector, 5, gen1, gen2) / ns;
            }
            image.setPixel(i, j, color);
        }
    }
    return image;
}

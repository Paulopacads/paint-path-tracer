#include "engine.hpp"

inline Vector3 clampColor(Vector3 color)
{
    double r = color.x;
    double g = color.y;
    double b = color.z;

    if (r < 0)
        color.x = 0;
    else if (r > 1)
        color.x = 1;

    if (g < 0)
        color.y = 0;
    else if (g > 1)
        color.y = 1;

    if (b < 0)
        color.z = 0;
    else if (b > 1)
        color.z = 1;

    return color;
}

Image raytrace(Scene scene, int width, int height, int spp, int halton1,
               int halton2)
{
    Image image = Image(width, height);

    Halton *gen1 = new Halton();
    Halton *gen2 = new Halton();

    gen1->init(0, halton1);
    gen2->init(0, halton2);

    double fakeplanwidth = 2 * tan(M_PI * scene.camera.betaFOV / 360);
    double fakeplanheight = 2 * tan(M_PI * scene.camera.alphaFOV / 360);

    Vector3 plancenter =
        scene.camera.center + scene.camera.direction * scene.camera.distance;
    double planwidth = fakeplanwidth * scene.camera.distance;
    double planheight = fakeplanheight * scene.camera.distance;

    Vector3 plantopleft = plancenter + scene.camera.up * planheight / 2
        - scene.camera.right * planwidth / 2;

    Vector3 rightbase = scene.camera.right * planwidth / width;
    Vector3 upbase = scene.camera.up * planheight / height;

#pragma omp parallel for schedule(dynamic) firstprivate(gen1, gen2)
    for (int i = 0; i < width; ++i)
    {
        fprintf(stdout, "\rRendering, %3.2f%%", 100. * i / width);
        for (int j = 0; j < height; ++j)
        {
            double ppp = 1. / spp;

            Vector3 color = Vector3();
            for (int s = 0; s < spp; ++s)
            {
                //gen1->next();
                //gen2->next();

                Vector3 origin = plantopleft + rightbase * (i + gen1->get())
                    - upbase * (j + gen2->get()); // antialiasing
                Vector3 vector = (origin - scene.camera.center).norm();
                Vector3 nc = scene.castRay(origin, vector, 0, gen1, gen2);
                nc = clampColor(nc);
                color = color + nc * ppp;
            }

            image.setPixel(i, j, color);
        }
    }
    return image;
}

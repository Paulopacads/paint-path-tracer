#include "engine.hpp"

// make sure `color` is a correct color vector ((r, g, b) E [0, 1]^3)
inline Vector3 clampColor(Vector3 color)
{
    color.x = color.x < 0 ? 0 : color.x > 1 ? 1 : color.x;
    color.y = color.y < 0 ? 0 : color.y > 1 ? 1 : color.y;
    color.z = color.z < 0 ? 0 : color.z > 1 ? 1 : color.z;

    return color;
}

Image trace(Scene scene, int width, int height, int spp, int halton1,
            int halton2)
{
    Image image = Image(width, height);

    // Halton generators, 2 for path tracer, 1 for secondary rnd generation
    Halton *gen1 = new Halton();
    Halton *gen2 = new Halton();
    Halton *rnd = new Halton();

    gen1->init(0, halton1);
    gen2->init(0, halton2);
    rnd->init(10, 2);

    double fakeplanwidth = 2 * tan(M_PI * scene.camera.betaFOV / 360);
    double fakeplanheight = 2 * tan(M_PI * scene.camera.alphaFOV / 360);

    Vector3 plancenter =
        scene.camera.center + scene.camera.direction * scene.camera.distance;
    double planwidth = fakeplanwidth * scene.camera.distance;
    double planheight = fakeplanheight * scene.camera.distance;

    Vector3 plantopleft = plancenter + scene.camera.up * planheight / 2
        - scene.camera.right * planwidth / 2;

    // up & right unit vectors for pixels pos on plan computation
    Vector3 rightbase = scene.camera.right * planwidth / width;
    Vector3 upbase = scene.camera.up * planheight / height;

#pragma omp parallel for schedule(dynamic) firstprivate(gen1, gen2, rnd)
    for (int i = 0; i < width; ++i)
    {
        // rendering user feedback
        fprintf(stderr, "\rRendering, %3.2f%%", 100. * i / width);
        for (int j = 0; j < height; ++j)
        {
            double wps = 1. / spp; // weight per sample

            Vector3 color = Vector3();
            for (int s = 0; s < spp; ++s)
            {
                double r1 = rnd->next(); // antialiasing : different
                double r2 = rnd->next(); // rays for each sample

                Vector3 origin =
                    plantopleft + rightbase * (i + r1) - upbase * (j + r2);
                Vector3 vector = (origin - scene.camera.center).norm();
                Vector3 nc = scene.castRay(origin, vector, 0, gen1, gen2, rnd);

                color = color + nc * wps;
            }

            image.setPixel(i, j, clampColor(color));
        }
    }
    return image;
}

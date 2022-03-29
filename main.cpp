#include <cstdlib>
#include <fstream>

#include "libs/json.cpp"
#include "src/engine.hpp"

int main(int argc, char *argv[])
{
    std::ifstream source(argv[1]);

    nlohmann::json json;
    source >> json;

    source.close();

    nlohmann::json scene = json["scene"];
    nlohmann::json cam = scene["cam"];
    nlohmann::json sources = scene["src"];
    nlohmann::json object = scene["obj"];

    double width = json["width"];
    double height = json["height"];

    Vector3 camPos = Vector3(cam["pos"]);
    Vector3 camLook = Vector3(cam["look"]);
    Vector3 camUp = Vector3(cam["up"]);

    Camera camera =
        Camera(camPos, camLook, camUp, cam["fov"], cam["dist"], height / width);

    Vector3 ambiant = Vector3(scene["amb"]);
    Vector3 sky = Vector3(scene["sky"]);

    Scene scene1 = Scene(camera, ambiant, sky);

    for (nlohmann::json object : scene["obj"])
    {
        if (object["type"] == "Sphere")
        {
            Material *material;
            if (object["mat"]["type"] == "UniformMaterial")
                material = new UniformMaterial(object["mat"]);
            else if (object["mat"]["type"] == "SinMaterial")
                material = new ApplyMaterial(object["mat"], [](double a) {
                    return std::rand() % 100 / 100.;
                });
            else
                material = new Material();

            scene1.objects.push_back(
                new Sphere(material, Vector3(object["pos"]), object["rad"]));
        }
        else if (object["type"] == "Triangle")
        {
            Material *material;
            if (object["mat"]["type"] == "UniformMaterial")
                material = new UniformMaterial(object["mat"]);
            else if (object["mat"]["type"] == "SinMaterial")
                material = new ApplyMaterial(object["mat"], [](double a) {
                    return std::rand() % 100 / 100.;
                });
            else
                material = new Material();

            scene1.objects.push_back(new Triangle(
                material, Vector3(object["pos"]["a"]),
                Vector3(object["pos"]["b"]), Vector3(object["pos"]["c"])));
        }
    }

    for (nlohmann::json source : scene["src"])
        if (source["type"] == "PointLightSource")
            scene1.sources.push_back(
                new PointLightSource(Vector3(source["pos"]),
                                     Vector3(source["col"]), source["inty"]));

    Material *material =
        new UniformMaterial(Vector3(.4, .8, .1), 1, .6, .2, 0, 1);
    Vector3 origin = Vector3(7.5, -10, 0);
    double size = 20;
    int disc = 5;
    double min = 5;
    double ***poten = (double ***)malloc((disc + 1) * sizeof(double **));
    for (int i = 0; i < disc + 1; ++i)
    {
        poten[i] = (double **)malloc((disc + 1) * sizeof(double *));
        for (int j = 0; j < disc + 1; ++j)
        {
            poten[i][j] = (double *)malloc((disc + 1) * sizeof(double));
            for (int k = 0; k < disc + 1; ++k)
                poten[i][j][k] = 0;
        }
    }

    poten[1][1][2] = poten[1][2][2] = poten[1][3][2] = poten[1][4][2] =
        poten[1][2][3] = poten[1][3][3] = poten[1][4][3] = 6;

    poten[2][2][1] = poten[2][3][1] = poten[2][1][2] = poten[2][2][2] =
        poten[2][3][2] = poten[2][4][2] = poten[2][1][3] = poten[2][2][3] =
            poten[2][3][3] = poten[2][4][3] = poten[2][1][4] = poten[2][2][4] =
                6;

    poten[3][2][1] = poten[3][3][1] = poten[3][1][2] = poten[3][2][2] =
        poten[3][3][2] = poten[3][1][3] = poten[3][2][3] = poten[3][3][3] =
            poten[3][2][4] = 6;

    poten[3][2][1] = poten[3][3][1] = poten[3][1][2] = poten[3][2][2] =
        poten[3][3][2] = poten[3][2][3] = poten[3][3][3] = poten[3][3][4] = 6;

    scene1.objects.push_back(
        new Blob(material, origin, size, disc, min, poten));

    Image image = raytrace(scene1, width, height);
    image.save(json["name"]);

    for (int i = 0; i < disc + 1; ++i)
    {
        for (int j = 0; j < disc + 1; ++j)
            free(poten[i][j]);
        free(poten[i]);
    }
    free(poten);

    return 0;
}

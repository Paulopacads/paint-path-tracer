#include <cstdlib>
#include <ctime>
#include <fstream>
#include <random>

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

    if (json["with_seed"])
        srand(json["seed"]);
    else
        srand(time(NULL));

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
            else
                material = new Material();

            scene1.objects.push_back(
                new Sphere(material, Vector3(object["pos"]), object["rad"]));
        }
        else if (object["type"] == "Plane")
        {
            Material *material;
            if (object["mat"]["type"] == "UniformMaterial")
                material = new UniformMaterial(object["mat"]);
            else
                material = new Material();

            scene1.objects.push_back(new Plane(
                material, Vector3(object["pos"]["norm"]), object["pos"]["d"]));
        }
    }

    Image image = raytrace(scene1, width, height, json["spp"]);
    image.save(json["name"]);

    return 0;
}

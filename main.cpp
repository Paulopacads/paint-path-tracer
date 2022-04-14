#include <fstream>
#include <iostream>

#include "libs/json.hpp"
#include "src/engine.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr
            << "Welcome to `Paint Path-Tracer` (ppt)!\n"
            << "Usage: " << argv[0] << " FILEPATH\n"
            << '\n'
            << "- FILEPATH:\n"
            << "\tPath to your scene file (json).\n"
            << "\tAn example should be available as `simple_scene.json`.\n"
            << "\tVisit https://hackmd.io/@Qwarks/SJPvMQ_X9 for details.\n"
            << '\n'
            << "This program was created by melanie.tcheou and paul.galand.\n";
        return 1;
    }

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

    Vector3 sky = Vector3(scene["sky"]);

    Scene scene1 = Scene(camera, sky);

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

            scene1.objects.push_back(
                new Plane(material, Vector3(object["norm"]), object["d"]));
        }
    }

    Image image = trace(scene1, width, height, json["spp"], json["halton1"],
                        json["halton2"]);
    image.save(json["name"]);

    return 0;
}

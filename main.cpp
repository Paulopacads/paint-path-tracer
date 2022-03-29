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

    Image image = raytrace(scene1, width, height);
    image.save(json["name"]);

    return 0;
}

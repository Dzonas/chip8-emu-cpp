#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <json.hpp>
#include "conf.hpp"
#include "app.hpp"

using json = nlohmann::json;

const std::string RESOURCE_DIR = "resources";

int main(int argc, char *argv[]) {
    std::filesystem::path resource_path = std::filesystem::current_path().append(RESOURCE_DIR);
    if (argc < 2) {
        std::cout << "no rom to launch" << std::endl;
        return 0;
    }

    std::ifstream i(std::filesystem::path(resource_path).append("roms.json"));
    json j;
    i >> j;
    i.close();

    std::string rom_name = argv[1];
    json rom_data;

    try {
        rom_data = j[rom_name];
    } catch(json::out_of_range&) {
        std::cerr << "got unknown rom" << std::endl;
        return 0;
    }

    Conf config(rom_data, resource_path);

    App app;
    app.init_emulation(config);
    app.run();

    return 0;
}

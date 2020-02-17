#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <json.hpp>
#include "conf.hpp"
#include "app.hpp"

using json = nlohmann::json;

const std::string RESOURCE_DIR = "resources";

json load_configuration_file(const std::string &name);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "no rom to launch" << std::endl;
    return 0;
  }

  // Load rom info
  json j = load_configuration_file("roms.json");

  std::string rom_name = argv[1];
  json rom_data;

  try {
    rom_data = j[rom_name];
  } catch (json::out_of_range &) {
    std::cerr << "got unknown rom" << std::endl;
    return 0;
  }

  RomConf config(rom_data, std::filesystem::current_path().append(RESOURCE_DIR));

  // Load app config
  json k = load_configuration_file("app_conf.json");
  AppConf app_configuration(k);

  App app(app_configuration);
  app.init_emulation(config);
  app.run();

  return 0;
}

json load_configuration_file(const std::string &name) {
  std::filesystem::path resource_path = std::filesystem::current_path().append(RESOURCE_DIR);
  resource_path.append(name);
  std::ifstream configuration_file(resource_path);
  json configuration_json;
  configuration_file >> configuration_json;
  configuration_file.close();

  return configuration_json;
}

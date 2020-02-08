#include "conf.hpp"

using json = nlohmann::json;

Conf::Conf(json rom_data, std::filesystem::path resources_path){
    try{
        emulation_period = 1.0 / (double)rom_data.at("speed");
    } catch (json::out_of_range&) {
        // dont do anything
    }
    try {
        load_store_quirk = rom_data.at("load_store_quirk");
    } catch(json::out_of_range&) {
        // dont do anything
    }

    try {
        shift_quirk = rom_data.at("shift_quirk");
    } catch(json::out_of_range&) {
        // dont do anything
    }
    try {
        wrapping = rom_data.at("wrapping");
    } catch (json::out_of_range&) {
        // dont do anything
    }

    try {
        std::string relative_rom_location = rom_data.at("location");
        rom_location = resources_path.append(relative_rom_location).string();
    } catch(json::out_of_range&) {
        throw std::runtime_error("didn't get rom location");
    }
}
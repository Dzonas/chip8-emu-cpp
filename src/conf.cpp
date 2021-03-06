#include <iostream>
#include "conf.hpp"

using json = nlohmann::json;

RomConf::RomConf(json rom_data, std::filesystem::path resources_path) {
  try {
	emulation_period = 1.0 / (double)rom_data.at("speed");
  } catch (json::out_of_range &) {
	// dont do anything
  }
  try {
	load_store_quirk = rom_data.at("load_store_quirk");
  } catch (json::out_of_range &) {
	// dont do anything
  }

  try {
	shift_quirk = rom_data.at("shift_quirk");
  } catch (json::out_of_range &) {
	// dont do anything
  }
  try {
	wrapping = rom_data.at("wrapping");
  } catch (json::out_of_range &) {
	// dont do anything
  }

  try {
	std::string relative_rom_location = rom_data.at("location");
	rom_location = resources_path.append(relative_rom_location).string();
  } catch (json::out_of_range &) {
	throw std::runtime_error("didn't get rom location");
  }
}

AppConf::AppConf(nlohmann::json app_data) {
  try {
	screen_width = app_data.at("screen_width");
  } catch (json::out_of_range &) {
	// dont do anything
  } catch (json::type_error &e) {
	std::cerr << "Error during screen width parsing:" << std::endl;
	std::cerr << e.what() << std::endl;
	std::cerr << "Using default screen width." << std::endl;
  }
  try {
	screen_height = app_data.at("screen_height");
  } catch (json::out_of_range &) {
	// dont do anything
  } catch (json::type_error &e) {
	std::cerr << "Error during screen height parsing:" << std::endl;
	std::cerr << e.what() << std::endl;
	std::cerr << "Using default screen height." << std::endl;
  }
  try {
	refresh_rate = app_data.at("refresh_rate");
	if (refresh_rate < 0)
	  throw std::runtime_error("refresh rate can't be smaller than 0");
  } catch (json::out_of_range &) {
	// dont do anything
  } catch (json::type_error &e) {
	std::cerr << "Error during screen refresh rate parsing:" << std::endl;
	std::cerr << e.what() << std::endl;
	std::cerr << "Using default screen refresh rate." << std::endl;
  }

  try {
	auto user_keymap = app_data.at("keymap");
	for (const auto &key_name : DEFAULT_KEYS) {
	  try {
		keymap[key_name] = user_keymap.at(key_name);
	  } catch (json::out_of_range &) {
	    // no mapping
	  } catch (json::type_error &e) {
	    throw std::runtime_error(std::string("error during keymap parsing at key") + key_name);
	  }
	}
  } catch (json::out_of_range &) {
	for (const auto &key_name : DEFAULT_KEYS) {
	  keymap[key_name] = key_name;
	}
  }
}

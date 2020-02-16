find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_subdirectory(chip8)
add_executable(chip8_emu_cpp main.cpp conf.hpp conf.cpp emulator.cpp emulator.hpp app.cpp app.hpp)
target_include_directories(chip8_emu_cpp PRIVATE ${PROJECT_SOURCE_DIR}/lib/nlohmann_json)
target_link_libraries(chip8_emu_cpp chip8_lib)
target_link_libraries(chip8_emu_cpp SDL2::Main)
target_link_libraries(chip8_emu_cpp SDL2::Mixer)


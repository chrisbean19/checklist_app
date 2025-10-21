#pragma once

#include <cstddef>

struct constants
{
    // File names
    static constexpr const char* IMGUI_INI_FILE = "build/imgui.ini";
    static constexpr const char* STATE_FILE = "build/checklist.txt";

    // Versions
    static constexpr const char* OPENGL_VERSION = "#version 330";

    // Buffer size
    static constexpr const size_t BUFFER_SIZE = 64;
};
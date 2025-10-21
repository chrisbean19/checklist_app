#pragma once

extern "C" {
#include <glad/glad.h>
}
#include <GLFW/glfw3.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <vector>
#include <array>
#include "ListManager.hpp"
#include "constants.hpp"

class Application
{
    private:
        ListManager mListManager;
        GLFWwindow* mWindow;
    public:
        Application() : mListManager(constants::STATE_FILE) {}
        int init();
        void run();
        void shutdown();
};
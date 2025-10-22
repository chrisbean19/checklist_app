#pragma once

extern "C" {
#include <glad/glad.h>
}
#include <GLFW/glfw3.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ListManager.hpp"
#include <memory>

class WindowManager
{
    private:
        GLFWwindow* mWindow;
        std::unique_ptr<ListManager> mListManager;
    public:
        WindowManager();
        bool windowShouldClose();
        void startNewFrame();
        void buildUI();
        void render();
        void swapBuffers();
        ~WindowManager();
};
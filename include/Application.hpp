#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Application
{
    private:
        GLFWwindow* mWindow;
        std::vector<std::string> mTasks;
        std::vector<uint8_t> mCompleted;
    public:
        Application();
        int init();
        void run();
        void shutdown();
};
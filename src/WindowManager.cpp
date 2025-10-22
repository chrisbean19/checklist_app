#include "WindowManager.hpp"
#include "constants.hpp"
#include <stdexcept>

WindowManager::WindowManager()
{
    if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW\n");

    mWindow = glfwCreateWindow(800, 600, "Checklist App", nullptr, nullptr);
    if (!mWindow)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create window\n");
    }

    glfwMakeContextCurrent(mWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD\n");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = constants::IMGUI_INI_FILE;
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark(); // or Light()

    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init(constants::OPENGL_VERSION);
}

bool WindowManager::windowShouldClose()
{
    return glfwWindowShouldClose(mWindow);
}
        
void WindowManager::startNewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void WindowManager::buildUI(std::unique_ptr<ListManager> &lm)
{
    ImGui::Begin("Checklist");
        for (size_t i = 0; i < lm->getListSize(); ++i)
        {
            bool value = lm->getCompletedAt(i);
            if (ImGui::Checkbox(("##check" + std::to_string(i)).c_str(), &value)) // Invisible label
            {
                lm->setCompletedAt(i, value);
            }
            ImGui::SameLine();
            ImGui::InputText(("##task" + std::to_string(i)).c_str(), lm->getTasksAt(i), constants::BUFFER_SIZE);
            ImGui::SameLine();
            if (ImGui::Button(("X##" + std::to_string(i)).c_str())) {
                lm->eraseTasksAt(i);
                lm->eraseCompletedAt(i);
                --i;
            }
        }
        if (ImGui::Button("+")) {
            std::array<char, constants::BUFFER_SIZE> buf;
            strncpy(buf.data(), "New Task", sizeof(buf));
            lm->pushBackTasks(buf);
            lm->pushBackCompleted(0);
        }
        ImGui::End();
}
        
void WindowManager::render()
{
    ImGui::Render();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void WindowManager::swapBuffers()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

WindowManager::~WindowManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mWindow);
    glfwTerminate();
}
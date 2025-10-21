#include "Application.hpp"

int Application::init()
{
    mListManager.setListFromFile();
    if (!glfwInit()) return -1;

    mWindow = glfwCreateWindow(800, 600, "Checklist App", nullptr, nullptr);
    if (!mWindow)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(mWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = constants::IMGUI_INI_FILE;
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark(); // or Light()

    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init(constants::OPENGL_VERSION);

    return 0;
}

void Application::run()
{
    std::cout << "Print once" << std::endl;
    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Checklist");
        for (size_t i = 0; i < mListManager.getListSize(); ++i)
        {
            bool value = mListManager.getCompletedAt(i);
            if (ImGui::Checkbox(("##check" + std::to_string(i)).c_str(), &value)) // Invisible label
            {
                mListManager.setCompletedAt(i, value);
            }
            ImGui::SameLine();
            ImGui::InputText(("##task" + std::to_string(i)).c_str(), mListManager.getTasksAt(i), constants::BUFFER_SIZE);
            ImGui::SameLine();
            if (ImGui::Button(("X##" + std::to_string(i)).c_str())) {
                mListManager.eraseTasksAt(i);
                mListManager.eraseCompletedAt(i);
                --i;
            }
        }
        if (ImGui::Button("+")) {
            std::array<char, constants::BUFFER_SIZE> buf;
            strncpy(buf.data(), "New Task", sizeof(buf));
            mListManager.pushBackTasks(buf);
            mListManager.pushBackCompleted(0);
        }
        ImGui::End();

        ImGui::Render();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(mWindow);
    }
}

void Application::shutdown()
{
    mListManager.saveListToFile();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mWindow);
    glfwTerminate();
}
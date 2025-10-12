#include "Application.hpp"

Application::Application()
{
    std::ifstream in(constants::STATE_FILE);
    if (in.is_open() && in.peek() != std::ifstream::traits_type::eof()) {
        mTasks.clear();
        mCompleted.clear();

        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            int doneInt;
            std::string task;

            if (!(iss >> doneInt)) continue;  // Skip malformed lines
            std::getline(iss, task);
            if (task.empty()) continue;

            mCompleted.push_back(static_cast<uint8_t>(doneInt));
            std::array<char, constants::BUFFER_SIZE> buf;
            strncpy(buf.data(), task.substr(1).c_str(), constants::BUFFER_SIZE);  // Remove leading space
            mTasks.push_back(buf);
        }
    }
    else
    {
        std::vector<std::string> defaultTasks = { "Write code", "Test app", "Refactor UI" };
        // Initialize editable buffers
        for (const auto& task : defaultTasks) {
            std::array<char, constants::BUFFER_SIZE> buf;
            strncpy(buf.data(), task.c_str(), sizeof(buf));
            mTasks.push_back(buf);
        }
        std::vector<uint8_t> defaultCompleted(defaultTasks.size(), 0);
        mCompleted = defaultCompleted;
    }
}

int Application::init()
{
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
    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Checklist");
        for (size_t i = 0; i < mTasks.size(); ++i)
        {
            bool value = mCompleted.at(i);
            if (ImGui::Checkbox(("##check" + std::to_string(i)).c_str(), &value)) // Invisible label
            {
                mCompleted.at(i) = value;
            }
            ImGui::SameLine();
            ImGui::InputText(("##task" + std::to_string(i)).c_str(), mTasks.at(i).data(), constants::BUFFER_SIZE);
            ImGui::SameLine();
            if (ImGui::Button(("X##" + std::to_string(i)).c_str())) {
                mTasks.erase(mTasks.begin() + i);
                mCompleted.erase(mCompleted.begin() + i);
                --i;
            }
        }
        if (ImGui::Button("+")) {
            std::array<char, constants::BUFFER_SIZE> buf;
            strncpy(buf.data(), "New Task", sizeof(buf));
            mTasks.push_back(buf);
            mCompleted.push_back(0);
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
    // Save state before closing
    std::ofstream out(constants::STATE_FILE);
    for (size_t i = 0; i < mTasks.size(); ++i)
    {
        out << static_cast<int>(mCompleted.at(i)) << " " << mTasks.at(i).data() << "\n";
    }
    out.close();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mWindow);
    glfwTerminate();
}
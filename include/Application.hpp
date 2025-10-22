#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include "WindowManager.hpp"
#include "constants.hpp"

class Application
{
    private:
        std::unique_ptr<WindowManager> mWindowManager;
    public:
        Application() : mWindowManager(std::make_unique<WindowManager>()) {}
        void init();
        void run();
        void shutdown();
};
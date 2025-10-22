#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include "ListManager.hpp"
#include "WindowManager.hpp"
#include "constants.hpp"

class Application
{
    private:
        std::unique_ptr<ListManager> mListManager;
        std::unique_ptr<WindowManager> mWindowManager;
    public:
        Application() : 
            mListManager(std::make_unique<ListManager>(constants::STATE_FILE)), 
            mWindowManager(std::make_unique<WindowManager>()) {}
        void init();
        void run();
        void shutdown();
};
#pragma once

#include <array>
#include <string>
#include <vector>
#include <cstdint>
#include "constants.hpp"

class ListManager
{
    private:
        std::string mFilename;
        std::vector<std::array<char, constants::BUFFER_SIZE>> mTasks;
        std::vector<uint8_t> mCompleted;
    public:
        ListManager(std::string file);
        void setListFromFile();
        void saveListToFile();

        size_t getListSize();

        // Interactions with mCompleted list
        uint8_t getCompletedAt(size_t idx);
        void setCompletedAt(size_t idx, bool value);
        void eraseCompletedAt(size_t idx);
        void pushBackCompleted(bool value);

        // Interactions with mTasks list
        char* getTasksAt(size_t idx);
        void eraseTasksAt(size_t idx);
        void pushBackTasks(std::array<char, constants::BUFFER_SIZE> value);
};
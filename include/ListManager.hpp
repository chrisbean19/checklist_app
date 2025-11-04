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
        std::vector<std::string> mTasks;
        std::vector<std::array<char, constants::BUFFER_SIZE>> mEditableTasks;
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
        void swapCompleted(size_t idx1, size_t idx2);

        // Interactions with mTasks list
        std::string getTasksAt(size_t idx);
        void setTasksAt(size_t idx, std::string value);
        void eraseTasksAt(size_t idx);
        void pushBackTasks(std::string value);
        void swapTasks(size_t idx1, size_t idx2);

        // Interactions with mEditableTasks list
        char* getEditableTasksAt(size_t idx);
        void pushBackEditableTasks(std::array<char, constants::BUFFER_SIZE> value);
        void swapEditableTasks(size_t idx1, size_t idx2);
};
#include "ListManager.hpp"
#include <fstream>
#include <cstring>
#include <sstream>
#include <array>

ListManager::ListManager(std::string file) : mFilename(file)
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

void ListManager::setListFromFile()
{
    std::ifstream in(mFilename);
    if (in.is_open() && in.peek() != std::ifstream::traits_type::eof())
    {
        mTasks.clear();
        mCompleted.clear();

        std::string line;
        while (std::getline(in, line))
        {
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
}

void ListManager::saveListToFile()
{
    // Save state before closing
    std::ofstream out(mFilename);
    for (size_t i = 0; i < mTasks.size(); ++i)
    {
        out << static_cast<int>(mCompleted.at(i)) << " " << mTasks.at(i).data() << "\n";
    }
    out.close();
}

size_t ListManager::getListSize()
{
    return mTasks.size();
}

uint8_t ListManager::getCompletedAt(size_t idx)
{
    return mCompleted.at(idx);
}
        
void ListManager::setCompletedAt(size_t idx, bool value)
{
    mCompleted.at(idx) = value;
}

void ListManager::eraseCompletedAt(size_t idx)
{
    mCompleted.erase(mCompleted.begin() + idx);
}

void ListManager::pushBackCompleted(bool value)
{
    mCompleted.push_back(value);
}

char* ListManager::getTasksAt(size_t idx)
{
    return mTasks.at(idx).data();
}

void ListManager::eraseTasksAt(size_t idx)
{
    mTasks.erase(mTasks.begin() + idx);
}

void ListManager::pushBackTasks(std::array<char, constants::BUFFER_SIZE> value)
{
    mTasks.push_back(value);
}

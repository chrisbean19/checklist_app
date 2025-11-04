#include "ListManager.hpp"
#include <fstream>
#include <cstring>
#include <sstream>
#include <array>

ListManager::ListManager(std::string file) : mFilename(file)
{
    mTasks = { "Write code", "Test app", "Refactor UI" };
    // Initialize editable buffers
    for (const auto& task : mTasks)
    {
        std::array<char, constants::BUFFER_SIZE> buf{};
        std::snprintf(buf.data(), buf.size(), "%s", task.c_str());
        mEditableTasks.push_back(buf);
    }
    std::vector<uint8_t> defaultCompleted(mTasks.size(), 0);
    mCompleted = defaultCompleted;
}

void ListManager::setListFromFile()
{
    std::ifstream in(mFilename);
    if (in.is_open() && in.peek() != std::ifstream::traits_type::eof())
    {
        mTasks.clear();
        mEditableTasks.clear();
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
            mTasks.push_back(task.substr(1));
            std::array<char, constants::BUFFER_SIZE> buf{};
            std::snprintf(buf.data(), buf.size(), "%s", task.substr(1).c_str());  // Remove leading space
            mEditableTasks.push_back(buf);
        }
    }
}

void ListManager::saveListToFile()
{
    // Save state before closing
    std::ofstream out(mFilename);
    for (size_t i = 0; i < mTasks.size(); ++i)
    {
        out << static_cast<int>(mCompleted.at(i)) << " " << mTasks.at(i) << "\n";
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

void ListManager::swapCompleted(size_t idx1, size_t idx2)
{
    std::swap(mCompleted.at(idx1), mCompleted.at(idx2));
}

std::string ListManager::getTasksAt(size_t idx)
{
    return mTasks.at(idx);
}

void ListManager::setTasksAt(size_t idx, std::string value)
{
    mTasks.at(idx) = value;
}

void ListManager::eraseTasksAt(size_t idx)
{
    mTasks.erase(mTasks.begin() + idx);
}

void ListManager::pushBackTasks(std::string value)
{
    mTasks.push_back(value);
}

void ListManager::swapTasks(size_t idx1, size_t idx2)
{
    std::swap(mTasks.at(idx1), mTasks.at(idx2));
}

char* ListManager::getEditableTasksAt(size_t idx)
{
    return mEditableTasks.at(idx).data();
}

void ListManager::pushBackEditableTasks(std::array<char, constants::BUFFER_SIZE> value)
{
    mEditableTasks.push_back(value);
}

void ListManager::swapEditableTasks(size_t idx1, size_t idx2)
{
    std::swap(mEditableTasks.at(idx1), mEditableTasks.at(idx2));
}

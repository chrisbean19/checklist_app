#include "Application.hpp"
#include <memory>

int main()
{
    std::unique_ptr<Application> checklist = std::make_unique<Application>();

    checklist->run();

    return 0;
}
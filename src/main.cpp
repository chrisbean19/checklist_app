#include "Application.hpp"

int main()
{
    Application checklist;

    checklist.init();

    checklist.run();

    checklist.shutdown();

    return 0;
}
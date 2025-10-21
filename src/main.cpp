#include "Application.hpp"
#include "constants.hpp"

int main()
{
    Application checklist;

    checklist.init();

    checklist.run();

    checklist.shutdown();

    return 0;
}
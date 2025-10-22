#include "Application.hpp"

void Application::run()
{
    while (!mWindowManager->windowShouldClose())
    {
        mWindowManager->startNewFrame();

        mWindowManager->buildUI();

        mWindowManager->render();

        mWindowManager->swapBuffers();
    }
}

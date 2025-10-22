#include "Application.hpp"

void Application::init()
{
    mListManager->setListFromFile();
}

void Application::run()
{
    while (!mWindowManager->windowShouldClose())
    {
        mWindowManager->startNewFrame();

        mWindowManager->buildUI(mListManager);

        mWindowManager->render();
        
        mWindowManager->swapBuffers();
    }
}

void Application::shutdown()
{
    mListManager->saveListToFile();
}
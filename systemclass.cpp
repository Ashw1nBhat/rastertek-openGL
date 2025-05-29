////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"


SystemClass::SystemClass()
{
    m_Input = 0;
    m_Application = 0;
}


SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize()
{
    int screenWidth = 0, screenHeight = 0;
    bool result;

    // Create and initailize the Input object
    m_Input = new InputClass;
    m_input->Initialize();

    // Initialize the screen dimensions
    screenHeight = 0;
    screenWidth = 0;

    // Initialize the X11 window
    result = InitializeWindow(screenWidth, screenHeight);
    if(!result)
    {
        return false;
    }

    // Create and initialize the Application object
    m_Application = new ApplicationClass;
    result = m_Application->Initialize(m_videoDisplay, m_hwnd, screenWidth, screenHeight);
    if(!result)
    {
        return false;
    }

    return true;
}


void SystemClass::Shutdown()
{
    // Release and clean up the Application object
    if(m_Application)
    {
        m_Application->Shutdown();
        delete m_Application;
        m_Application = 0;
    }

    // Release the X11 window
    ShutdownWindow();

    // Release and clean up the input object
    if(m_Input)
    {
        delete m_Input;
        m_Input = 0;
    }
    return;
}


void SystemClass::Frame()
{
    bool done, result;

    // Loop until the application is finished running
    done = false;
    while(!done)
    {
        // Read the X11 input
        ReadInput();

        // Do the frame processing for the application object
        result = m_Application->Frame(m_Input);
        if(!result)
        {
            done = true;
        }
    }
    return;
}

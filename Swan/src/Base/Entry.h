#pragma once
#ifdef SWAN_ENTRY_POINT
#include "pch.h"
#include "Application.h"

#include <iostream>

extern Swan::Application* Swan::CreateApplication();

int main()
{

    Swan::Application* app = Swan::CreateApplication();
    app->Init();
    app->Run();

    delete app;

    return 0;
}
#endif

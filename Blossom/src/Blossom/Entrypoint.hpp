#pragma once

// To be defined by user.
extern Blossom::Application* Blossom::CreateApplication(int argc, char* argv[]);

#if !defined(BL_DIST) // Non Dist build on all Platforms

int main(int argc, char* argv[])
{
	Blossom::Application* app = Blossom::CreateApplication(argc, argv);
	app->Run();
	delete app;
	return 0;
}

#elif defined(BL_PLATFORM_WINDOWS) // Dist on Windows
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	Blossom::Application* app = Blossom::CreateApplication(__argc, __argv);
    app->Run();
    delete app;
    return 0;
} 
#else // Dist on all other platforms // Maybe fix this? Or maybe this works? // TODO(Jorben): Test this on MacOS and Linux

int main(int argc, char* argv[])
{
	Blossom::Application* app = Blossom::CreateApplication(argc, argv);
	app->Run();
	delete app;
	return 0;
}

#endif

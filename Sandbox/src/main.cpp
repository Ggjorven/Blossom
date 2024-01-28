#include <Blossom/Core/Application.hpp>
#include <Blossom/Entrypoint.hpp>

// Create your own application class
class Sandbox : public Blossom::Application
{
public:
	Sandbox(const Blossom::AppInfo& appInfo)
		: Blossom::Application(appInfo)
	{
		// Add your own custom layers/overlays
	}
};

// ----------------------------------------------------------------
//                    Set Application specs here...
// ----------------------------------------------------------------
Blossom::Application* Blossom::CreateApplication(int argc, char* argv[])
{
	AppInfo appInfo(argc, argv);
	appInfo.WindowProperties.Name = "Custom";
	appInfo.WindowProperties.VSync = false;

	return new Sandbox(appInfo);
}
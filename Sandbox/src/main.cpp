#include <Blossom/Core/Application.hpp>
#include <Blossom/Entrypoint.hpp>

// Create your own application class
class Sandbox : public VkApp::Application
{
public:
	Sandbox(const VkApp::AppInfo& appInfo)
		: VkApp::Application(appInfo)
	{
		// Add your own custom layers/overlays
	}
};



// ----------------------------------------------------------------
//                    Set Application specs here...
// ----------------------------------------------------------------
VkApp::Application* VkApp::CreateApplication(int argc, char* argv[])
{
	AppInfo appInfo;
	appInfo.ArgCount = argc;
	appInfo.Args = argv;

	// Add more application specs...
	appInfo.WindowProperties.Name = "Custom";
	appInfo.WindowProperties.VSync = false;

	return new Sandbox(appInfo);
}
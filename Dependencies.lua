VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLEW"] = "%{wks.location}/vendor/GLEW/include"
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"
IncludeDir["ImGui"] = "%{wks.location}/vendor/ImGui"
IncludeDir["spdlog"] = "%{wks.location}/vendor/spdlog/include"
IncludeDir["stb_image"] = "%{wks.location}/vendor/stb_image/include"
IncludeDir["glm"] = "%{wks.location}/vendor/glm"
IncludeDir["assimp"] = "%{wks.location}/vendor/assimp/include"
IncludeDir["tracy"] = "%{wks.location}/vendor/tracy/tracy/public"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["VMA"] = "%{wks.location}/vendor/VulkanMemoryAllocator/include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}

Library["OpenGL"] = "opengl32.lib"
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

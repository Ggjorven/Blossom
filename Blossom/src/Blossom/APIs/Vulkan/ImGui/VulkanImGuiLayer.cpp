#include "blpch.h"
#include "VulkanImGuiLayer.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_vulkan.h>

#include "Blossom/Core/Application.hpp"
#include "Blossom/Core/Logging.hpp"
#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/Vulkan/VulkanManager.hpp"
#include "Blossom/APIs/Vulkan/VulkanContext.hpp"
#include "Blossom/APIs/Vulkan/VulkanActions.hpp"
#include "Blossom/APIs/Vulkan/VulkanRenderer.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanHelper.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanResources.hpp"

#include <GLFW/glfw3.h>

namespace Blossom
{

	void VulkanImGuiLayer::OnAttach()
	{
		CreateDescriptorPool();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForVulkan(window, true);

		auto& deviceInfo = VulkanManager::GetDeviceInfo();
		auto& swapchainInfo = VulkanManager::GetSwapChainInfo();
		auto& resourceInfo = VulkanManager::GetResourceInfo();

		ImGui_ImplVulkan_InitInfo  initInfo = {};
		initInfo.Instance = deviceInfo.Instance;
		initInfo.PhysicalDevice = deviceInfo.PhysicalDevice;
		initInfo.Device = deviceInfo.Device;
		initInfo.QueueFamily = VulkanHelper::QueueFamilyIndices::Find(VulkanContext::Get()->GetInstance(), deviceInfo.PhysicalDevice).GraphicsFamily.value();
		initInfo.Queue = deviceInfo.GraphicsQueue;
		//initInfo.PipelineCache = vkPipelineCache;
		initInfo.DescriptorPool = m_DescriptorPool;
		initInfo.Allocator = nullptr; // Optional, use nullptr to use the default allocator
		initInfo.MinImageCount = static_cast<uint32_t>(swapchainInfo.SwapChainImageViews.size());
		initInfo.ImageCount = static_cast<uint32_t>(swapchainInfo.SwapChainImageViews.size());
		initInfo.CheckVkResultFn = nullptr; // Optional, a callback function for Vulkan errors
		//init_info.MSAASamples = vkMSAASamples; // The number of samples per pixel in case of MSAA
		//init_info.Subpass = 0; // The index of the subpass where ImGui will be drawn

		// TODO(Jorben): Create some sort of renderpass for ImGui
		ImGui_ImplVulkan_Init(&initInfo, VulkanContext::Get()->GetResources()->GetRenderPasses()[0]->m_RenderPass);

		// Create fonts
		io.Fonts->AddFontDefault();
		{
			VkCommandBuffer commandBuffer = VulkanActions::BeginSingleTimeCommands();
			ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
			VulkanActions::EndSingleTimeCommands(commandBuffer);

			ImGui_ImplVulkan_DestroyFontUploadObjects();
		}
	}

	void VulkanImGuiLayer::OnDetach()
	{
		vkDeviceWaitIdle(VulkanManager::GetDeviceInfo().Device);

		vkDestroyDescriptorPool(VulkanManager::GetDeviceInfo().Device, m_DescriptorPool, nullptr);

		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void VulkanImGuiLayer::Begin()
	{
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void VulkanImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2((float)Application::Get().GetWindow().GetWidth(), (float)Application::Get().GetWindow().GetHeight());

		auto& resourceInfo = VulkanManager::GetResourceInfo();

		// Rendering
		ImGui::Render();
		Renderer::AddToUIQueue([this]() {
			auto& resourceInfo = VulkanManager::GetResourceInfo();

			ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), resourceInfo.CommandBuffers[VulkanRenderer::GetCurrentFrame()]);
			});

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void VulkanImGuiLayer::CreateDescriptorPool()
	{
		std::vector<VkDescriptorPoolSize> poolSizes =
		{
			{ VK_DESCRIPTOR_TYPE_SAMPLER, 10 },
			{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 50 }, // Important for ImGui
			{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 10 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 10 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 10 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 10 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 10 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 10 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 10 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 10 },
			{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 10 }
		};

		VkDescriptorPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data();
		poolInfo.maxSets = static_cast<uint32_t>(BL_MAX_FRAMES_IN_FLIGHT); // Amount of sets?

		if (vkCreateDescriptorPool(VulkanManager::GetDeviceInfo().Device, &poolInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS)
			BL_LOG_ERROR("Failed to create descriptor pool!");
	}

}
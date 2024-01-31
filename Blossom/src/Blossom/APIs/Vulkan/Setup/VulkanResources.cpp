#include "blpch.h"
#include "VulkanResources.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/Vulkan/VulkanManager.hpp"
#include "Blossom/APIs/Vulkan/VulkanContext.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanHelper.hpp"

namespace Blossom
{

    VulkanResources::VulkanResources()
    {
        CreateCommandPool();
        CreateCommandBuffers();
        CreateSyncObjects();
    }

    VulkanResources::~VulkanResources()
    {
        VulkanDeviceInfo& info = VulkanManager::GetDeviceInfo();

        for (size_t i = 0; i < BL_MAX_FRAMES_IN_FLIGHT; i++)
        {
            vkDestroySemaphore(info.Device, m_RenderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(info.Device, m_ImageAvailableSemaphores[i], nullptr);
            vkDestroyFence(info.Device, m_InFlightFences[i], nullptr);
        }

        // Note(Jorben): This is not necessary since the commandbuffers would be automatically free'd when free'ing the commandpool
        // I prefer it this way since it's clearer to see when they are created and destroyed.
        for (size_t i = 0; i < BL_MAX_FRAMES_IN_FLIGHT; i++)
            vkFreeCommandBuffers(info.Device, m_CommandPool, 1, &m_CommandBuffers[i]);

        vkDestroyCommandPool(info.Device, m_CommandPool, nullptr);
    }

    void VulkanResources::AddRenderPass(VulkanRenderPass* renderpass)
    {
        m_RenderPasses.push_back(renderpass);
    }

    void VulkanResources::RecreateFramebuffers()
    {
        // ... TODO for loop all renderpasses recreate
    }

    void VulkanResources::CreateCommandPool()
    {
        VulkanDeviceInfo& info = VulkanManager::GetDeviceInfo();

        VulkanHelper::QueueFamilyIndices queueFamilyIndices = VulkanHelper::QueueFamilyIndices::Find(VulkanContext::Get()->GetInstance(), info.PhysicalDevice);

        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueFamilyIndices.GraphicsFamily.value();

        if (vkCreateCommandPool(info.Device, &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS)
            BL_LOG_ERROR("Failed to create command pool!");
    }

    void VulkanResources::CreateCommandBuffers()
    {
        VulkanDeviceInfo& info = VulkanManager::GetDeviceInfo();

        m_CommandBuffers.resize(BL_MAX_FRAMES_IN_FLIGHT);

        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = m_CommandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t)m_CommandBuffers.size();

        if (vkAllocateCommandBuffers(info.Device, &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS)
            BL_LOG_ERROR("Failed to allocate command buffers!");
    }

    void VulkanResources::CreateSyncObjects()
    {
        VulkanDeviceInfo& info = VulkanManager::GetDeviceInfo();

        m_ImageAvailableSemaphores.resize(BL_MAX_FRAMES_IN_FLIGHT);
        m_RenderFinishedSemaphores.resize(BL_MAX_FRAMES_IN_FLIGHT);
        m_InFlightFences.resize(BL_MAX_FRAMES_IN_FLIGHT);

        VkSemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo = {};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < BL_MAX_FRAMES_IN_FLIGHT; i++)
        {
            if (vkCreateSemaphore(info.Device, &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(info.Device, &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(info.Device, &fenceInfo, nullptr, &m_InFlightFences[i]) != VK_SUCCESS)
            {
                BL_LOG_ERROR("Failed to create synchronization objects for a frame!");
            }
        }
    }

}
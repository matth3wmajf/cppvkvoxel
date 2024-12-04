#include <memory>
#include <cstdint>
#include <iostream>
#include <stdexcept>

#include <vulkan/vulkan.h>

#include <cppvkvoxel/engine.hpp>
#include <vulkan/vulkan_core.h>

cppvkvoxel::engine::engine(window *pa_window, std::vector<std::string> a_required_extensions, std::vector<std::string> a_required_layers) : pm_window(pa_window), l_required_extensions(a_required_extensions), l_required_layers(a_required_layers)
{
	/* Check if the window is nullified. */
	if(this->pm_window == nullptr) throw std::runtime_error("Couldn't create engine, nullified window!");

	/* Fill out the structure representing the application. */
	VkApplicationInfo l_application_info = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "cppvkvoxel",
		.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName = "No Engine",
		.engineVersion = VK_MAKE_VERSION(1, 0, 0),
		.apiVersion = VK_API_VERSION_1_3
	};

	/* Get the extensions required by the window class. */
	std::vector<std::string> l_window_required_extensions;
	cppvkvoxel::window::get_required_extensions(&l_window_required_extensions);

	/* Append these extensions to the overall required extensions. */
	this->l_required_extensions.insert(l_required_extensions.end(), this->l_required_extensions.begin(), this->l_required_extensions.end());

	/* Append the debug-related extension & layer. */
	this->l_required_extensions.push_back("VK_EXT_debug_utils");
	this->l_required_layers.push_back("VK_LAYER_KHRONOS_validation");

	/* Convert the vectors to C strings. */
	auto l_extensions = std::make_unique<const char*[]>(this->l_required_extensions.size());
	for(uintmax_t l_i = 0; l_i < this->l_required_extensions.size(); l_i++) l_extensions[l_i] = this->l_required_extensions[l_i].c_str();
	auto l_layers = std::make_unique<const char*[]>(this->l_required_layers.size());
	for(uintmax_t l_i = 0; l_i < this->l_required_layers.size(); l_i++) l_layers[l_i] = this->l_required_layers[l_i].c_str();

	/* Fill out the structure required to create an instance. */
	VkInstanceCreateInfo l_instance_create_info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &l_application_info,
		.enabledLayerCount = static_cast<uint32_t>(this->l_required_layers.size()),
		.ppEnabledLayerNames = l_layers.get(),
		.enabledExtensionCount = static_cast<uint32_t>(this->l_required_extensions.size()),
		.ppEnabledExtensionNames = l_extensions.get()
	};

	/* Create the instance. */
	if(vkCreateInstance(&l_instance_create_info, nullptr, &this->l_instance) != VK_SUCCESS) throw std::runtime_error("Couldn't create engine, failed to create instance!");

	/* Load the function required to create a debug messenger. */
	PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(l_instance, "vkCreateDebugUtilsMessengerEXT");

	/* Fill out the structure required to create a debug messenger. */
	VkDebugUtilsMessengerCreateInfoEXT l_debug_utils_messenger_create_info = {
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
		.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
		.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
		.pfnUserCallback = [](VkDebugUtilsMessageSeverityFlagBitsEXT a_message_severity, VkDebugUtilsMessageTypeFlagsEXT a_message_type, const VkDebugUtilsMessengerCallbackDataEXT *pa_callback_data, void *pa_user_data) -> VkBool32 {
			if(a_message_severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
			{
				std::cerr << pa_callback_data->pMessage << std::endl;
				throw std::runtime_error("Encountered a validation layer error!");
			}
			
			return VK_FALSE;
		}
	};

	/* Create the debug messenger. */
	if(vkCreateDebugUtilsMessengerEXT(this->l_instance, &l_debug_utils_messenger_create_info, NULL, &this->l_debug_messenger) != VK_SUCCESS) throw std::runtime_error("Couldn't create engine, failed to create debug messenger!");
}

cppvkvoxel::engine::~engine()
{
	/* Load the function required to destroy a debug messenger. */
	PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(l_instance, "vkDestroyDebugUtilsMessengerEXT");
	
	/* Destroy the debug messenger. */
	vkDestroyDebugUtilsMessengerEXT(this->l_instance, this->l_debug_messenger, nullptr);

	/* Destroy the instance. */
	vkDestroyInstance(this->l_instance, nullptr);
}
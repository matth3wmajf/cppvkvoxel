#pragma once

#include <vector>
#include <string>

#include <vulkan/vulkan.h>

#include <cppvkvoxel/window.hpp>

namespace cppvkvoxel
{
	class engine
	{
	private:
		/* The instance handle. */
		VkInstance l_instance;

		/* The debug messenger. */
		VkDebugUtilsMessengerEXT l_debug_messenger;

		/* The required extension(s). */
		std::vector<std::string> l_required_extensions;

		/* The required layer(s). */
		std::vector<std::string> l_required_layers;
	public:
		/* Declare the window class as a friend class. */
		friend class window;

		/* The window class. */
		window *pm_window;

		engine(window *pa_window, std::vector<std::string> a_required_extensions = {}, std::vector<std::string> a_required_layers = {});

		~engine();
	};
};
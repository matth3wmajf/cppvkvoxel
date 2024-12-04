#pragma once

#include <string>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cppvkvoxel/engine.hpp>

namespace cppvkvoxel
{
	class window
	{
	private:
		/* The window handle. */
		GLFWwindow *pl_window;

		/* The width & height of the window. */
		int l_width, l_height;

		/* The title of the window. */
		std::string l_title;
	public:
		/* Declare the engine class as a friend class. */
		friend class engine;

		/* The function for getting the available instance extension(s). */
		static void get_required_extensions(std::vector<std::string> *required_extensions)
		{
			/* How many extension(s) will be returned? */
			uint32_t l_glfw_extension_count = 0;

			/* Where do we store the extension(s)? */
			const char **ppl_glfw_extensions;

			/* Get the instance extension(s) required by GLFW. */
			ppl_glfw_extensions = glfwGetRequiredInstanceExtensions(&l_glfw_extension_count);

			/* Define the vector of string(s) that will be returned. */
			std::vector<std::string> l_required_extensions(ppl_glfw_extensions, ppl_glfw_extensions + l_glfw_extension_count);

			/* Return the vector of string(s). */
			*required_extensions = l_required_extensions;
		}

		window();
		window(uintmax_t a_width, uintmax_t a_height);
		window(uintmax_t a_width, uintmax_t a_height, std::string a_title);
		window(std::string a_title);

		~window();
	};
};
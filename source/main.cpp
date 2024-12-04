#include <string>
#include <vector>
#include <memory>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cppvkvoxel/window.hpp>
#include <cppvkvoxel/engine.hpp>

int main(int argc, const char *argv[])
{
	/* Initialize GLFW. */
	glfwInit();

	/*
	 *	Register GLFW's termination to be called at the end of the program's
	 *	scope.
	 */
	auto l_glfw_runtime = std::unique_ptr<void, void(*)(void*)>(nullptr, [](void*) {
		glfwTerminate();
	});

	/* Create a window. */
	cppvkvoxel::window l_window(1920, 1080, "Window");

	/* Create an engine. */
	cppvkvoxel::engine l_engine(&l_window);

	return 0;
}
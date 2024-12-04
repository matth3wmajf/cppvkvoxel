#pragma once

#include <vector>

#include <cppvkvoxel/window.hpp>
#include <cppvkvoxel/engine.hpp>

namespace cppvkvoxel
{
	class render
	{
	private:
		/* The shader bytecode. */
		std::vector<std::byte> l_shader_bytecode;

		/* The physical device index. */
		uintmax_t l_physical_device_index;
	public:
		/* Declare the window class and the engine class as friend classes. */
		friend class window;
		friend class engine;

		/* The window class. */
		window *pm_window;

		/* The engine class. */
		engine *pm_engine;

		render(window *pa_window, engine *pa_engine, std::vector<std::byte> a_shader_bytecode, uintmax_t a_physical_device_index = 0);
		~render();
	}
}
#include <cstdint>
#include <stdexcept>

#include <cppvkvoxel/render.hpp>
#include <cppvkvoxel/window.hpp>

#include <vulkan/vulkan.h>

cppvkvoxel::render::render(window *pa_window, engine *pa_engine, std::vector<std::byte> a_shader_bytecode, uintmax_t a_physical_device_index) : pm_window(pa_window), pm_engine(pa_engine), l_shader_bytecode(a_shader_bytecode), l_physical_device_index(a_physical_device_index)
{
	/* Check if the window is nullified. */
	if(this->pm_window == nullptr) throw std::runtime_error("Couldn't create render, nullified window!");

	/* Check if the engine is nullified. */
	if(this->pm_engine == nullptr) throw std::runtime_error("Couldn't create render, nullified engine!");

	
}

cppvkvoxel::render::~render()
{

}
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cppvkvoxel/window.hpp>

cppvkvoxel::window::window() : l_width(1920), l_height(1080), l_title("Window")
{
	this->pl_window = glfwCreateWindow(this->l_width, this->l_height, this->l_title.c_str(), nullptr, nullptr);
}

cppvkvoxel::window::window(uintmax_t a_width, uintmax_t a_height) : l_width(a_width), l_height(a_height), l_title("Window")
{
	this->pl_window = glfwCreateWindow(this->l_width, this->l_height, this->l_title.c_str(), nullptr, nullptr);
}

cppvkvoxel::window::window(uintmax_t a_width, uintmax_t a_height, std::string a_title) : l_width(a_width), l_height(a_height), l_title(a_title)
{
	this->pl_window = glfwCreateWindow(this->l_width, this->l_height, this->l_title.c_str(), nullptr, nullptr);
}

cppvkvoxel::window::window(std::string a_title) : l_width(1920), l_height(1080), l_title(a_title)
{
	this->pl_window = glfwCreateWindow(this->l_width, this->l_height, this->l_title.c_str(), nullptr, nullptr);
}

cppvkvoxel::window::~window()
{
	glfwDestroyWindow(this->pl_window);
}
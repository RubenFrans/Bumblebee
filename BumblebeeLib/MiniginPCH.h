#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#pragma comment(lib, "xinput.lib")

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push, 1)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

#include "Components/BaseComponent.h"
#include "Components/RenderComponent/RenderComponent.h"
#include "Components/TransformComponent/TransformComponent.h"

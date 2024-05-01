#pragma once

#include "SME_Variables.h"
#include "Utils/Color.h"
#include "Utils/Log.h"
#include "SDL.h"
#include "SME_FuncLibrary.h"
#include <glm/glm.hpp>

#define CHECK(x, ...) { if(!(x)) { TETRIS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
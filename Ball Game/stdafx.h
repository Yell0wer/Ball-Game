#pragma once
#define GLEW_STATIC
typedef unsigned int uint;
// std libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <set>
#include <cstdint>
#include <typeinfo>

// other libraries
#include "SDL.h"
#include "glew.h"
#include "Math.h"
#include "SOIL2.h"
#include "box2d.h"

// headers
#include "Component.h"
#include "SpriteComponent.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Actor.h"
#include "DynamicActor.h"
#include "StaticActor.h"
#include "Texture.h"
#include "Projectile.h"
#include "Player.h"
#include "ControllerComponent.h"
#include "Block.h"
#include "Crate.h"
#include "Camera.h"
#include "Game.h"

// TODO: enemies bg animation refinecamera ui audio
// organize headers?
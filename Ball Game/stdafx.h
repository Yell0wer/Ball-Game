#pragma once
#define GLEW_STATIC
typedef unsigned int uint;
// std libraries
#include <map>
#include <unordered_map>
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
#include "Texture.h"
#include "SpriteComponent.h"
#include "AnimatedSpriteComponent.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Actor.h"
#include "DynamicActor.h"
#include "StaticActor.h"
#include "Character.h"
#include "Projectile.h"
#include "Player.h"
#include "ControllerComponent.h"
#include "Block.h"
#include "Crate.h"
#include "Camera.h"
#include "ContactListener.h"
#include "Game.h"
#include "Enemy.h"


// TODO: enemies bg refinecamera particlefx ui audio
// organize headers?
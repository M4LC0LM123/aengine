#pragma once

// Data types
#include "../ArrayList.cpp"

// box2D -> 2D physics
#include "box2d.h"

// sol2 -> lua scripting
#include "../../include/sol/sol.hpp"
#include "cassert"

// config 
#include "config.h"

// enums 
#include "BodyType.h" // box2D to Engine physics
#include "ParticleBehaviour.h" // particle behaviour 
#include "ParticleSpawnType.h" // particle spawn shape
#include "AudioType.h" // audio types (Music or sound)

// Quad tree
#include "../QuadTree.cpp"

// ecs
#include "../Entity.cpp"
#include "../Component.cpp"
#include "../ScriptComponent.cpp"
#include "../AmbientAudio.cpp"
#include "../Collider.cpp"
#include "../BoxCollider.cpp"
#include "../CircleCollider.cpp"
#include "../Object.cpp"
#include "../Body.cpp"
#include "../KinematicBody.cpp"
#include "../RigidBody.cpp"
#include "../StaticBody.cpp"
#include "../Sprite.cpp"
#include "../Bloom.cpp"
#include "../PhysicsBody.cpp"
#include "../EntityManager.cpp"

// 3D
#include "Render3D.h"
#include "../PerspectiveCamera.cpp"

// object pooling
#include "../ObjectPool.cpp"

// toolbox
#include "toolbox.h"

// animation
#include "Animation.h"

// tilemap
#include "loadArray.h"
#include "TileMap.h"

// particle system
#include "../ParticleSystem.cpp"

// camera2D
#include "../OrthographicCamera.cpp"
#include "../Camera.cpp"

// prefab 
#include "Prefab.h"

// debug and debug console
#include "../Debug.cpp"
#include "../Console.cpp"
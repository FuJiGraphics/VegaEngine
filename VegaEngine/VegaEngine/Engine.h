#pragma once

// Cores
#include "Core/System.h"
#include "Core/Layer/Layer.h"
#include "Core/Collider/Collider.h"
#include "Core/Camera/Camera.h"

// Frameworks
#include "Framework/ResourceManager.h"
#include "Framework/SceneManager.h"

// Utility
#include "Utility/Math.h"

// Objects
#include "Object/GameObject.h"

// Entry Point
#include "Core/EntryPoint.h"

// Animation
#include "Core/Animation/Anim.h"
#include "Core/Animation/AnimList.h"

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define	DSetClassName(className)	inline std::string GetName() const override { return(#className); }

enum class Direction
{
	Default,
	Left,
	Right,
};

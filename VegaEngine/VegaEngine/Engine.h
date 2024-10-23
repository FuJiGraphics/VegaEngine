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

// Entry Point
#include "Core/EntryPoint.h"

#define	DSetClassName(className)	inline std::string GetName() const override { return(#className); }

enum class Direction
{
	Default,
	Left,
	Right,
};

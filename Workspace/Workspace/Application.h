#pragma once

// Headers
#include "VegaEngine/Engine.h"

class Application : public fz::Layer
{
public:
	DSetClassName(Application);
	
	void			OnAttach() override;
	void			OnEvent(fz::Event& event) override;

public:
	bool	IsFirstStart() const;

private:
	bool	m_IsFirstStart;
};


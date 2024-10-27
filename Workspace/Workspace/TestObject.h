#pragma once

#include <VegaEngine2.h>

class TestObject : public fz::Object
{
public:
	TestObject();
	virtual ~TestObject();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnEvent(fz::Event& ev) override;
};


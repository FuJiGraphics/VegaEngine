#include "TestObject.h"

TestObject::TestObject()
	: Object("TestObject")
{
}

TestObject::~TestObject()
{
}

void TestObject::OnAttach()
{
	fz::Log.Info("TestObject::OnAttach()");
}

void TestObject::OnDetach()
{
	fz::Log.Info("TestObject::OnDetach()");
}

void TestObject::OnUpdate(float dt)
{

}

void TestObject::OnEvent(fz::Event& ev)
{
	if (fz::InputManager::IsKeyPressed(fz::KeyType::A))
	{
		fz::Log.Info("Key A");
	}

	if (fz::InputManager::IsMouseButtonPressed(fz::Button::Left))
	{
		fz::Log.Info("Left");
	}
	const auto& pos = fz::InputManager::GetMousePosition();
	fz::Log.Info("Mouse X:{0}, Y:{1}", pos.x, pos.y);
}

#pragma once
#include <VegaEngine2.h>

namespace fz {

	class BulletScript : public VegaScript
	{
	public:
		void OnCreate()
		{
		}

		void OnDestroy()
		{

		}

		void OnUpdate(float dt)
		{
		}

	};

} // namespace fz

BIND_SCRIPT(BulletScript, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Bullet", BulletScript);


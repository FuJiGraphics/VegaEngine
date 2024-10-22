#pragma once
#include "ColliderList.h"

namespace fz{

	class HitData
	{
	//// Delete, Enum, Using
	protected:
		// friend
		friend ColliderList;

	//// Member Functions
	public:
		// Impl
		std::string ClassName() const;

	protected:
		void SetLayer(Layer* layer);
		void SetCollider(Collider* collider);
		
		bool empty() const;
		void reset();

		// Constructor, Destructor
		HitData();
		HitData(const HitData& other);
		HitData(HitData&& other);
		HitData(Layer* layer, Collider* collider);
		virtual ~HitData();

		// operator
		HitData& operator=(const HitData& other);
		HitData& operator=(HitData&& other);
		bool operator==(const HitData& other);

		// inlines
		Collider* GetCollider() const { return m_Collider; }

	//// Member Variables
	private:
		Layer* m_Class;
		Collider* m_Collider;
	};

}
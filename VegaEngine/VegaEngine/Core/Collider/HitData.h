#pragma once

namespace fz{

	class Layer;
	class Collider;

	class HitData
	{
	//// Delete, Enum, Using
	protected:
		// Using
		using Super = HitData;

	//// Member Functions
	public:
		// Impl
		std::string ClassName() const;

	public:
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
		inline Collider* GetCollider() const	{ return m_Collider; }
		inline Layer* GetLayer()				{ return m_Class; }
		inline Layer* GetLayer() const			{ return m_Class; }

	//// Member Variables
	private:
		Layer* m_Class;
		Collider* m_Collider;
	};

}
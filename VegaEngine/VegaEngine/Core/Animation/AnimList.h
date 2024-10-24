#pragma once
#include "Anim.h"

namespace fz {
	class Window;

	class AnimList final
	{
	//// Delete, Enum, Using
	protected:
		// Using
		using Iter = typename MemoryPool<Anim>::iterator;
		using Const_iter = typename MemoryPool<Anim>::const_iterator;

		// delete
		AnimList(const AnimList&) = delete;
		AnimList& operator=(const AnimList&) = delete;

	//// Member Functions
	public:
		AnimList(const std::string& name);
		virtual ~AnimList();

		void Insert(const std::string& name, sf::Sprite& target);
		Anim& GetAnim(const std::string& name);

		void Update(float dt);
		void Draw(Camera& window);
		void SetActivated(bool enabled, const std::string& name);
		void SetActivatedAll(bool enabled);
		void SetRepeatAll(bool enabled);

		Anim& operator[](const std::string& name); 

		inline Iter begin()					{ return m_AnimList.begin(); }
		inline Iter end()					{ return m_AnimList.end(); }
		inline Const_iter begin() const		{ return m_AnimList.begin(); }
		inline Const_iter end() const		{ return m_AnimList.end(); }

	//// Member Variables
	private:
		std::string m_Name;
		MemoryPool<Anim> m_AnimList;
	};

} // namespace fz
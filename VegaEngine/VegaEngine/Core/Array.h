#pragma once
#include <vector>
#include <deque>

namespace fz {

	template <typename T>
	class Array
	{
	//// Delete, Enum, Using
	protected:
		// EnumClass
		enum class Section {
			Left, Right
		};

		// Using
		using Iter = std::deque<T>::iterator;
		using Const_iter = std::deque<T>::const_iterator;

		// Delete
		Array(Array&) = delete;
		void operator=(Array&) = delete;

	//// Member Functions
	public:
		// Constructor, Destructor
		Array();
		virtual	~Array();

		// Impl 
		void Insert(T data, Section place);
		Iter Remove(T data, Section place);
		Iter Find(const T& target);

		template <typename Fn>
		Array<T>::Iter Find(Iter first, Iter last, Fn pred);

		// Inlines
		inline bool Empty() const { return m_Array.empty(); }
		inline Iter begin() { return m_Array.begin(); }
		inline Iter end() { return m_Array.end(); }
		inline Const_iter begin() { return m_Array.begin(); };
		inline Const_iter end() { return m_Array.end(); };

	private:
		void InsertLeft(const T& data);
		void InsertRight(const T& data);
		Iter RemoveLeft(const T& data);
		Iter RemoveRight(const T& data);
		
	//// Member Variables
	private: 
		std::deque<T*> m_Array;
		Iter m_LeftEnd;
		unsigned int m_LeftSize;
		Iter m_RightBegin;
		unsigned int m_RightSize;
	};

} // namespace fz

#include "Array.hpp"
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
		using Super = Array<T>;
		using Iter = typename std::deque<T>::iterator;
		using Const_iter = typename std::deque<T>::const_iterator;

		// Delete
		Array(const Array&) = delete;
		void operator=(const Array&) = delete;

	//// Member Functions
	public:
		// Inlines
		inline Iter begin()				{ return m_Array.begin(); }
		inline Iter end()				{ return m_Array.end(); }
		inline Const_iter begin() const	{ return m_Array.begin(); }
		inline Const_iter end() const	{ return m_Array.end(); }
		inline bool empty() const		{ return m_Array.empty(); }
		inline int size() const			{ return m_Array.size(); }
		inline void clear()				{ m_Array.clear(); }

		template <typename Fn>
		Iter remove(Iter first, Iter last, Fn pred);

	protected:
		// Constructor, Destructor
		Array();
		virtual	~Array();

		// Impl 
		void insert(const T& data, Section place = Section::Right);
		Iter remove(const T& data, Section place = Section::Right);
		Iter find(const T& target);

		template <typename Fn>
		Iter find(Iter first, Iter last, Fn pred);
		void pop_front();

	private:
		void InsertLeft(const T& data);
		void InsertRight(const T& data);
		Iter RemoveLeft(const T& data);
		Iter RemoveRight(const T& data);
		
	//// Member Variables
	private: 
		std::deque<T> m_Array;
		unsigned int m_LeftSize;
	};

} // namespace fz

#include "Array.hpp"
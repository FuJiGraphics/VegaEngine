#pragma once
#include "Array.h"

namespace fz {

	template<typename T>
	inline Array<T>::Array()
		: m_Array()
		, m_LeftSize(0)
	{
		// Empty
	}

	template<typename T>
	inline Array<T>::~Array()
	{
		// Empty
	}

	template<typename T>
	inline void Array<T>::insert(const T& data, Section place)
	{
		switch (place)
		{
			case Section::Left: 
				this->InsertLeft(data);
				break;
			case Section::Right:
				this->InsertRight(data);
		}
	}

	template<typename T>
	inline typename Array<T>::Iter Array<T>::remove(T& data, Section place)
	{
		Iter result;
		switch (place)
		{
			case Section::Left:
				result = this->RemoveLeft(data);
				break;
			case Section::Right:
				result = this->RemoveRight(data);
		}
		return result;
	}

	template<typename T>
	inline typename Array<T>::Iter Array<T>::find(const T& target)
	{
		Array<T>::Iter iter = m_Array.begin();
		for (auto layer : m_Array)
		{
			if (layer == target)
			{
				break;
			}
			iter++;
		}
		return iter;
	}

	template<typename T>
	template<typename Fn>
	inline typename Array<T>::Iter Array<T>::remove(Iter first, Iter last, Fn pred)
	{
		Iter result = first;
		for (result; result != last; ++result)
		{
			if (pred(*result))
			{
				m_Array.erase(result);
				break;
			}
		}
		return result;
	}

	template<typename T>
	template<typename Fn>
	inline typename Array<T>::Iter Array<T>::find(Iter first, Iter last, Fn pred)
	{
		Iter result = first;
		for (result; result != last; ++result)
		{
			if (pred(*result)) 
			{
				break;
			}
		}
		return result;
	}

	template<typename T>
	inline void Array<T>::pop_front()
	{
		m_Array.pop_front();
	}

	template<typename T>
	inline void Array<T>::InsertLeft(const T& data)
	{
		m_Array.insert(m_Array.begin() + m_LeftSize, data);
		m_LeftSize++;
	}

	template<typename T>
	inline void Array<T>::InsertRight(const T& data)
	{
		m_Array.emplace_back(data);
	}

	template<typename T>
	inline typename Array<T>::Iter Array<T>::RemoveLeft(T& data)
	{
		auto find = this->find(m_Array.begin(), m_Array.begin() + m_LeftSize,
			[&data](T target)
			{
				return (data == target);
			});
		if (find != m_Array.begin() + m_LeftSize)
		{
			find = m_Array.erase(find);
		}
		return (find == m_Array.begin() + m_LeftSize) ?
			m_Array.end() : find;
	}

	template<typename T>
	inline typename Array<T>::Iter Array<T>::RemoveRight(T& data)
	{
		auto find = this->find(m_Array.begin() + m_LeftSize, m_Array.end(),
			[&data](T target)
			{
				return (data == target);
			});
		if (find != m_Array.end())
		{
			find = m_Array.erase(find);
		}
		return (find);
	}

} // namespace fz
#pragma once

#include "ResourceManager.h"

namespace fz {

	template<typename T>
	inline bool ResourceManager<T>::Load(const std::string& path)
	{
		return (_internel::ResourceManager_internal<T>::Instance().Load(path));
	}

	template<typename T>
	inline bool ResourceManager<T>::Unload(const std::string& path)
	{
		return (_internel::ResourceManager_internal<T>::Instance().Unload(path));
	}

	template<typename T>
	inline void ResourceManager<T>::UnloadAll()
	{
		(_internel::ResourceManager_internal<T>::Instance().UnloadAll());
	}

	template<typename T>
	inline T& ResourceManager<T>::Get_Safety(const std::string& path)
	{
		return (_internel::ResourceManager_internal<T>::Instance().Get_Safety(path));
	}

	template<typename T>
	inline T& ResourceManager<T>::Get(const std::string& path)
	{
		return (_internel::ResourceManager_internal<T>::Instance().Get(path));
	}

} // namespace fz
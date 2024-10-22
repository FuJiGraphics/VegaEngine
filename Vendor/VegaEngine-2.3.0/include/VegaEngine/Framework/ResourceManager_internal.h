#pragma once
#include "Singleton.h"

namespace fz {
	namespace _internel {

		template <typename T>
		class ResourceManager_internal : public Singleton<ResourceManager_internal<T>>
		{
			friend Singleton<ResourceManager_internal<T>>;

		public:
			static T Empty;

			inline bool Load(const std::string& path)
			{
				if (m_resources.find(path) != m_resources.end())
					return (false);

				T* resource = new T();
				if (resource == nullptr)
					return (false);

				bool success = resource->loadFromFile(path);
				if (success)
				{
					m_resources.insert({ path, resource });
				}
				else
				{
					delete resource;
					resource = nullptr;
				}
				return (true);
			}

			inline bool Unload(const std::string& path)
			{
				auto target = m_resources.find(path);
				if (target == m_resources.end())
					return (false);

				delete target->second;
				target->second = nullptr;
				m_resources.erase(target);

				return (true);
			}
			
			inline void UnloadAll()
			{
				for (auto& res : m_resources)
				{
					delete res.second;
					res.second = nullptr;
				}
				m_resources.clear();
			}

			T& Get_Safety(const std::string& path)
			{
				auto target = m_resources.find(path);
				if (target == m_resources.end())
					return (Empty);

				return (*target->second);
			}

			T& Get(const std::string& path)
			{
				return (*m_resources[path]);
			}


		protected:
			explicit ResourceManager_internal() = default;
			~ResourceManager_internal()
			{
				this->UnloadAll();
			}

			ResourceManager_internal(const ResourceManager_internal&) = delete;
			ResourceManager_internal& operator=(const ResourceManager_internal&) = delete;

		private:
			std::unordered_map<std::string, T*>	m_resources;
		};

		template <typename T>
		T ResourceManager_internal<T>::Empty;

	} // namespace internal
} // namespace fz
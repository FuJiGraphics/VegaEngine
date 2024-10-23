#include "Core/stdafx.h"
#include "HitData.h"
#include "Core/Layer/Layer.h"
#include "Core/Collider/Collider.h"

namespace fz {
    namespace _internal {
#if defined(__GNUG__) 
#include <cxxabi.h>
#include <cstdlib>
        std::string demangle(const char* mangledName)
        {
            int status = 0;
            char* demangledName = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);
            std::string result = (status == 0) ? demangledName : mangledName;
            free(demangledName);
            return result;
        }
#elif defined(_MSC_VER)
        std::string demangle(const char* name)
        {
            return name;
        }
#else
        std::string demangle(const char* name)
        {
            return name;
        }
#endif
    }

   	std::string HitData::ClassName() const
	{
		return _internal::demangle(typeid(m_Class).name());
	}

    void HitData::SetLayer(Layer* layer)
    {
        m_Class = layer;
    }

    void HitData::SetCollider(Collider* collider)
    {
        m_Collider = collider;
    }

    bool HitData::empty() const
    {
        return (m_Class == nullptr) ? 
            (m_Collider == nullptr) ? 
            true : false : false;
    }

    void HitData::reset()
    {
        m_Class = nullptr;
        m_Collider = nullptr;
    }

    HitData::HitData()
        : m_Class(nullptr)
        , m_Collider(nullptr)
    {
        // Empty
    }

    HitData::HitData(const HitData& other)
        : m_Class(other.m_Class)
        , m_Collider(other.m_Collider)
    {
        // Empty
    }

    HitData::HitData(HitData&& other)
        : m_Class(other.m_Class)
        , m_Collider(other.m_Collider)
    {
        other.reset();
    }

    HitData::HitData(Layer* layer, Collider* collider)
        : m_Class(layer)
        , m_Collider(collider)
    {
        // Empty
    }

    HitData::~HitData()
    {
        this->reset();
    }

    HitData& HitData::operator=(const HitData& other)
    {
        m_Class = other.m_Class;
        m_Collider = other.m_Collider;
        return *this;
    }

    HitData& HitData::operator=(HitData&& other)
    {
        m_Class = other.m_Class;
        m_Collider = other.m_Collider;
        other.reset();
        return *this;
    }

    bool HitData::operator==(const HitData& other)
    {
        return (m_Class == other.m_Class) ? 
            (m_Collider == other.m_Collider) ? 
            true : false : false;
    }

} // namespace fz

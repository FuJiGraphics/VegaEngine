#include "Core/stdafx.h"
#include "LayerArray.h"

namespace fz {

	LayerList::LayerList() 
		: m_LayerArray()
		, m_InsertIndex(0)
	{
		// Empty
	}

	LayerList::~LayerList()
	{
		if (!m_LayerArray.empty())
		{
			int arrSize = m_LayerArray.size();
			for (int i = 0; i < arrSize; ++i)
			{
				if (m_LayerArray[i] != nullptr)
				{
					delete m_LayerArray[i];
					m_LayerArray[i] = nullptr;
				}
			}
		}
	}

	bool LayerList::InsertLayer(Layer* pLayer)
	{
		bool result = false;
		auto findLevel = this->find(pLayer);
		if (findLevel == this->end())
		{
			// m_LayerArray.emplace_back(pLevel);
			m_AddLayerBuffer.push_back(pLayer);
			result = true;
		}
		return (result);
	}

	bool LayerList::InsertOverlay(Layer* pOverlay)
	{
		// TODO: Attach 함수 호출 구문 및 최적화
		bool result = false;
		auto findOverlay = this->find(pOverlay);
		if (findOverlay == m_LayerArray.end())
		{
			// m_LayerArray.emplace(m_LayerArray.begin() + m_InsertIndex, pOverlay);
			// m_InsertIndex++;
			m_AddOverlayBuffer.push_back(pOverlay);
			result = true;
		}
		return (result);
	}

	bool LayerList::RemoveLayer(Layer* pLayer)
	{
		bool result = false;
		auto findLayer = this->find(pLayer);
		if (findLayer != m_LayerArray.end())
		{
			// m_LayerArray.erase(findLevel);
			// m_InsertIndex--;
			m_DeleteLayerBuffer.push_back(pLayer);
			result = true;
		}
		return (result);
	}

	bool LayerList::RemoveOverlay(Layer* pOverlay)
	{
		bool result = false;
		auto findOverlay = this->find(pOverlay);
		if (findOverlay != m_LayerArray.end())
		{
			// m_LayerArray.erase(findOverlay);
			m_DeleteOverlayBuffer.push_back(pOverlay);
			result = true;
		}
		return (result);
	}

	void LayerList::WorkingInsertLayers()
	{
		for (Layer* addLayer : m_AddLayerBuffer)
		{
			m_LayerArray.emplace_back(addLayer);
		}
		for (Layer* addOverlay : m_AddOverlayBuffer)
		{
			m_LayerArray.emplace(m_LayerArray.begin() + m_InsertIndex, addOverlay);
			m_InsertIndex++;
		}
		m_AddLayerBuffer.clear();
		m_AddOverlayBuffer.clear();
	}

	void LayerList::WorkingGarbage()
	{
		for (Layer* delLayer : m_DeleteLayerBuffer)
		{
			m_LayerArray.erase(this->find(delLayer));
			m_InsertIndex--;
			delLayer->OnDetach();
			delete delLayer;
			delLayer = nullptr;
		}
		for (Layer* delOverlay : m_DeleteOverlayBuffer)
		{
			m_LayerArray.erase(this->find(delOverlay));
			delOverlay->OnDetach();
			delete delOverlay;
			delOverlay = nullptr;
		}
		m_DeleteLayerBuffer.clear();
		m_DeleteOverlayBuffer.clear();
	}

	LayerList::iter LayerList::find(Layer* target)
	{
		return std::find_if(m_LayerArray.begin(), m_LayerArray.end(),
			[target](Layer* pTarget)
			{
				return (target == pTarget);
			});
	}

	bool LayerList::empty() const
	{
		return (m_LayerArray.empty());
	}

	LayerList::iter LayerList::begin()
	{
		return (m_LayerArray.begin());
	}

	LayerList::iter LayerList::end()
	{
		return (m_LayerArray.end());
	}

	LayerList::const_iter LayerList::begin() const
	{
		return (m_LayerArray.begin());
	}

	LayerList::const_iter LayerList::end() const
	{
		return (m_LayerArray.end());
	}

} // namespace fz
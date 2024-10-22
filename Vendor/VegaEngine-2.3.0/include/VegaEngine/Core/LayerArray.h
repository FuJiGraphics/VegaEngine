#pragma once

#include "Core.h"
#include "Layer.h"

namespace fz {

	class LayerArray
	{
		using iter = std::vector<Layer*>::iterator;
		using const_iter = std::vector<Layer*>::const_iterator;

	public:
		explicit	LayerArray();
		virtual		~LayerArray();

		bool		InsertLayer(Layer* pLevel);
		bool		InsertOverlay(Layer* pOverlay);
		bool		RemoveLayer(Layer* pLevel);
		bool		RemoveOverlay(Layer* pOverlay);
		void		WorkingInsertLayers();
		void		WorkingGarbage();

		iter		find(Layer* target);
		bool		empty() const;
		iter		begin();
		iter		end();		
		const_iter	begin() const;
		const_iter	end() const;

	private:
		// TODO: 20241017) 구조 리팩토링
		std::vector<Layer*>		m_LayerArray;
		std::vector<Layer*>		m_AddLayerBuffer;
		std::vector<Layer*>		m_AddOverlayBuffer;
		std::vector<Layer*>		m_DeleteLayerBuffer;
		std::vector<Layer*>		m_DeleteOverlayBuffer;
		int						m_InsertIndex;
	};

} // namespace fz
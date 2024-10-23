#include "Core/stdafx.h"
#include "LayerList.h"

namespace fz {

	fz::LayerList::LayerList()
	{
		// Empty
	}
	LayerList::~LayerList()
	{
		// Empty
	}

	void LayerList::AttachLayer(Layer* layer)
	{
		layer->OnAttach();
		Super::insert(layer, Section::Right);
	}

	void LayerList::AttachOverlay(Layer* overlay)
	{
		overlay->OnAttach();
		Super::insert(overlay, Section::Left);
	}

	void LayerList::DetachLayer(Layer* layer)
	{
		this->remove(layer, Section::Right);
		layer->OnDetach();
		this->Delete(&layer);
	}

	void LayerList::DetachOverlay(Layer* overlay)
	{
		this->remove(overlay, Section::Left);
		overlay->OnDetach();
		this->Delete(&overlay);
	}

	void LayerList::Delete(Layer** pp)
	{
		if ((*pp) != nullptr)
		{
			delete (*pp);
			(*pp) = nullptr;
		}
	}

} // namespace fz
#pragma once
#include "Core/Core.h"
#include "Core/Array.h"
#include "Layer.h"

namespace fz {

	class LayerList : public Array<Layer*>
	{
	//// Delete, Enum, Using
	protected:
		// Delete
		LayerList(const LayerList&) = delete;
		void operator=(const LayerList&) = delete;

	//// Member Functions
	public:
		// Constructor, Destructor
		LayerList();
		virtual ~LayerList();

		// Impl 
		void AttachLayer(Layer* layer);
		void AttachOverlay(Layer* overlay);
		void DetachLayer(Layer* layer);
		void DetachOverlay(Layer* overlay);

	protected:
		// new, delete
		void Delete(Layer** pp);
	};

} // namespace fz

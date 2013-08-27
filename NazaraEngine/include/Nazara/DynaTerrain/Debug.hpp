// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine - Module name"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/DynaTerrain/Config.hpp>
#if NAZARA_DYNATERRAIN_MEMORYLEAKTRACKER || defined(NAZARA_DEBUG)
	#include <Nazara/Core/Debug/MemoryLeakTracker.hpp>

	#define delete NzMemoryManager::NextFree(__FILE__, __LINE__), delete
	#define new new(__FILE__, __LINE__)
#endif

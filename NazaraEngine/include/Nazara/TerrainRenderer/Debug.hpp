// Copyright (C) 2013 Rémi Bèges
// This file is part of the "Nazara Engine - Terrain Renderer module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/TerrainRenderer/Config.hpp>
#if NAZARA_TERRAINRENDERER_MEMORYLEAKTRACKER || defined(NAZARA_DEBUG)
	#include <Nazara/Core/Debug/MemoryLeakTracker.hpp>

	#define delete NzMemoryManager::NextFree(__FILE__, __LINE__), delete
	#define new new(__FILE__, __LINE__)
#endif

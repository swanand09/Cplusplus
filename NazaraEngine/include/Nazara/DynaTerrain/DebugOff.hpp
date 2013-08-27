// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine - DynaTerrain"
// For conditions of distribution and use, see copyright notice in Config.hpp

#if NAZARA_DYNATERRAIN_MEMORYLEAKTRACKER || defined(NAZARA_DEBUG)
	#undef delete
	#undef new
#endif

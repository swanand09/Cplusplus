// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_DYNATERRAIN_FUNCTIONS_HPP
#define NAZARA_DYNATERRAIN_FUNCTIONS_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/DynaTerrain/Enums.hpp>
#include <array>

NAZARA_API nzNeighbourDirection Reverse(nzNeighbourDirection direction);
NAZARA_API void Split(nzNodeLocation location, nzNeighbourDirection& first, nzNeighbourDirection& second);

#endif // NAZARA_DYNATERRAIN_FUNCTIONS_HPP

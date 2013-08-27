// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/DynaTerrain/Configuration/TerrainConfiguration.hpp>
#include <Nazara/DynaTerrain/Debug.hpp>

NzTerrainConfiguration::NzTerrainConfiguration()
{
    //Taille d'un côté du terrain
    terrainSize = 4000.f;
    //La rotation du terrain dans les trois axes exprimé en angles d'euler
    terrainOrientation = NzEulerAnglesf(0.f,0.f,0.f);
}

NzTerrainConfiguration::~NzTerrainConfiguration()
{
    //dtor
}

void NzTerrainConfiguration::AutoFix()
{
    NzDynaTerrainConfigurationBase::AutoFix();
}

bool NzTerrainConfiguration::IsValid() const
{
    return NzDynaTerrainConfigurationBase::IsValid();
}



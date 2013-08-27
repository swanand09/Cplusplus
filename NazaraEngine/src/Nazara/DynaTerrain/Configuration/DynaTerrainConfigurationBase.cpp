// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/DynaTerrain/Configuration/DynaTerrainConfigurationBase.hpp>
#include <Nazara/DynaTerrain/Debug.hpp>

NzDynaTerrainConfigurationBase::NzDynaTerrainConfigurationBase()
{
    //La hauteur maximale du terrain/planète (sous condition que la source de hauteur renvoie bien des valeurs dans [0;1])
    maxHeight = 1000.f;
    terrainMinimalPrecision = 3;
    x_offset = 0;
    y_offset = 0;
}

NzDynaTerrainConfigurationBase::~NzDynaTerrainConfigurationBase()
{
    //dtor
}

void NzDynaTerrainConfigurationBase::AutoFix()
{

}

bool NzDynaTerrainConfigurationBase::IsValid() const
{
    return true;
}



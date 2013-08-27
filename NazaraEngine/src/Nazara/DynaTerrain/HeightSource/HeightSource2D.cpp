// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/HeightSource/HeightSource2D.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <iostream>
#include <Nazara/Core/File.hpp>
#include <Nazara/DynaTerrain/Debug.hpp>

NzHeightSource2D::NzHeightSource2D()
{

}
NzHeightSource2D::~NzHeightSource2D()
{

}

float NzHeightSource2D::GetHeight(float x, float y)
{
    //Coder ici la routine permettant de récupérer les données du terrain non procédurales

    return this->GetNoiseValue(x,y);
}

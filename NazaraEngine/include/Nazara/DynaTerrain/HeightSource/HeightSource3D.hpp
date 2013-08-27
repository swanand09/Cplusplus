// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_HEIGHTSOURCE3D_HPP
#define NAZARA_HEIGHTSOURCE3D_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/DynaTerrain/HeightSource/HeightSourceBase.hpp>
#include <vector>

class NAZARA_API NzHeightSource3D : public NzHeightSourceBase
{
    public:
        NzHeightSource3D();
        ~NzHeightSource3D();
        float GetHeight(float x, float y, float z);
    protected:
        virtual float GetNoiseValue(float x, float y, float z) = 0;
    private:

};

#endif // NAZARA_HEIGHTSOURCE3D_HPP

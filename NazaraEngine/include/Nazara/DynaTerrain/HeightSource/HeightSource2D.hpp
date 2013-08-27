// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_HEIGHTSOURCE2D_HPP
#define NAZARA_HEIGHTSOURCE2D_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/DynaTerrain/HeightSource/HeightSourceBase.hpp>
#include <vector>

class NAZARA_API NzHeightSource2D : public NzHeightSourceBase
{
    public:
        NzHeightSource2D();
        ~NzHeightSource2D();
        float GetHeight(float x, float y);
    protected:
        virtual float GetNoiseValue(float x, float y) = 0;
    private:
};

#endif // NAZARA_HEIGHTSOURCE2D_HPP

// Copyright (C) 2013 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef HYBRIDMULTIFRACTAL2D_HPP
#define HYBRIDMULTIFRACTAL2D_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Noise/ComplexNoiseBase.hpp>
#include <Nazara/Noise/Abstract2DNoise.hpp>
#include <Nazara/Noise/Enums.hpp>

class NAZARA_API NzHybridMultiFractal2D : public NzAbstract2DNoise, public NzComplexNoiseBase
{
    public:
        NzHybridMultiFractal2D(nzNoise source, unsigned int seed);
        float GetValue(float x, float y, float resolution);
        ~NzHybridMultiFractal2D();
    protected:
    private:
        NzAbstract2DNoise* m_source;
        float m_value;
        float m_remainder;
        float m_offset;
        float m_weight;
        float m_signal;
        nzNoise m_noiseType;
};

#endif // HYBRIDMULTIFRACTAL2D_HPP


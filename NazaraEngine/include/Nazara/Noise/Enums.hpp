// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine - Noise module".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_ENUMS_NOISE_HPP
#define NAZARA_ENUMS_NOISE_HPP

enum nzNoise
{
    nzNoise_perlin,
    nzNoise_simplex,
    nzNoise_cell
};

enum nzWorleyFunction
{
    nzWorleyFunction_F1 = 0,
    nzWorleyFunction_F2 = 1,
    nzWorleyFunction_F3 = 2,
    nzWorleyFunction_F4 = 3
};

#endif // NAZARA_ENUMS_NOISE_HPP

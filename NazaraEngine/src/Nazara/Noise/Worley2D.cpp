// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine - Noise module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/Noise/Config.hpp>
#include <Nazara/Noise/Worley2D.hpp>
#include <Nazara/Noise/Debug.hpp>
#include <iterator>

NzWorley2D::NzWorley2D(nzWorleyFunction function)
{
    m_function = function;
    scale[0] = 1.f / std::sqrt(2);
    scale[1] = scale[0] / 2.f;
    scale[2] = scale[1];
    scale[3] = scale[2];
}

NzWorley2D::NzWorley2D(unsigned int seed) : NzWorley2D()
{
    this->SetNewSeed(seed);
    this->ShufflePermutationTable();
}

float NzWorley2D::GetValue(float x, float y, float resolution)
{
    x *= resolution;
    y *= resolution;

    x0 = fastfloor(x);
    y0 = fastfloor(y);

    fractx = x - static_cast<float>(x0);
    fracty = y - static_cast<float>(y0);

    featurePoints.clear();
    //Dummy points : FIX ME : Remove them
    featurePoints[100.f] = NzVector2f(0.f,0.f);
    featurePoints[101.f] = NzVector2f(0.f,0.f);
    featurePoints[102.f] = NzVector2f(0.f,0.f);
    featurePoints[103.f] = NzVector2f(0.f,0.f);

    SquareTest(x0,y0,x,y);

    it = featurePoints.begin();
    std::advance(it,m_function);

    if(fractx < it->first)
        SquareTest(x0 - 1,y0,x,y);

    it = featurePoints.begin();
    std::advance(it,m_function);

    if(1.f - fractx < it->first)
        SquareTest(x0 + 1,y0,x,y);

    it = featurePoints.begin();
    std::advance(it,m_function);

    if(fracty < it->first)
        SquareTest(x0,y0 - 1,x,y);

    it = featurePoints.begin();
    std::advance(it,m_function);

    if(1.f - fracty < it->first)
        SquareTest(x0,y0 + 1,x,y);

    it = featurePoints.begin();
    std::advance(it,m_function);

    if(fractx < it->first &&
       fracty < it->first)
       SquareTest(x0 - 1, y0 - 1,x,y);

    it = featurePoints.begin();
    std::advance(it,m_function);

    if(1.f - fractx < it->first &&
       fracty < it->first)
       SquareTest(x0 + 1, y0 - 1,x,y);

    it = featurePoints.begin();
    std::advance(it,m_function);

    if(fractx < it->first &&
       1.f - fracty < it->first)
       SquareTest(x0 - 1, y0 + 1,x,y);

    it = featurePoints.begin();
    std::advance(it,m_function);

    if(1.f - fractx < it->first &&
       1.f - fracty < it->first)
       SquareTest(x0 + 1, y0 + 1,x,y);

    it = featurePoints.begin();
    std::advance(it,m_function);

    //Remove dummy points
    featurePoints.erase(--(featurePoints.end()));
    featurePoints.erase(--(featurePoints.end()));
    featurePoints.erase(--(featurePoints.end()));
    featurePoints.erase(--(featurePoints.end()));

    return it->first * scale[m_function];
}

void NzWorley2D::SetFunction(nzWorleyFunction function)
{
    m_function = function;
}

void NzWorley2D::SquareTest(int xi, int yi, float x, float y)
{
    ii = xi & 255;
    jj = yi & 255;

    seed = perm[ii +     perm[jj]];

    //On initialise notre rng avec seed
    randomNumberGenerator.seed(seed);

    //On prend un nombre de points à déterminer dans le cube, compris entre 1 et 8
    unsigned int m = (seed & 7) + 1;

    //On calcule les emplacements des différents points
    for(unsigned int i(0) ; i < m ; ++i)
    {
        NzVector2f featurePoint;
        featurePoint.x = (randomNumberGenerator() & 1023) / 1023.f + static_cast<float>(xi);
        featurePoint.y = (randomNumberGenerator() & 1023) / 1023.f + static_cast<float>(yi);

        //Insertion dans la liste triée
        featurePoints[featurePoint.Distance(NzVector2f(x,y))] = featurePoint;
    }
}

#include <cmath>
#include "MyHeightSource2D.hpp"

MyHeightSource2D::MyHeightSource2D()
{
    m_source = new NzSimplex2D(15954);
    m_source2 = new NzFBM2D(nzNoise_simplex,15954);
    m_source3 = new NzHybridMultiFractal2D(nzNoise_simplex,15955);
    m_source3->SetOctavesNumber(7);
    m_source3->SetLacunarity(2.7);
    m_source3->SetHurstParameter(0.28);

    resolution = 1/2400.f;
}

MyHeightSource2D::~MyHeightSource2D()
{
    delete m_source;
    delete m_source2;
    delete m_source3;
}

float MyHeightSource2D::GetNoiseValue(float x, float y)
{
    /*
    if(x > 100)
        return (x-100.f)*(x-100.f)/30000.f;
    else
        return 0.f;*/
/*
    if(x > 30)
        return (x-30.f)/100.f;
    else
        return 0.f;*/
    //return (std::sin(x/100.f)+1)/2.f;
    //return m_source->GetValue(x,y,0.005);
    //return m_source2->GetValue(x,y,0.0008);
    //return (m_source3->GetValue(x,y,resolution)+1)/2.f;
    //return std::exp(y/100.f);
    return 0.f;
}

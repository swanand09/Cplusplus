#include <cmath>
#include "MyHeightSource3D.hpp"

MyHeightSource3D::MyHeightSource3D()
{
    m_source = new NzSimplex3D(15954);
    m_source2 = new NzFBM3D(nzNoise_simplex,15954);
    m_source3 = new NzHybridMultiFractal3D(nzNoise_simplex,15955);
    m_source3->SetOctavesNumber(7);
    m_source3->SetLacunarity(2.7);
    m_source3->SetHurstParameter(0.28);

    resolution = 1/2800.f;
    resolution2 = 1/5800.f;
}

MyHeightSource3D::~MyHeightSource3D()
{
    delete m_source;
    delete m_source2;
    delete m_source3;
}

float MyHeightSource3D::GetNoiseValue(float x, float y, float z)
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
    //return m_source->GetValue(x,y,z,0.005);
    //return (m_source2->GetValue(x,y,z,resolution)+1)/2.f;
    return (m_source3->GetValue(x,y,z,resolution2)+1)/2.f;
    //return std::exp(y/100.f);
    //return 0.f;
}

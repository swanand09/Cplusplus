#ifndef MYHEIGHTSOURCE2D_HPP
#define MYHEIGHTSOURCE2D_HPP

#include <Nazara/Noise/FBM2D.hpp>
#include <Nazara/Noise/HybridMultiFractal2D.hpp>
#include <Nazara/Noise/Simplex2D.hpp>
#include <Nazara/DynaTerrain/HeightSource/HeightSource2D.hpp>

class MyHeightSource2D : public NzHeightSource2D
{
    public:
        MyHeightSource2D();
        ~MyHeightSource2D();
        float GetNoiseValue(float x, float y);
    protected:
    private:
        NzSimplex2D* m_source;
        NzFBM2D* m_source2;
        NzHybridMultiFractal2D* m_source3;
        float resolution;
};

#endif // MYHEIGHTSOURCE2D_HPP

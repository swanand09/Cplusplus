#ifndef MYHEIGHTSOURCE3D_HPP
#define MYHEIGHTSOURCE3D_HPP

#include <Nazara/Noise/FBM3D.hpp>
#include <Nazara/Noise/HybridMultiFractal3D.hpp>
#include <Nazara/Noise/Simplex3D.hpp>
#include <Nazara/DynaTerrain/HeightSource/HeightSource3D.hpp>

class MyHeightSource3D : public NzHeightSource3D
{
    public:
        MyHeightSource3D();
        ~MyHeightSource3D();
        float GetNoiseValue(float x, float y, float z);
    protected:
    private:
        NzSimplex3D* m_source;
        NzFBM3D* m_source2;
        NzHybridMultiFractal3D* m_source3;
        float resolution;
        float resolution2;
};

#endif // MYHEIGHTSOURCE3D_HPP

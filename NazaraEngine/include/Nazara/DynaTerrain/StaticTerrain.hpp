// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_STATICTERRAIN_HPP
#define NAZARA_STATICTERRAIN_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/DynaTerrain/HeightSource/HeightSource2D.hpp>
#include <Nazara/DynaTerrain/Configuration/TerrainConfiguration.hpp>
#include <Nazara/DynaTerrain/TerrainQuadTree.hpp>
#include <Nazara/DynaTerrain/TerrainBase.hpp>

//TODO : Ramener les textures dans NzDynaTerrainMainCLass, ce n'est pas à la classe de config de s'en occuper

class NAZARA_API NzStaticTerrain : public NzTerrainBase
{
    public:
        NzStaticTerrain(NzHeightSource2D* heightSource);
        ~NzStaticTerrain();

        void Initialize(const NzVector2f& size, unsigned int resolution);

        virtual void Draw() const;

        void Update(const NzVector3f& cameraPosition);

    private:


        //NzTerrainConfiguration m_configuration;
        NzHeightSource2D* m_heightSource;
        NzTexture m_terrainTexture;

        NzShaderProgram m_shader;
        NzVector2f m_size;
        unsigned int resolution;
};

#endif // NAZARA_STATICTERRAIN_HPP

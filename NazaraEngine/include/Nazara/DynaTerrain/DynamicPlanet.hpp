// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_DYNAMICPLANET_HPP
#define NAZARA_DYNAMICPLANET_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/DynaTerrain/HeightSource/HeightSource3D.hpp>
#include <Nazara/DynaTerrain/Configuration/TerrainConfiguration.hpp>
#include <Nazara/DynaTerrain/TerrainQuadTree.hpp>
#include <Nazara/DynaTerrain/TerrainBase.hpp>
#include <vector>

//TODO : modifier shader du terrain pour qu'il fonctionne avec n'importe quelle direction (slope, altitude)

class NAZARA_API NzDynamicPlanet : public NzTerrainBase
{
    public:

        NzDynamicPlanet(const NzPlanetConfiguration& configuration, NzHeightSource3D* heightSource);
        ~NzDynamicPlanet();

        void Initialize();

        virtual void Draw() const;

        void Update(const NzVector3f& cameraPosition);

    private:

        NzPlanetConfiguration m_configuration;
        NzHeightSource3D* m_heightSource;
        NzTexture m_terrainTexture;

        NzShaderProgram m_shader;
        std::vector<NzTerrainQuadTree*> quadtrees;
        //NzTerrainQuadTree* quadtree2;
};

#endif // NAZARA_DYNAMICPLANET_HPP

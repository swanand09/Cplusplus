// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_DYNAMICTERRAIN_HPP
#define NAZARA_DYNAMICTERRAIN_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/DynaTerrain/HeightSource/HeightSource2D.hpp>
#include <Nazara/DynaTerrain/Configuration/TerrainConfiguration.hpp>
#include <Nazara/DynaTerrain/TerrainQuadTree.hpp>
#include <Nazara/DynaTerrain/TerrainBase.hpp>
#include <vector>

//TODO : Ramener les textures dans NzDynaTerrainMainCLass, ce n'est pas à la classe de config de s'en occuper
//TODO : Définir une taille maximale (visible) du terrain. Travailler avec 4,16 ou 32 quadtrees pour gérer le déplacement
class NAZARA_API NzDynamicTerrain : public NzTerrainBase
{
    public:

        NzDynamicTerrain(const NzTerrainConfiguration& configuration, NzHeightSource2D* heightSource);
        NzDynamicTerrain(NzHeightSource2D* heightSource);
        ~NzDynamicTerrain();

        const NzBoundingVolumef& GetBoundingVolume() const;

        void Initialize();

        virtual void Draw() const;

        virtual void Update();


    private:


        NzTerrainConfiguration m_configuration;
        NzHeightSource2D* m_heightSource;
        NzTexture m_terrainTexture;

        NzShaderProgram m_shader;

        // Les quadtrees gèrent la construction/mise à jour du maillage de manière optimisé
        // Chaque quadtree représente une sous-région fixe du terrain
        //std::array<4,std::array<4,NzTerrainQuadTree*>> quadtree;
        NzTerrainQuadTree* quadtree;

};

#endif // NAZARA_DYNAMICTERRAIN_HPP

// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/DynaTerrain/DynamicTerrain.hpp>
#include <Nazara/Renderer/Renderer.hpp>
#include <Nazara/TerrainRenderer/TerrainChunksManager.hpp>
#include <iostream>
#include <Nazara/Graphics/Camera.hpp>
#include <Nazara/DynaTerrain/Debug.hpp>

using namespace std;

NzDynamicTerrain::NzDynamicTerrain(const NzTerrainConfiguration& configuration, NzHeightSource2D* heightSource)
{
   if(configuration.IsValid())
        m_configuration = configuration;

    m_heightSource = heightSource;
}

NzDynamicTerrain::NzDynamicTerrain(NzHeightSource2D* heightSource)
{
    m_heightSource = heightSource;
}

NzDynamicTerrain::~NzDynamicTerrain()
{
    delete quadtree;
    //delete quadtree2;
    //delete quadtree3;
}

void NzDynamicTerrain::Draw() const
{
    if(!m_transformMatrixUpdated)
        UpdateTransformMatrix();

    NzRenderer::SetMatrix(nzMatrixType_World,m_transformMatrix);

    //TODO : PRENDRE EN COMPTE CETTE MATRICE, CAR POUR L'INSTANT CHAQUE CHUNKSMANAGER CLEAR LA MATRICE AVANT DESSIN
    quadtree->m_chunksManager->DrawChunks();
}

const NzBoundingVolumef& NzDynamicTerrain::GetBoundingVolume() const
{
    //FIXME : Avec plusieurs quadtrees, le terrain doit avoir une aabb qui lui est propre
    //et qui doit être mise à jour à chaque fois que l'on cherche à s'en servir
    return quadtree->m_chunksManager->GetGlobalBoundingVolume();
}

void NzDynamicTerrain::Initialize()
{

    //m_configuration.x_offset = 0;
    //m_configuration.y_offset = 0;
    quadtree = new NzTerrainQuadTree(m_configuration,m_heightSource);
    quadtree->Initialize();

    GetScene()->RegisterForUpdate(this);

    /*NzTerrainConfiguration second = m_configuration;

    second.x_offset = 0;
    second.y_offset = 1;
    quadtree2 = new NzTerrainQuadTree(second,m_heightSource);
    quadtree2->Initialize();

    quadtree->ConnectNeighbor(quadtree2,BOTTOM,TOP);
    NzTerrainConfiguration third = m_configuration;
    third.x_offset = 1;
    third.y_offset = 0;
    quadtree3 = new NzTerrainQuadTree(third,m_heightSource);
    quadtree3->Initialize();
    quadtree->ConnectNeighbor(quadtree3,RIGHT,LEFT);
    quadtree3->ConnectNeighbor(quadtree2,BOTTOM,RIGHT);*/
}

void NzDynamicTerrain::Update()
{
    //On récupère la position de la caméra dans le repère local, et on maj le(s) quadtrees
    //TODO : Calculer la position dans le repère local ? Normalement oui, to check
    quadtree->Update(GetScene()->GetViewer()->GetEyePosition());
    //quadtree2->Update(localCamPos);
    //quadtree3->Update(localCamPos);
}

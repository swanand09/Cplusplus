// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/DynaTerrain/StaticTerrain.hpp>
#include <Nazara/Renderer/Renderer.hpp>
#include <iostream>
#include <Nazara/DynaTerrain/Debug.hpp>

using namespace std;

NzStaticTerrain::NzStaticTerrain(NzHeightSource2D* heightSource)
{
    m_heightSource = heightSource;
}

NzStaticTerrain::~NzStaticTerrain()
{
    //delete quadtree;
    //delete quadtree2;
    //delete quadtree3;
}

void NzStaticTerrain::Draw() const
{
    //NzDynaTerrainMainClassBase::Draw();
    //quadtree->Render();
    //quadtree2->Render();
    //quadtree3->Render();
}

void NzStaticTerrain::Initialize(const NzVector2f& size, unsigned int resolution)
{

    //m_configuration.x_offset = 0;
    //m_configuration.y_offset = 0;
    /*quadtree = new NzTerrainQuadTree(m_configuration,m_heightSource);
    quadtree->Initialize();

    NzTerrainConfiguration second = m_configuration;

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

void NzStaticTerrain::Update(const NzVector3f& cameraPosition)
{
    //On transforme la position de la caméra du repère global dans le repère local
    NzVector3f localCamPos = cameraPosition - this->GetPosition();

    //quadtree->Update(localCamPos);
    //quadtree2->Update(localCamPos);
    //quadtree3->Update(localCamPos);
}

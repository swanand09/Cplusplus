// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/DynaTerrain/DynamicPlanet.hpp>
#include <Nazara/Renderer/Renderer.hpp>
#include <iostream>
#include <Nazara/DynaTerrain/Debug.hpp>

using namespace std;

NzDynamicPlanet::NzDynamicPlanet(const NzPlanetConfiguration& configuration, NzHeightSource3D* heightSource)
{
   if(configuration.IsValid())
        m_configuration = configuration;

    m_heightSource = heightSource;
}

NzDynamicPlanet::~NzDynamicPlanet()
{
    for (auto& it: quadtrees)
        delete it;
}

void NzDynamicPlanet::Draw() const
{
    if (!m_transformMatrixUpdated)
		UpdateTransformMatrix();

    NzRenderer::SetMatrix(nzMatrixType_World,m_transformMatrix);

    //TODO !!
    //quadtree.m_chunksManager->Render();

    //quadtrees.at(0)->Render();
    //quadtrees.at(1)->Render();
    //quadtrees.at(2)->Render();
    //quadtrees.at(3)->Render();
    //quadtrees.at(4)->Render();
    ///quadtrees.at(5)->Render();
}

void NzDynamicPlanet::Initialize()
{

    quadtrees.emplace_back(new NzTerrainQuadTree(m_configuration,m_heightSource));
    quadtrees.at(0)->Initialize();
    quadtrees.emplace_back(new NzTerrainQuadTree(m_configuration,m_heightSource,NzEulerAnglesf(0.f,0.f,-90.f)));
    quadtrees.at(1)->Initialize();
    quadtrees.emplace_back(new NzTerrainQuadTree(m_configuration,m_heightSource,NzEulerAnglesf(0.f,0.f,-170.f)));
    quadtrees.at(2)->Initialize();
    quadtrees.emplace_back(new NzTerrainQuadTree(m_configuration,m_heightSource,NzEulerAnglesf(0.f,0.f,90.f)));
    quadtrees.at(3)->Initialize();
    quadtrees.emplace_back(new NzTerrainQuadTree(m_configuration,m_heightSource,NzEulerAnglesf(90.f,0.f,0.f)));
    quadtrees.at(4)->Initialize();
    quadtrees.emplace_back(new NzTerrainQuadTree(m_configuration,m_heightSource,NzEulerAnglesf(-90.f,0.f,0.f)));
    quadtrees.at(5)->Initialize();
    //BUG MAJ MESH

    ///4 PREMIERS : OK !
    //quadtrees.at(0)->ConnectNeighbor(quadtrees.at(1),RIGHT,LEFT);
    //quadtrees.at(1)->ConnectNeighbor(quadtrees.at(2),RIGHT,LEFT);
    //quadtrees.at(2)->ConnectNeighbor(quadtrees.at(3),RIGHT,LEFT);
    //quadtrees.at(3)->ConnectNeighbor(quadtrees.at(0),RIGHT,LEFT);

    ///quadtrees.at(4)->ConnectNeighbor(quadtrees.at(0),TOP,BOTTOM);
    //quadtrees.at(4)->ConnectNeighbor(quadtrees.at(1),RIGHT,BOTTOM);
    //quadtrees.at(4)->ConnectNeighbor(quadtrees.at(2),BOTTOM,BOTTOM);//INVERSE A CAUSE DE LA ROTATION !
    //quadtrees.at(4)->ConnectNeighbor(quadtrees.at(3),LEFT,BOTTOM);

    ///quadtrees.at(5)->ConnectNeighbor(quadtrees.at(0),BOTTOM,TOP);
    //quadtrees.at(5)->ConnectNeighbor(quadtrees.at(1),LEFT);
    //quadtrees.at(5)->ConnectNeighbor(quadtrees.at(2),,BOTTOM);
    //quadtrees.at(5)->ConnectNeighbor(quadtrees.at(3),RIGHT);
}

void NzDynamicPlanet::Update(const NzVector3f& cameraPosition)
{
     //On transforme la position de la caméra du repère global dans le repère local
    NzVector3f localCamPos = cameraPosition - this->GetPosition();

    quadtrees.at(0)->Update(localCamPos);
    quadtrees.at(1)->Update(localCamPos);
    quadtrees.at(2)->Update(localCamPos);
    quadtrees.at(3)->Update(localCamPos);
    quadtrees.at(4)->Update(localCamPos);
    quadtrees.at(5)->Update(localCamPos);
}

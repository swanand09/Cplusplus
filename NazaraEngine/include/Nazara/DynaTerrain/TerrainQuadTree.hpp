// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_DYNATERRAINQUADTREEBASE_HPP
#define NAZARA_DYNATERRAINQUADTREEBASE_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Core/String.hpp>
#include <Nazara/Math/Matrix4.hpp>
#include <Nazara/DynaTerrain/TerrainNode.hpp>
#include <Nazara/DynaTerrain/ObjectPool.hpp>
#include <Nazara/TerrainRenderer/TerrainNodeID.hpp>
#include <Nazara/TerrainRenderer/TerrainChunksManager.hpp>
#include <Nazara/DynaTerrain/Configuration/TerrainConfiguration.hpp>
#include <Nazara/DynaTerrain/Configuration/PlanetConfiguration.hpp>
#include <Nazara/DynaTerrain/HeightSource/HeightSource2D.hpp>
#include <Nazara/DynaTerrain/HeightSource/HeightSource3D.hpp>
#include <Nazara/DynaTerrain/TerrainNormalsManager.hpp>
#include <Nazara/DynaTerrain/Enums.hpp>
#include <Nazara/Core/Clock.hpp>
#include <map>

//TODO URGENT : Remplacer calls au dispatcher
//TODO : Gain réels du pool ? voir boost Pool

class NAZARA_API NzTerrainQuadTree
{
    public:
        friend class NzTerrainNode;
        friend class NzTerrainConfiguration;
        friend class NzDynamicPlanet;
        friend class NzDynamicTerrain;

        NzTerrainQuadTree(const NzTerrainConfiguration& configuration, NzHeightSource2D* heightSource);
        NzTerrainQuadTree(const NzPlanetConfiguration& configuration, NzHeightSource3D* heightSource, const NzEulerAnglesf& quadtreeOrientation = NzEulerAnglesf(0.f,0.f,0.f));
        ~NzTerrainQuadTree();

        // Interaction avec les quadtrees voisins
        void ConnectNeighbor(NzTerrainQuadTree* neighbour, nzNeighbourDirection toCaller, nzNeighbourDirection toCallee);
        void DisconnectNeighbor(NzTerrainQuadTree* neighbour, nzNeighbourDirection direction);//DO NOT USE : Modifs todo
        NzTerrainQuadTree* GetContainingQuadTree(const NzTerrainNodeID& nodeID);//DO NOT USE : Outdated
        NzTerrainQuadTree* GetNeighbourQuadTree(nzNeighbourDirection direction);
        nzNeighbourDirection GetNeighbourDirection(NzTerrainQuadTree* neighbour);
        nzConnectionType GetConnectionType(NzTerrainQuadTree* neighbour);

        // Interaction avec les nodes
        unsigned int GetLeafNodesAmount() const;
        NzTerrainNode* GetNode(const NzTerrainNodeID& nodeID);
        NzTerrainNode* GetRootNode();

        // Informations
        virtual NzVector3f GetVertexPosition(const NzTerrainNodeID& nodeID, int x, int y);
        float GetMaximumHeight() const;//??
        unsigned int GetSubdivisionsAmount();//??

        // Opérations principales
        void Initialize();
        void Update(const NzVector3f& cameraPosition);

    protected:
        NzTerrainChunksManager* m_chunksManager;
        NzTerrainNormalsManager m_normalsManager;
        nzQuadTreeType m_type;
        NzTerrainNode* m_root;
        nzTerrainNodeData m_data;// A intégrer dans le node ?
        // Pour récupérer un pointer de node à partir de son identifiant
        std::map<NzTerrainNodeID,NzTerrainNode*> m_nodesMap;
        std::list<NzTerrainNode*> m_leaves;

        void DeleteNode(NzTerrainNode* node);

        void RegisterLeaf(NzTerrainNode* node);
        bool UnRegisterLeaf(NzTerrainNode* node);
        bool UnRegisterNode(NzTerrainNode* node);

        // Opérations sur les nodes
        void AddLeaveToSubdivisionQueue(NzTerrainNode* node);
        void AddNodeToRefinementQueue(NzTerrainNode* node);
        void TryRemoveNodeFromRefinementQueue(NzTerrainNode* node);
        std::map<NzTerrainNodeID,NzTerrainNode*> m_subdivisionQueue;
        std::map<NzTerrainNodeID,NzTerrainNode*> m_refinementQueue;

        //NzTerrainMasterNode m_dispatcher;

        // Configuration du terrain, bof bof
        float m_halfTerrainSize;//??
        NzTerrainConfiguration m_terrainConfiguration;
        NzPlanetConfiguration m_planetConfiguration;
        NzDynaTerrainConfigurationBase m_commonConfiguration;

        // Les sources de hauteur, aussi bof bof les 2 en même temps
        NzHeightSource2D* m_heightSource2D;
        NzHeightSource3D* m_heightSource3D;

        // Les voisins du quadtree
        NzTerrainQuadTree* m_neighbours[4];
        std::map<NzTerrainQuadTree*,nzConnectionType> m_connectionType;
        std::map<NzTerrainQuadTree*,nzNeighbourDirection> m_connectionDirectionLookup;

        NzMatrix4f m_rotationMatrix;


        unsigned int m_subdivisionsAmount;
        unsigned int m_maxOperationsPerFrame;
        NzClock updateClock;

        bool m_isInitialized;

    private:
        void Construct();

};

#endif // NAZARA_TERRAINQUADTREE_HPP

// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_TERRAINNODE_HPP
#define NAZARA_TERRAINNODE_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Math/Vector3.hpp>
#include <Nazara/Math/Sphere.hpp>
#include <Nazara/DynaTerrain/Patch.hpp>
#include <Nazara/DynaTerrain/Enums.hpp>
#include <Nazara/TerrainRenderer/TerrainNodeID.hpp>

class NzTerrainQuadTree;
class NzHeightSource;

//TODO : Un node subdivisé devrait renvoyer son pointer vers le patch pour réduire l'utilisation des ressources

class NAZARA_API NzTerrainNode
{
    public:

        NzTerrainNode();
        ~NzTerrainNode();

        // Actions hiérarchiques
        void CleanTree(unsigned int minDepth);//RENOMMER ReleaseAllChildren
        bool HierarchicalRefine();
        void HierarchicalSubdivide(unsigned int maxDepth, bool isNotReversible = false);
        void HierarchicalSlopeBasedSubdivide(unsigned int maxDepth);

        // Gestion du patch
        void CreatePatch();
        void DeletePatch();

        // Getters
        const NzBoundingVolumef& GetAABB() const;
        NzTerrainNode* GetChild(nzNodeLocation location);
        NzTerrainNode* GetChild(unsigned int i);
        unsigned int GetLevel() const;
        static int GetNodeAmount();
        const NzTerrainNodeID& GetNodeID() const;
        NzTerrainNode* GetParent();

        // Interaction avec les nodes voisins
        NzTerrainNode* GetDirectNeighbor(nzNeighbourDirection direction);

        // Actions principales
        void Update(const NzVector3f& cameraPosition);
        void Initialize(nzTerrainNodeData *data, NzTerrainNode* parent, nzNodeLocation location = nzNodeLocation_topleft);
        void Invalidate();
        bool Refine();
        bool Subdivide(bool isNotReversible = false);

        // Infos
        bool IsLeaf() const;
        bool IsRoot() const;
        bool IsValid() const;


    private:
        void Initialize(nzTerrainNodeData *data, NzTerrainNode* parent, const NzPatch& parentPatch, nzNodeLocation location = nzNodeLocation_topleft);
        void InitializeData(nzTerrainNodeData *data, NzTerrainNode* parent, nzNodeLocation location = nzNodeLocation_topleft);

        void HandleNeighborSubdivision(nzNeighbourDirection direction, bool isNotReversible = false);


        nzTerrainNodeData* m_data;
        NzTerrainNode* m_parent;
        NzTerrainNode* m_children[4];

        bool m_isLeaf;
        bool m_isRoot;
        bool m_isInitialized;

        //L'identifiant unique du node
        NzTerrainNodeID m_nodeID;
        NzBoundingVolumef m_aabb;
        NzPatch* m_patch;
        //L'emplacement du node par rapport au parent
        nzNodeLocation m_location;

        static int nbNodes;

        //Indique que le node ne doit pas être refiné, pour conserver une précision du terrain lors de variation de pente
        bool m_doNotRefine;
};

#endif // NAZARA_TERRAINNODE_HPP

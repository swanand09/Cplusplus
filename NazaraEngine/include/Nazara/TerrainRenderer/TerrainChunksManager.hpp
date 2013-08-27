// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine - Terrain Renderer module".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_TERRAINCHUNKSMANAGER_HPP
#define NAZARA_TERRAINCHUNKSMANAGER_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Math/Vector3.hpp>
#include <Nazara/Utility/VertexBuffer.hpp>
#include <Nazara/Utility/VertexDeclaration.hpp>
#include <Nazara/Utility/IndexBuffer.hpp>
//#include <Nazara/DynaTerrain/TerrainNode.hpp>
#include <Nazara/DynaTerrain/Enums.hpp>
//#include <Nazara/Graphics/SceneNode.hpp>
#include <Nazara/Math/BoundingVolume.hpp>
#include <Nazara/TerrainRenderer/TerrainChunk.hpp>
#include <Nazara/TerrainRenderer/TerrainRenderer.hpp>
#include <vector>
#include <queue>
#include <memory>

//FIX ME : Utiliser un arbre en structure interne pour le fast culling
//TODO : Rajouter position au chunk manager, modifs à faire dans addMesh,Update,Remove
class NAZARA_API NzTerrainChunksManager
{
    public:
        NzTerrainChunksManager(float edgelenght, unsigned int depth);
        ~NzTerrainChunksManager() = default;

        bool AddMesh(const std::array<float,150>& vertexData, const NzBoundingVolumef& meshBoundingBox, NzTerrainNodeID meshIdentifiant);

        void DrawChunks() const;

		const NzBoundingVolumef& GetGlobalBoundingVolume() const;

		NzTerrainChunk* LocateChunk(NzVector2f location);

		bool RemoveMesh(const NzBoundingVolumef& meshBoundingBox, NzTerrainNodeID meshIdentifiant);

		bool UpdateMesh(const std::array<float,150>& vertexData, const NzBoundingVolumef& meshBoundingBox, NzTerrainNodeID meshIdentifiant);

		//virtual void AddToRenderQueue(NzRenderQueue& renderQueue) const;
		//unsigned int GetFreeBuffersAmount() const;
		//virtual nzSceneNodeType GetSceneNodeType() const;

        //bool Initialize();

        //NzVertexBuffer* QueryFreeBuffer();

    protected:
        //virtual bool VisibilityTest(const NzFrustumf& frustum);

        //NzBoundingBoxf m_aabb;
    private:
        //bool m_isReady;
        unsigned int m_depth;
        float m_edgeLenght;
        float m_gridStep;

        //std::vector<std::unique_ptr<NzTerrainNode>> m_zones;
        std::vector<NzTerrainChunk> m_chunks;

        NzBoundingVolumef m_aabb;

        NzRenderStates m_renderStates;

        //unsigned int m_bufferSize;
        //unsigned int m_patchSize;
        //unsigned int m_patchAmount;
};

#endif // NAZARA_TERRAINCHUNKSMANAGER_HPP

// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_PATCH_HPP
#define NAZARA_PATCH_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Math/Vector3.hpp>
#include <Nazara/DynaTerrain/Enums.hpp>
#include <Nazara/TerrainRenderer/TerrainNodeID.hpp>
#include <array>
#include <Nazara/Math/BoundingVolume.hpp>
#include <Nazara/DynaTerrain/TerrainVertex.hpp>

//TODO : Renommer m_aabb en boundingVolume
//TODO : Le unupload mesh devrait se faire dans Reset ?
//TODO : UN BON NETTOYATE !

class NAZARA_API NzPatch
{
    public:
        NzPatch();
        ~NzPatch() = default;

        NzBoundingVolumef& GetAABB();
        const NzBoundingVolumef& GetAABB() const;
        float GetGlobalSlope() const;

        void Initialize(NzTerrainNodeID nodeID, nzTerrainNodeData* data);
        void InitializeFromParent(NzTerrainNodeID nodeID, nzTerrainNodeData* data, const NzPatch& parentPatch);
        void Invalidate();
        void Reset();
        void SetConfiguration(nzNeighbourDirection toNeighbor, unsigned int levelDifference, bool autoUpdate = true);

        void UploadMesh(bool firstTime = true);
        void UnUploadMesh();

        void OnNormalChanged(NzVector2i normalLocation, const NzVector3f& newValue);

    protected:
    private:

        void ComputeNormals();
        void ComputeSlope();
        void ComputeHeights();
        void CorrectNormalsAtInterface();

        nzTerrainNodeData* m_data;
        NzTerrainNodeID m_id;
        NzBoundingVolumef m_aabb;
        unsigned short int m_configuration;
        std::array<NzVector3f,49> m_vertexPositions;
        std::array<NzVector3f,25> m_vertexNormals;
        std::array<float,150> m_uploadedData;
        float m_slope;
        bool m_isUploaded;
        bool m_isInitialized;
        bool m_fromScratch;

        std::array<std::array<NzTerrainVertex,7>,7> m_vertices;
};

#endif // NAZARA_PATCH_HPP

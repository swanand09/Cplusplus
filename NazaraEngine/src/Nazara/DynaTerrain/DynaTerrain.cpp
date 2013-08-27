// Copyright (C) 2013  BEGES Rémi
// This file is part of the "Nazara Engine - Module name"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/DynaTerrain/DynaTerrain.hpp>
#include <Nazara/Core/Core.hpp>
#include <Nazara/Core/Error.hpp>
#include <Nazara/Core/Log.hpp>
#include <Nazara/DynaTerrain/ObjectPool.hpp>
#include <map>
#include <Nazara/TerrainRenderer/TerrainRenderer.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/DynaTerrain/Debug.hpp>

namespace
{
    unsigned int m_minimalPrecision = 3;
    unsigned int m_maximalPrecision = 10;
    unsigned int m_radiusAmount = 7;
    float m_smallerRadius = 10.f;
    float m_radiusSizeIncrement = 2.5f;

    std::map<float,unsigned int> m_precisionRadii;

    NzObjectPool<NzTerrainNode> m_nodesPool;
    NzObjectPool<NzPatch> m_patchesPool;
    NzObjectPool<NzTerrainVertex> m_verticesPool;
}

void NzDynaTerrain::ConfigurePrecisionSettings(unsigned int minimalPrecision, unsigned int maximalPrecision, unsigned int radiusAmount,
                                               float smallerRadius, float radiusSizeIncrement)
{
    m_minimalPrecision = minimalPrecision;
    m_maximalPrecision = maximalPrecision;
    m_radiusAmount = radiusAmount;
    m_smallerRadius = smallerRadius;
    m_radiusSizeIncrement = radiusSizeIncrement;

    NzDynaTerrain::ComputeRadii();
}

int NzDynaTerrain::GetPrecisionLevelFromDistance(float distance)
{
    if(distance > m_precisionRadii.rbegin()->first)
        return m_minimalPrecision;

    if(distance < m_precisionRadii.begin()->first)
        return m_maximalPrecision;

    std::map<float,unsigned int>::iterator it = m_precisionRadii.lower_bound(distance);

    if(it != m_precisionRadii.end())
        return it->second;

    #if NAZARA_DYNATERRAIN_SAFE
    NazaraError("Could not identify correct radius for distance " + NzString::Number(distance));
    #endif
    return m_minimalPrecision;
}

NzTerrainNode* NzDynaTerrain::GetTerrainNode()
{
    return m_nodesPool.GetObjectPtr();
}

NzPatch* NzDynaTerrain::GetTerrainPatch()
{
    return m_patchesPool.GetObjectPtr();
}

NzTerrainVertex* NzDynaTerrain::GetTerrainVertex()
{
    return m_verticesPool.GetObjectPtr();
}

bool NzDynaTerrain::Initialize()
{
	if (s_moduleReferenceCounter++ != 0)
		return true; // Déjà initialisé

	// Initialisation des dépendances
	if (!NzTerrainRenderer::Initialize())
	{
		NazaraError("Failed to initialize terrain renderer module");
		return false;
	}

	// Initialisation du module
	m_nodesPool.SetChunkSize(5000);
    m_patchesPool.SetChunkSize(1000);
    m_verticesPool.SetChunkSize(1000);

    NzDynaTerrain::ComputeRadii();

	NazaraNotice("Initialized: DynaTerrain module");

	return true;
}

bool NzDynaTerrain::IsInitialized()
{
	return s_moduleReferenceCounter != 0;
}

void NzDynaTerrain::ReturnTerrainNode(NzTerrainNode* node)
{
    return m_nodesPool.ReturnObjectPtr(node);
}

void NzDynaTerrain::ReturnTerrainPatch(NzPatch* patch)
{
    return m_patchesPool.ReturnObjectPtr(patch);
}

void NzDynaTerrain::ReturnTerrainVertex(NzTerrainVertex* vertex)
{
    return m_verticesPool.ReturnObjectPtr(vertex);
}

void NzDynaTerrain::Uninitialize()
{
	if (s_moduleReferenceCounter != 1)
	{
		// Le module est soit encore utilisé, soit pas initialisé
		if (s_moduleReferenceCounter > 1)
			s_moduleReferenceCounter--;

		return;
	}

	// Libération du module
	s_moduleReferenceCounter = 0;

    m_nodesPool.ReleaseAll();
    m_patchesPool.ReleaseAll();
    m_verticesPool.ReleaseAll();

	NazaraNotice("Uninitialized: DynaTerrain module");

	// Libération des dépendances
	NzTerrainRenderer::Uninitialize();
}

void NzDynaTerrain::ComputeRadii()
{
    float radius = m_smallerRadius;
    m_precisionRadii.clear();

    for(unsigned int i(0) ; i < m_radiusAmount ; ++i)
    {
        // Attention, on utilise la longueur du radius commé clé et non pas comme valeur
        // Ca permet de déterminer immédiatement à quel rayon appartient un point
        m_precisionRadii[radius] = m_maximalPrecision - i;
        radius *= m_radiusSizeIncrement;
    }
}

unsigned int NzDynaTerrain::s_moduleReferenceCounter = 0;

// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/Core/Log.hpp>
#include <Nazara/Core/String.hpp>
#include <Nazara/DynaTerrain/TerrainQuadTree.hpp>
#include <Nazara/Math/Matrix4.hpp>
#include <Nazara/Math/Quaternion.hpp>
#include <Nazara/Renderer/Renderer.hpp>
#include <Nazara/DynaTerrain/DynaTerrain.hpp>
#include <iostream>
#include <cmath>
#include <Nazara/DynaTerrain/Debug.hpp>

using namespace std;

NzTerrainQuadTree::NzTerrainQuadTree(const NzTerrainConfiguration& configuration, NzHeightSource2D* heightSource)
{
    m_type = nzQuadTreeType_terrain;

    m_heightSource2D = heightSource;
    m_terrainConfiguration = configuration;
    m_halfTerrainSize = m_terrainConfiguration.terrainSize / 2.f;
    m_chunksManager = new NzTerrainChunksManager(m_terrainConfiguration.terrainSize,5);
    m_commonConfiguration = static_cast<NzDynaTerrainConfigurationBase>(configuration);

    m_isInitialized = false;
    m_rotationMatrix.MakeRotation(NzQuaternionf(m_terrainConfiguration.terrainOrientation));
    Construct();

}

NzTerrainQuadTree::NzTerrainQuadTree(const NzPlanetConfiguration& configuration, NzHeightSource3D* heightSource, const NzEulerAnglesf& quadtreeOrientation)
{
    m_type = nzQuadTreeType_planet;

    m_heightSource3D = heightSource;
    m_planetConfiguration = configuration;
    //m_halfTerrainSize = m_planetConfiguration.terrainSize / 2.f;
    m_commonConfiguration = static_cast<NzDynaTerrainConfigurationBase>(configuration);
    // TODO ! SINON SEGFAULT !
    m_chunksManager = new NzTerrainChunksManager(5,m_halfTerrainSize);
    m_rotationMatrix.MakeRotation(NzQuaternionf(quadtreeOrientation));

    m_isInitialized = false;

    Construct();
}

void NzTerrainQuadTree::Construct()
{
    //m_dispatcher.Initialize(m_commonConfiguration.minPrecision);

    m_data.quadtree = this;
    m_data.chunksManager = m_chunksManager;
    m_data.normalsManager = &m_normalsManager;
    m_root = NzDynaTerrain::GetTerrainNode();
    m_root->Initialize(&m_data,nullptr);
    m_leaves.push_back(m_root);//Utile ?
    m_nodesMap[NzTerrainNodeID(0,0,0)] = m_root;
    m_subdivisionsAmount = 0;
    m_neighbours[0] = nullptr;
    m_neighbours[1] = nullptr;
    m_neighbours[2] = nullptr;
    m_neighbours[3] = nullptr;

    m_maxOperationsPerFrame = 0;
}

NzTerrainQuadTree::~NzTerrainQuadTree()
{
    delete m_chunksManager;
    m_isInitialized = false;
}

void NzTerrainQuadTree::ConnectNeighbor(NzTerrainQuadTree* neighbour, nzNeighbourDirection callerDirection, nzNeighbourDirection calleeDirection)
{
    m_neighbours[callerDirection] = neighbour;
    neighbour->m_neighbours[calleeDirection] = this;

    nzConnectionType connection;

    if(callerDirection == calleeDirection)
        connection = nzConnectionType_reverse;
    else if(std::abs(callerDirection - calleeDirection) == 1)
    {
        //|TOP - BOTTOM| = 1
        //|LEFT - RIGHT| = 1
        connection = nzConnectionType_straight;
    }
    else
        connection = nzConnectionType_orthogonal;

    m_connectionType[neighbour] = connection;
    neighbour->m_connectionType[this] = connection;

    m_connectionDirectionLookup[neighbour] = callerDirection;
    neighbour->m_connectionDirectionLookup[this] = calleeDirection;
}

void NzTerrainQuadTree::DisconnectNeighbor(NzTerrainQuadTree* neighbour, nzNeighbourDirection direction)
{
    nzNeighbourDirection invDirection = direction;
    switch(direction)
    {
        case nzNeighbourDirection_top :
            invDirection = nzNeighbourDirection_bottom;
        break;

        case nzNeighbourDirection_right :
            invDirection = nzNeighbourDirection_left;
        break;

        case nzNeighbourDirection_bottom :
            invDirection = nzNeighbourDirection_top;
        break;

        case nzNeighbourDirection_left :
            invDirection = nzNeighbourDirection_right;
        break;
    }

    m_neighbours[direction] = nullptr;
    neighbour->m_neighbours[invDirection] = nullptr;
}

void NzTerrainQuadTree::Initialize()
{
    m_isInitialized = true;
    //On subdivise l'arbre équitablement au niveau minimum
    m_root->HierarchicalSubdivide(m_commonConfiguration.terrainMinimalPrecision,true);
    //Si on doit améliorer l'arbre là où la pente est la plus forte, on le fait également
    //m_root->HierarchicalSlopeBasedSubdivide(m_commonConfiguration.maxSlopePrecision);
}

NzTerrainQuadTree* NzTerrainQuadTree::GetContainingQuadTree(const NzTerrainNodeID& nodeID)
{
    if(nodeID.locx < 0)
        return m_neighbours[nzNeighbourDirection_left];

    if(nodeID.locy < 0)
        return m_neighbours[nzNeighbourDirection_top];

    if(nodeID.locx > (std::pow(2,nodeID.depth)-1))
        return m_neighbours[nzNeighbourDirection_right];

    if(nodeID.locy > (std::pow(2,nodeID.depth)-1))
        return m_neighbours[nzNeighbourDirection_bottom];

    return nullptr;
}

NzTerrainQuadTree* NzTerrainQuadTree::GetNeighbourQuadTree(nzNeighbourDirection direction)
{
    return m_neighbours[direction];
}

nzNeighbourDirection NzTerrainQuadTree::GetNeighbourDirection(NzTerrainQuadTree* neighbour)
{
    return m_connectionDirectionLookup[neighbour];
}

nzConnectionType NzTerrainQuadTree::GetConnectionType(NzTerrainQuadTree* neighbour)
{
    std::map<NzTerrainQuadTree*,nzConnectionType>::iterator it = m_connectionType.find(neighbour);

    if(it == m_connectionType.end())
        return nzConnectionType_none;
    else
        return it->second;
}

unsigned int NzTerrainQuadTree::GetLeafNodesAmount() const
{
    return m_leaves.size();
}

float NzTerrainQuadTree::GetMaximumHeight() const
{
    return m_commonConfiguration.maxHeight;
}

NzTerrainNode* NzTerrainQuadTree::GetNode(const NzTerrainNodeID& nodeID)
{
    if(m_nodesMap.count(nodeID) == 1)
        return m_nodesMap.at(nodeID);
    else
        return nullptr;
}

NzTerrainNode* NzTerrainQuadTree::GetRootNode()
{
    return m_root;
}

void NzTerrainQuadTree::DeleteNode(NzTerrainNode* node)
{
    //Avant de supprimer un node, on l'envèle des tasks lists si besoin

    std::map<NzTerrainNodeID,NzTerrainNode*>::iterator it = m_refinementQueue.find(node->GetNodeID());

    if(it != m_refinementQueue.end())
        m_refinementQueue.erase(it);

    //Si la camera se déplace très rapidement, un node peut se retrouver à la fois
    //dans la liste de subdivision et de fusion
    it = m_subdivisionQueue.find(node->GetNodeID());
    if(it != m_subdivisionQueue.end())
        m_subdivisionQueue.erase(it);

    it = m_nodesMap.find(node->GetNodeID());

    if(it != m_nodesMap.end())
        m_nodesMap.erase(it);

    NzDynaTerrain::ReturnTerrainNode(node);
}

unsigned int NzTerrainQuadTree::GetSubdivisionsAmount()
{
    unsigned int temp = m_subdivisionsAmount;
    m_subdivisionsAmount = 0;
    return temp;
}

NzVector3f NzTerrainQuadTree::GetVertexPosition(const NzTerrainNodeID& nodeID, int x, int y)
{
    ///Les terrains sont centrées en 0
    ///Avec le système de node
    ///Leur position "affichée" peut changer à l'exécution
    ///La configuration ne peut donc pas contenir la position du terrain, ce doit être géré par lee système de node
    ///Néanmoins, pour un terrain infini, les quadtree autres que le central doivent avoir un offset
    ///Par conséquent la configuration contient la taille du terrain en floattant
    ///Et un offset (x,y) en coordonnées entières

    //Note : nodeID.depth should never be < 0
    float power = 1.f/(1 << nodeID.depth);
    NzVector3f position;

    switch(m_type)
    {
        case nzQuadTreeType_terrain:
            position.x = m_terrainConfiguration.terrainSize * (m_commonConfiguration.x_offset + (x * 0.25f + nodeID.locx) * power);
            position.z = m_terrainConfiguration.terrainSize * (m_commonConfiguration.y_offset + (y * 0.25f + nodeID.locy) * power);
            position.y = m_heightSource2D->GetHeight(position.x,position.z) * m_commonConfiguration.maxHeight;
            return m_rotationMatrix.Transform(position);
        break;

        case nzQuadTreeType_planet:
        default:

            //Les coordonnées d'un plan
            position.x = 2.f * (x * 0.25f + nodeID.locx) / std::pow(2,nodeID.depth) - 1.f;
            position.y = 1.f;
            position.z = 2.f * (y * 0.25f + nodeID.locy) / std::pow(2,nodeID.depth) - 1.f;

            //On normalise le vecteur pour obtenir une sphère
            position.Normalize();
            position *= m_planetConfiguration.planetRadius;

            //On l'oriente correctement
            position = m_rotationMatrix.Transform(position);

            //Et applique la hauteur en cette position (A Optimiser)
            float height = m_heightSource3D->GetHeight(position.x, position.y, position.z) * m_commonConfiguration.maxHeight;
            position.Normalize();
            position *= m_planetConfiguration.planetRadius + height;

            ///position += m_commonConfiguration.center;

            return position;

        break;
    }

}

void NzTerrainQuadTree::RegisterLeaf(NzTerrainNode* node)
{
    if(m_nodesMap.count(node->GetNodeID()) == 0)
    {
        m_leaves.push_back(node);
        m_nodesMap[node->GetNodeID()] = node;
    }
}

bool NzTerrainQuadTree::UnRegisterLeaf(NzTerrainNode* node)
{
    m_leaves.remove(node);

    return true;
}

bool NzTerrainQuadTree::UnRegisterNode(NzTerrainNode* node)
{
    std::map<NzTerrainNodeID,NzTerrainNode*>::iterator it = m_nodesMap.find(node->GetNodeID());

    if(it != m_nodesMap.end())
    {
        m_nodesMap.erase(it);
        return true;
    }
    else
    {
        NazaraError("NzTerrainQuadTree::UnRegisterLeaf : Trying to remove unexisting node" +
                    NzString::Number(node->GetNodeID().depth) + "|" +
                    NzString::Number(node->GetNodeID().locx) + "|" +
                    NzString::Number(node->GetNodeID().locy));
        return false;
    }
}

void NzTerrainQuadTree::Update(const NzVector3f& cameraPosition)
{

    nzUInt64 maxTime = 10;//ms
    std::map<NzTerrainNodeID,NzTerrainNode*>::iterator it;
    int subdivisionsPerFrame = 0;

    //if(updateClock.GetMilliseconds() > 200)
    updateClock.Restart();

    ///A chaque frame, on recalcule quels noeuds sont dans le périmètre de la caméra
    m_root->Update(cameraPosition);

    ///On subdivise les nodes
    it = m_subdivisionQueue.begin();
    while(updateClock.GetMilliseconds() < maxTime/2.f)
    {
        if(it == m_subdivisionQueue.end())
            break;

        it->second->Subdivide();

        m_subdivisionQueue.erase(it);
        it = m_subdivisionQueue.begin();
        subdivisionsPerFrame++;
    }
    if(subdivisionsPerFrame > m_maxOperationsPerFrame)
        m_maxOperationsPerFrame = subdivisionsPerFrame;

    m_subdivisionsAmount += subdivisionsPerFrame;

     ///On refine les nodes nécessaires
    it = m_refinementQueue.begin();
    while(updateClock.GetMilliseconds() < maxTime)
    {
        if(it == m_refinementQueue.end())
            break;

        #if NAZARA_DYNATERRAIN_SAFE
        if(!(it->second->IsValid()))
        {
            NazaraError("Tried to refine non valid node : updateList have been cleaned up");
            m_refinementQueue.erase(it++);
            continue;
        }

        if(it->second == nullptr)
        {
            NazaraError("Tried to refine non existing node : updateList have been cleaned up");
            m_refinementQueue.erase(it++);
            continue;
        }
        #endif

        if(it->second->HierarchicalRefine())
        {
            m_refinementQueue.erase(it++);
        }
        else
            it++;
    }
}

void NzTerrainQuadTree::AddLeaveToSubdivisionQueue(NzTerrainNode* node)
{
    m_subdivisionQueue[node->GetNodeID()] = node;
}

void NzTerrainQuadTree::AddNodeToRefinementQueue(NzTerrainNode* node)
{
    m_refinementQueue[node->GetNodeID()] = node;
}

void NzTerrainQuadTree::TryRemoveNodeFromRefinementQueue(NzTerrainNode* node)
{
    m_refinementQueue.erase(node->GetNodeID());
}

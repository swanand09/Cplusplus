// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/DynaTerrain/Patch.hpp>
#include <Nazara/DynaTerrain/TerrainQuadTree.hpp>
#include <Nazara/TerrainRenderer/TerrainChunksManager.hpp>
#include <cmath>
#include <iostream>
#include <Nazara/DynaTerrain/Debug.hpp>

NzPatch::NzPatch()
{
    m_isInitialized = false;
}

void NzPatch::ComputeHeights()
{
    int j;
    for(int j0(-1) ; j0 < 6 ; ++j0)
    {
        j = j0 + 1;

        m_vertices[0].at(j).ComputePosition(m_data->quadtree, m_id,NzVector2i(-1,j0));
        m_vertices[1].at(j).ComputePosition(m_data->quadtree, m_id,NzVector2i(0,j0));
        m_vertices[2].at(j).ComputePosition(m_data->quadtree, m_id,NzVector2i(1,j0));
        m_vertices[3].at(j).ComputePosition(m_data->quadtree, m_id,NzVector2i(2,j0));
        m_vertices[4].at(j).ComputePosition(m_data->quadtree, m_id,NzVector2i(3,j0));
        m_vertices[5].at(j).ComputePosition(m_data->quadtree, m_id,NzVector2i(4,j0));
        m_vertices[6].at(j).ComputePosition(m_data->quadtree, m_id,NzVector2i(5,j0));
    }

    m_aabb.aabb.x = m_vertices[1][1].GetPosition().x;
    m_aabb.aabb.y = m_vertices[1][1].GetPosition().y;
    m_aabb.aabb.z = m_vertices[1][1].GetPosition().z;
    m_aabb.aabb.width = 0.1f;
    m_aabb.aabb.depth = 0.1f;
    m_aabb.aabb.height = 0.1f;

    for(int j(1) ; j < 6 ; ++j)
    {
        m_aabb.aabb.ExtendTo(m_vertices[1][j].GetPosition());
        m_aabb.aabb.ExtendTo(m_vertices[2][j].GetPosition());
        m_aabb.aabb.ExtendTo(m_vertices[3][j].GetPosition());
        m_aabb.aabb.ExtendTo(m_vertices[4][j].GetPosition());
        m_aabb.aabb.ExtendTo(m_vertices[5][j].GetPosition());
    }
}

void NzPatch::ComputeNormals()
{
    //top, right, bottom, left
    NzVector3f v1,v2,v3,v4;
    NzVector3f v12;
    NzVector3f v23;
    NzVector3f v34;
    NzVector3f v41;
    NzVector3f sum;

    unsigned int i0,j0;

    unsigned int hx,hy;
    NzVector2i normalLocation;

    for(unsigned int j(0) ; j < 5 ; ++j)
        for(unsigned int i(0) ; i < 5 ; ++i)
        {
            i0 = i + 1;
            j0 = j + 1;

            normalLocation.x = (m_id.locx * 4 + i) * std::pow(2,NAZARA_DYNATERRAIN_MAXIMUM_TERRAIN_DEPTH - m_id.depth);
            normalLocation.y = (m_id.locy * 4 + j) * std::pow(2,NAZARA_DYNATERRAIN_MAXIMUM_TERRAIN_DEPTH - m_id.depth);

            if(m_data->normalsManager->IsNormalSet(normalLocation))
            {
                m_data->normalsManager->GetNormal(normalLocation,sum);
            }
            else
            {
                //Compute four vectors
                v1 = m_vertices[i0+1][j0  ].GetPosition();
                v2 = m_vertices[i0  ][j0+1].GetPosition();
                v3 = m_vertices[i0-1][j0  ].GetPosition();
                v4 = m_vertices[i0+1][j0-1].GetPosition();

                v12 = v1.CrossProduct(v2);
                v23 = v2.CrossProduct(v3);
                v34 = v3.CrossProduct(v4);
                v41 = v4.CrossProduct(v1);

                sum = v12 + v23 + v34 + v41;
                sum.Normalize();

                if(sum.y < 0.f)
                    sum *= -1.f;

                m_data->normalsManager->SetNormal(normalLocation,sum,this);
            }
            m_data->normalsManager->AddNormalListenner(normalLocation,this);
            m_vertexNormals.at(i+5*j) = sum;
        }
}

void NzPatch::ComputeSlope()
{
    float slope[25];
    NzVector3f upVector(0.f,1.f,0.f);

    float maxSlope = -10000.f;
    float minSlope = 10000.f;

    for(unsigned int j(0) ; j < 5 ; ++j)
        for(unsigned int i(0) ; i < 5 ; ++i)
        {
            slope[i+5*j] = m_vertexNormals.at(i+5*j).DotProduct(upVector);
            minSlope = std::min(std::fabs(slope[i+5*j]),minSlope);
            maxSlope = std::max(std::fabs(slope[i+5*j]),maxSlope);
        }

        //On calcule le contraste absolu entre la pente la plus forte et la plus faible
        m_slope = (maxSlope - minSlope)/(maxSlope + minSlope);
        float inv_sensitivity = 2;
        m_slope = std::pow(m_slope,inv_sensitivity);
}

void NzPatch::CorrectNormalsAtInterface()
{
    // Normalement, les seuls points dont les normales à corriger
    // lors d'une interface d'adaptation
    // sont (1,1) (1,3) (3,1) (3,3)

    // La seule chose à déterminer est si le point est concerné par deux interfaces
    // (haut et gauche par exemple) à la fois, ou une seule

    //Ensuite, il s'agit juste de calculer les normales avec des points en plus

    //l'état des interfaces, true si en adaptation
    bool top = false, right = false, bottom = false, left = false;
    // true si concerné par une interface en adaptation
    bool p11 = false, p13 = false, p31 = false, p33 = false;
    // true si concerné par 2 interfaces, false si seulement 1
    bool i11 = false, i13 = false, i31 = false, i33 = false;

    left   = (m_configuration & 0x1) == 0x1;
    top    = (m_configuration & 0x2) == 0x2;
    right  = (m_configuration & 0x4) == 0x4;
    bottom = (m_configuration & 0x8) == 0x8;

    p11 = top || left;
    p13 = bottom || left;
    p31 = top || right;
    p33 = bottom || right;

    i11 = top && left;
    i13 = bottom && left;
    i31 = top && right;
    i33 = bottom && right;

    // Avec ces infos on corrige les normales de ce(s) point(s)
}

NzBoundingVolumef& NzPatch::GetAABB()
{
    return m_aabb;
}

const NzBoundingVolumef& NzPatch::GetAABB() const
{
    return m_aabb;
}

float NzPatch::GetGlobalSlope() const
{
    return m_slope;
}

void NzPatch::Initialize(NzTerrainNodeID nodeID, nzTerrainNodeData* data)
{
    Reset();

    m_id = nodeID;
    m_data = data;

    ComputeHeights();
    ComputeNormals();
    ComputeSlope();
}

void NzPatch::InitializeFromParent(NzTerrainNodeID nodeID, nzTerrainNodeData* data, const NzPatch& parentPatch)
{
    Reset();

    m_id = nodeID;
    m_data = data;

    int offx = 2 * (m_id.locx - std::floor(m_id.locx / 2.f) * 2);
    int offy = 2 * (m_id.locy - std::floor(m_id.locy / 2.f) * 2);

    m_vertices[1][1].SetPosition(parentPatch.m_vertices[1 + offx][1 + offy]);
    m_vertices[3][1].SetPosition(parentPatch.m_vertices[2 + offx][1 + offy]);
    m_vertices[5][1].SetPosition(parentPatch.m_vertices[3 + offx][1 + offy]);

    m_vertices[1][3].SetPosition(parentPatch.m_vertices[1 + offx][2 + offy]);
    m_vertices[3][3].SetPosition(parentPatch.m_vertices[2 + offx][2 + offy]);
    m_vertices[5][3].SetPosition(parentPatch.m_vertices[3 + offx][2 + offy]);

    m_vertices[1][5].SetPosition(parentPatch.m_vertices[1 + offx][3 + offy]);
    m_vertices[3][5].SetPosition(parentPatch.m_vertices[2 + offx][3 + offy]);
    m_vertices[5][5].SetPosition(parentPatch.m_vertices[3 + offx][3 + offy]);

    ComputeHeights();
    ComputeNormals();
    ComputeSlope();
}

void NzPatch::Reset()
{
    m_isUploaded = false;
    m_isInitialized = true;
    m_fromScratch = true;

    m_configuration = 0;

    for(int i(0) ; i < 7 ; ++i)
    {
        m_vertices[0][i].Invalidate();
        m_vertices[1][i].Invalidate();
        m_vertices[2][i].Invalidate();
        m_vertices[3][i].Invalidate();
        m_vertices[4][i].Invalidate();
        m_vertices[5][i].Invalidate();
        m_vertices[6][i].Invalidate();
    }
}

void NzPatch::Invalidate()
{
    UnUploadMesh();

    m_isUploaded = false;
    m_isInitialized = true;
    m_fromScratch = true;

    m_configuration = 0;

    for(int i(0) ; i < 7 ; ++i)
    {
        m_vertices[0][i].Invalidate();
        m_vertices[1][i].Invalidate();
        m_vertices[2][i].Invalidate();
        m_vertices[3][i].Invalidate();
        m_vertices[4][i].Invalidate();
        m_vertices[5][i].Invalidate();
        m_vertices[6][i].Invalidate();
    }
}

void NzPatch::OnNormalChanged(NzVector2i normalLocation, const NzVector3f& newValue)
{
    normalLocation.x = normalLocation.x / std::pow(2,NAZARA_DYNATERRAIN_MAXIMUM_TERRAIN_DEPTH - m_id.depth) - m_id.locx;
    normalLocation.y = normalLocation.y / std::pow(2,NAZARA_DYNATERRAIN_MAXIMUM_TERRAIN_DEPTH - m_id.depth) - m_id.locy;

    #if NAZARA_DYNATERRAIN_SAFE
    if(normalLocation.x >= 5 || normalLocation.x < 0 ||
       normalLocation.y >= 5 || normalLocation.y < 0)
       {
           NazaraError("Error in computing normal location : [" + NzString::Number(normalLocation.x) + ";" + NzString::Number(normalLocation.y) + "]");
           return;
       }
    #endif
    m_vertexNormals.at(normalLocation.x + 5 * normalLocation.y) = newValue;
    UploadMesh(false);
}

void NzPatch::SetConfiguration(nzNeighbourDirection toNeighbor, unsigned int levelDifference, bool autoUpdate)
{
    if(!m_isInitialized)
    {
        std::cout<<"NzPatch::SetConfig : invalid patch called : "<<m_id.depth<<"|"<<m_id.locx<<"|"<<m_id.locy<<std::endl;
        return;
    }

    if(levelDifference > 1)
    {
        std::cout<<"Difference of level at interface must be < 1, here : "<<levelDifference<<std::endl;
        return;
    }

    unsigned short int newConfiguration = m_configuration;

    switch(toNeighbor)
    {
        case nzNeighbourDirection_left :
            if(levelDifference == 1)
                newConfiguration = newConfiguration | 0x1;
            else
                newConfiguration = newConfiguration & 0xE;
        break;

        case nzNeighbourDirection_top :
            if(levelDifference)
                newConfiguration = newConfiguration | 0x2;
            else
                newConfiguration = newConfiguration & 0xD;
        break;

        case nzNeighbourDirection_right :
            if(levelDifference == 1)
                newConfiguration = newConfiguration | 0x4;
            else
                newConfiguration = newConfiguration & 0xB;
        break;

        case nzNeighbourDirection_bottom :
            if(levelDifference)
                newConfiguration = newConfiguration | 0x8;
            else
                newConfiguration = newConfiguration & 0x7;
        break;
    }

    if(newConfiguration != m_configuration)
    {
        m_configuration = newConfiguration;
        UploadMesh(false);
    }
}

void NzPatch::UploadMesh(bool firstTime)
{
    if(!m_isInitialized)
    {
        std::cout<<"NzPatch::SetConfig : invalid patch called : old node : "<<m_id.depth<<"|"<<m_id.locx<<"|"<<m_id.locy<<std::endl;
        return;
    }

    unsigned int index, index2, index3, i2, j2;

    for(int j(0) ; j < 5 ; ++j)
        for(int i(0) ; i < 5 ; ++i)
        {
            index = i+5*j;

            i2 = i;
            j2 = j;

            if(((m_configuration & 0x1) == 0x1) && (index == 5 || index == 15))
                j2 += 1;
            else if(((m_configuration & 0x4) == 0x4) && (index == 9 || index == 19))
                j2 -= 1;
            else if((m_configuration & 0x2) == 0x2 && (index == 1 || index == 3))
                i2 += 1;
            else if((m_configuration & 0x8) == 0x8 && (index == 21 || index == 23))
                i2 -= 1;

            index2 = (i2+1)+7*(j2+1);
            index3 = i2 + 5*j2;

            //Position
            m_uploadedData.at((index)*6)   = m_vertices[i2 + 1][j2 + 1].GetPosition().x;
            m_uploadedData.at((index)*6+1) = m_vertices[i2 + 1][j2 + 1].GetPosition().y;
            m_uploadedData.at((index)*6+2) = m_vertices[i2 + 1][j2 + 1].GetPosition().z;
            //Normales
            m_uploadedData.at((index)*6+3) = m_vertexNormals.at(index3).x;
            m_uploadedData.at((index)*6+4) = m_vertexNormals.at(index3).y;
            m_uploadedData.at((index)*6+5) = m_vertexNormals.at(index3).z;
        }

    if(firstTime)
        m_data->chunksManager->AddMesh(m_uploadedData,m_aabb, m_id);
    else
        m_data->chunksManager->UpdateMesh(m_uploadedData,m_aabb, m_id);

    m_isUploaded = true;
}

void NzPatch::UnUploadMesh()
{
    if(m_isUploaded)
    {
        m_data->chunksManager->RemoveMesh(m_aabb, m_id);
        m_isUploaded = false;
    }
}


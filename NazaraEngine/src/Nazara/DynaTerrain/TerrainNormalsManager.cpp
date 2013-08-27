// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/DynaTerrain/TerrainNormalsManager.hpp>
#include <Nazara/DynaTerrain/Debug.hpp>

NzTerrainNormalsManager::NzTerrainNormalsManager()
{

}

void NzTerrainNormalsManager::AddNormalListenner(const NzVector2i& location, NzPatch* patch)
{
    auto it = m_locationToNormalTable.find(location);

    if(it != m_locationToNormalTable.end())
    {
        it->second.listenners.insert(patch);
    }
    #if NAZARA_DYNATERRAIN_SAFE
    else
    {
        NazaraError("Trying to add listenner to non-existing normal");
    }
    #endif
}

bool NzTerrainNormalsManager::GetNormal(const NzVector2i& location, NzVector3f& normal)
{
    auto it = m_locationToNormalTable.find(location);

    if(it != m_locationToNormalTable.end())
    {
        normal = it->second.v;
        return true;
    }
    return false;
}

bool NzTerrainNormalsManager::IsNormalSet(const NzVector2i& location) const
{
    auto it = m_locationToNormalTable.find(location);

    if(it != m_locationToNormalTable.end())
    {
        return true;
    }
    return false;
}

void NzTerrainNormalsManager::RemoveNormalListenner(const NzVector2i& location, NzPatch* patch)
{
    auto it = m_locationToNormalTable.find(location);

    if(it != m_locationToNormalTable.end())
    {
        auto it2 =  it->second.listenners.find(patch);

        if(it2 != it->second.listenners.end())
        {
            it->second.listenners.erase(it2);
        }
        #if NAZARA_DYNATERRAIN_SAFE
        else
        {
            NazaraError("Trying to remove non-existing listenner from an existing normal");
        }
        #endif
    }
    #if NAZARA_DYNATERRAIN_SAFE
    else
    {
        NazaraError("Trying to remove listenner to non-existing normal");
    }
    #endif
}

bool NzTerrainNormalsManager::SetNormal(const NzVector2i& location, const NzVector3f& normal, NzPatch* setterPatch)
{
    auto it = m_locationToNormalTable.find(location);

    if(it == m_locationToNormalTable.end())
    {
        customStruct temp;
        temp.v = normal;
        m_locationToNormalTable.insert(std::pair<NzVector2i,customStruct>(location,temp));
    }
    else
    {
        it->second.v = normal;

        for(auto i = it->second.listenners.begin() ; i != it->second.listenners.end() ; ++i)
        {
            if((*i) != setterPatch)
                (*i)->OnNormalChanged(location,normal);
        }
    }
}

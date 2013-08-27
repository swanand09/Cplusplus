// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_TERRAINNORMALSMANAGER_HPP
#define NAZARA_TERRAINNORMALSMANAGER_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/DynaTerrain/Enums.hpp>
#include <Nazara/DynaTerrain/Patch.hpp>
#include <set>
#include <map>

class NAZARA_API NzTerrainNormalsManager
{
    public:
        NzTerrainNormalsManager();
        ~NzTerrainNormalsManager() = default;

        void AddNormalListenner(const NzVector2i& location, NzPatch* patch);

        bool GetNormal(const NzVector2i& location, NzVector3f& normal);

        bool IsNormalSet(const NzVector2i& location) const;

        void RemoveNormalListenner(const NzVector2i& location, NzPatch* patch);

        bool SetNormal(const NzVector2i& location, const NzVector3f& normal, NzPatch* setterPatch);

    protected:
    private:
        struct customStruct
        {
            NzVector3f v;
            std::set<NzPatch*> listenners;
        };

        std::map<NzVector2i,customStruct> m_locationToNormalTable;
};

#endif // NAZARA_TERRAINNORMALSMANAGER_HPP

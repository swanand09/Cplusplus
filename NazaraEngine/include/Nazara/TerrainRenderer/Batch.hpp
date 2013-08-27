// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine - Terrain Renderer module".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_BATCH_HPP
#define NAZARA_BATCH_HPP

#include <Nazara/Prerequesites.hpp>

class NAZARA_API NzBatch
{
    public:
        NzBatch(unsigned int start, unsigned int count);
        ~NzBatch();

        bool Add(unsigned int index);
        int Remove(unsigned int index, NzBatch& newBatch);

        bool Contains(unsigned int index) const;
        unsigned int Count() const;

        bool IsEmpty() const;

        bool IsAfter(unsigned int index) const;
        bool IsAtLast(unsigned int index) const;
        bool IsBefore(unsigned int index) const;
        bool IsRightAfter(unsigned int index) const;
        bool IsRightBefore(unsigned int index) const;

        bool MergeWith(const NzBatch& batch);

        unsigned int Start() const;

    protected:
    private:
        nzUInt16 m_index;
        nzUInt16 m_count;
};

#endif // NAZARA_BATCH_HPP

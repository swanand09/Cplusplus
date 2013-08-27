// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_OBJECTPOOL_HPP
#define NAZARA_OBJECTPOOL_HPP

#include <Nazara/Prerequesites.hpp>
#include <deque>
#include <list>

template <typename T> class NzObjectPool
{
    public:
        NzObjectPool(std::size_t chunkSize = 10);
        ~NzObjectPool() = default;

        T* GetObjectPtr();
        std::size_t GetPoolSize() const;
        void Grow();

        void ReleaseAll();
        void ReturnObjectPtr(T* pointer);

        void SetChunkSize(std::size_t chunkSize);

    protected:
    private:
    std::deque<T> m_objects;
    std::list<T*> m_freePointers;
    std::size_t m_chunkSize;
    std::size_t m_totalSize;
};

#include "ObjectPool.inl"

#endif // NAZARA_OBJECTPOOL_HPP

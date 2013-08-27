// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

template<typename T>
NzObjectPool<T>::NzObjectPool(std::size_t chunkSize)
{
    m_chunkSize = chunkSize;
    m_totalSize = 0;
    Grow();
}

template<typename T>
T* NzObjectPool<T>::GetObjectPtr()
{
    if(m_freePointers.empty())
        Grow();

    T* pointer = m_freePointers.front();
    m_freePointers.pop_front();
    return pointer;
}

template<typename T>
void NzObjectPool<T>::Grow()
{
    m_objects.resize(m_totalSize + m_chunkSize);
    m_totalSize += m_chunkSize;

    typename std::deque<T>::iterator it = m_objects.end();
    --it;

    for(std::size_t i(0) ; i < m_chunkSize ; ++i)
    {
        m_freePointers.push_front(&(*it));
        --it;
    }
}

template<typename T>
std::size_t NzObjectPool<T>::GetPoolSize() const
{
    return m_objects.size();
}

template<typename T>
void NzObjectPool<T>::ReleaseAll()
{
    m_freePointers.clear();
    std::deque<T> emptyContainer;
    m_objects.swap(emptyContainer);
    m_totalSize = 0;
}

template<typename T>
void NzObjectPool<T>::ReturnObjectPtr(T* pointer)
{
    m_freePointers.push_back(pointer);
    //m_freePointers.push_front(pointer);//FIX ME : WHat's better ?
}

template<typename T>
void NzObjectPool<T>::SetChunkSize(std::size_t chunkSize)
{
    m_chunkSize = chunkSize;
}

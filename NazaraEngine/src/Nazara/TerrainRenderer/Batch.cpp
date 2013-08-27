// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine - Terrain Renderer module".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/TerrainRenderer/Batch.hpp>

NzBatch::NzBatch(unsigned int start, unsigned int count)
{
    m_index = start;
    m_count = count;
}

NzBatch::~NzBatch()
{
    //dtor
}

bool NzBatch::Add(unsigned int index)
{
    if(IsRightAfter(index))
    {
        m_count++;
        return true;
    }
    else if(IsRightBefore(index))
    {
        m_index--;
        m_count++;
        return true;
    }
    else
        return false;

}

int NzBatch::Remove(unsigned int index, NzBatch& newBatch)
{
    if(index == m_index)
    {
        m_index++;
        m_count--;

        if(IsEmpty())
            return 0;
        else
            return 1;
    }
    else if(IsAtLast(index))
    {
        m_count--;
        if(IsEmpty())
            return 0;
        else
            return 1;
    }
    else if(Contains(index))
    {
        newBatch.m_count = m_count - (index - m_index + 1);
        newBatch.m_index = index + 1;
        //Never empty
        m_count = index - m_index;
        return 2;
    }
    else
        return -1;
}

bool NzBatch::Contains(unsigned int index) const
{
    return index >= m_index && index < m_index + m_count;
}

unsigned int NzBatch::Count() const
{
    return m_count;
}

bool NzBatch::IsEmpty() const
{
    return m_count == 0;
}

bool NzBatch::IsAfter(unsigned int index) const
{
    return index > m_index + m_count;
}

bool NzBatch::IsAtLast(unsigned int index) const
{
    return index == m_index + m_count - 1;
}

bool NzBatch::IsBefore(unsigned int index) const
{
    return index < m_index - 1;
}

bool NzBatch::IsRightAfter(unsigned int index) const
{
    return index == m_index + m_count;
}

bool NzBatch::IsRightBefore(unsigned int index) const
{
    return index == m_index - 1;
}

 bool NzBatch::MergeWith(const NzBatch& batch)
 {
        if(IsRightAfter(batch.m_index))
        {
            m_count += batch.m_count;
            return true;
        }
        else
            return false;
 }

unsigned int NzBatch::Start() const
{
    return m_index;
}


// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine - Terrain Interval module".
// For conditions of distribution and use, see copyright notice in Config.hpp

template <typename T>
NzIntervalBuffer<T>::NzIntervalBuffer(unsigned int bufferSize)
{
    m_bufferSize = bufferSize;
    m_occupiedSlotsAmount = 0;
    //Il y a m_bufferSize cases de libres à partir de l'index 0
    m_freeSlotBatches.push_front(NzBatch(0,bufferSize));

    m_occupationMap.assign(bufferSize,false);
}
/*
template <typename T>
T NzIntervalBuffer<T>::at(unsigned int index)
{
    //TODO
}
*/
template <typename T>
bool NzIntervalBuffer<T>::IsFilled(unsigned int index)
{
    return m_occupationMap.at(index);
}

template <typename T>
int NzIntervalBuffer<T>::FindValue(const T& value) const
{
    //On récupère l'emplacement de la valeur
    typename std::map<T,int>::const_iterator it = m_slots.find(value);

    //Si la valeur n'existe pas dans le buffer
    if(it == m_slots.end())
        return -1;

    return (*it).second;
}

template <typename T>
bool NzIntervalBuffer<T>::FillFreeSlot(unsigned int index, const T& value)
{
    //On vérifie que l'emplacement ne soit pas déjà occupé
    if(IsFilled(index))
        return false;

    //On vérifie que la clé ne soit pas déjà utilisée
    if(m_slots.find(value) != m_slots.end())
        return false;

    //On ajoute la valeur dans le buffer à l'emplacement libre
    m_slots[value] = index;

    if(!AtomicKeyRemoval(m_freeSlotBatches,index))
        return false;

    //L'insertion ne peut normalement pas échouer car l'index est valide
    AtomicKeyInsertion(m_filledSlotBatches,index);
    m_occupationMap.at(index) = true;
    m_occupiedSlotsAmount++;

    return true;
}

template <typename T>
bool NzIntervalBuffer<T>::FreeFilledSlot(unsigned int index, const T& value)
{
    // On vérifie que l'emplacement à supprimer soit bien plein
    if(!IsFilled(index))
        return false;

    //On supprime la valeur dans le buffer
    //FIXME : vérifier que ça a bien été fait, que faire dans le cas contraire ?
    m_slots.erase(value);

    if(!AtomicKeyRemoval(m_filledSlotBatches,index))
        return false;

    //L'insertion ne peut pas échouer
    AtomicKeyInsertion(m_freeSlotBatches,index);
    m_occupationMap.at(index) = false;
    m_occupiedSlotsAmount--;

    return true;
}

template <typename T>
int NzIntervalBuffer<T>::GetFreeSlot() const
{
    //On vérifie qu'il y ait bien de la place
    if(m_occupiedSlotsAmount == m_bufferSize)
        return -1;

    //On récupère le premier emplacement libre avec m_freeSlotBatches
    return m_freeSlotBatches.front().Start();
}

template <typename T>
unsigned int NzIntervalBuffer<T>::GetFilledSlotsAmount() const
{
    return m_occupiedSlotsAmount;
}

template <typename T>
const std::list<NzBatch>& NzIntervalBuffer<T>::GetFilledIntervals() const
{
    return m_filledSlotBatches;
}

template <typename T>
std::list<NzBatch> NzIntervalBuffer<T>::GetFilledIntervalsCopy()
{
    return m_filledSlotBatches;
}

template <typename T>
const std::list<NzBatch>& NzIntervalBuffer<T>::GetFreeIntervals() const
{
    return m_freeSlotBatches;
}

template <typename T>
std::list<NzBatch> NzIntervalBuffer<T>::GetFreeIntervalsCopy()
{
    return m_freeSlotBatches;
}

template <typename T>
unsigned int NzIntervalBuffer<T>::GetFreeSlotsAmount() const
{
    return m_bufferSize - m_occupiedSlotsAmount;
}

template <typename T>
NzVector2i NzIntervalBuffer<T>::ReduceFragmentation()
{
    return NzVector2i(0,0);
}

template <typename T>
bool NzIntervalBuffer<T>::AtomicKeyInsertion(std::list<NzBatch>& buffer, unsigned int index)
{
    std::list<NzBatch>::iterator it;
    std::list<NzBatch>::iterator it_2;
    std::list<NzBatch>::iterator it_last = buffer.end();
    it_last--;

    //Si il n'y a pas d'espace disponible on en crée un et on lui affecte immédiatement la valeur
    if(buffer.empty())
    {
        buffer.push_front(NzBatch(index,1));
        it = buffer.begin();
    }
    else
    {
        //On l'ajoute à la liste des batches pleins
        for(it = buffer.begin() ; it != buffer.end() ; ++it)
        {
            if(it->Add(index))//Ajout à un emplacement existant réussi
            {
                break;
            }
            else if(it->Start() > index + 1)//Création d'un nouveau bloc nécessaire
            {
                buffer.insert(it,NzBatch(index,1));
                break;
            }
            else if(it == it_last)//L'index est situé après le dernier emplacement, création d'un nouveau bloc a la fin
            {
                buffer.push_back(NzBatch(index,1));
                break;
            }
        }

    }

    //L'insertion a été réalisée, maintenant on regarde si un regroupement (avant et/ou après) est possible

    //avant
    if(it != buffer.begin())
    {
        it--;
        it_2 = it;
        it++;

        if(it_2->MergeWith(*it))
        {
            it = buffer.erase(it);
        }
    }

    //après
    it++;
    if(it != buffer.end())
    {
        it_2 = it;
        it--;

        if(it->MergeWith(*it_2))
        {
            it = buffer.erase(it_2);
        }
    }

    return true;
}

template <typename T>
bool NzIntervalBuffer<T>::AtomicKeyRemoval(std::list<NzBatch>& buffer, unsigned int index)
{
    std::list<NzBatch>::iterator it;
    std::list<NzBatch>::iterator it_2;
    std::list<NzBatch>::iterator it_last = buffer.end();
    it_last--;

    //Si il n'y a pas d'emplacements occupés, aucune suppression à effectuer
    if(buffer.empty())
    {
        return false;
    }
    else
    {
        int situation;
        NzBatch temp(0,0);

        //On l'ajoute à la liste des batches pleins
        for(it = buffer.begin() ; it != buffer.end() ; ++it)
        {
            situation = it->Remove(index,temp);

            if(situation == 2)//Une suppression au milieu a eu lieu, un nouvel emplacement a été créé
            {
                ++it;
                buffer.insert(it,temp);
                --it;
                break;
            }
            else if(situation == 1)
            {
                //La suppression s'est faite sans encombres
                break;
            }
            else if(situation == 0)
            {
                //Le bloc est vide, on le supprime
                it = buffer.erase(it);
                break;
            }
        }

    }

    return true;
}

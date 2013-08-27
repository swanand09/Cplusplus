// Copyright (C) 2012 Jérôme Leclercq
// This file is part of the "Nazara Engine - Mathematics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/StringStream.hpp>
#include <iostream>
#include <algorithm>
#include <Nazara/Math/Segment.hpp>
#include <Nazara/Math/Rect.hpp>
#include <Nazara/Core/Debug.hpp>

#define F(a) static_cast<T>(a)

template<typename T>
NzCircle<T>::NzCircle(T centerX, T centerY, T radius)
{
	Set(centerX,centerY,radius);
}

template<typename T>
NzCircle<T>::NzCircle(const NzVector2<T>& center, T radius)
{
	Set(center,radius);
}

template<typename T>
template<typename U>
NzCircle<T>::NzCircle(const NzCircle<U>& circle)
{
	Set(circle);
}

template<typename T>
bool NzCircle<T>::Contains(T X, T Y) const
{
	return center.SquaredDistance(NzVector2<T>(X,Y)) <= GetSquaredRadius();
}

template<typename T>
bool NzCircle<T>::Contains(const NzVector2<T>& point) const
{
	return Contains(point.x, point.y);
}

template<typename T>
bool NzCircle<T>::Contains(const NzCircle<T>& circle) const
{
	return center.SquaredDistance(circle.center) + circle.GetSquaredRadius() <= GetSquaredRadius();
}


template<typename T>
bool NzCircle<T>::Contains(const NzRect<T>& rect) const
{
	return Contains(rect.x, rect.y) &&
           Contains(rect.x, rect.y + rect.height) &&
           Contains(rect.x + rect.width, rect.y) &&
           Contains(rect.x + rect.width, rect.y + rect.height);
}


template<typename T>
NzCircle<T>& NzCircle<T>::ExtendTo(const NzVector2<T>& point)
{
	radius = std::max(center.Distance(point), radius);

	return *this;
}

template<typename T>
NzRect<T> NzCircle<T>::GetBoundingRect() const
{
    return NzRect<T>(center.x - radius, center.y - radius, 2 * radius, 2 * radius);
}

template<typename T>
T NzCircle<T>::GetSquaredRadius() const
{
	return radius * radius;
}

template<typename T>
bool NzCircle<T>::Intersect(const NzCircle& circle) const
{
    return center.SquaredDistance(circle.center) + circle.GetSquaredRadius() > GetSquaredRadius() &&
           center.SquaredDistance(circle.center) <= GetSquaredRadius() + circle.GetSquaredRadius();
}

template<typename T>
bool NzCircle<T>::Intersect(const NzRect<T>& rect) const
{
    NzRect<T> AABB = GetBoundingRect();

    if(!AABB.Intersect(rect))
        return false;

    unsigned int count = 0;

    if(Contains(rect.x, rect.y))
        count++;
    if(Contains(rect.x, rect.y + rect.height))
        count++;
    if(Contains(rect.x + rect.width, rect.y))
        count++;
    if(Contains(rect.x + rect.width, rect.y + rect.height))
        count++;

    if(count >= 1 && count < 4)
        return true;

    if(rect.Contains(center))
      return true;

    NzSegment<T> vertical(rect.x, rect.y, rect.x, rect.y + rect.height);
    NzSegment<T> horizontal(rect.x, rect.y, rect.x + rect.width, rect.y);

    return vertical.IsPointProjectionPossible(center) ^ horizontal.IsPointProjectionPossible(center);
}

template<typename T>
bool NzCircle<T>::IsValid() const
{
	return radius > F(0.0);
}

template<typename T>
NzCircle<T>& NzCircle<T>::MakeZero()
{
	center.x = F(0.0);
	center.y = F(0.0);
	radius = F(0.0);

	return *this;
}

template<typename T>
NzCircle<T>& NzCircle<T>::Set(T centerX, T centerY, T Radius)
{
	center.x = centerX;
	center.y = centerY;
	radius = Radius;

	return *this;
}

template<typename T>
NzCircle<T>& NzCircle<T>::Set(const NzVector2<T>& Center, T Radius)
{
	center = Center;
	radius = Radius;

	return *this;
}

template<typename T>
template<typename U>
NzCircle<T>& NzCircle<T>::Set(const NzCircle<U>& circle)
{
	center = F(circle.center);
	radius = F(circle.radius);

	return *this;
}

template<typename T>
NzString NzCircle<T>::ToString() const
{
	NzStringStream ss;

	return ss << "Circle(" << center.x << ", " << center.y << ", " << radius << ')';
}

template<typename T>
NzCircle<T>::operator NzString() const
{
	return ToString();
}

template<typename T>
NzCircle<T> NzCircle<T>::operator*(T scalar) const
{
	return NzCircle(center, radius*scalar);
}

template<typename T>
NzCircle<T>& NzCircle<T>::operator*=(T scalar)
{
	radius *= scalar;
}

template<typename T>
bool NzCircle<T>::operator==(const NzCircle& circle) const
{
	return center == circle.center && NzNumberEquals(radius, circle.radius);
}

template<typename T>
bool NzCircle<T>::operator!=(const NzCircle& circle) const
{
	return !operator==(circle);
}

template<typename T>
NzCircle<T> NzCircle<T>::Lerp(const NzCircle& from, const NzCircle& to, T interpolation)
{
	#ifdef NAZARA_DEBUG
	if (interpolation < F(0.0) || interpolation > F(1.0))
	{
		NazaraError("Interpolation must be in range [0..1] (Got " + NzString::Number(interpolation) + ')');
		return Zero();
	}
	#endif

	NzCircle circle;
	circle.center.x = NzLerp(from.center.x, to.center.x, interpolation);
	circle.center.y = NzLerp(from.center.y, to.center.y, interpolation);
	circle.radius = NzLerp(from.radius, to.radius, interpolation);

	return circle;
}

template<typename T>
NzCircle<T> NzCircle<T>::Zero()
{
	NzCircle circle;
	circle.MakeZero();

	return circle;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const NzCircle<T>& circle)
{
	return out << circle.ToString();
}

#undef F

#include <Nazara/Core/DebugOff.hpp>

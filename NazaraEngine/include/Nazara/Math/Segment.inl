// Copyright (C) 2012 Jérôme Leclercq
// This file is part of the "Nazara Engine - Mathematics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/StringStream.hpp>
#include <algorithm>
#include <Nazara/Core/Debug.hpp>

#define F(a) static_cast<T>(a)

template<typename T>
NzSegment<T>::NzSegment(const NzVector2<T>& A, const NzVector2<T>& B)
{
	Set(A,B);
}

template<typename T>
NzSegment<T>::NzSegment(T Ax, T Ay, T Bx, T By)
{
	Set(Ax,Ay,Bx,By);
}

template<typename T>
template<typename U>
NzSegment<T>::NzSegment(const NzSegment<U>& segment)
{
	Set(segment);
}

template<typename T>
T NzSegment<T>::GetSquaredLenght() const
{
	return A.SquaredDistance(B);
}

template<typename T>
bool NzSegment<T>::Intersect(const NzSegment<T>& segment) const
{
    if(!IntersectWithLine(segment))
        return false;

    return segment.IntersectWithLine(*this);
}

template<typename T>
bool NzSegment<T>::Intersect(const NzCircle<T>& circle) const
{
    return circle.Contains(A) ^ circle.Contains(B);
}

template<typename T>
bool NzSegment<T>::Intersect(const NzRect<T>& rect) const
{
    //FIX ME : TODO
}

template<typename T>
bool NzSegment<T>::IntersectWithLine(const NzSegment<T>& segment) const
{
    NzVector2<T> AO,AP,AB;
    AB = B - A;
    AP = segment.B - A;
    AO = segment.A - A;

    return AB.Determinant(AP) * AB.Determinant(AO) < 0;
}

template<typename T>
bool NzSegment<T>::IsValid() const
{
	return A.Distance(B) > F(0.0);
}

template<typename T>
NzSegment<T>& NzSegment<T>::MakeZero()
{
	A.x = F(0.0);
	A.y = F(0.0);
	B.x = F(0.0);
	B.y = F(0.0);

	return *this;
}

template<typename T>
bool NzSegment<T>::IsPointProjectionPossible(const NzVector2<T>& point)
{
    NzVector2<T> AC = point - A;
    NzVector2<T> AB = B - A;
    NzVector2<T> BC = point - B;

    return AC.DotProduct(AB) + BC.DotProduct(AB) < 0;
}

template<typename T>
NzSegment<T>& NzSegment<T>::Set(T Ax, T Ay, T Bx, T By)
{
	A.x = Ax;
	A.y = Ay;
	B.x = Bx;
	B.y = By;

	return *this;
}

template<typename T>
NzSegment<T>& NzSegment<T>::Set(const NzVector2<T>& P1, const NzVector2<T>& P2)
{
	A = P1;
	B = P2;

	return *this;
}

template<typename T>
template<typename U>
NzSegment<T>& NzSegment<T>::Set(const NzSegment<U>& segment)
{
	A = F(segment.A);
	B = F(segment.B);

	return *this;
}

template<typename T>
NzString NzSegment<T>::ToString() const
{
	NzStringStream ss;

	return ss << "Segment(" << A.x << ", " << A.y << ", " << B.x << ", "<< B.y << ')';
}

template<typename T>
NzSegment<T>::operator NzString() const
{
	return ToString();
}

template<typename T>
NzSegment<T> NzSegment<T>::operator*(T scalar) const
{
	return NzSegment(A * scalar, B*scalar);
}

template<typename T>
NzSegment<T>& NzSegment<T>::operator*=(T scalar)
{
	A *= scalar;
	B *= scalar;
}

template<typename T>
bool NzSegment<T>::operator==(const NzSegment& segment) const
{
	return A == segment.A && B == segment.B;
}

template<typename T>
bool NzSegment<T>::operator!=(const NzSegment& segment) const
{
	return !operator==(segment);
}

template<typename T>
NzSegment<T> NzSegment<T>::Lerp(const NzSegment& from, const NzSegment& to, T interpolation)
{
	#ifdef NAZARA_DEBUG
	if (interpolation < F(0.0) || interpolation > F(1.0))
	{
		NazaraError("Interpolation must be in range [0..1] (Got " + NzString::Number(interpolation) + ')');
		return Zero();
	}
	#endif

	NzSegment segment;
	segment.A = NzLerp(from.A, to.A, interpolation);
	segment.B = NzLerp(from.B, to.B, interpolation);

	return segment;
}

template<typename T>
NzSegment<T> NzSegment<T>::Zero()
{
	NzSegment segment;
	segment.MakeZero();

	return segment;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const NzSegment<T>& segment)
{
	return out << segment.ToString();
}

#undef F

#include <Nazara/Core/DebugOff.hpp>

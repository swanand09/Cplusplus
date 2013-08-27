// Copyright (C) 2012 Jérôme Leclercq
// This file is part of the "Nazara Engine - Mathematics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_SEGMENT_HPP
#define NAZARA_SEGMENT_HPP

#include <Nazara/Core/String.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Math/Rect.hpp>

template<typename T>
class NzSegment
{
	public:
		NzSegment() = default;
		NzSegment(const NzVector2<T>& A, const NzVector2<T>& B);
		NzSegment(T Ax, T Ay, T Bx, T By);
		template<typename U> explicit NzSegment(const NzSegment<U>& segment);
		NzSegment(const NzSegment& segment) = default;
		~NzSegment() = default;

		T GetSquaredLenght() const;

        bool Intersect(const NzSegment& segment) const;
		bool Intersect(const NzRect<T>& rect) const;
		bool Intersect(const NzCircle<T>& circle) const;
		bool IntersectWithLine(const NzSegment& segment) const;

		bool IsValid() const;

		NzSegment& MakeZero();

		bool IsPointProjectionPossible(const NzVector2<T>& point);

		NzSegment& Set(T Ax, T Ay, T Bx, T By);
		NzSegment& Set(const NzVector2<T>& P1, const NzVector2<T>& P2);
		template<typename U> NzSegment& Set(const NzSegment<U>& segment);

		NzString ToString() const;

		operator NzString() const;

		NzSegment operator*(T scalar) const;

		NzSegment& operator*=(T scalar);

		bool operator==(const NzSegment& segment) const;
		bool operator!=(const NzSegment& segment) const;

		static NzSegment Lerp(const NzSegment& from, const NzSegment& to, T interpolation);
		static NzSegment Zero();

		NzVector2<T> A, B;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const NzSegment<T>& segment);

typedef NzSegment<double> NzSegmentd;
typedef NzSegment<float> NzSegmentf;
typedef NzSegment<int> NzSegmenti;
typedef NzSegment<unsigned int> NzSegmentui;

#include <Nazara/Math/Segment.inl>

#endif // NAZARA_CIRCLE_HPP

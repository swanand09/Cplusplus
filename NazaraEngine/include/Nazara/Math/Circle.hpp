// Copyright (C) 2012 Jérôme Leclercq
// This file is part of the "Nazara Engine - Mathematics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_CIRCLE_HPP
#define NAZARA_CIRCLE_HPP

#include <Nazara/Core/String.hpp>
#include <Nazara/Math/Vector2.hpp>

template<typename T> class NzRect;

template<typename T>
class NzCircle
{
	public:
		NzCircle() = default;
		NzCircle(T centerX, T centerY, T radius);
		NzCircle(const NzVector2<T>& center, T radius);
		template<typename U> explicit NzCircle(const NzCircle<U>& circle);
		NzCircle(const NzCircle& circle) = default;
		~NzCircle() = default;

		bool Contains(T X, T Y) const;
		bool Contains(const NzVector2<T>& point) const;
		bool Contains(const NzCircle& circle) const;
		bool Contains(const NzRect<T>& rect) const;

		NzCircle& ExtendTo(const NzVector2<T>& point);

		NzRect<T> GetBoundingRect() const;

		T GetSquaredRadius() const;

		bool Intersect(const NzRect<T>& rect) const;
		bool Intersect(const NzCircle& circle) const;

		bool IsValid() const;

		NzCircle& MakeZero();

		NzCircle& Set(T centerX, T centerY, T Radius);
		NzCircle& Set(const NzVector2<T>& Center, T Radius);
		template<typename U> NzCircle& Set(const NzCircle<U>& circle);

		NzString ToString() const;

		operator NzString() const;

		NzCircle operator*(T scalar) const;

		NzCircle& operator*=(T scalar);

		bool operator==(const NzCircle& circle) const;
		bool operator!=(const NzCircle& circle) const;

		static NzCircle Lerp(const NzCircle& from, const NzCircle& to, T interpolation);
		static NzCircle Zero();

		NzVector2<T> center;
		T radius;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const NzCircle<T>& circle);

typedef NzCircle<double> NzCircled;
typedef NzCircle<float> NzCirclef;
typedef NzCircle<int> NzCirclei;
typedef NzCircle<unsigned int> NzCircleui;

#include <Nazara/Math/Circle.inl>

#endif // NAZARA_CIRCLE_HPP

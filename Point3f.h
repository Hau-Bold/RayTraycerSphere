#pragma once

#ifndef _POINT_3F_H__
#define _POINT_3F_H__

#include<math.h>

class Point3f
{
public:
	float m_X, m_Y, m_Z;

	Point3f() : m_X(0.0), m_Y(0.0), m_Z(0.0) {}

	Point3f(float x) : m_X(x), m_Y(x), m_Z(x) {}

	Point3f(float x, float y, float z) : m_X(x), m_Y(y), m_Z(z) {}


	Point3f normalize();

	Point3f getMultipliedWith(const float & f);
	

	Point3f operator * (const Point3f &other) const { return Point3f(m_X * other.m_X, m_Y * other.m_Y, m_Z * other.m_Z); }
	Point3f operator - (const Point3f &other) const { return Point3f(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z); }
	Point3f operator + (const Point3f &other) const { return Point3f(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z); }
	Point3f operator += (const Point3f &other) { m_X += other.m_X, m_Y += other.m_Y, m_Z += other.m_Z; return *this; }
	Point3f operator *= (const Point3f &other) { m_X *= other.m_X, m_Y *= other.m_Y, m_Z *= other.m_Z; return *this; }

	float dot(const Point3f &other) const { return m_X * other.m_X + m_Y * other.m_Y + m_Z * other.m_Z; }
	float length2() const { return m_X * m_X + m_Y * m_Y + m_Z * m_Z; }
	float length() const { return sqrt(length2()); }

};



#endif

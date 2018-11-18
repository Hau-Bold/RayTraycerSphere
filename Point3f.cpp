#include "Point3f.h"


Point3f Point3f::normalize()
{
	float nor2 = length2();
	if (nor2 > 0) {
		float invNor = 1 / sqrt(nor2);
		m_X *= invNor, m_Y *= invNor, m_Z *= invNor;
	}
	return *this;
}

Point3f Point3f::cross(Point3f & other)
{
	float u = m_Y * other.m_Z + m_Z * other.m_Y;
	float v = m_Z * other.m_X + m_X * other.m_Z;
	float w = m_X * other.m_Y + m_Y * other.m_X;

	return Point3f(u, v, w);
}

Point3f Point3f::getMultipliedWith(float & f)
{
	float x=m_X * f;
	float y=m_Y * f;
	float z=m_Z * f;

	return Point3f(x,y,z);
}

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

Point3f Point3f::getMultipliedWith(const float & f)
{
	m_X *= f;
	m_Y *= f;
	m_Z *= f;

	return *this;
}

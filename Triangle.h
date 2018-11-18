#pragma once
#ifndef TRIANGLE_H__
#define TRIANGLE_H__

#include "Point3f.h"
#include "Ray.h"

#include "Constants.h"

class Triangle
{
private:
	Point3f m_A, m_B, m_C;
	Point3f m_Center,m_Normal;

	Point3f m_SurfaceColor, m_EmissionColor; /// surface color and emission (light)
	float m_Transparency, m_Reflection; /// surface transparency and reflectivity


public:
	Triangle(const Point3f& a, const Point3f& b, const Point3f& c, const Point3f& surfaceColor, const float& reflection,
		const float& transparency, const Point3f& emissionColor) :
		m_A(a), m_B(b), m_C(c), m_SurfaceColor(surfaceColor), m_EmissionColor(emissionColor),
		m_Transparency(transparency), m_Reflection(reflection)
	{
		float z = 0.33;
		m_Center = (a + b + c).getMultipliedWith(z);

		Point3f v0v1 = m_B - m_A;
		Point3f v0v2 = m_C - m_A;
		// no need to normalize
		m_Normal = v0v1.cross(v0v2).normalize(); // N

		float r = -1;
		m_Normal = m_Normal.getMultipliedWith(r);
	}

	bool rayTriangleIntersect(const Ray& ray, float &t, float& u, float& v);



	Point3f getCenter() const
	{
		return m_Center;
	}


	Point3f getSurfaceColor() const
	{
		return m_SurfaceColor;
	}

	Point3f getEmissionColor() const
	{
		return m_EmissionColor;
	}

	float getTransparency() const
	{
		return m_Transparency;
	}

	float getReflection() const
	{
		return m_Reflection;
	}

	Point3f getNormal(void)const { return m_Normal; }

};

#endif
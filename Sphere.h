#pragma once
#ifndef _SPHERE_H__
#define _SPHERE_H__

#include "Point3f.h"
#include "Ray.h"
#include<math.h>

/**the class sphere*/
class Sphere
{
private:
	Point3f m_Center; /// position of the sphere
	Point3f m_SurfaceColor, m_EmissionColor; /// surface color and emission (light)
	float m_Radius, m_Radius2; /// sphere radius and radius^2
	float m_Transparency, m_Reflection; /// surface transparency and reflectivity

public:
	/*
	*Constructor:
	*/
	Sphere(const Point3f &center, const float &radius, const Point3f &surfaceColor, const float &reflection = 0,
		const float &transparancy = 0, const Point3f &emissionColor = 0) :
		m_Center(center), m_Radius(radius), m_Radius2(radius * radius), m_SurfaceColor(surfaceColor), m_EmissionColor(emissionColor),
		m_Transparency(transparancy), m_Reflection(reflection){}

	bool isRayIntersecting(const Ray ray, float & intersectionParameter1, float & intersectionParameter2) const;


	Point3f getCenter() const
	{
		return m_Center;
	}

	float getRadius() const
	{
		return m_Radius;
	}

	float getRadius2() const
	{
		return m_Radius2;
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



};








#endif
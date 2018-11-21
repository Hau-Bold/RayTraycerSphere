#ifndef CONE_H__
#define CONE_H__

#include "Point3f.h"
#include "Ray.h"
#include <math.h>

#include "Constants.h"

#include<algorithm>
class Cone
{
private:
	Point3f m_Apex,m_ReferencePoint,m_Center;
	float m_Radius;
	float m_Height;
	Point3f m_RelNormal;//the normal on the disc

	Point3f m_SurfaceColor, m_EmissionColor; /// surface color and emission (light)
	float m_Transparency, m_Reflection; /// surface transparency and reflectivity
	double m_Phi;

	double computePhi(const float& radius, const float& height);


public:
	/*
	*Constructor:
	*/
	Cone(Point3f &referencePoint, float &radius, Point3f& normal, float & height, Point3f &surfaceColor, float &reflection,
		float &transparency, Point3f &emissionColor);

	Cone(Point3f ref, float r, Point3f x, float h, Point3f s, float f, float t, Point3f e);

	bool isRayIntersecting(const Ray ray, float & intersectionParameter1, float & intersectionParameter2) const;

	Point3f initializeApex(const Point3f& referencePoint,Point3f& normal,float& height);

	Point3f getNormalAt(const Point3f& pointOfIntersection);



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

	Point3f getCenter() const
	{
		return m_Center;
	}

};
#endif
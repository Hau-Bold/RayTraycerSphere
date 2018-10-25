#ifndef PLANE_H__
#define PLANE_H__

#include "Point3f.h"
#include "Ray.h"
/**the class Plane*/
class Plane
{
	Point3f m_ReferencePoint;
	Point3f m_Normal;


public:
	/*
	*Constructor.
	*
	*@param referencPoint - the reference point
	*
	*@param normal - the normal
	*/
	Plane(const Point3f & referencePoint, Point3f & normal)
		: m_ReferencePoint(referencePoint), m_Normal(normal) {}

	bool isRayIntersecting(const Ray & ray, float & intersectionParameter, const float & epsilon)
	{
		if (m_Normal.dot(ray.getDirection()) < epsilon)
		{
			return false;
		}

		float numerator = m_Normal.dot(m_ReferencePoint - ray.getOrigin());
		float denominator = m_Normal.dot(ray.getDirection());

		intersectionParameter = numerator / denominator;

		return true;
	}





	//get & set follows below here
	Point3f getReferencePoint() const
	{
		return m_ReferencePoint;
	}

	Point3f getNormal() const
	{
		return m_Normal;
	}

};
#endif


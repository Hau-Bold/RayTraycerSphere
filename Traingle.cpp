#include "Triangle.h"


bool Triangle::rayTriangleIntersect(const Ray& ray, float &t, float& u, float& v)
{
	// compute plane's normal

	float area2 = m_Normal.length();

	// Step 1: finding P

	// check if ray and plane are parallel ?
	float NdotRayDirection = m_Normal.dot(ray.getDirection());
	if (fabs(NdotRayDirection) < Constants::EPSILON) // almost 0
		return false; // they are parallel so they don't intersect !

					  // compute d parameter using equation 2
	float d = m_Normal.dot(m_A);

	// compute t (equation 3)
	t = (m_Normal.dot(ray.getOrigin()) + d) / NdotRayDirection;
	// check if the triangle is in behind the ray
	if (t < 0)
	{
		return false; // the triangle is behind
	}

	// compute the intersection point using equation 1
	Point3f P = ray.getOrigin() + ray.getDirection().getMultipliedWith(t);

	// Step 2: inside-outside test
	Point3f C; // vector perpendicular to triangle's plane

			 // edge 0
	Point3f edge0 = m_B - m_A;
	Point3f vp0 = P - m_A;
	C = edge0.cross(vp0);
	if (m_Normal.dot(C) < 0)
	{
		return false; // P is on the right side
	}

										   // edge 1
	Point3f edge1 = m_C - m_B;
	Point3f vp1 = P - m_B;
	C = edge1.cross(vp1);
	if (m_Normal.dot(C) < 0)
	{
		return false; // P is on the right side
	}

										   // edge 2
	Point3f edge2 = m_A - m_C;
	Point3f vp2 = P - m_C;
	C = edge2.cross(vp2);
	if (m_Normal.dot(C) < 0)
	{
		return false; // P is on the right side;
	}

	return true; // this ray hits the triangle
}
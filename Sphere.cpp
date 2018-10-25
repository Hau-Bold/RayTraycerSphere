#include "Sphere.h"

	bool Sphere::isRayIntersecting(const Ray ray, float & intersectionParameter1, float & intersectionParameter2) const
	{
		Point3f originToCenter = getCenter() - ray.getOrigin();

		//compute projection of originToCenter on ray:
		float t_ca = originToCenter.dot(ray.getDirection());

		if (t_ca < 0)
		{
			//ray is not pointing in direction of sphere
			return false;
		}

		float d2 = originToCenter.length2() - t_ca * t_ca;

		if (d2 > m_Radius2)
		{
			return false;
		}

		float t_o = sqrt(m_Radius2 - d2);
		intersectionParameter1 = t_ca - t_o;
		intersectionParameter2 = t_ca + t_o;

		return true;
	}


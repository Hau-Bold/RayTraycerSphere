#include "Cone.h"

Point3f Cone::initializeApex(const Point3f& referencePoint, Point3f& normal, float& height)
{
	return referencePoint + normal.getMultipliedWith(height);
}

double Cone::computePhi(const float& radius, const float& height)
{
	return atan(radius / height);
}

Cone::Cone(Point3f &referencePoint, float &radius, Point3f& normal, float & height, Point3f &surfaceColor, float &reflection,
	float &transparency, Point3f &emissionColor)
{
	m_ReferencePoint = referencePoint;
	m_Radius = radius;
	m_RelNormal = normal;
	m_Height = height;
	m_SurfaceColor = surfaceColor;
	m_EmissionColor = emissionColor;
	m_Transparency = transparency;
	m_Reflection = reflection;




}


Cone::Cone(Point3f ref, float r, Point3f x, float h, Point3f s, float f, float t, Point3f e)
{
	m_ReferencePoint = ref;
	m_Radius = r;
	m_RelNormal = x;
	m_Height = h;
	m_SurfaceColor = s;
	m_EmissionColor = e;
	m_Transparency = t;
	m_Reflection = f;


	m_Apex = initializeApex(m_ReferencePoint, m_RelNormal, m_Height);
	m_Phi = computePhi(m_Radius, m_Height);//Öffnungswinkel
	float z = 1.0 / 3.0;
	m_Center = m_ReferencePoint + (m_RelNormal.getMultipliedWith(z));
}

bool Cone::isRayIntersecting(const Ray ray, float & intersectionParameter1, float & intersectionParameter2) const
{
	//check if disc is intersected....
	// check if ray and plane are parallel ?
	//float NdotRayDirection = (m_Apex - m_ReferencePoint).dot(ray.getDirection());
	//if (fabs(NdotRayDirection) < Constants::EPSILON) // almost 0
	//	return false; // they are parallel so they don't intersect !


	/*if (cos(m_Phi) < 0)
	{
		return false;
	}*/

	Point3f V = (m_ReferencePoint - m_Apex).normalize();



	float cos2Phi = cos(m_Phi)*cos(m_Phi);
	Point3f CO = ray.getOrigin() - m_Apex;
	float coDotV = CO.dot(V);
	//compute a:

	float a = (ray.getDirection().dot(V))*(ray.getDirection().dot(V)) - (cos2Phi);

	//compute b:

	float b = 2 * (	ray.getDirection().dot(V)*coDotV - ray.getDirection().dot(CO)*cos2Phi);

	//compute c
	float c = coDotV * coDotV - CO.dot(CO)*cos2Phi;

	float delta = b * b - 4 * a*c;

	if (delta < 0)
	{
		return false;
	}

	if (delta == 0)
	{
		intersectionParameter1 = -b / (2 * a);
		intersectionParameter2 = intersectionParameter1;

		float t = std::min(intersectionParameter1, intersectionParameter2);
		Point3f intersect = ray.getOrigin() + ray.getDirection().getMultipliedWith(t);
		float r = (intersect - m_Apex).dot(V);

		if (r < 0)
		{
			return false;
		}
		else
		{
			float norm = (intersect - m_Apex).length();
			float norm2 = norm * norm;
			if (norm2 <= ((m_Radius * m_Radius) + (m_Height*m_Height)))
			{
				return true;
			}
			return false;
		}
	}

	intersectionParameter1 = (-b - sqrt(delta)) / (2 * a);
	intersectionParameter2 = (-b + sqrt(delta)) / (2 * a);

	float t = std::min(intersectionParameter1, intersectionParameter2);

	Point3f intersect = ray.getOrigin() + ray.getDirection().getMultipliedWith(t);
	float r = (intersect - m_Apex).dot(V);

	if (r < 0)
	{
		return false;
	}
	else
	{
		float norm = (intersect - m_Apex).length();
		float norm2 = norm * norm;
		if (norm2 <= ((m_Radius * m_Radius) + (m_Height*m_Height)))
		{
			return true;
		}
		return false;
	}
}

Point3f Cone::getNormalAt(const Point3f& pointOfIntersection)
{
	//falls Grundfläche andere Argumentation

	Point3f tmp = pointOfIntersection - m_ReferencePoint;

	if (tmp.dot(m_RelNormal) != 0)
	{
		Point3f apexToIntersection = pointOfIntersection - m_Apex;
		float d = apexToIntersection.length() / cos(m_Phi);

		Point3f refToApex = (m_ReferencePoint - m_Apex).normalize();

		Point3f X = refToApex.getMultipliedWith(d);

		return (pointOfIntersection - (m_Apex + X)).normalize();
	}
    else
	{
		float y = -1.0;
		return m_RelNormal.getMultipliedWith(y);
	}

}
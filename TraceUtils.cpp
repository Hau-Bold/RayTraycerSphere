#include"TraceUtils.h"



float TraceUtils::lerp(const float &a, const float &b, const float &mix)
{
	return b * mix + a * (1 - mix);
}

float TraceUtils::getFresnelEffect(const Ray & ray, const Point3f & normalAtIntersection, const float & mix)
{
	float facingratio = -ray.getDirection().dot(normalAtIntersection);
	// change the mix value to tweak the effect
	return lerp(pow(1 - facingratio, 3), 1, mix);
}


Point3f TraceUtils::traceSpheres(const Ray ray, const std::vector<Sphere> &spheres, const int &depth)
{
	//if (raydir.length() != 1) std::cerr << "Error " << raydir << std::endl;
	float tnear = Constants::INFINIT;//to find nearest sphere
	const Sphere* nearestSphere = nullptr;
	// find intersection of this ray with the sphere in the scene
	for (Sphere sphere: spheres) {

		float t0 = Constants::INFINIT, t1 = Constants::INFINIT;
		if (sphere.isRayIntersecting(ray, t0, t1)) {
			if (t0 < 0) t0 = t1;
			if (t0 < tnear) {
				tnear = t0;
				nearestSphere = &sphere;
			}
		}
	}
	// if there's no intersection return black or background color
	if (!nearestSphere)
	{
		return Constants::BACK_GROUND_COLOR;
	}

		Point3f surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray
		Point3f pointOfIntersection = ray.getOrigin() + ray.getDirection() * tnear; // point of intersection
		Point3f normalAtIntersection = pointOfIntersection - nearestSphere->getCenter(); // normal at the intersection point
		normalAtIntersection.normalize(); // normalize normal direction
						  // If the normal and the view direction are not opposite to each other
						  // reverse the normal direction. That also means we are inside the sphere so set
						  // the inside bool to true. Finally reverse the sign of IdotN which we want
						  // positive.
		//float bias = 1e-4; // add some bias to the point from which we will be tracing
		float bias = 0.0;
		bool inside = false;
		if (ray.getDirection().dot(normalAtIntersection) > 0)
		{
			normalAtIntersection = normalAtIntersection.getMultipliedWith(-1);
			inside = true;
		}
		if ((nearestSphere->getTransparency() > 0 || nearestSphere->getReflection() > 0) && depth < Constants::MAX_RAY_DEPTH) {
			//float facingratio = -ray.getDirection().dot(nhit);
			// change the mix value to tweak the effect
			float fresneleffect = getFresnelEffect(ray,normalAtIntersection,0.1); 
			// compute reflection direction (not need to normalize because all vectors
			// are already normalized)
			Point3f directionOfReflection = getDirectionOfReflection(ray,normalAtIntersection);
			Point3f reflection = traceSpheres(Ray(pointOfIntersection + normalAtIntersection * bias, directionOfReflection), spheres, depth + 1);

			Point3f refraction = 0;
			// if the sphere is also transparent compute refraction ray (transmission)
			if (nearestSphere->getTransparency()) {
				float ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
				float cosi = -normalAtIntersection.dot(ray.getDirection());
				float k = 1 - eta * eta * (1 - cosi * cosi);
				Point3f refrdir = ray.getDirection() * eta + normalAtIntersection * (eta * cosi - sqrt(k));
				refrdir.normalize();
				refraction = traceSpheres(Ray(pointOfIntersection - normalAtIntersection * bias, refrdir), spheres, depth + 1);
			}
			// the result is a mix of reflection and refraction (if the sphere is transparent)
			surfaceColor = (
				reflection * fresneleffect +
				refraction * (1 - fresneleffect) * nearestSphere->getTransparency()) * nearestSphere->getSurfaceColor();
		}
		else {
			//it's a diffuse object, no need to raytrace any further
			for (unsigned i = 0; i < spheres.size(); ++i) {
				if (spheres[i].getEmissionColor().m_X > 0) {
					// this is a light
					Point3f transmission = 1;
					Point3f lightDirection = spheres[i].getCenter() - pointOfIntersection;
					lightDirection.normalize();
					for (unsigned j = 0; j < spheres.size(); ++j) {
						if (i != j) {
							float t0, t1;
							if (spheres[j].isRayIntersecting(Ray(pointOfIntersection + normalAtIntersection * bias, lightDirection), t0, t1)) {
								transmission = 0;
								break;
							}
						}
					}
					surfaceColor += nearestSphere->getSurfaceColor() * transmission *
						std::max(float(0), normalAtIntersection.dot(lightDirection)) * spheres[i].getEmissionColor();
				}
			}
		}
		return surfaceColor;// +sphere->emissionColor;
}

Point3f TraceUtils::tracePlanes(const Ray ray, const std::vector<Plane> & planes, const int & depth)
{

	float tnear = Constants::INFINIT;//to find nearest sphere
	const Plane * nearestPlane = nullptr;
	// find intersection of this ray with the sphere in the scene
	for (Plane plane : planes) {

		float t0 =  Constants::INFINIT;
		const float epsilon = 1e-4f;
		if (plane.isRayIntersecting(ray,t0, epsilon)) {
			
			if (t0< tnear) {
				tnear = t0;
				nearestPlane = &plane;
			}
		}
	}
	// if there's no intersection return black or background color
	if (!nearestPlane)
	{
		return Constants::BACK_GROUND_COLOR;
	}

	Point3f surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray
	Point3f pointOfIntersection = ray.getOrigin() + ray.getDirection() * tnear; // point of intersection
	Point3f normalAtIntersection = nearestPlane->getNormal(); // normal at the intersection point
	normalAtIntersection.normalize(); 
	float bias = 0.0;


	//return surfaceColor;

	return Point3f(0);
}




Point3f * TraceUtils::render(const std::vector<Sphere> &spheres, const unsigned int & width, const unsigned int & height)
{
	Point3f* image = new Point3f[width * height];
	Point3f*pixel = image;
	float invWidth = 1 / float(width), invHeight = 1 / float(height);
	float fov = 30, aspectratio = width / float(height);
	float angle = tan(Constants::M_PI * 0.5 * fov / 180.);

	// Trace rays
	for (unsigned y = 0; y < height; ++y) {
		for (unsigned x = 0; x < width; ++x, ++pixel) {

			float x_Dir = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float y_Dir = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			Point3f raydir(x_Dir, y_Dir, -1);
			raydir.normalize();
			*pixel = traceSpheres(Ray(Point3f(0), raydir), spheres, 0);
		}
	}

	return image;
}


void TraceUtils::paintImage(const Point3f * image, const unsigned int & width, const unsigned int & height)
{
	// Save result to a PPM image (keep these flags if you compile under Windows)
	std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (unsigned i = 0; i < width * height; ++i) {
		ofs << (unsigned char)(std::min(float(1), image[i].m_X) * 255) <<
			(unsigned char)(std::min(float(1), image[i].m_Y) * 255) <<
			(unsigned char)(std::min(float(1), image[i].m_Z) * 255);
	}
	ofs.close();
	delete[] image;
}


Point3f TraceUtils::getDirectionOfReflection(const Ray & ray, const Point3f & normalAtIntersection)
{
	Point3f reflectionDirection = ray.getDirection() - normalAtIntersection * 2 * ray.getDirection().dot(normalAtIntersection);
	reflectionDirection.normalize();
	return reflectionDirection;
}


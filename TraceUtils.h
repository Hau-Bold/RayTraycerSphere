#pragma once
#ifndef TRACE_UTILS_H__
#define TRACE_UTILS_H__

#include "Constants.h"
#include "Point3f.h"

#include "Sphere.h"
#include "Plane.h"

#include<algorithm>
#include<fstream>
#include<math.h>
#include<vector>

#include "Point3f.h"
#include "Ray.h"
#include "Triangle.h"

class TraceUtils
{
public:

	static float getFresnelEffect(const Ray & ray, const Point3f & normalAtIntersection, const float & mix);

	static Point3f traceSpheres(const Ray ray, const std::vector<Sphere>& spheres, const int &depth);

	static Point3f traceTriangles(const Ray ray, const std::vector<Triangle>& triangles, const int &depth);

	static Point3f tracePlanes(const Ray ray, const std::vector<Plane> &planes, const int &depth);

	static void paintImage(const Point3f * image, const unsigned int & width, const unsigned int & height);

	static Point3f * render(const std::vector<Sphere> &spheres, const unsigned int & width, const unsigned int & height);
	
	static Point3f * render(const std::vector<Triangle> &triangle, const unsigned int & width, const unsigned int & height);


private:

	static float lerp(const float &a, const float &b, const float &mix);

	static Point3f getDirectionOfReflection(const Ray & ray, const Point3f & normalAtIntersection);

};

#endif
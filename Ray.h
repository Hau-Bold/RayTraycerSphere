#pragma once
#ifndef _RAY_H__
#define _RAY_H__
#include "Point3f.h"

/**the class Ray*/
class Ray
{

private:

	Point3f m_Origin;
	Point3f m_Direction;

public:

	/**Constructor: default*/
	Ray()
	{
		m_Origin = Point3f(0);
		m_Direction = Point3f(0);
	}

	/*
	*Constructor: holds an origin and a normalized direction
	*
	*@param origin - the origin
	*
	*@param direction - the normalized direction
	*/
	Ray(const Point3f & origin, const Point3f & direction) : m_Origin(origin), m_Direction(direction) {
		m_Direction.normalize();
	}

	//get & set follows below here

	Point3f getOrigin() const
	{
		return m_Origin;
	}

	Point3f getDirection() const
	{
		return m_Direction;
	}

};

#endif
#include <cstdio>
#include<stdlib.h>
#include<ctime>
#include <cmath>
#include <math.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include<algorithm>

#include "Constants.h"
#include "Point3f.h"
#include "Sphere.h"
#include "TraceUtils.h"
#include "Triangle.h"

const unsigned int W = 300;
const unsigned int H = 300;

int main(int argc, char **argv)
{
	//srand48(13);
	std::vector<Sphere> spheres;
	// position, radius, surface color, reflectivity, transparency, emission color
	spheres.push_back(Sphere(Point3f(0.0, -10004, -20), 1000, Point3f(0.20, 0.20, 0.20), 0, 0.0));
	spheres.push_back(Sphere(Point3f(0.0, 0, -20), 4, Point3f(1.00, 0.32, 0.36), 0.0, 0.1));
	/*spheres.push_back(Sphere(Point3f(5.0, -1, -15), 2, Point3f(0.90, 0.76, 0.46), 1, 0.0));
	spheres.push_back(Sphere(Point3f(5.0, 0, -25), 3, Point3f(0.65, 0.77, 0.97), 1, 0.0));
	spheres.push_back(Sphere(Point3f(-5.5, 0, -15), 3, Point3f(0.90, 0.90, 0.90), 1, 0.0));*/
	// light
	//spheres.push_back(Sphere(Point3f(0.0, 20, 0.0), 3, Point3f(0.00, 0.00, 0.00), 0, 0.0, Point3f(4)));
	
	Point3f* image =TraceUtils::render(spheres,W,H);
	TraceUtils::paintImage(image, W, H);

	/*std::vector<Triangle> triangles;
	triangles.emplace_back(Triangle(Point3f(0.0, 0.0, -20), Point3f(1.0, 0.0, -20), Point3f(0.0, 1.0, -20), Point3f(1.00, 0.32, 0.36), 0.8, 0.1, Point3f(0)));
	Point3f* image =TraceUtils::render(triangles,W,H);
	TraceUtils::paintImage(image, W, H);*/
}



//void display()
//{
//
//	glClearColor(0, 0, 0, 1);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	unsigned int data[H][W][3];
//	for (size_t y = 0; y < H; ++y)
//	{
//		for (size_t x = 0; x < W; ++x)
//		{
//
//			data[y][x][0] = (rand() % 256) * 256 * 256 * 256;
//			data[y][x][1] = (rand() % 256) * 256 * 256 * 256;
//			data[y][x][2] = (rand() % 256) * 256 * 256 * 256;
//			
//		}
//	}
//
//	glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_INT, data);
//
//	glutSwapBuffers();
//}
//
//void wait_for_data()
//{
//	glutPostRedisplay();
//}

//int main(int argc, char **argv)
//{
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
//	glutInitWindowSize(W, H);
//	glutCreateWindow("GLUT");
//
//	glutDisplayFunc(display);
//	
//	glutIdleFunc(wait_for_data);
//	glutMainLoop();
//
//	return 0;
//}


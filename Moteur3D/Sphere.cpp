#include "pch.h"
#include "Sphere.h"


Sphere::Sphere()
{
	rbd = &RigidBody();
	radius = 1;
}

Sphere::Sphere(RigidBody* rbd, float radius) {
	this->rbd = rbd;
	this->radius = radius;
}

Sphere::~Sphere()
{

}

Vecteur3D Sphere::getCenter()
{
	return rbd->getPosition();
}


float Sphere::getRadius()
{
	return radius;
}

void Sphere::setRadius(float r)
{
	radius = r;
}



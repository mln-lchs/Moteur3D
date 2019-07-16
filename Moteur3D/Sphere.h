#ifndef SPHERE_H
#define SPHERE_H

#include "Vecteur3D.h"
#include "RigidBody.h"

class Sphere
{
	public:
		Sphere();
		Sphere(RigidBody* rbd, float radius);
		virtual ~Sphere();
		Vecteur3D getCenter();
		float getRadius();
		void setRadius(float r);

	private:
		RigidBody* rbd;
		float radius;
};

#endif
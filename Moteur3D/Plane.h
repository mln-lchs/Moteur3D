#ifndef PLANE_H
#define PLANE_H

#include "Vecteur3D.h"
#include "Primitive.h"

class Plane :
	public Primitive
{
public:
	Plane();
	Plane(Vecteur3D normal, float offset, RigidBody *body, Matrix4 offsetObj);
	virtual ~Plane();
	Vecteur3D getNormal();
	void setNormal(Vecteur3D normal);
	float getOffset();
	void setOffset(float offset);

private:
	Vecteur3D normal;
	float offset;
};

#endif
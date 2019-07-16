#include "pch.h"
#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator()
{
}

SpringForceGenerator::SpringForceGenerator(float constant, float length, Vecteur3D end1, Vecteur3D end2, RigidBody *rb)
{
	k = constant;
	l0 = length;
	p1 = end1;
	p2 = end2;
	otherRB = rb;
}

SpringForceGenerator::~SpringForceGenerator()
{

}

void SpringForceGenerator::updateForce(RigidBody * rb, float duration)
{
	Vecteur3D force = p1.soustractionFun(p2);
	float value = -k * (force.norme() - l0);
	force.normalize();
	force.multiplication(value);
	rb->addForceAtBodyPoint(force, p1);
}

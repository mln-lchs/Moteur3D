#ifndef SPRINGFORCEGENERATOR_H
#define SPRINGFORCEGENERATOR_H

#include "Vecteur3D.h"
#include "RigidBody.h"

class SpringForceGenerator {
public:
	SpringForceGenerator();
	SpringForceGenerator(float constant, float length, Vecteur3D end1, Vecteur3D end2, RigidBody *rb);
	virtual ~SpringForceGenerator();
	void updateForce(RigidBody *rb, float duration);

private:
	float k, l0;
	Vecteur3D p1, p2;
	RigidBody *otherRB;
};

#endif

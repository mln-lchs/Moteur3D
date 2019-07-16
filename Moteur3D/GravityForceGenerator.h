#ifndef GRAVITYFORCEGENERATOR_H
#define GRAVITYFORCEGENERATOR_H

#include "Vecteur3D.h"
#include "RigidBody.h"

class GravityForceGenerator {
public :
	GravityForceGenerator();
	GravityForceGenerator(Vecteur3D gravity);
	virtual ~GravityForceGenerator();
	void updateForce(RigidBody *rb, float duree);
	void setGravity(Vecteur3D gravity);
	Vecteur3D getGravity();

private :
	Vecteur3D g;
};




#endif

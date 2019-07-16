#include "pch.h"
#include "GravityForceGenerator.h"

/* Constructeur */
GravityForceGenerator::GravityForceGenerator()
{
	g = Vecteur3D();
}

/* Constructeur */
GravityForceGenerator::GravityForceGenerator(Vecteur3D gravity)
{
	g = gravity;
}

/* Destructeur */
GravityForceGenerator::~GravityForceGenerator()
{

}

/* Met � jour les forces */
void GravityForceGenerator::updateForce(RigidBody * rb, float duree)
{
	if (rb->getInverseMass() > 0) {
		Vecteur3D force = g.multiplicationFun(rb->getMass());
		rb->addForceAtPoint(force, rb->getPosition());
	}
}

/* Affecte une valeur � la gravit� */
void GravityForceGenerator::setGravity(Vecteur3D gravity)
{
	g = gravity;
}

/* Renvoie la valeur de la gravit� */
Vecteur3D GravityForceGenerator::getGravity()
{
	return g;
}

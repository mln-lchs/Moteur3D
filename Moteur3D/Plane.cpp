#include "pch.h"
#include "Plane.h"

/* Constructeur */
Plane::Plane()
{
	this->normal = Vecteur3D();
	this->offset = 0;
}

/* Constructeur */
Plane::Plane(Vecteur3D normal, float offset, RigidBody *body, Matrix4 offsetObj)
{
	Primitive(body, offsetObj);
	this->normal = normal;
	this->offset = offset;
}

/* Destructeur */
Plane::~Plane()
{
}

/* Renvoie la normale du plan */
Vecteur3D Plane::getNormal()
{
	return normal;
}

/* Affecte une normale au plan */
void Plane::setNormal(Vecteur3D normal)
{
	this->normal = normal;
}

/* Renvoie l'offset du plan */
float Plane::getOffset()
{
	return offset;
}

/* Affecte un offset au plan */
void Plane::setOffset(float offset)
{
	this->offset = offset;
}

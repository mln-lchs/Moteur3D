#include "pch.h"
#include "Box.h"

/* Constructeur */
Box::Box()
{
	this->halfSizes = Vecteur3D();
}

/* Constructeur */
Box::Box(Vecteur3D halfSizes, RigidBody *body, Matrix4 offset) : Primitive(body, offset)
{
	this->halfSizes = halfSizes;
}


Box::~Box()
{
}

/* Renvoie les demi longueurs de la bo�te */
Vecteur3D Box::getHalfSizes()
{
	return halfSizes;
}

/* Affecte des demi longueurs � la boi�te */
void Box::setHalfSizes(Vecteur3D halfSizes)
{
	this->halfSizes = halfSizes;
}

/* Renvoie la demi longueur selon l'axe des x */
float Box::getA()
{
	return halfSizes.getX();
}

/* Renvoie la demi longueur selon l'axe des y */
float Box::getB()
{
	return halfSizes.getY();
}

/* Renvoie la demi longueur selon l'axe des z */
float Box::getC()
{
	return halfSizes.getZ();
}

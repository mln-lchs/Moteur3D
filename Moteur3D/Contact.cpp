#include "pch.h"
#include "Contact.h"

/* Constructeur */
Contact::Contact()
{
	this->contactPoint = Vecteur3D();
	this->contactNormal = Vecteur3D();
	this->penetration = 0.0f;
}

/* Constructeur */
Contact::Contact(Vecteur3D contactPoint, Vecteur3D contactNormal, float penetration)
{
	this->contactPoint = contactPoint;
	this->contactNormal = contactNormal;
	this->penetration = penetration;
}

/* Destructeur */
Contact::~Contact()
{
}

/* Renvoie le point de contact */
Vecteur3D Contact::getContactPoint()
{
	return contactPoint;
}

/* Affecte un point de contact */
void Contact::setContactPoint(Vecteur3D contactPoint)
{
	this->contactPoint = contactPoint;
}

/* Récupère la normale au point de contact */
Vecteur3D Contact::getContactNormal()
{
	return contactNormal;
}

/* Affecte une normale au contact */
void Contact::setContactNormal(Vecteur3D contactNormal)
{
	this->contactNormal = contactNormal;
}

/* Renvoie la distance de pénétration */
float Contact::getPenetration()
{
	return penetration;
}

/* Affecte une distance de pénétration */
void Contact::setPenetration(float penetration)
{
	this->penetration = penetration;
}

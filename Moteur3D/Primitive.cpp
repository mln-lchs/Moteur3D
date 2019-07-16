#include "pch.h"
#include "Primitive.h"

/* Constructeur */
Primitive::Primitive()
{
	this->body = nullptr;
	this->offset = Matrix4();
}

/* Constructeur */
Primitive::Primitive(RigidBody * body, Matrix4 offset)
{
	this->body = body;
	this->offset = offset;
}

/* Destructeur */
Primitive::~Primitive()
{
}

/* Renvoie le corps */
RigidBody * Primitive::getBody()
{
	return body;
}

/* Affecte un corps */
void Primitive::setBody(RigidBody * body)
{
	this->body = body;
}

/* Renvoie l'offset */
Matrix4 Primitive::getOffset()
{
	return offset;
}

/* Affecte un offset */
void Primitive::setOffset(Matrix4 offset)
{
	this->offset = offset;
}



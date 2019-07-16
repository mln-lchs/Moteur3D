#include "pch.h"
#include "CollisionData.h"


/* Constructeur */
CollisionData::CollisionData(int contactsLeft)
{
	this->contactsLeft = contactsLeft;
	this->size = 0;
	this->contacts = new Contact[contactsLeft];
}

/* Constructeur */
CollisionData::CollisionData(Contact * contacts, int contactsLeft)
{
	this->contacts = contacts;
	this->size = 0;
	this->contactsLeft = contactsLeft;
}

/* Destructeur */
CollisionData::~CollisionData()
{
}

/* Renvoie la liste des contacts */
Contact* CollisionData::getContacts()
{
	return contacts;
}

/* Affecte une liste de contact */
void CollisionData::setContacts(Contact * contacts)
{
	this->contacts = contacts;
}

/* Renvoie la nombre de contacts */
int CollisionData::getSize()
{
	return size;
}

/* Renvoie le nombre de contacts max pris en compte */
int CollisionData::getContactsLeft()
{
	return contactsLeft;
}

/* Affecte un nombre de contacts max à prendre en compte */
void CollisionData::setContactsLeft(int contactsLeft)
{
	this->contactsLeft = contactsLeft;
}

/* Ajoute un contact à la liste des contacts */
void CollisionData::addContact(Contact contact)
{
	if (size < contactsLeft) {
		contacts[size] = contact;
		size++;
	}
}

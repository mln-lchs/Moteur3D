#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include "Contact.h"

class CollisionData
{
	public:
		CollisionData(int contactsLeft);
		CollisionData(Contact *contacts, int contactsLeft);
		virtual ~CollisionData();
		Contact* getContacts();
		void setContacts(Contact *contacts);
		int getSize();
		int getContactsLeft();
		void setContactsLeft(int contactsLeft);
		void addContact(Contact contact);

	private:
		Contact *contacts;
		int size;
		int contactsLeft;
};

#endif
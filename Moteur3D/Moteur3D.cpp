#include"pch.h"
#include<windows.h>
#include <iostream>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include "Vecteur3D.h"
#include <chrono>
#include "RigidBody.h"
#include "Quaternion.h"
#include "GravityForceGenerator.h"
#include "Primitive.h"
#include "CollisionData.h"
#include "Box.h"
#include "Plane.h"
#include "Sphere.h"
#include "Octree.h"
#include "Plane.h"
#include "Box.h"
#include "CollisionData.h"

using namespace std;
using namespace std::chrono;

Vecteur3D p1l, p2l, p3l, p4l, p5l, p6l, p7l, p8l; // Coordonnées locales des points de notre cube
Vecteur3D p1w, p2w, p3w, p4w, p5w, p6w, p7w, p8w; // Coordonnées globales des points de notre cube
high_resolution_clock::time_point t1, t2; // Utilisés pour mesurer le temps entre deux frames
const float frameDuration = 0.033f; // 30 FPS
duration<double, std::milli> time_span; // durée du calcul
RigidBody body; // le rigid body de notre cube
GravityForceGenerator gravity; // Le générateur de gravité pour notre cube
Sphere sphere; // la sphère englobante de notre cube
Octree octree; // L'octree dans lequel on va stocker les éléments de la scène
Plane listePlans[6]; // Les 6 plans qui encadrent la salle dans laquelle le cube est lancé
Box box; // La primitive de notre cube
void narrowPhase(Box box, Plane *planes, int nbPlanes, CollisionData *data); // une fonction qui va exécuter la narrow phase
bool blocked; // un boooléen permettant de bloquer la frame quand on a un contact



void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
	}
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
}


void changeSize(int w, int h) {

	// Eviter la division par zéro si la fenêtre est trop petite
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Utiliser la matrice de projection
	glMatrixMode(GL_PROJECTION);

	// Reset la matrice
	glLoadIdentity();

	// Régler le viewport sur toute la fenêtre
	glViewport(0, 0, w, h);

	// Mettre la perspective en place
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Revenir au Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderScene() {

	if (!blocked) {
		// Initialisation du timer
		t1 = high_resolution_clock::now();

		// Nettoyer les buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Reset la matrice
		glLoadIdentity();

		// Positionner la camera

		gluLookAt(0.0f, 75, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f);

		// On fait bouger le cube pour la frame
		gravity.updateForce(&body, frameDuration);
		body.integrate(frameDuration);

		// Création de l'Octree
		octree = Octree(4, 4, Vecteur3D(), Vecteur3D(50, 50, 50), Vecteur3D(-50, -50, -50));

		// Ajout de la sphère dans l'octree
		octree.addElement(&sphere);

		// On récupère le résultat de la broad phase
		std::vector<int> plans = octree.collisionsForExample();
		Plane* listePlansEffectifs = new Plane[plans.size()];
		int size = plans.size();
		int i;
		int j = 0;

		// On convertit la liste d'entiers en liste de plans
		while (!plans.empty()) {
			i = plans.back();
			plans.pop_back();
			listePlansEffectifs[j] = listePlans[i];
			j++;
		}

		CollisionData collision = CollisionData(10);

		// On rajoute le contact s'il a eu lieu à notre liste de contacts
		narrowPhase(box, listePlansEffectifs, j, &collision);

		
		// Affichage du cube
		p1w = p1l.localToWorld4(body.getTransformMatrix());
		p2w = p2l.localToWorld4(body.getTransformMatrix());
		p3w = p3l.localToWorld4(body.getTransformMatrix());
		p4w = p4l.localToWorld4(body.getTransformMatrix());
		p5w = p5l.localToWorld4(body.getTransformMatrix());
		p6w = p6l.localToWorld4(body.getTransformMatrix());
		p7w = p7l.localToWorld4(body.getTransformMatrix());
		p8w = p8l.localToWorld4(body.getTransformMatrix());

		glBegin(GL_QUADS);
		glVertex3f(p1w.getX(), p1w.getY(), p1w.getZ());
		glVertex3f(p2w.getX(), p2w.getY(), p2w.getZ());
		glVertex3f(p3w.getX(), p3w.getY(), p3w.getZ());
		glVertex3f(p4w.getX(), p4w.getY(), p4w.getZ());
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(p1w.getX(), p1w.getY(), p1w.getZ());
		glVertex3f(p2w.getX(), p2w.getY(), p2w.getZ());
		glVertex3f(p6w.getX(), p6w.getY(), p6w.getZ());
		glVertex3f(p5w.getX(), p5w.getY(), p5w.getZ());
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(p4w.getX(), p4w.getY(), p4w.getZ());
		glVertex3f(p3w.getX(), p3w.getY(), p3w.getZ());
		glVertex3f(p7w.getX(), p7w.getY(), p7w.getZ());
		glVertex3f(p8w.getX(), p8w.getY(), p8w.getZ());
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(p3w.getX(), p3w.getY(), p3w.getZ());
		glVertex3f(p2w.getX(), p2w.getY(), p2w.getZ());
		glVertex3f(p6w.getX(), p6w.getY(), p6w.getZ());
		glVertex3f(p7w.getX(), p7w.getY(), p7w.getZ());
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(p1w.getX(), p1w.getY(), p1w.getZ());
		glVertex3f(p4w.getX(), p4w.getY(), p4w.getZ());
		glVertex3f(p8w.getX(), p8w.getY(), p8w.getZ());
		glVertex3f(p5w.getX(), p5w.getY(), p5w.getZ());
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(p5w.getX(), p5w.getY(), p5w.getZ());
		glVertex3f(p6w.getX(), p6w.getY(), p6w.getZ());
		glVertex3f(p7w.getX(), p7w.getY(), p7w.getZ());
		glVertex3f(p8w.getX(), p8w.getY(), p8w.getZ());
		glEnd();


		// Affichage grossier des murs
		glBegin(GL_QUADS);
		glVertex3f(30, 0, 30);
		glVertex3f(30, 0, -30);
		glVertex3f(40, 0, -30);
		glVertex3f(40, 0, 30);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-30, 0, 30);
		glVertex3f(-30, 0, -30);
		glVertex3f(-40, 0, -30);
		glVertex3f(-40, 0, 30);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(30, 0, 30);
		glVertex3f(-30, 0, 30);
		glVertex3f(-30, 0, 40);
		glVertex3f(30, 0, 40);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(30, 0, -30);
		glVertex3f(-30, 0, -30);
		glVertex3f(-30, 0, -40);
		glVertex3f(30, 0, -40);
		glEnd();

		// Fin du timer 
		t2 = high_resolution_clock::now();

		// Durée du calcul
		time_span = t2 - t1;

		// Si cela a duré moins d'un trentième de seconde, on attend
		if (time_span.count() / 1000 < frameDuration) {
			Sleep(frameDuration * 1000 - time_span.count());
		}

		// Affichage
		glutSwapBuffers();

		// On freeze la frame s'il y a eu contact, et on attend un input (F1 à F5) pour bouger la caméra à nouveau
		if (collision.getSize() > 0) {
			Contact* contact = collision.getContacts();
			std::cout << "Point de contact : \n";
			std::cout << contact[0].getContactPoint().getX();
			std::cout << "\n";
			std::cout << contact[0].getContactPoint().getY();
			std::cout << "\n";
			std::cout << contact[0].getContactPoint().getZ();
			std::cout << "\n";
			std::cout << "Vecteur normal : \n";
			std::cout << contact[0].getContactNormal().getX();
			std::cout << "\n";
			std::cout << contact[0].getContactNormal().getY();
			std::cout << "\n";
			std::cout << contact[0].getContactNormal().getZ();
			std::cout << "\n";
			std::cout << "Interpenetration :";
			std::cout << contact[0].getPenetration();
			std::cout << "\n";
			blocked = true;
		}

	}
}

void processSpecialKeys(int key, int x, int y) {

	// On utilise l'input de l'utilisateur pour choisir comment envoyer le cube
	switch (key) {
	case GLUT_KEY_F1:
		blocked = false;
		body = RigidBody(1 / 10.0f, 0.95f, 0.95f, Vecteur3D(0.0f, 0.0f, 0.0f), Vecteur3D(8.0f, 0.0f, 15.0f), Quaternion(1, 0.0f, 0.0f, 0.0f), Vecteur3D(0.0f, 1.0f, 0.0f), Matrix3(Vecteur3D(1 / 666.7f, 0.0f, 0.0f), Vecteur3D(0.0f, 1 / 666.7f, 0.0f), Vecteur3D(0.0f, 0.0f, 1 / 666.7f)));

		break;

	case GLUT_KEY_F2:
		body = RigidBody(1 / 10.0f, 0.95f, 0.95f, Vecteur3D(0.0f, 0.0f, 0.0f), Vecteur3D(-8.0f, 0.0f, 15.0f), Quaternion(1, 0.0f, 0.0f, 0.0f), Vecteur3D(1.0f, 1.0f, 0.0f), Matrix3(Vecteur3D(1 / 666.7f, 0.0f, 0.0f), Vecteur3D(0.0f, 1 / 666.7f, 0.0f), Vecteur3D(0.0f, 0.0f, 1 / 666.7f)));
		blocked = false;

		break;

	case GLUT_KEY_F3:
		body = RigidBody(1 / 10.0f, 0.95f, 0.95f, Vecteur3D(0.0f, 0.0f, 0.0f), Vecteur3D(0.0f, 0.0f, 15.0f), Quaternion(1, 0.0f, 0.0f, 0.0f), Vecteur3D(1.0f, 0.0f, 0.0f), Matrix3(Vecteur3D(1 / 666.7f, 0.0f, 0.0f), Vecteur3D(0.0f, 1 / 666.7f, 0.0f), Vecteur3D(0.0f, 0.0f, 1 / 666.7f)));
		blocked = false;

		break;

	case GLUT_KEY_F4:
		body = RigidBody(1 / 10.0f, 0.95f, 0.95f, Vecteur3D(0.0f, 0.0f, 0.0f), Vecteur3D(0.0f, 0.0f, 25.0f), Quaternion(1, 0.0f, 0.0f, 0.0f), Vecteur3D(1.0f, 0.0f, 0.0f), Matrix3(Vecteur3D(1 / 666.7f, 0.0f, 0.0f), Vecteur3D(0.0f, 1 / 666.7f, 0.0f), Vecteur3D(0.0f, 0.0f, 1 / 666.7f)));
		blocked = false;

		break;

	case GLUT_KEY_F5:
		body = RigidBody(1 / 10.0f, 0.95f, 0.95f, Vecteur3D(0.0f, 0.0f, 0.0f), Vecteur3D(0.0f, -8.0f, 15.0f), Quaternion(1, 0.0f, 0.0f, 0.0f), Vecteur3D(1.0f, 0.0f, 0.0f), Matrix3(Vecteur3D(1 / 666.7f, 0.0f, 0.0f), Vecteur3D(0.0f, 1 / 666.7f, 0.0f), Vecteur3D(0.0f, 0.0f, 1 / 666.7f)));
		blocked = false;

		break;
	}


}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	// Initialisation des variables pour la suite
	gravity = GravityForceGenerator(Vecteur3D(0.0f, 0.0f, -5.0f));

	body = RigidBody(1/10.0f, 0.95f, 0.95f, Vecteur3D(0.0f, 0.0f, 0.0f), Vecteur3D(8.0f, 0.0f, 15.0f), Quaternion(1, 0.0f, 0.0f, 0.0f), Vecteur3D(0.0f, 1.0f, 0.0f), Matrix3(Vecteur3D(1 / 666.7f, 0.0f, 0.0f), Vecteur3D(0.0f, 1 / 666.7f, 0.0f), Vecteur3D(0.0f, 0.0f, 1 / 666.7f)));

	sphere = Sphere(&body, 4.33);
	box = Box(Vecteur3D(5, 5, 5), &body, Matrix4());

	p1l = Vecteur3D(-5, -5, -5);
	p2l = Vecteur3D(-5, 5, -5);
	p3l = Vecteur3D(5, 5, -5);
	p4l = Vecteur3D(5, -5, -5);
	p5l = Vecteur3D(-5, -5, 5);
	p6l = Vecteur3D(-5, 5, 5);
	p7l = Vecteur3D(5, 5, 5);
	p8l = Vecteur3D(5, -5, 5);

	listePlans[0] = Plane(Vecteur3D(1, 0, 0), 30, new RigidBody(), Matrix4());
	listePlans[1] = Plane(Vecteur3D(0, 1, 0), 30, new RigidBody(), Matrix4());
	listePlans[2] = Plane(Vecteur3D(0, 0, 1), 30, new RigidBody(), Matrix4());
	listePlans[3] = Plane(Vecteur3D(-1, 0, 0), 30, new RigidBody(), Matrix4());
	listePlans[4] = Plane(Vecteur3D(0, -1, 0), 30, new RigidBody(), Matrix4());
	listePlans[5] = Plane(Vecteur3D(0, 0, -1), 30, new RigidBody(), Matrix4());


	glutCreateWindow("Moteur3D");
	initRendering();

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(changeSize);
	glutSpecialFunc(processSpecialKeys);
	glutMainLoop();
	return 0;
}

void narrowPhase(Box box, Plane *planes, int nbPlanes, CollisionData *data) {
	const int nbVertices = 8;
	Vecteur3D vertices[nbVertices];
	Vecteur3D center;
	Vecteur3D position;
	center = box.getBody()->getPosition();


	// Calcul des sommets du cube
	position = Vecteur3D(-box.getA(), -box.getB(), box.getC());
	vertices[0] = position.localToWorld4(body.getTransformMatrix());
	position = Vecteur3D(-box.getA(), -box.getB(), -box.getC());
	vertices[1] = position.localToWorld4(body.getTransformMatrix());
	position = Vecteur3D(-box.getA(), box.getB(), -box.getC());
	vertices[2] = position.localToWorld4(body.getTransformMatrix());
	position = Vecteur3D(-box.getA(), box.getB(), box.getC());
	vertices[3] = position.localToWorld4(body.getTransformMatrix());
	position = Vecteur3D(box.getA(), -box.getB(), box.getC());
	vertices[4] = position.localToWorld4(body.getTransformMatrix());
	position = Vecteur3D(box.getA(), -box.getB(), -box.getC());
	vertices[5] = position.localToWorld4(body.getTransformMatrix());
	position = Vecteur3D(box.getA(), box.getB(), -box.getC());
	vertices[6] = position.localToWorld4(body.getTransformMatrix());
	position = Vecteur3D(box.getA(), box.getB(), box.getC());
	vertices[7] = position.localToWorld4(body.getTransformMatrix());

	int vertexMax;
	// Interpenetration Max et distance au plan
	float interMax, dist;
	// Normale et point de contact
	Vecteur3D n, contactPt;
	float d;
	Contact contact;
	for (int i = 0; i < nbPlanes; i++) {
		interMax = 1.0f;
		vertexMax = -1;
		n = planes[i].getNormal();
		d = planes[i].getOffset();
		for (int j = 0; j < nbVertices; j++) {
			dist = vertices[j].produitScalaire(n) + d;
			if (dist <= 0) {
				if (dist < interMax) {
					// On garde l'interpenetration max et le vertex associé pour calculer le point de contact
					interMax = dist;
					vertexMax = j;
				}
			}
		}

		// Si on q trouvé un contact, on l'ajoute
		if (vertexMax != -1) {
			contactPt = vertices[vertexMax].soustractionFun(n.multiplicationFun(interMax/2.0f));
			contact = Contact(contactPt, n, std::abs(interMax));
			data->addContact(contact);
		}
	}
}


#include "pch.h"
#include "Vecteur3D.h"
#include "math.h"

/* Constructeur */
Vecteur3D::Vecteur3D() : x(0), y(0), z(0)
{
	
}

/* Constructeur */
Vecteur3D::Vecteur3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

/* Destructeur */
Vecteur3D::~Vecteur3D()
{

}

/* Fonction qui renvoie la coordonnée en x */
float Vecteur3D::getX() {
	return x;
}

/* Fonction qui renvoie la coordonnée en y */
float Vecteur3D::getY() {
	return y;
}

/* Fonction qui renvoie la coordonnée en z */
float Vecteur3D::getZ() {
	return z;
}

/* Fonction qui affecte une valeur à x */
void Vecteur3D::setX(float newX) {
	x = newX;
}

/* Fonction qui affecte une valeur à y */
void Vecteur3D::setY(float newY) {
	y = newY;
}

/* Fonction qui affecte une valeur à z */
void Vecteur3D::setZ(float newZ) {
	z = newZ;
}

/* Fonction qui affecte les coordonnées en x, y et z */
void Vecteur3D::setCoordonnees(float newX, float newY, float newZ) {
	x = newX;
	y = newY;
	z = newZ;
}

/* Fonction qui additionne un vecteur à un autre */
void Vecteur3D::addition(Vecteur3D &vecteur){
	x += vecteur.getX();
	y += vecteur.getY();
	z += vecteur.getZ();
}

/* Fonction qui additionne deux vecteurs avec les coordonnées du second */
void Vecteur3D::addition(float x, float y, float z)
{
	this->x += x;
	this->y += y;
	this->z += z;
}

/* Fonction qui soustrait un vecteur à un autre */
Vecteur3D Vecteur3D::additionFun(Vecteur3D v) {
	Vecteur3D res;
	res.setX(getX() + v.getX());
	res.setY(getY() + v.getY());
	res.setZ(getZ() + v.getZ());
	return res;
}

/* Fonction qui soustrait un vecteur à un autre */
void Vecteur3D::soustraction(Vecteur3D &vecteur) {
	x -= vecteur.getX();
	y -= vecteur.getY();
	z -= vecteur.getZ();
}

/* Fonction qui additionne un vecteur à un autre */
Vecteur3D Vecteur3D::soustractionFun(Vecteur3D v) {
	Vecteur3D res;
	res.setX(getX() - v.getX());
	res.setY(getY() - v.getY());
	res.setZ(getZ() - v.getZ());
	return res;
}

/* Fonction qui multiplie un vecteur par un scalaire */
void Vecteur3D::multiplication(float k) {
	x *= k;
	y *= k;
	z *= k;
}

/* Fonction qui multiplie un vecteur par un scalaire et retourne un vecteur */
Vecteur3D Vecteur3D::multiplicationFun(float k) {
	Vecteur3D res;
	res.setCoordonnees(getX()*k, getY()*k, getZ()*k);
	return res;
}

/* Fonction qui multiplie chaque composante d'un vecteur par celles d'un autre vecteur */
void Vecteur3D::produitComposantes(Vecteur3D &vecteur) {
	x *= vecteur.getX();
	y *= vecteur.getY();
	z *= vecteur.getZ();
}

/* Fonction qui multiplie chaque composante d'un vecteur par celles d'un autre vecteur et retourne un vecteur */
Vecteur3D Vecteur3D::produitComposantesFun(Vecteur3D v) {
	Vecteur3D res;
	res.setX(getX() * v.getX());
	res.setY(getY() * v.getY());
	res.setZ(getZ() * v.getZ());
	return res;
}

/* Fonction qui calcule le produit scalaire d'un vecteur avec un autre */
float Vecteur3D::produitScalaire(Vecteur3D &vecteur) {
	return x * vecteur.getX() + y * vecteur.getY() + z * vecteur.getZ();
}

/* Fonction qui calcule la norme d'un vecteur */
float Vecteur3D::norme() {
	return sqrt(x*x+y*y+z*z);
}

/* Fonction qui normalise un vecteur */
void Vecteur3D::normalize() {
	x /= norme();
	y /= norme();
	z /= norme();
}

/* Fonction qui normalise un vecteur et retourne un vecteur */
Vecteur3D Vecteur3D::normalizeFun() {
	Vecteur3D res;
	res.setX(getX() / norme());
	res.setY(getY() / norme());
	res.setZ(getZ() / norme());
	return res;
}

/* Fonction qui renvoie le cosinus de l'angle entre deux vecteurs */
float Vecteur3D::cosAngle(Vecteur3D &vecteur) {
	return produitScalaire(vecteur) / (norme()*vecteur.norme());
}

/* Fonction qui renvoie le sinus de l'angle entre deux vecteurs */
float Vecteur3D::sinAngle(Vecteur3D &vecteur) {
	return sqrt(1-pow(cosAngle(vecteur),2));
}

/* Fonction qui calcule la projection d'un vecteur sur une droite définie par un autre vecteur */
Vecteur3D Vecteur3D::projection(Vecteur3D &vecteur) {
	Vecteur3D result = vecteur;
	result.multiplication(produitScalaire(vecteur) / (vecteur.norme()*vecteur.norme()));
	return result;
}

/* Fonction qui renvoie la distance entre deux vecteurs */
float Vecteur3D::distance(Vecteur3D vecteur) {
	return sqrt((x - vecteur.getX())*(x - vecteur.getX()) +(y - vecteur.getY())*(y - vecteur.getY())+ (z - vecteur.getZ())*(z - vecteur.getZ()));
}

/* Fonction qui calcule le produit vectoriel d'un vecteur avec un autre */
Vecteur3D Vecteur3D::produitVectoriel(Vecteur3D &vecteur) {
	Vecteur3D result;
	result.setCoordonnees(y*vecteur.getZ() - z*vecteur.getY(), z*vecteur.getX() - x*vecteur.getZ(), x*vecteur.getY() - y*vecteur.getX());
	return result;
}

/* Fonction qui calcule le produit mixte de trois vecteurs */
float Vecteur3D::produitMixte(Vecteur3D &vecteur1, Vecteur3D &vecteur2) {
	Vecteur3D aux = vecteur1.produitVectoriel(vecteur2);
	return produitScalaire(aux);
}

/* Fonction qui effectue un changement de base, de la base locale à celle du monde sans rotation */
Vecteur3D Vecteur3D::localToWorld(Matrix3 p)
{
	return p.multiplicationVect(*this);
}

/* Fonction qui effectue un changement de base, de la base du monde à celle locale sans rotation */
Vecteur3D Vecteur3D::worldToLocal(Matrix3 p) {
	return p.inverse().multiplicationVect(*this);
}

/* Fonction qui effectue un changement de base, de la base locale à celle du monde avec rotation sans rotation */
Vecteur3D Vecteur3D::localToWorld4(Matrix4 p)
{
	return p.multiplicationVect(*this);
}

/* Fonction qui effectue un changement de base, de la base du monde à celle locale avec rotation sans rotation */
Vecteur3D Vecteur3D::worldToLocal4(Matrix4 p) {
	return p.inverse().multiplicationVect(*this);
}
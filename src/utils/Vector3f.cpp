/*
 * Vector3f.cpp
 *
 *  Created on: 24.07.2015
 *      Author: Kevin
 */

#include "Vector3f.h"

Vector3f::Vector3f( float x, float y, float z ) : m_x(x), m_y(y), m_z(z) {


}

Vector3f::Vector3f() : m_x(0), m_y(0), m_z(0) {
}

Vector3f::~Vector3f() { }

float Vector3f::GetX() const {
	return m_x;
}

void Vector3f::SetX(float x) {
	m_x = x;
}

float Vector3f::GetY() const  {
	return m_y;
}

void Vector3f::SetY(float y) {
	m_y = y;
}

float Vector3f::GetZ() const {
	return m_z;
}

void Vector3f::SetZ(float z) {
	m_z = z;
}

Vector3f Vector3f::Forward()
{
	return Vector3f(0, 0, -1);
}

Vector3f Vector3f::Backward()
{
	return Vector3f(0, 0, 1);
}

Vector3f Vector3f::Left()
{
	return Vector3f( 1, 0, 0 );
}

Vector3f Vector3f::Right()
{
	return Vector3f( -1, 0, 0 );
}



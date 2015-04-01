//-----------------------------------------------------------------------------
// Programmer: Bakir Hajdarevic
// Name: Circle.cpp
// Description: Implementation of member functions of Circle class for homework 5. This class
//              represents a circle shape only defined by the radius
//-----------------------------------------------------------------------------

#include "Circle.h"
#include <cmath>

// compute area
double Circle::getArea() const
{
    return m_pi*m_radius*m_radius;
}
    
// compute perimeter
double Circle::getPerimeter() const 
{
    return 2*(m_pi*m_radius); //Compute and return the perimeter
}
    
// get radius
double Circle::getRadius() const
{
    return m_radius;
}

// set radius to val
void Circle::setRadius(double val) {
    m_radius=val;
}

//compute radius from area
void Circle::setRadiusFromArea (int area) {
    //Given the area, compute and store the radius of the circle   
    m_radius = sqrt(area/m_pi);
}

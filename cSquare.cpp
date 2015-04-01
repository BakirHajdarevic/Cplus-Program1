//-----------------------------------------------------------------------------
// Programmer: Bakir Hajdarevic
// Name: cSquare.cpp
// Description: Implementation of member functions of Square class for homework 5. 
//-----------------------------------------------------------------------------
#include "cSquare.h"
#include <cmath>

// compute area
double cSquare::getArea() const
{
    return m_sideLength*m_sideLength;
}

// compute perimeter
double cSquare::getPerimeter() const
{
    return m_sideLength*4; //Compute and return the perimeter
}
    
// get sideLength
double cSquare::getSideLength() const {
    return m_sideLength;
}

// set sideLength to val
void cSquare::setSideLength(double val) {
    m_sideLength=val;
}

//compute side length from area
void cSquare::setSideLengthFromArea (int area) {
    //Given the area, compute and store the side length of the square
    m_sideLength = sqrt(area);
}

//-----------------------------------------------------------------------------
// Programmer: Bakir Hajdarevic
// Name: hw5.cpp
// Description: This program identifies the shapes in an inpit image and estimates
// their perimeter from their area (number of pixels). A shape is defined as a
// connected component of white pixels. There are only two types of shapes: circles
// and squares. A circle is always bigger than a square (255). This program also
// takes the image and modifies it so that a new colored image is outputted with
// each shape type now is a different color.
//-----------------------------------------------------------------------------
#include "Image.h"
#include "Circle.h"
#include "cSquare.h"
#include <iostream>
#include <cmath>
#include <stack>
#include <vector>

#define CIRCLE 10000    // minimum number of pixels for a circle
#define LABELCIRCLE 85  // label for circles
#define LABELSQUARE 170    // label for squares


// define struct to hold pixel location
struct pixelLocation {
    int r;
    int c;
};

typedef struct pixelLocation PixelLocation;

// possible function prototypes that you may consider using (optional):
bool findPixelLocationWithGivenValue(const Image &image, int pixelValue, int &foundRow, int &foundCol);
int markConnectedComponent(Image &image, int seedRow, int seedCol, int ccLabel);

int main( int argc, char* argv[] )
{
    // get input/output image file names from command line
    if (argc != 3)
    {
        std::cout << "Usage instructions: " << std::endl;
        std::cout << "> hw5.exe inputFileName.bmp coloredOutputFileName.bmp" << std::endl;
        return -1;
    }
    std::string inputFileName(argv[1]);
    std::string coloredOutputFileName(argv[2]);

    // read image from input file
    std::cout << "Reading input image: " << inputFileName << std::endl;
    Image myImage;
    bool success = myImage.readFromBMPFile(inputFileName);
    if (! success)
    {
        std::cout << "Error reading input image." << std::endl;
        return -1;
    }

	//The rest of your code goes here...
    int seedpixel = 0; //stores the value returned from markConnectedComponent
    int numCircles = 0; //stores number of circles
    int numSquares = 0; //stores number of squares
    int rows; //stores the image's row number
    int cols; //stores the image's column number
    int ccLabel = 0; //Connected Component Label
    //Pixel markers
    pixelLocation foundLoc;
    foundLoc.r = 0;
    foundLoc.c = 0;

    Circle circleObj; //Circle class object
    cSquare squareObj; //Square class object

    std::vector<Circle> cVect1; //Circle vector
    std::vector<cSquare> sqVect1; //Square vector
    
    int cVect2[100];
    int sqVect2[100];

    //Get number of rows and cols in Image
    rows = myImage.getNumRows();
    cols = myImage.getNumCols();

    //sorts through the image to find the circles and squares
    while(findPixelLocationWithGivenValue(myImage, 255, foundLoc.r, foundLoc.c) && ccLabel<100)
    {
        ccLabel++;
        seedpixel = markConnectedComponent(myImage, foundLoc.r, foundLoc.c, 100);
            
        if( seedpixel >= CIRCLE)
        {
            circleObj.setRadiusFromArea(seedpixel);
            cVect2[numCircles] = circleObj.getPerimeter();
            cVect1.push_back(circleObj);
            myImage.setAllPixelsWithOldValToNewVal(100, LABELCIRCLE);
            numCircles++;
        }
        else{                
            squareObj.setSideLengthFromArea(seedpixel);
            sqVect2[numSquares] = squareObj.getPerimeter();
            sqVect1.push_back(squareObj);
            myImage.setAllPixelsWithOldValToNewVal(100, LABELSQUARE);
            numSquares++;
        }
    }

    //Writes the resulting labeled-shape image to a file, assigning each label a random color
    myImage.switchToRandomColorMapping();    
    myImage.writeToBMPFile("My Mona Lisa");
    
    //Output of the number of circles found and each circle's estimated Perimeter (Radius) pairs
    std::cout << "Number of CIRCLES: " << numCircles << std::endl;
    std::cout << "Circle Perimeters (Radius): " << std::endl;
    for(int i = 0; i < numCircles ; i++)
    {
        std::cout << cVect2[i] << " " << cVect2[i]/(2*3.14159) << std::endl;
    } 

    //Output of the number of squares found and each square's estimated Perimeter (Side Length) pairs
    std::cout << "Number of SQUARES: " << numSquares << std::endl;
    std::cout << "Square Perimters (Side Length):" << std::endl;
    for(int j = 0; j < numSquares ; j++)
    {
        std::cout << sqVect2[j] << " " << sqVect2[j]/4 << std::endl;
    }

    return 0;
}
/************************************************************************************
* Function name: findPixelLocationWithGivenValue
* Input: image, pixelvalue, foundRow, foundCol
* Output: whether a seed pixel has been found, row/column of the found seed pixel
* Description: This function sorts through the image searching for the locations of
* the circles and squares. It returns a true if it was able to find a pixel with
* the appropriate value.
*************************************************************************************/
bool findPixelLocationWithGivenValue(const Image &image, int pixelValue, int &foundRow, int &foundCol)
{
    int i,j;//i = rows, j = cols

    for(i = 0; i < image.getNumRows(); i++)
    {
        for(j = 0; j < image.getNumCols(); j++)
        {
            if(image.getPixel(i,j) == pixelValue)//Check if pixel value (255) found
            {
                foundRow = i;
                foundCol = j;
                return true;
            }
        }
    }
    return false;
}
/************************************************************************************
* Function name: markConnectedComponent
* Input: image, seedRow, seedCol, ccLabel
* Output: number of pixels in connected component and modified image
* Description: This function marks all pixels in a connected component within an image.
*************************************************************************************/
int markConnectedComponent(Image &image, int seedRow, int seedCol, int ccLabel)
{
    int count = 0; //counter
    int intensity = image.getPixel(seedRow,seedCol); //intensity value for pixel

    PixelLocation locPixel;//Pixel Location object
    std::stack< PixelLocation > pixelLocStack;
    locPixel.r = seedRow;
    locPixel.c = seedCol;
    pixelLocStack.push(locPixel);

    while(! pixelLocStack.empty() )
    {
        locPixel = pixelLocStack.top();//tops pixel location
        pixelLocStack.pop();//pops pixel location
        
        if(image.isInBounds(locPixel.r, locPixel.c))//checks if image is within boundary
        {
            if(image.getPixel(locPixel.r,locPixel.c) == intensity)
            {
                count++;
                image.setPixel(locPixel.r,locPixel.c,ccLabel); //sets image to the particular pixel
            
                //Pushes all of this pixel's neighbors onto the stack
                locPixel.r++;
                pixelLocStack.push(locPixel);
                locPixel.r = locPixel.r - 2;
                pixelLocStack.push(locPixel);
                locPixel.r++;

                locPixel.c++;
                pixelLocStack.push(locPixel);
                locPixel.c = locPixel.c - 2;
                pixelLocStack.push(locPixel);
            }
        }
    }
    return count;//returns pixel count
}

// An OpenGL Polygon Drawer Program

//Linux headers 
#include <GL/glut.h>

#include <stdio.h>

//Mac headers 
/*
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
*/
#include <stdlib.h>
#include <vector>
#include "GraphxMath.h"
using namespace std;


// These are defined in a global scope

GLubyte red, green, blue;
int COLORS_DEFINED;

// Specity the values to place and size the window on the screen

const int WINDOW_POSITION_X = 100;
const int WINDOW_POSITION_Y = 100;
const int WINDOW_MAX_X = 800;
const int WINDOW_MAX_Y = 800;

// Specify the coordinate ranges for the world coordinates in the 2D Frame

const float WORLD_COORDINATE_MIN_X = 0.0;
const float WORLD_COORDINATE_MAX_X = 800.0;
const float WORLD_COORDINATE_MIN_Y = 0.0;
const float WORLD_COORDINATE_MAX_Y = 800.0;

//A struct declaration to use throughout the project

 struct polPoint{
     
     double tailPoint[2]; //Saves (x,y) of line origin
     double headPoint[2]; //Saves (x,y) of line end
     
 };

vector<polPoint> POLYGON_POINTS;

void myglutInit( int argc, char** argv )
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(WINDOW_MAX_X,WINDOW_MAX_Y); /* set pixel window */
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y); /* place window top left on display */
    glutCreateWindow("Polygon Wizard"); /* window title */
}


void myInit(void)
{
    
    /* standard OpenGL attributes */
    
    glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
    glColor3f(1.0, 0.0, 0.0); /* draw in red */
    glPointSize(10.0);
    
    COLORS_DEFINED = 0;
    
    /* set up viewing window with origin lower left */
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,
               WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
    glMatrixMode(GL_MODELVIEW);
}


void display( void )
{
    
    /* define a point data type */
    
    typedef GLfloat point[2];
    
    point p; /* A point in 2-D space */
    
    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */
    
    if (!COLORS_DEFINED) {
        red   = 255;
        green = 0;
        blue  = 0;
    }
    
    glColor3ub( red, green, blue );
    
    glFlush(); /* clear buffers */
    
}


void newPoint( int x, int y )
{
    typedef GLfloat point[2];
    point p;
    
    glColor3ub( red, green, blue );
    
    p[0] = x;
    p[1] = y;
    
    if( POLYGON_POINTS.empty() ){//If no points have been drawn
        polPoint firstPoint;
        firstPoint.headPoint[0] = x;
        firstPoint.headPoint[1] = y;
        POLYGON_POINTS.push_back(firstPoint); //Add new point to the list
    } else { //If there are points already drawn
        polPoint point;
        point.headPoint[0] = x;
        point.headPoint[1] = y;//head index = vector.size()-1
        point.tailPoint[0] = POLYGON_POINTS[ POLYGON_POINTS.size()-1 ].headPoint[0];//Connects x val from last point to this point
        point.tailPoint[1] = POLYGON_POINTS[ POLYGON_POINTS.size()-1 ].headPoint[1];//Connects y val from last point to this point
        POLYGON_POINTS.push_back( point );
        
        //glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2d(point.tailPoint[0], point.tailPoint[1]);
        glVertex2d(point.headPoint[0], point.headPoint[1]);
        glEnd();
    }
    
    //This code is optional (Just creates big dots at line ends)
    glBegin(GL_POINTS);
    glVertex2fv(p);
    glEnd();
    glFlush();
}

bool polygonIntersect( ){
    //test case will be line segment <last head value in POLYGON_POINTS> --> <new mouse point>
    //                                vs. all lines
    //                                  for( int x = 0; x < size()-1; x++)
    return true; 
}

void closePolygon( int x, int y )
{
    //If there are enough points to close a polygon
    if( POLYGON_POINTS.size() > 2){
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 1.0f);
        // the last point drawn by user
        glVertex2d(POLYGON_POINTS[ POLYGON_POINTS.size()-1 ].headPoint[0],
                   POLYGON_POINTS[ POLYGON_POINTS.size()-1 ].headPoint[1]);
        //the original point drawn by user
        glVertex2d(POLYGON_POINTS[0].headPoint[0],
                   POLYGON_POINTS[0].headPoint[1]);
        glEnd();
    }
    
    glFlush();
}


void clearBox()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}


void mouse( int button, int state, int x, int y )
{
    
    if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
    {
        printf ("%d   %d\n", x, WINDOW_MAX_Y-y);
        newPoint( x, WINDOW_MAX_Y-y );
    }
    
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        printf ("%d   %d\n", x, WINDOW_MAX_Y-y);
        closePolygon( x, WINDOW_MAX_Y-y );
    }
    
    if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
    {
        printf ("%d   %d\n", x, WINDOW_MAX_Y-y);
        clearBox();
    }
}

//Assign commands to certain keys
void keyboard( unsigned char key, int x, int y )
{
    if ( key == 'q' || key == 'Q') exit(0);
}



int main(int argc, char** argv)
{
    
    myglutInit(argc,argv); //Set up Window
    myInit(); /* set attributes */
    
    
    // Now start the standard OpenGL glut callbacks //
    double p1[]={-7,-1};
    double q1[]={8,3};
    double p2[]={-2,1};
    double q2[]={-1,-2};
   cout <<  doesIntersect(p1, q1, p2, q2) << endl;
    
    glutMouseFunc(mouse);  /* Define Mouse Handler */
    glutKeyboardFunc(keyboard); /* Define Keyboard Handler */
    glutDisplayFunc(display); /* Display callback invoked when window opened */
    glutMainLoop(); /* enter event loop */
}


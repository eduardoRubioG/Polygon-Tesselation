
// An OpenGL Polygon Drawer Program

#include <stdio.h>

//Linux headers 
#include <GL/glut.h>

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
bool CAN_CONTINUE_DRAWING = true;

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
    glPointSize(2.0);
    
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

// Test whether or not a point intersects with any points of the existing polygon
bool polygonIntersect( double x, double y ){

    //Create a temporary point value for the new point the user is trying to add
    double Prospective_New_Point[] = { x, y } ;
    
    //Make sure we have appropriate points on the window before intersection checks need to happen
    if( POLYGON_POINTS.size() >= 3 ) {
        for ( int iter = 0; iter < POLYGON_POINTS.size()-2; iter++ ) {
            
            if( doesIntersect( POLYGON_POINTS[ iter ].headPoint,
                               POLYGON_POINTS[ iter+1].headPoint,
                                POLYGON_POINTS[ POLYGON_POINTS.size() - 1].headPoint,
                                Prospective_New_Point ) == true )
                return true; // end of nested if-statement
            
        }//end of for-loop
    }//end of main if-statement
    return false;
}

// Special intersection check for when the user attempts to close the polygon
//  Modified to take into account that the closing line will be adjacent to the
//  first segment in the polygon
bool closePolygonIntersect( double x, double y ){
    
    //Create a temporary point value for the new point the user is trying to add
    double Prospective_New_Point[] = { x, y } ;
    
    //Make sure we have appropriate points on the window before intersection checks need to happen
    if( POLYGON_POINTS.size() >= 3 ) {
        for ( int iter = 1; iter < POLYGON_POINTS.size()-2; iter++ ) {
            
            if( doesIntersect( POLYGON_POINTS[ iter ].headPoint,
                              POLYGON_POINTS[ iter+1].headPoint,
                              POLYGON_POINTS[ POLYGON_POINTS.size() - 1].headPoint,
                              Prospective_New_Point ) == true )
                return true; // end of nested if-statement
            
        }//end of for-loop
    }//end of main if-statement
    return false;
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
        POLYGON_POINTS.push_back(firstPoint);
        
    } else { //If there are points already drawn
        
            //Before drawing anything/adding a point into the PP vector, check to see if
            //prospective point will intersect with the polygon
        
            if( polygonIntersect( x , y ) == false ) {
            
            //Commit point to the POLYGON_POINTS vector
            polPoint point;
            point.headPoint[0] = x;
            point.headPoint[1] = y;//head index = vector.size()-1
            point.tailPoint[0] = POLYGON_POINTS[ POLYGON_POINTS.size()-1 ].headPoint[0];//Connects x val from last point to this point
            point.tailPoint[1] = POLYGON_POINTS[ POLYGON_POINTS.size()-1 ].headPoint[1];//Connects y val from last point to this point
            
            POLYGON_POINTS.push_back( point );
            
            //Draw line from last point to new user point
            
            glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 1.0f);
            glVertex2d(point.tailPoint[0], point.tailPoint[1]);
            glVertex2d(point.headPoint[0], point.headPoint[1]);
            glEnd();
                
            //This code is optional (Just creates dots at line ends)
            glBegin(GL_POINTS);
            glVertex2fv(p);
            glEnd();
            glFlush();
                
            } else {//Simple message for command line when intersections occur. Maybe add text popup later???
                cout << "INTERSECTION: TRY AGAIN" << endl;
            }
    }
}//End of newPoint function


//Clears the screen and polygon points if user wants to restart drawing
void clearScreen( ) {
    
    CAN_CONTINUE_DRAWING=true;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    POLYGON_POINTS.clear();
    glFlush();

}

//Quick little function to display text on the screen
void displayText( float x, float y, const char *string ) {
    size_t j = strlen( string );
    
    glColor3f( 1.0, 0.0, 0.0 );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
}

void closePolygon( int x, int y )
{
    //If there are enough points to close a polygon
    if( POLYGON_POINTS.size() > 2){
        
        //Check to see if the closing line would intersect with the existing polygon
        double Prospective_New_Point[] = { POLYGON_POINTS[0].headPoint[0],
                                        POLYGON_POINTS[0].headPoint[1] } ;
        
        if( closePolygonIntersect(Prospective_New_Point[0] , Prospective_New_Point[1]) == false ) {
          
        //Draw closing line
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 1.0f);
        // the last point drawn by user
        glVertex2d(POLYGON_POINTS[ POLYGON_POINTS.size()-1 ].headPoint[0],
                   POLYGON_POINTS[ POLYGON_POINTS.size()-1 ].headPoint[1]);
        //the original point drawn by user
        glVertex2d(POLYGON_POINTS[0].headPoint[0],
                   POLYGON_POINTS[0].headPoint[1]);
        glEnd();
        glFlush();
            
        } else { cout << "CLOSE POLYGON INTERSECTS: TRY AGAIN " << endl; }//end of nested if-statement
    }//end of first if-statement
}

void mouse( int button, int state, int x, int y )
{
    
    if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
    {
        printf ("%d   %d\n", x, WINDOW_MAX_Y-y);
        if( CAN_CONTINUE_DRAWING == true ) newPoint( x, WINDOW_MAX_Y-y );
    }
    
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        printf ("%d   %d\n", x, WINDOW_MAX_Y-y);
        closePolygon( x, WINDOW_MAX_Y-y );
        CAN_CONTINUE_DRAWING=false;
    }
    
    if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
    {
        printf ("%d   %d\n", x, WINDOW_MAX_Y-y);
        clearScreen();
    }
}

//Assign commands to certain keys
void keyboard( unsigned char key, int x, int y )
{
    if ( key == 'q' || key == 'Q' ) exit(0);
    if ( key == 'c' || key == 'C' ) clearScreen();
}



int main(int argc, char** argv)
{
    
    myglutInit(argc,argv); //Set up Window
    myInit(); /* set attributes */
    
    
    // Now start the standard OpenGL glut callbacks //
    glutMouseFunc(mouse);  /* Define Mouse Handler */
    glutKeyboardFunc(keyboard); /* Define Keyboard Handler */
    glutDisplayFunc(display); /* Display callback invoked when window opened */
    glutMainLoop(); /* enter event loop */
}


// An OpenGL Polygon Drawer Program
#include <stdio.h>
//Linux Headers
/*
#include <GL/glut.h>
*/
//Mac headers
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
//
#include <stdlib.h>
#include <vector>
#include "GraphxMath.h"
using namespace std;

// These are defined in a global scope
GLubyte red, green, blue;
int COLORS_DEFINED;
bool CAN_CONTINUE_DRAWING = true; //Global boolean that dictates whether user can continue drawing lines or not

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
     
     double point[2]; //Saves (x,y) of line end
     
 };

struct triangle {
    
    polPoint p;
    polPoint q;
    polPoint r;
    
};

vector<polPoint> POLYGON_POINTS; //Main container for all polygon points. Global scope for all functions
vector<polPoint> T_POLYGON_POINTS;//Main container for tesselated points. Global scope for all functions
vector<triangle> TRIANGLES;//Main container for triangles post-tesselation. Global scope for all functions.


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
    glClearColor(0.0, 0.0, 0.0, 0.0); /* white background */
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

/**
 *Invoked when opening window
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

/**
 * Prints polPoints contained in vector
 */
void printPolPointVectors( vector<polPoint> v ) {
    for( int x  = 0; x < v.size(); x++ )
    {
        cout << "V" << x << " (" << v[x].point[0] << ", " << v[x].point[1] << ")  --  ";
    }
    cout << "\n\n" ;
}

/**
 * Draw line between specified points
 */
void drawLine( polPoint firstPoint, polPoint secondPoint ) {
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2d(firstPoint.point[0], firstPoint.point[1]);
    glVertex2d(secondPoint.point[0], secondPoint.point[1]);
    glEnd();
    glFlush();
}

/**
 * Test whether or not a point intersects with any points of the existing polygon
 */
bool polygonIntersect( double x, double y ){

    double Prospective_New_Point[] = { x, y } ;
    
    if( POLYGON_POINTS.size() >= 3 ) {
        for ( int iter = 0; iter < POLYGON_POINTS.size()-2; iter++ )

            if( doesIntersect( POLYGON_POINTS[ iter ].point,
                               POLYGON_POINTS[ iter+1].point,
                                POLYGON_POINTS[ POLYGON_POINTS.size() - 1].point,
                                Prospective_New_Point ) == true )
                return true;
    }//end of main if-statement
    return false;
}

/**
 * Modified version of intersection checks. Used for closing the polygon.
 */
bool closePolygonIntersect( double x, double y ){
    
    double Prospective_New_Point[] = { x, y } ;
    
    if( POLYGON_POINTS.size() >= 3 ) {
        for ( int iter = 1; iter < POLYGON_POINTS.size()-2; iter++ )
            
            if( doesIntersect( POLYGON_POINTS[ iter ].point,
                              POLYGON_POINTS[ iter+1].point,
                              POLYGON_POINTS[ POLYGON_POINTS.size() - 1].point,
                              Prospective_New_Point ) == true )
                return true;
            
    }
    return false;
}

/**
 * Called by user to draw new point/line on screen
 */
void newPoint( int x, int y ){

    polPoint newPoint;
    newPoint.point[0] = x;
    newPoint.point[1] = y;
    
    //If first point has not been drawn
    if( POLYGON_POINTS.empty() ){
        glPointSize(2.0);
        glBegin(GL_POINTS);
        glVertex2d(x, y);
        glEnd();
        glFlush();
        
        POLYGON_POINTS.push_back(newPoint);
        
    } else
        if( !polygonIntersect( x , y ) ) {
            drawLine( POLYGON_POINTS[ POLYGON_POINTS.size()-1 ], newPoint);
            POLYGON_POINTS.push_back( newPoint );
        } else cout << "Intersection found; Please try again"<< endl;
}

/*
 ============================   TESSELATION BLOCK BEGINS   ==================================
 */

/**
 * Check to see if the polygon drawn by user was drawn clockwise or not
 */
bool drawnClockWise( ) {
    
    double sum = 0;
    for( int x = 0; x < POLYGON_POINTS.size(); x++ ) {
        
        double x1 = POLYGON_POINTS[ x ].point[0];
        double y1 = POLYGON_POINTS[ x ].point[1];
        double x2 = POLYGON_POINTS[ x + 1].point[0];
        double y2 = POLYGON_POINTS[ x + 1].point[1];
        
        if( x+1 == POLYGON_POINTS.size() ) {
            x2 = POLYGON_POINTS[ 0 ].point[0];
            y2 = POLYGON_POINTS[ 0 ].point[1];
        }
        
        sum += ( x2 - x1 ) * ( y2 + y1 );
    }
    
    //If sum is positive then polygon was drawn clockwise
    //and polygon points will need to be flipped
    if( sum > 0 ) return true;
    else         return false;
}

/**
 * Flips designated vector but maintains starting vertex. Will be used in case of user-drawn polygon being clockwise
 */
vector<polPoint> flipPolygonPoints( vector<polPoint> const originalVec ){
    
    vector<polPoint> newVec;
    
    newVec.push_back( originalVec[0] );
    for( int pos = (int) originalVec.size(); 1 < pos; pos-- ) {
        newVec.push_back( originalVec[ pos-1 ] );
    }
    
    return newVec;
}

/**
 * Intersection checker specifically for use during tesselation
 */
bool finishedPolygonIntersect( int firstPointIndex, int secondPointIndex, vector<polPoint> untouchedPoints ) {
    
    //1.    Check if point a, middle point, and point b are counterclockwise
    //      If counterclockwise proceed to next step. If not, report intersection
    if( orientation( untouchedPoints[ firstPointIndex ].point,
                    untouchedPoints[ firstPointIndex + 1 ].point,
                    untouchedPoints[ secondPointIndex ].point) != 2 )
        return true;
    
    //2. Check to see if proposed line will go outside of the polygon
    if( getAngle(untouchedPoints[ firstPointIndex ].point,
                 untouchedPoints[ firstPointIndex + 1 ].point,
                 untouchedPoints[ secondPointIndex ].point) > 180)
        return true;
    
    //3. Check for intersections
    for( int x = 0; x < untouchedPoints.size(); x++ ){
        
        int xPlusOne = (x+1)%untouchedPoints.size();
        
        //Check if line segments in question are adjacent
        if( !isAdjacent(x, xPlusOne, firstPointIndex, secondPointIndex))

            //Lines are not adjacent, so check for intersection
            if (  doesIntersect(  untouchedPoints[ x ].point,
                                 untouchedPoints[ xPlusOne ].point,
                                 untouchedPoints[ firstPointIndex ].point,
                                 untouchedPoints[ secondPointIndex ].point) )
                return true;
        
    }
    return false;
}

/**
 * Add new triangle
 */
void newTriangle( int indexP, int indexQ, int indexR, vector<polPoint> const vector ) {
    triangle t;
    t.p = vector[ indexP ];
    t.q = vector[ indexQ ];
    t.r = vector[ indexR ];
    TRIANGLES.push_back( t );
}

/**
 * Final steps to finishing tesselation. Called when there are 4 points left in polygon
 */
void fourTipFinish( vector<polPoint> v ) {
    
    //Finds midpoint of proposed line
    double mp13[2];
    midpoint( v[1].point, v[3].point, mp13);
    
    //Checks to make sure the midpoint is within the constraints of the polygon
    if( (mp13[0] > v[0].point[0] && mp13[0] < v[2].point[0]
        && mp13[1] < v[3].point[1] && mp13[1] > v[1].point[1])
        ||
       (mp13[0] > v[1].point[0] && mp13[0] < v[3].point[0]
        && mp13[1] < v[0].point[1] && mp13[1] > v[2].point[1])){
            
            drawLine(v[1], v[3]);
            newTriangle( 0,1,3,v );
            newTriangle( 1,2,3,v );
            
        } else {
            drawLine(v[0], v[2]);
            newTriangle( 0,1,2,v );
            newTriangle( 0,2,3,v );
        }
}

/**
 * Tesselate the user drawn polygon using ear-clipping method
 */
void tesselate( ) {
    
    //Will be used for to maintain which points have not been clipped
    vector<polPoint> untouchedPoints;
    
    //If polygon was drawn clockwise, then flip the polygon points into the T_POLY list
    if( drawnClockWise() )
        T_POLYGON_POINTS = flipPolygonPoints( POLYGON_POINTS ) ;
    else
        T_POLYGON_POINTS = POLYGON_POINTS;
    
    untouchedPoints = T_POLYGON_POINTS;
    
    for( int x = 0; x < untouchedPoints.size(); x++ ){
        
        //printPolPointVectors(untouchedPoints);
        int xPlusOne = (x+1)%untouchedPoints.size();
        int xPlusTwo = (x+2)%untouchedPoints.size();
        
        //In the special case that there is a four point polygon, simply 'cut' it in half
        if( untouchedPoints.size() == 4 ){
            fourTipFinish(untouchedPoints);
            return;
        }
        
        if( untouchedPoints.size() == 3 )
        {
            newTriangle(0, 1, 2, untouchedPoints);
            return;
        }
  
        if( !finishedPolygonIntersect( x , xPlusTwo , untouchedPoints) ) {// point x and x+2 do not have an intersection
            drawLine( untouchedPoints[x], untouchedPoints[xPlusTwo] );
            newTriangle(x, xPlusOne, xPlusTwo, untouchedPoints);
            untouchedPoints.erase( untouchedPoints.begin() + xPlusOne );     //Remove the middle point of the triangle
            x = 0;  //Return x to 0 to continue ear-clipping algorithm
        }
        
    }//end of for-loop
}

/*
 ============================   TESSELATION BLOCK ENDING   ==================================
 */

/**
 * Clear the screen of everything and clear all stored data
 */
void clearScreen( ) {
    
    CAN_CONTINUE_DRAWING=true;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    POLYGON_POINTS.clear();
    T_POLYGON_POINTS.clear();
    TRIANGLES.clear();
    glFlush();

}

/**
 * Redraw the outline of the original polygon
 */
void getOriginalPolygon( ) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    TRIANGLES.clear();
    
    for( int x = 0; x < POLYGON_POINTS.size(); x++ ) {

        int secondPointIndex = (x+1)%POLYGON_POINTS.size();
        drawLine( POLYGON_POINTS[x], POLYGON_POINTS[secondPointIndex]);
        
    }
}

/**
 * Fill all triangles of a tesselated polygon
 */
void fillPolygonT( ) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if( TRIANGLES.empty() )
        tesselate();
    
    glBegin(GL_TRIANGLES);
    for( int x = 0; x < TRIANGLES.size(); x ++ ) {
        glVertex2d(TRIANGLES[x].p.point[0], TRIANGLES[x].p.point[1]);
        glVertex2d(TRIANGLES[x].q.point[0], TRIANGLES[x].q.point[1]);
        glVertex2d(TRIANGLES[x].r.point[0], TRIANGLES[x].r.point[1]);
    }
    glEnd();
    glFlush();
}

/**
 * Fill polygon consisting of vertices
 */
void fillPolygon( ) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for (int x = 0; x < POLYGON_POINTS.size(); x++)
        glVertex2d(POLYGON_POINTS[ x ].point[ 0 ], POLYGON_POINTS[ x ].point[ 1 ] );
    glEnd();
    glFlush();
}

/**
 * Sums the area of all triangles
 */
void findArea( vector<triangle> t){
    
    double seg1[3];
    double seg2[3];
    double totalSum = 0;
    
    for( int x = 0; x < TRIANGLES.size(); x++ ){
        
        seg1[0] = TRIANGLES[x].q.point[0] - TRIANGLES[x].p.point[0];
        seg1[1] = TRIANGLES[x].q.point[1] - TRIANGLES[x].p.point[1];
        seg1[2] = 0; //Because we are dealing with only 2 dimensions
        seg2[0] = TRIANGLES[x].r.point[0] - TRIANGLES[x].p.point[0];
        seg2[1] = TRIANGLES[x].r.point[1] - TRIANGLES[x].p.point[1];
        seg2[2] = 0;
        
        //Calculate only z-component (since we are in the 2D)
        double zComp = (seg1[0] * seg2[1]) - (seg2[0] * seg1[1]);
        double localTriArea = (.5)*(abs(zComp));
        cout << "Triangle " << x+1 << " has an area of: " << localTriArea << endl;
        totalSum +=  localTriArea;
    }
    cout << "Total polygon area: " << totalSum << endl;
    
}

/**
 * Draw the final line of a polygon to close it off
 */
void closePolygon( int x, int y )
{
    if( POLYGON_POINTS.size() > 2){
        
        double Prospective_New_Point[] = { POLYGON_POINTS[0].point[0],
                                        POLYGON_POINTS[0].point[1] } ;
        
        if( !closePolygonIntersect(Prospective_New_Point[0] , Prospective_New_Point[1]) ){
                  printf ("Point accepted: %d   %d\n", x, WINDOW_MAX_Y-y);
                  drawLine( POLYGON_POINTS[ POLYGON_POINTS.size()-1 ], POLYGON_POINTS[0] );
                  CAN_CONTINUE_DRAWING=false;
        }
        
    }
}

/**
 * Acts as the listener interface for mouse commands
 */
void mouse( int button, int state, int x, int y )
{
    
    if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
        if( CAN_CONTINUE_DRAWING ){
            printf ("Point accepted: %d   %d\n", x, WINDOW_MAX_Y-y);
            newPoint( x, WINDOW_MAX_Y-y );
        }
    
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
        closePolygon( x, WINDOW_MAX_Y-y );
    
    if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
        clearScreen();
}

/**
 *Assign commands to certain keys
 */
void keyboard( unsigned char key, int x, int y )
{
    if ( key == 'q' || key == 'Q' ) exit(0);
    if ( key == 'c' || key == 'C' ) clearScreen();
    if ( key == 'i' || key == 'I' ) getOriginalPolygon();
    if ( key == 'f' || key == 'F' ) fillPolygon();
    if ( key == 'p' || key == 'P' ) fillPolygonT();
    if ( key == 't' || key == 'T' ) {
        tesselate();
        findArea(TRIANGLES);
    }
}


int main(int argc, char** argv) {
    myglutInit(argc,argv); //Set up Window
    myInit(); /* set attributes */
    // Now start the standard OpenGL glut callbacks //
    
    glutMouseFunc(mouse);  /* Define Mouse Handler */
    glutKeyboardFunc(keyboard); /* Define Keyboard Handler */
    glutDisplayFunc(display); /* Display callback invoked when window opened */
    glutMainLoop(); /* enter event loop */
}


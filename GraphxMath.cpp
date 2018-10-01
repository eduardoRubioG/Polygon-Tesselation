//
//  GraphxMath.cpp
//  LbsProject
//
//  Created by Eduardo Rubio on 9/18/18.
//  Copyright © 2018 Eduardo Rubio. All rights reserved.
//

#include "GraphxMath.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

/*
 PRE-CONDITION:
 Input to vectors to take cross product and store resulting vector into <resultingVector>
 */
template <class Object>
void crossProd( std::vector<Object> const& a, std::vector<Object> const& b, std::vector<Object>  resultingVector ) {
    resultingVector[0] = a[1]*b[2] - a[2]*b[1];
    resultingVector[1] = a[0]*b[2] - a[2]*b[0];
    resultingVector[2] = a[0]*b[1] - a[1]*b[0];
}
/*
 POST-CONDITION:
 The input vector <resultingVector> now has resulting vector from a x b 
 */

/*
 PRE-CONDITION:
 Enter two equal sized vectors containing numerical variables
 */
template <class Object>
double dotProd( std::vector<Object> const& a, std::vector<Object> const& b  ) {
    if (a.size() != b.size()) { throw std::runtime_error("DOT PRODUCT ERROR: Vectors different sizes"); }
    double DOT_PRODUCT = 0;
    for( int x = 0; x < a.size()-1; x++ )
        DOT_PRODUCT += (a[x])*(b[x]);
    return DOT_PRODUCT;
}
/*
 POST-CONDITION:
 Returns a scalar value between two vectors
 */

/*
 PRE-CONDITION:
 Enter 3 colinear points to check if point 'q' lies in segment 'p -> r'
 */
template <class Object>
bool onSegment( Object const p[],
                Object const q[],
                Object const r[]  ) {
    
    if (q[0] <= std::max(p[0], r[0]) && q[0] >= std::min(p[0], r[0]) &&
        q[1] <= std::max(p[1], r[1]) && q[1] >= std::min(p[1], r[1]))
        return true;
    
    return false; 
}
/*
 POST-CONDITION:
 Returns TRUE if q lies in segment pr. Otherwise, it returns FALSE
 */

/*
 PRE-CONDITION:
 Input ordered triplet of points to find if points are colinear, clockwise, or counterclockwise
 */
template<class Object>
int orientation( Object const p[],
                 Object const q[],
                 Object const r[] ) {
    
    int val = (q[1] - p[1]) * (r[0] - q[0]) -
                (q[0] - p[0]) * (r[1] - q[1]);
    
    if (val == 0) return 0;  // colinear
    
    return (val > 0)? 1: 2;
    
}
/*
 POST-CONDITION:
 Function returns following values:
    0 --> p, q, and r are colinear
    1 --> Clockwise
    2 --> Counterclockwise
 */

/*
 PRE-CONDITION:
 Input four points to check whether their line segments intersect
*/
template <class Object> //POLYGON_POINTS[3].headPoint
bool doesIntersect( Object const p1[], Object const q1[], /*Algorithm from GeeksforGeeks*/
                   Object const p2[], Object const q2[] ) {
    
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
    
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    
    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    
    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    
    return false; // Doesn't fall in any of the above cases
}
/*
 POST-CONDITION:
 Return true if there is intersection and false if there is none 
 */

/*
 PRE-CONDITION:
 Gets the angle between two vectors. Just input the two vector points
*/
template <class Object>
double getAngle(  Object const P[], Object const Q[], Object const R[] ) {
    
    //Create the 3 points into two vectors
    double PQ[] = { (double) Q[0]-P[0], (double) Q[1]-P[1] };//Create vector PQ
    double QR[] = { (double) R[0]-Q[0], (double) R[1]-Q[1] };//Create vector QR
    
    //Calculate values needed for the angle calculation
    double dotProduct = PQ[0]*QR[0] + PQ[1]*QR[1];
    double PQmagnitude = sqrt( PQ[0]*PQ[0] + PQ[1]*PQ[1] );
    double QRmagnitude = sqrt( QR[0]*QR[0] + QR[1]*QR[1] );
    
    //Solve
    double angleInRadians = acos( dotProduct / (PQmagnitude*QRmagnitude) );
    
    //Converts from radians to degrees
    return ( (180 * angleInRadians) / M_PI ) ;
}
/*
 POST-CONDITION:
 Returns double representing angle between two line segments in the form of degrees
*/

/**
 *Checks to see if two line segments are adjacents
 */
template <class Object>
bool isAdjacent( Object x, Object xPlusOne, Object firstPointIndex, Object secondPointIndex) {
    
    if ( x != firstPointIndex && xPlusOne != firstPointIndex &&
        x != secondPointIndex && xPlusOne != secondPointIndex )
        return false;
    
    return true;
}

/**
 *Given two points, return the midpoint 
 */
template <class Object>
void midpoint( Object const p[], Object const q[], double midpointArray[]){
    midpointArray[0] = (p[0] + q[0])/2;
    midpointArray[1] = (p[1] + q[1])/2;
}
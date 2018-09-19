//
//  GraphxMath.hpp
//

#ifndef _GraphxMath_H
#define _GraphxMath_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>


template <class Object>
class gMath {
    
public:
    double dotProd( std::vector<Object> const& a, std::vector<Object> const& b );
    void crossProd( std::vector<Object> const& a, std::vector<Object> const& b,
                   std::vector<Object> const& resultingVector );
    bool doesIntersect( Object const p1[], Object const q1[], /*Algorithm from GeeksforGeeks*/
                       Object const p2[], Object const q2[]  );

private:
    bool onSegment( Object const p[],
                    Object const q[],
                    Object const r[] ); /*For doesIntersect function*/
    
    int orientation( Object const p[],
                     Object const q[],
                     Object const r[] );/*For doesIntersectfunction*/
  
};

#include "GraphxMath.cpp"
#endif /* GraphxMath_hpp */
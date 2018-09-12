In its most simple form, this project will allow the user to draw simple polygons and then fill in. 
However, because OpenGL would run into problems filling in some polygons, we need to tesselate the polygon too. 

Program specifications: 
    Dimensions of the screen should be 700x700 (Use constants to define this) 

Development Stages: 
1.  The program allows the user to select points on the screen (these points will be saved into a data 
    structure) and then these points will become the vertices of the polygon with lines connecting all of them 

2.  Implement a way for the user to 'undo' a point. Essentially, go back into the data structure

3.  Now, implement a method to check if the user will intersect lines before it draws out a new line and vertex 

4.  Once the user is ready to fill the polygon in, tesselate it. 

Mouse: 
Using the code we developed in class for putting dots on the screen as a starting point,
write code that collects a series of points to form the vertices of your polygon.  Each right
click should define a new point and at the last point use a left click.  As you build your
polygon make sure that none of your points form polygon sides that intersect.   This can
easily be done by checking to see if the last line segment intersects with any of the line
segments prior to it in the list.  If you do try to create a new point that violates these
rules, indicate it on the console.   Also, it will be save some steps if you build you
polygon in a CCW manner.

Keyboard: 
Once you hit the left mouse button the outline of your polygon should appear.  Hitting “f”
should attempt to draw the polygon filled in with no tesselation.  Hitting “t” should show
the triangles used in the tesselation.  Hitting “p” should show the filled in polygon after
tesselation.  Hitting “l” should return you to the initial polygon outline.  Hitting “q” should
exit the program
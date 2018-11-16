In its most simple form, this project will allow the user to draw simple polygons and then fill them in. 
However, because OpenGL would run into problems filling in concave polygons, we need to tesselate the polygon as well. 

Dimensions of the screen should be 700x700 (Use constants to define this) 

Development Stages: 
1.  The program allows the user to select points on the screen (these points will be saved into a data 
    structure) and then these points will become the vertices of the polygon with lines connecting all of them 

2.  Implement a way for the user to 'undo' a point. Essentially, go back into the data structure

3.  Now, implement a method to check if the user will intersect lines before it draws out a new line and vertex 

4.  Once the user is ready to fill the polygon in, tesselate it. 

Mouse: 
Each right click should define a new point and at the last point use a left click.  As you build your
polygon, the program will ensure no lines intersect.

Keyboard: 
Once you hit the left mouse button the outline of your polygon should appear.  Hitting “f”
will attempt to draw the polygon filled in with no tesselation.  Hitting “t” will show
the triangles used in the tesselation.  Hitting “p” will show the filled in polygon after
tesselation.  Hitting “l” will return you to the initial polygon outline.  Hitting “q” should
exit the program

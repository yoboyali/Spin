<img src="https://github.com/yoboyali/Spin/blob/main/imgs/Banner.png?raw=true"/>
<br>
Using ascii characters and rotational matrices we can achieve a 3D effect with any geometric shape we want!

# Demo
<img src="https://github.com/yoboyali/Spin/blob/main/imgs/Demo.gif" width=100% />

# Code Explanation

These are the rotational matrices that are used to calculate the pixel position<br>
the i , j , k are changing variables for each face that are updated every frame<br>
the A , B , C are angles that are updated everyframe with a fixed ratio

<img src="https://github.com/yoboyali/Spin/blob/main/imgs/CalcCube.png?raw=true"/>

This is the function used to calculate the pixel positions for the donut and (the one for the cube is very similar)<br>
the i , j , k are changing variables of a loop that are updated everyframe but the difference here is that we add<br>
the radius of the small and bigger circle and then multiply by cos(theta) to get a point on the circle and then<br>
we multiply by cos(phi)/sin(phi) to make it rotate around the tube, we then position the point using the xp and xy<br>
and add them to the buffer after calculating the luminance.

<img src="https://github.com/yoboyali/Spin/blob/main/imgs/CalcCircle.png?raw=true"/>

# Running the program
this program can be executed using the cmake command<br>
from inside the cmake-build-debug directory run:

<img src="https://github.com/yoboyali/Spin/blob/main/imgs/build.png?raw=true"/>

To clean the program from inside the same directory run:

<img src="https://github.com/yoboyali/Spin/blob/main/imgs/clean.png?raw=true"/>

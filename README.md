# BellmanFordAnimationOpenGL

This project is an OpenGL animation of the Bellamn-Ford algorithm.
 
 ### Installation and Execution (Windows)

1. Clone repo

2. Install OpenGL and its dependencies. For that, you can follow this guide: https://medium.com/swlh/setting-opengl-for-windows-d0b45062caf

3. Change to directory

````
cd BellmanFordAnimationO
````   

4. Compile both 2D and 3D implementations using GCC:

````
g++ trabalho2d.cpp -o trabalho2d -lopengl32 -I ./glew-2.2.0/include/ -I ./freeglut/include/ ./glew-2.2.0/bin/Release/x64/glew32.dll ./freeglut/bin/x64/freeglut.dll -I ./glm

g++ trabalho3d.cpp -o trabalho3d -lopengl32 -I ./glew-2.2.0/include/ -I ./freeglut/include/ ./glew-2.2.0/bin/Release/x64/glew32.dll ./freeglut/bin/x64/freeglut.dll -I ./glm
````  

5. Execute the 2D or 3D implementation:

````
trabalho2d
````  
````
trabalho3d
````  

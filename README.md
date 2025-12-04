# About

This is a lightweight graphics engine I built in 2022/2023 that loads OBJ/MTL files and manages scene objects, transforms, and camera movement. The goal was to build a flexible foundation for a future game engine, starting with custom file loading and a basic scene graph architecture. I paused development during college, but I plan to return to it and expand the engine with more advanced features.

To modify, Program.cpp has an Start and Update function where you can load and manipulate models such as position or rotation.
There is example code already there so you can see how to do it, but you should use 'sceneObjects' to store all SimObjects.
SimObject's are used to store Mesh's and Model's position and rotation in world space as well as provide a way to make children objects. This allows you to combine models into larger objects which share relative position and rotation.
The Camera is also inhereted from SimObject which allows you to move around the camera if you want, use 'mainCamera' to do this. Note that camera rotation is based on world position.

# To Run
To run the program, use the provided shortcut called "build_test" located in the same folder as the readme file. 
It will open up a command line (as the program is in debug mode) and a window that shows a mock solar system with the Sun, Earth and Moon 'orbiting' eachother. (Note there isn't physics, they're just children of eachother and change rotations)
It should look like this:

https://github.com/user-attachments/assets/12de7c65-9bac-4a23-b987-c6653922bfd5

# Common Errors
I reccommend running this from Visual Studio 2022 (purple one) as that should be the easiest to set up.
If you get an error saying something like "cannot load .lib" or .dll, etc. thats a Linker problem. Make sure you set the proper filepaths to the lib and include folders within the project and link the .lib files as well.
To do this, go to Project->DonEngine2 Properties, then to VC++ Directories to set the filepaths and Linker->Input to set the .lib names. 
Also note that running for the first time will attempt to load symbols, which can take a while, but this is only for the first load.

# To-Do List
- Lighting Objects
- Sound Objects
- UI Objects
- Scripting
- Physics

# Libraries Used
 - OpenGL for graphics
 - GLAD for window creation and management
 - GLM for math and vector/matrix use
 - SDL2 for audio/keyboard/mouse connection and graphics management

Assimp and mono are in there but never used, mono is for scripting so I left it and assimp is for a more robust file loading system if I ever get around to that.

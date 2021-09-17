# TicTacToeInC++
An implementation of Tic Tac Toe with an unbeatable AI that uses the minmax algorithm, and graphics that are powered by OpenGL.

<img width="1913" alt="ticTacToeInC++" src="https://user-images.githubusercontent.com/43594702/133703856-63c48b1e-5a13-4743-b1af-2b1bb7af057d.png">

[See it in action!](https://www.youtube.com/watch?v=ZvJK15RH2OE)

## Installer: 

If are not interested in compiling or messing around with the code here, I will be releasing an installer to simply install the game 
here pretty soon. 

__COMING SOON__

## How to play

- Use mouse to hover over the grid you want to pick, left click to pick it
- Press esc key at any time to shut the game down
- When game is over, it automatically restarts itself 

## Using the source code: 

The source code is intended to be used and edited from within Visual Studio 2019. To set up a project for these source files, create a new, empty visual studio project, and copy and paste the src, shaders, and res folders into the directory that gets created for your visual studio project. There will now be some external libraries which you will have to download and link via the project properties in visual studio. Below is a list of the libraries you will need and why: 

1. GLFW - For handling user input and events, and also for the creation of a window 
2. GLAD - For locating and loading the implementations of the OpenGL functions on the GPU, so that they can be used from within the program. This is what allows for the usage of modern OpenGL 
3. stb_image - This should already be all set to go, provided you kept the header file and cpp file for it within the src directory.
4. GLM - For the mathematics we need in order to allow us to work with OpenGL 

__HOW TO SETUP GLFW IN VISUAL STUDIO 2019__

Follow the instructions provided right here: 

[Setting up GLFW for visual studio 2019](https://learnopengl.com/Getting-started/Creating-a-window)

__HOW TO SETUP GLAD IN VISUAL STUDIO 2019__

Follow the instructions at the bottom of this article: 

[Setting up GLAD for visual studio 2019](https://learnopengl.com/Getting-started/Creating-a-window)

__HOW TO SETUP GLM IN VISUAL STUDIO 2019__

Download GLM from [here](https://glm.g-truc.net/0.9.8/index.html). Since GLM is a header only library, there is 
no linking or compiling we need to do. Simply copy all the header files in it and paste them into the include directory you 
created for GLFW and GLAD when you were setting those 2 things up.

## References

1. https://learnopengl.com/ - For learning about how to use OpenGL
2. https://gsurma.medium.com/tic-tac-toe-creating-unbeatable-ai-with-minimax-algorithm-8af9e52c1e7d#14e6 - For how to use minmax algorithm within Tic Tac Toe
3. https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/ - For some more information on minmax algorithm

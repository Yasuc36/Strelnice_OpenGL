//----------------------------------------------------------------------------------------
/**
 * \file    vancafra.cpp : This file contains the 'main' function and callbacks.
			Program execution begins and ends there.
 * \author  Frantisek Vancaz
 * \date    2023/05/16
 * \brief   Main app file.
 */

 /**
  * \brief	\mainpage Documentation of the app of simple 3D game, Shooting Range
  *
  * This is the OpenGL application written in FreeGLUT and PGR framework.
  * Scene contains small area in the forest. There is located small shooting range with many objects scattered around.
  * It is day, but fog and some lights can be turned on/off.
  * Also there is some interactive objects and functions.
  *
  * Controls:
  * [W, S, A, D] / [Up, Down, Left, Right] - Movement
  * [R] - Restarts the application
  * [V] - Change camera
  * [M] - Turn on/off the fog
  * [K] - Turn on/off the collisions
  * [F] - Turn on/off the flashlight (spot light)
  * [Shift + "Movement keys"] - Faster movement
  * [Shift + V] - Change to player camera
  * [Left click] - Clicks on object in the center of the screen (look for "Clickable objects" section)
  * [Right click] - Swap aiming with the weapon
  * [Mouse movement] - Look around the scene
  * 
  * Clickable objects:
  * Lamp - Turn on/off the point light and flame
  * Button - Resets all targets
  * Targets - Remove the target
  * 
  * Collisions:
  * Fence,
  * Bench,
  * Barrels,
  * Lamp
  * 
  */

#include <iostream>
#include "pgr.h"
#include "GameObject.h"
#include "Camera.h"
#include "CommonShaders.h"
#include "Callbacks.h"
#include "Globals.h"
#include "ServiceClass.h"

/**
 * \brief Entry point of the application.
 * \param argc number of command line arguments
 * \param argv array with argument strings
 * \return 0 if OK, <> elsewhere
 */
int main(int argc, char** argv) {
	// initialize the GLUT library (windowing system)
	glutInit(&argc, argv);

	glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// for each window
	{
		//   initial window size + title
		glutInitWindowSize(windowWidth, windowHeight);
		glutCreateWindow(WINDOW_TITLE);

		glutDisplayFunc(Callbacks::Display);
		glutReshapeFunc(Callbacks::Reshape);
		glutKeyboardFunc(Callbacks::Keyboard);
		glutKeyboardUpFunc(Callbacks::KeyboardUp);
		glutPassiveMotionFunc(Callbacks::PassiveMouseMotion);
		glutMouseFunc(Callbacks::Mouse);
		glutSpecialFunc(Callbacks::SpecialKeyboard);
		glutSpecialUpFunc(Callbacks::SpecialKeyboardUp);
		glutTimerFunc(FRAME_TIME, Callbacks::Timer, 0);

	}
	// end for each window 

	// initialize pgr-framework (GL, DevIl, etc.)
	if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
		pgr::dieWithError("pgr init failed, required OpenGL not supported?");
	
	// init app specific stuff - shaders & program, buffers, s, state of the application
	ServiceClass::InitApplication();

	// handle window close by the user
#ifndef __APPLE__
	glutCloseFunc(ServiceClass::FinalizeApplication);
#else
	glutWMCloseFunc(ServiceClass::FinalizeApplication);
#endif

	// Infinite loop handling the events
	glutMainLoop();

	// code after glutLeaveMainLoop()
	// cleanup

	return EXIT_SUCCESS;
}

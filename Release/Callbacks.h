#pragma once

#include <iostream>
#include "pgr.h"
#include "Globals.h"
#include "ServiceClass.h"

/**
 * \brief Class encapsulating all callbacks of OpenGL
 */
static class Callbacks
{
public:
	// -----------------------  Window ---------------------------------
	/**
	 * \brief Draw the window contents.
	 */
	static void Display();	

	/**
	 * \brief Window was reshaped.
	 * 
	 * \param newWidth New window width
	 * \param newHeight New window height
	 */
	static void Reshape(int newWidth, int newHeight);



	// -----------------------  Keyboard ---------------------------------
	/**
	 * \brief Handle the key pressed event.
	 * 
	 * Called whenever a key on the keyboard was pressed. The key is given by the "keyPressed"
	 * parameter, which is an ASCII character.
	 * 
	 * \param keyPressed ASCII code of the key
	 * \param mouseX mouse (cursor) X position
	 * \param mouseY mouse (cursor) Y position
	 */
	static void Keyboard(unsigned char keyPressed, int mouseX, int mouseY);

	/**
	 * \brief Handle the key released event.
	 * 
	 * \param keyReleased ASCII code of the released key
	 * \param mouseX mouse (cursor) X position
	 * \param mouseY mouse (cursor) Y position
	 */
	static void KeyboardUp(unsigned char keyReleased, int mouseX, int mouseY);

	/**
	 * \brief Handle the non-ASCII key pressed event (such as arrows or F1).
	 * 
	 *  The special keyboard callback is triggered when keyboard function (Fx) or directional
	 *  keys are pressed.
	 * 
	 * \param specKeyPressed int value of a predefined glut constant such as GLUT_KEY_UP
	 * \param mouseX mouse (cursor) X position
	 * \param mouseY mouse (cursor) Y position
	 */
	static void SpecialKeyboard(int specKeyPressed, int mouseX, int mouseY);

	/**
	 * \brief Handle the special key released event.
	 *
	 * \param keyReleased int value of a predefined glut constant such as GLUT_KEY_UP
	 * \param mouseX mouse (cursor) X position
	 * \param mouseY mouse (cursor) Y position
	 */
	static void SpecialKeyboardUp(int specKeyReleased, int mouseX, int mouseY);



	// -----------------------  Mouse ---------------------------------
	/**
	 * \brief React to mouse button press and release (mouse click).
	 * When the user presses and releases mouse buttons in the window, each press
	 * and each release generates a mouse callback (including release after dragging).
	 *
	 * \param buttonPressed button code (GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON)
	 * \param buttonState GLUT_DOWN when pressed, GLUT_UP when released
	 * \param mouseX mouse (cursor) X position
	 * \param mouseY mouse (cursor) Y position
	 */
	static void Mouse(int buttonPressed, int buttonState, int mouseX, int mouseY);

	/**
	 * \brief Handle mouse movement over the window (with no button pressed).
	 * 
	 * \param mouseX mouse (cursor) X position
	 * \param mouseY mouse (cursor) Y position
	 */
	static void PassiveMouseMotion(int mouseX, int mouseY);



	// -----------------------  Timer ---------------------------------
	/**
	 * \brief Function called every frame
	 * 
	 * \param timer
	 */
	static void Timer(int);
};


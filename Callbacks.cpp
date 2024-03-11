#include "Callbacks.h"

// -----------------------  Window ---------------------------------
void Callbacks::Display()
{
	glClearColor(fogColor.r, fogColor.g, fogColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// draw the window contents (scene objects)
	ServiceClass::DrawScene();

	glutSwapBuffers();
}

void Callbacks::Reshape(int newWidth, int newHeight)
{
	windowWidth = newWidth;
	windowHeight = newHeight;
	windowWidthHalf = windowWidth / 2;
	windowHeightHalf = windowHeight / 2;
	glViewport(0, 0, windowWidth, windowHeight);
	projection = glm::perspective(glm::radians(Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
}

// -----------------------  Keyboard ---------------------------------
void Callbacks::Keyboard(unsigned char keyPressed, int mouseX, int mouseY)
{
	if (isupper(keyPressed)) keyPressed = keyPressed + 32;
	if (keyPressed == 27)	// ESC
	{
		glutLeaveMainLoop();
		exit(EXIT_SUCCESS);
	}
	if (keysPressed.find(keyPressed) != keysPressed.end()) keysPressed[keyPressed] = true;
}

void Callbacks::KeyboardUp(unsigned char keyReleased, int mouseX, int mouseY)
{
	if (isupper(keyReleased)) keyReleased = keyReleased + 32;
	if (keysPressed.find(keyReleased) != keysPressed.end()) keysPressed[keyReleased] = false;
}

void Callbacks::SpecialKeyboard(int specKeyPressed, int mouseX, int mouseY)
{
	if (specialKeysPressed.find(specKeyPressed) != specialKeysPressed.end()) specialKeysPressed[specKeyPressed] = true;
}

void Callbacks::SpecialKeyboardUp(int specKeyReleased, int mouseX, int mouseY)
{
	if (specialKeysPressed.find(specKeyReleased) != specialKeysPressed.end()) specialKeysPressed[specKeyReleased] = false;
}

// -----------------------  Mouse ---------------------------------
void Callbacks::Mouse(int buttonPressed, int buttonState, int mouseX, int mouseY)
{
	if (activeCamera == 0)  // Actions only player camera
	{
		if (buttonState == GLUT_UP && buttonPressed == GLUT_RIGHT_BUTTON)
		{
			for (auto& object : objects)
			{
				if (object.Name == "Revolver")
				{
					for (auto& weapon : object.Instances)
					{
						if (weapon.Ui)
						{
							if (Zoom == ZoomedOut)  // Change FOV and weapon aim position
							{
								Zoom = ZoomedIn;
								weapon.Transform(glm::vec3(0.0f, -0.6f, 0.4f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.5f, 1.5f, 1.5f));
							}
							else
							{
								Zoom = ZoomedOut;
								weapon.Transform(glm::vec3(0.5f, -0.8f, 0.4f), glm::vec3(0.0f, 264.0f, 7.0f), glm::vec3(1.5f, 1.5f, 1.5f));
							}
						}
					}
				}
			}
			projection = glm::perspective(glm::radians(Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
		}
	}
	if (buttonState == GLUT_UP && buttonPressed == GLUT_LEFT_BUTTON)  // Checked events, that should occure on left click, like stencil test for object picking
	{
		unsigned char clickedId = 0;
		glReadPixels(mouseX, windowHeight - 1 - mouseY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &clickedId);
		printf("Clicked on object with an StencilId: %d\n", (int)clickedId);
		if ((int)clickedId == resetButtonId)  // button to restart targets
		{
			for (auto& it : objects[targetPosition].Instances) it.Draw = true;
		}
		if ((int)clickedId == lightButtonId)  // lamp in the middle, to turn on/off point light
		{
			lights[pointLightPos].Use = !lights[pointLightPos].Use;
			for (auto& it : objects[firePosition].Instances) it.Draw = !it.Draw;
		}
		if ((int)clickedId >= firstTargetId) objects[targetPosition].Instances[(int)(clickedId - firstTargetId)].Draw = false;
	}
}

void Callbacks::PassiveMouseMotion(int mouseX, int mouseY)
{
	if (activeCamera == 0)  // Rotate player camera
	{
		if (firstMouse)
		{
			deltaX = mouseX;
			deltaY = mouseY;
			firstMouse = false;
		}
		else
		{
			deltaX = mouseX - windowWidthHalf;
			deltaY = mouseY - windowHeightHalf;
			cameras[0].Yaw += cameras[0].SensitivityX * deltaX;
			cameras[0].Pitch -= cameras[0].SensitivityY * deltaY;
			cameras[0].Pitch = GlobFunc::Clamp(cameras[0].Pitch, -80.0f, 80.0f);
		}
		glutWarpPointer(windowWidthHalf, windowHeightHalf);
		glutPostRedisplay();
	}
}

// -----------------------  Timer ---------------------------------
void Callbacks::Timer(int)
{
	currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	const glm::mat4 sceneRootMatrix = glm::mat4(1.0f);

	// check user input
	ServiceClass::ProccessInput();
		
	// update active camera
	cameras[activeCamera].Front.x = cos(glm::radians(cameras[activeCamera].Yaw)) * cos(glm::radians(cameras[activeCamera].Pitch));
	cameras[activeCamera].Front.y = sin(glm::radians(cameras[activeCamera].Pitch));
	cameras[activeCamera].Front.z = sin(glm::radians(cameras[activeCamera].Yaw)) * cos(glm::radians(cameras[activeCamera].Pitch));
	cameras[activeCamera].Front = glm::normalize(cameras[activeCamera].Front);
	
	// update fog
	fogMultiplier = 0.8f + cos((float)currentFrame / 1000.0f)*0.3f;

	// update other objects
	ServiceClass::Update();

	// and plan a new event
	glutTimerFunc(FRAME_TIME, Callbacks::Timer, 0);

	// create display event
	glutPostRedisplay();
}


/**
 * \file    Globals.h : This file contains global variables
 */
#pragma once

#include "CommonShaders.h"
#include "Light.h"
#include "GameObject.h"
#include "Camera.h"
#include <map>

#ifndef GLOBALS_H
#define GLOBALS_H

extern const char WINDOW_TITLE[];
extern const int FRAME_TIME;  // Duration of one frame.

extern int windowWidth;
extern int windowHeight;
extern int windowWidthHalf;
extern int windowHeightHalf;
extern float currentFrame;
extern float sceneRadius;  // Walkable area

extern glm::vec3 fogColor;
extern float fogDensity;
extern bool useFog;
extern float fogMultiplier;  // Used to modify fog density by time

extern CommonShaders commonShaders;  // Object for shader program used for lighting scene
extern CommonShaders colorShaders;  // Object for shader program used for color only scene

extern std::vector<GameObject> objects;  // collection of all object types
extern std::vector<Camera> cameras;  // Collection of all cameras
extern int activeCamera;  // Current active camera
extern int dynamicCamera;  // Dynamic camera
extern int butterflyPosition; // Position of butterfly object in object vector
extern int skyboxPosition; // Position of skybox object in object vector
extern int targetPosition; // Position of target object in object vector
extern int firePosition; // Position of fire object in object vector

extern glm::mat4 projection;  // projection matrix (3D coords to 2D screen coords)

extern float deltaTime;  // Time between current frame and last frame
extern float lastFrame;  // Time of last frame

extern std::map<unsigned char, bool> keysPressed;  // map of pressed keys
extern std::map<int, bool> specialKeysPressed;  // map of pressed special keys
extern std::map<int, bool> mouseKeysPressed;  // map of pressed mouse keys

extern bool activeCollisions;  // Overall detection of collisions ("noclip")

extern unsigned char resetButtonId;  // stencil ID of button
extern unsigned char lightButtonId;  // stencil ID of lamp light
extern unsigned char firstTargetId;  // stencil ID of first clickable target (all higher stencil IDs are other targets)

//lights
extern std::vector<Light> lights;  // collection of all lights
extern int dirLightPos;  // position of direction light in "lights" vector
extern int pointLightPos;  // position of point light in "lights" vector
extern int spotLightPos;  // position of spot light in "lights" vector

extern float lastX;  // last mouse X position
extern float lastY;  // last mouse Y position
extern float deltaX;  // mouse shift in X axis
extern float deltaY;  // mouse shift in Y axis

extern bool firstMouse;  // Used to detect, if mouse was moved for the first time. Used for application initialziaton and when the mouse gets into view for the 1st time.

extern float Zoom;  // Current zoom option for FOV
extern float ZoomedIn;  // ZoomedIn value for FOV option
extern float ZoomedOut;  // ZoomedOut value for FOV option
#endif
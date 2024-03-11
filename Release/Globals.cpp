/**
 * \file    Globals.cpp : This file contains global variable definitons
 */
#include "Globals.h"

const char WINDOW_TITLE[] = "PGR: Strelnice (vancafra)";
const int FRAME_TIME = 33;

int windowWidth = 800;
int windowHeight = 800;
int windowWidthHalf = windowWidth / 2;
int windowHeightHalf = windowHeight / 2;
float currentFrame = 0.0f;
float sceneRadius = 9.5f;

glm::vec3 fogColor(0.9f);
float fogDensity = 0.05f;
bool useFog = false;
float fogMultiplier = 1.0f;

CommonShaders commonShaders;
CommonShaders colorShaders;

std::vector<GameObject> objects;
std::vector<Camera> cameras;
int activeCamera = 0;
int dynamicCamera = 0;
int butterflyPosition = 0;
int skyboxPosition = 0;
int targetPosition = 0;
int firePosition = 0;

glm::mat4 projection;

float deltaTime = 0.0f;  // Time between current frame and last frame
float lastFrame = 0.0f;  // Time of last frame

std::map<unsigned char, bool> keysPressed = 
{
    { 'w', false },  // Pohyb vpred
    { 's', false },  // Pohyb vzad
    { 'a', false },  // Pohyb vlevo
    { 'd', false },  // Pohyb vpravo

    { 'r', false },  // Znovunacteni sceny
    { 'v', false },  // Prepnuti kamery
    { 'm', false },  // Prepnuti mlhy
    { 'k', false },  // Prepnuti kolize
    { 'f', false },  // Baterka
};
std::map<int, bool> specialKeysPressed = 
{
    { GLUT_KEY_SHIFT_L, false },
    { GLUT_KEY_UP, false },
    { GLUT_KEY_DOWN, false },
    { GLUT_KEY_LEFT, false },
    { GLUT_KEY_RIGHT, false }
};
std::map<int, bool> mouseKeysPressed
{
    { GLUT_LEFT_BUTTON, false },
    { GLUT_RIGHT_BUTTON, false }
};

bool activeCollisions = true;

unsigned char resetButtonId = 1;
unsigned char lightButtonId = 2;
unsigned char firstTargetId = 3;

//lights
std::vector<Light> lights;
int dirLightPos = 0;
int pointLightPos = 0;
int spotLightPos = 0;

float lastX = 0.0f;
float lastY = 0.0f;
float deltaX = 0.0f;
float deltaY = 0.0f;

bool firstMouse = true;

float Zoom = 45.0f;
float ZoomedIn = 25.0f;
float ZoomedOut = Zoom;

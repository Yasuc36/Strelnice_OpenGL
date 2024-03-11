#pragma once

#include <fstream>
#include <string>
#include <sstream>

#include <iostream>
#include <cmath>
#include <random>
#include "pgr.h"
#include "Globals.h"
#include "GlobFunc.h"
#include "Butterfly.h"

/**
 * \brief Class to compute all necessary application operations, that are not class-specific. 
 */
static class ServiceClass
{
public:
	/**
	 * \brief Sets all needed shader locations at the start of the application for all shader programs.
	 */
	static void LoadShaderPrograms();

	/**
	 * \brief Deletes all shader programs at the end of the applicaton run.
	 */
	static void CleanupShaderPrograms(void);

	/**
	 * \brief Updates objects (once per Timer tick)
	 */
	static void Update();

	/**
	 * \brief Draw the scene. Called from Display callback
	 */
	static void DrawScene(void);

	/**
	 * \brief Called on application start. Sets up all necessary OpenGL stuff and others.
	 */
	static void InitApplication();

	/**
	 * \brief Called on application end. Cleans arrays, etc.
	 */
	static void FinalizeApplication(void);

	/**
	 * \brief Load and create all object models and sets their initial values.
	 */
	static void LoadModels();

	/**
	 * \brief Procces player input. Check key maps setted by callbacks.
	 */
	static void ProccessInput();

	/**
	 * \brief Tries to parse the loaded value from config file. (int)
	 * 
	 * \param inputParameters List of loaded values in string format
	 * \param variable Variable, that should take the new value from config file
	 * \param name Name of the variable to match the line of the Config file to specified variable
	 * \param defaultVal Default value, if parse fails
	 */
	static void ParseParameter(std::map<std::string, std::string>* inputParameters, int* variable, const std::string name, const int defaultVal);

	/**
	 * \brief Tries to parse the loaded value from config file. (float)
	 *
	 * \param inputParameters List of loaded values in string format
	 * \param variable Variable, that should take the new value from config file
	 * \param name Name of the variable to match the line of the Config file to specified variable
	 * \param defaultVal Default value, if parse fails
	 */
	static void ParseParameter(std::map<std::string, std::string>* inputParameters, float* variable, const std::string name, const float defaultVal);

	/**
	 * \brief Used for loading of config.ini file.
	*/
	static void LoadConfig();

	/**
	 * \brief Called, when game should be restartet to its default values (Does not resets everything, just mandatory stuff to save time and power).
	 */
	static void RestartApplication();
};


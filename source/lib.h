#pragma once

/**
 * @brief Contains the name of the project
 */
struct library {
  char const* name;
};

/**
 * @brief Creates an instance of library with the name of the project
 */
struct library create_library(void);

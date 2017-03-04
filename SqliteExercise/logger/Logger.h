/*
 * Logger.h
 *
 * Updated on: December 6, 2016
 *     Author:
 */

#pragma once

#include "LogWritter.h"

/*
 * TIPS: Truncate only the file name (not the full path) from __FILE__
 *
 * Solution-1: Define a new variable using "strrchr()":
 * #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
 *
 * Solution-2: Within CMake:
 * set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")
 *
 * Of course later on you should use __FILENAME__ instead of __FILE__
 */


/* LOG LEVEL:
 *
 * INFO
 * DEBUG
 * WARN
 * ERROR
 *
 */

#ifndef __FILENAME__
#define __FILENAME__ __FILE__
#endif

/* PRINT IN CONSOLE */
#ifdef NODEBUG
#define logInfo()
#define logDebug()
#define logWarn()
#define logError()
#else
#define logInfo()   LOG_CONSOLE("INFO",  __FILENAME__, __LINE__, __FUNCTION__)
#define logDebug()  LOG_CONSOLE("DEBUG", __FILENAME__, __LINE__, __FUNCTION__)
#define logWarn()   LOG_CONSOLE("WARN",  __FILENAME__, __LINE__, __FUNCTION__)
#define logError()  LOG_CONSOLE("ERROR", __FILENAME__, __LINE__, __FUNCTION__)
#endif

#ifdef NODEBUG
#define LOG_CONSOLE(type, fileName, line, prettyFunction)
#else
#define LOG_CONSOLE(type, fileName, line, prettyFunction)       \
        ConsoleLogger(type, fileName, line, prettyFunction)
#endif

/* PRINT IN LOG FILE */
#ifdef NODEBUG
#define flogInfo()
#define flogDebug()
#define flogWarn()
#define flogError()
#else
#define flogInfo()   LOG_FILE("INFO",  __FILENAME__, __LINE__, __FUNCTION__)
#define flogDebug()  LOG_FILE("DEBUG", __FILENAME__, __LINE__, __FUNCTION__)
#define flogWarn()   LOG_FILE("WARN",  __FILENAME__, __LINE__, __FUNCTION__)
#define flogError()  LOG_FILE("ERROR", __FILENAME__, __LINE__, __FUNCTION__)
#endif

#ifdef NODEBUG
#define LOG_FILE(type, fileName, line, prettyFunction)
#else
#define LOG_FILE(type, fileName, line, prettyFunction)      \
        FileLogger(type, fileName, line, prettyFunction)
#endif

/**
 * @file constants.h
 * @brief Constants used in the library
 * @author Stuart Mathews
 * @date 10 January 2014
 *
 * This header contains constants
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page constants Constants in the library
The constants we use are here
*/
#ifndef LIBSTU_COMMON_H
#define LIBSTU_COMMON_H

#if HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef _WIN32
#  ifdef DLL_EXPORT
#    define LIBRARY_API	__declspec(dllexport)
#  else
#    ifdef LIBSTU_DLL_IMPORT
#      define LIBRARY_API	extern __declspec(dllimport)
#    endif
#  endif
#endif

#ifndef LIBRARY_API
# define LIBRARY_API	extern
#endif


#define true 1
#define TRUE true
#define false 0
#define FALSE false

#define null NULL

#define yes 1
#define YES yes
#define no 0
#define NO no

/** \brief Represents the size of an integer on the platform
 *
 * \param int
 * \return #define SIZEOFINT
 *
 */
#define SIZEOFINT sizeof(int)
/** \brief Represents the size of a pointer to an integer on the platform
 *
 * \param int*
 * \return #define SIZEOFPINT
 *
 */
#define SIZEOFPINT sieof(int*)
/** \brief Represents the size of a single character on the platform
 *
 * \param char
 * \return #define SIZEOFCHAR
 *
 */
#define SIZEOFCHAR sizeof(char)
/** \brief Represents the size of a pointer to a character on the platform
 *
 * \param char*
 * \return #define SIZEOFPCHAR
 *
 */
#define SIZEOFPCHAR sizeof(char*)
/** \brief Represents the size of a float on the platform
 *
 * \param float
 * \return #define SIZEOFFLOAT
 *
 */
#define SIZEOFFLOAT sizeof(float)
/** \brief Represents the size of a float on the platform
 *
 * \param float*
 * \return #define SIZEOFPFLOAT
 *
 */
#define SIZEOFPFLOAT sizeof(float*)
/** \brief Represents the size of a pointer to a float on the platform
 *
 * \param double
 * \return #define SIZEOFDOUBLE
 *
 */
#define SIZEOFDOUBLE sizeof(double)
/** \brief Represents the size of a pointer to a double on the platform
 *
 * \param double*
 * \return #define SIZEOFPDOUBLE
 *
 */
#define SIZEOFPDOUBLE sizeof(double*)
/** \brief Represents the size of a short on the platform
 *
 * \param short
 * \return #define SIZEOFSHORT
 *
 */
#define SIZEOFSHORT sizeof(short)
/** \brief Represents the size of a pointer to a short on the platform
 *
 * \param short*
 * \return #define SIZEOFPSHORT
 *
 */
#define SIZEOFPSHORT sizeof(short*)

#endif // LIBSTU_COMMON_H

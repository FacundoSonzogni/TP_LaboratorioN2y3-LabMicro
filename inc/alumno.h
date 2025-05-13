/*********************************************************************************************************************
Copyright (c) 2025, Facundo Sonzogni <facundosonzogni1@gmail.com>
Copyright (c) 2025, Laboratorio de Microprocesadores, Universidad Nacional de Tucumán

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

#ifndef ALUMNO_H
#define ALUMNO_H

/** @file alumno.h
 ** @brief Declaraciones del Módulo alumno
 **
 ** @addtogroup Alumno Modulo de Gestion de Alumnos
 ** @{
 **/

/* === Headers files inclusions ==================================================================================== */

#include <stdint.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

//! Estructura que representa a un alumno
typedef struct alumno_s * alumno_t;

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función que permite crear un alumno
 * 
 * @param nombre Nombre del alumno
 * @param apellido Apellido del alumno
 * @param documento Documento del alumno
 * @return alumno_t Puntero a la estructura con los datos del alumno
 */
alumno_t CrearAlumno(char nombre[], char apellido[], int documento);

/**
 * @brief Función que permite serializar los datos de un alumno en formato JSON
 *
 * @param alumno Puntero a la estructura que contiene los datos del alumno
 * @param buffer Cadena de caracteres en la que se almacenan los datos en formato JSON
 * @param size Espacio disponible para la cadena de caracteres
 * @return int Longitud de la cadena generada, o -1 si el espacio no es suficiente
 */
int SerializarAlumno(alumno_t alumno, char buffer[], uint32_t size);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif
//! @}

#endif /* ALUMNO_H */
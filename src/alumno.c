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

/** @file alumno.c
 ** @brief Código fuente del Módulo alumno
 **/

/* === Headers files inclusions ==================================================================================== */

#include "alumno.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/**
 * @brief Devuelve una cadena en formato JSON del tipo "campo":"valor", (con la Coma al final)
 *
 * @param campo Cadena de caracteres que se quiere colocar como nombre del campo
 * @param valor Cadena que representa el valor del campo que se desea colocar
 * @param buffer Cadena en la cual se escribe el resultado de la serialización
 * @param size Tamaño disponible para escribir la cadena
 * @return int Longitud de la cadena generada, o -1 si el espacio no es suficiente
 */
static int SerializarCadena(char campo[], const char valor[], char buffer[], uint32_t size);

/**
 * @brief Devuelve una cadena en formato JSON del tipo "campo":valor
 *
 * @param campo Cadena de caracteres que se quiere colocar como nombre del campo
 * @param valor Entero que se desea colocar como valor para el campo
 * @param buffer Cadena en la cual se escribe el resultado de la serialización
 * @param size Tamaño disponible para escribir la cadena
 * @return int Longitud de la cadena generada, o -1 si el espacio no es suficiente
 */
static int SerializarEntero(char campo[], int valor, char buffer[], uint32_t size);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static int SerializarCadena(char campo[], const char valor[], char buffer[], uint32_t size) {
    return snprintf(buffer, size, "\"%s\":\"%s\",", campo, valor);
}

static int SerializarEntero(char campo[], int valor, char buffer[], uint32_t size) {
    return snprintf(buffer, size, "\"%s\":%i", campo, valor);
}

/* === Public function definitions ================================================================================= */

int Serializar(const alumno_t* alumno, char buffer[], uint32_t size) {
    int escritos;
    int resultado;

    buffer[0] = '{';
    buffer = buffer + 1;
    escritos = 1;

    resultado = SerializarCadena("nombre", alumno->nombre, buffer, size - escritos);
    if (resultado < 0) {
        return -1;
    }

    buffer = buffer + resultado;
    escritos = escritos + resultado;
    resultado = escritos;

    escritos = escritos + SerializarCadena("apellido", alumno->apellido, buffer, size - escritos);
    if (escritos < 0) {
        return -1;
    }

    buffer = buffer + (escritos - resultado);
    resultado = escritos;

    escritos = escritos + SerializarEntero("documento", alumno->documento, buffer, size - escritos);
    if (escritos < 0) {
        return -1;
    }

    buffer = buffer + (escritos - resultado);

    if (escritos >= (size - 1)) {
        return -1;
    } else {
        *buffer = '}';
        buffer++;
        *buffer = '\0';

        escritos = escritos + 2;
    }

    return escritos;
}

/* === End of documentation ======================================================================================== */
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
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

//! Estructura con los datos del Alumno
struct alumno_s{
    char nombre[20];     //!< Nombre del alumno
    char apellido[20];   //!< Apellido del alumno
    int documento;       //!< Documento del alumno
#ifdef USAR_MEMORIA_ESTATICA
    bool ocupado;        //!< Indica si una instancia está ocupada (solo para Memoria Estática)
#endif
};

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
static int SerializarCadena(char campo[], char valor[], char buffer[], uint32_t size);

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

#ifdef USAR_MEMORIA_ESTATICA
/**
 * @brief Crea un alumno y lo guarda dentro del arrego de alumnos (si se quiere usar memoria estática)
 * 
 * @return alumno_t Puntero a la estructura con los datos del alumno creado o NULL si no hay espacio
 */
static alumno_t CrearAlumnoEstatico();
#endif

/* === Private variable definitions ================================================================================ */

#ifdef USAR_MEMORIA_ESTATICA
//! Arreglo de alumnos para cuando se usa Memoria Estática
static struct alumno_s arreglo_alumnos[MAX_CANT_ALUMNOS] = {0}; //! Inicialmente, todo en 0. Si se crea el i-ésimo alumno, los campos de arreglo_alumnos[i] NO serán 0
#endif

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static int SerializarCadena(char campo[], char valor[], char buffer[], uint32_t size) {
    return snprintf(buffer, size, "\"%s\":\"%s\",", campo, valor);
}

static int SerializarEntero(char campo[], int valor, char buffer[], uint32_t size) {
    return snprintf(buffer, size, "\"%s\":%i", campo, valor);
}

#ifdef USAR_MEMORIA_ESTATICA
static alumno_t CrearAlumnoEstatico(){
    alumno_t self = NULL;
    int i;

    for(i = 0; i < MAX_CANT_ALUMNOS; i++){
        if(arreglo_alumnos[i].ocupado == false){
            arreglo_alumnos[i].ocupado = true;
            self = &arreglo_alumnos[i];
            break;
        }
    }

    return self;
}
#endif

/* === Public function definitions ================================================================================= */

alumno_t CrearAlumno(char nombre[], char apellido[], int documento){

    #ifdef USAR_MEMORIA_ESTATICA
        alumno_t self = CrearAlumnoEstatico();
    #else
        alumno_t self = malloc(sizeof(struct alumno_s));
    #endif

    if(self != NULL){
        strncpy(self->nombre, nombre, sizeof(self->nombre)-1);
        strncpy(self->apellido, apellido, sizeof(self->apellido)-1);
        self->documento = documento;
    }

    return self;
}

int SerializarAlumno(alumno_t alumno, char buffer[], uint32_t size) {
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

    if ((uint32_t)escritos >= (size - 1)) { // Si se ejecuta esta linea es porque "escritos" es un numero POSITIVO
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
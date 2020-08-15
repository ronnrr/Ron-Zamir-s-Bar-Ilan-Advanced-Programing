#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    // DON'T CHANGE THIS VALUE!
    ERROR_SUCCESS = 0,
    MEMORY_ALLC_ERROR = 1,
    FAILED_HEIGHT_ERROR = 2,
    FAILED_WIDTH_ERROR = 3,
    NON_EXISTANT_MATRIX_ERROR = 4,
    NULL_POINTER_ERROR = 5,
    OUT_OF_BOUNDS_ERROR = 6,
    INAPROPRIATE_MATRIX_DIMENSIONS_FOR_ADDING_ERROR = 7,
    INAPROPRIATE_MATRIX_DIMENSIONS_FOR_MULTIPLICATION_ERROR = 8,
} ErrorCode;

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code);

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char* error_getErrorMessage(ErrorCode code);
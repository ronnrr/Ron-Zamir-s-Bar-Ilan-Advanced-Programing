#include "ErrorCode.h"
/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code) {
    if (code == ERROR_SUCCESS) {
        return true;
    }
    return false;
}

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char* error_getErrorMessage(ErrorCode code) {
    if (code == MEMORY_ALLC_ERROR) {
        return "Memory allocation failed.";
    }
    if (code == FAILED_HEIGHT_ERROR) {
        return "Given height is inapropriate and unsupported.";
    }
    if (code == FAILED_WIDTH_ERROR) {
        return "Given width is inapropriate and unsupported.";
    }
    if (code == NON_EXISTANT_MATRIX_ERROR) {
        return "Matrix sent to function either is not allocated properly or just doesn't exist.";
    }
    if (code == NULL_POINTER_ERROR) {
        return "Pointer given to function was a null pointer, and therefore the function was unable to proceed";
    }
    if (code == OUT_OF_BOUNDS_ERROR) {
        return "Index accessed was out of bounds. Please try to enter a valid index set.";
    }
    return nullptr;
}
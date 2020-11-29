#include "Matrix.h"
#include <stdlib.h>

typedef struct Matrix {
    uint32_t height;
    uint32_t width;
    double* values;
}Matrix;

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    if (matrix == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    *matrix = (PMatrix)(malloc)(1 * sizeof(Matrix));
    if (matrix == NULL) {
        return MEMORY_ALLC_ERROR;
    }
    (*matrix)->height = height;
    (*matrix)->width = width;
    (*matrix)->values = (double*)(calloc)(height * width, sizeof(double));
    return ERROR_SUCCESS;
}

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    if (result == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (source == NULL) {
        return NULL_POINTER_ERROR;
    }
    if ((source)->height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if ((source)->width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    else if ((*source).values == NULL) {
        return NULL_POINTER_ERROR;
    }
    *result = (PMatrix)(malloc)(1 * sizeof(Matrix));
    if (result == NULL) {
        return MEMORY_ALLC_ERROR;
    }
    (*result)->height = (source)->height;
    (*result)->width = (source)->width;
    (*result)->values = (double*)malloc(source->height * source->width * sizeof(double));
    if ((*result)->values == NULL) {
        return MEMORY_ALLC_ERROR;
    }
    for (uint32_t i = 0; i < source->height * source->width; ++i) {
        (*result)->values[i] = source->values[i];
    }
    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {
    if (matrix == NULL) {
        return;
    }
    free(matrix->values);
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    if (result == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (matrix == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (matrix->height < 1) {
        *result = matrix->height;
        return FAILED_HEIGHT_ERROR;
    }
    *result = matrix->height;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
    if (result == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (matrix == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (matrix->width < 1) {
        *result = matrix->width;
        return FAILED_WIDTH_ERROR;
    }
    *result = matrix->width;
    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
    double value) {
    if (matrix == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (matrix->height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (matrix->width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    else if (rowIndex >= matrix->height) {
        return OUT_OF_BOUNDS_ERROR;
    }
    else if (colIndex >= matrix->width) {
        return OUT_OF_BOUNDS_ERROR;
    }
    else if (matrix->values == NULL) {
        return NULL_POINTER_ERROR;
    }
    matrix->values[rowIndex * matrix->width + colIndex] = value;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
    double* value) {
    if (matrix == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (value == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (matrix->height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (matrix->width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    else if (rowIndex >= matrix->height) {
        return OUT_OF_BOUNDS_ERROR;
    }
    else if (colIndex >= matrix->width) {
        return OUT_OF_BOUNDS_ERROR;
    }
    else if (matrix->values == NULL) {
        return NULL_POINTER_ERROR;
    }
    *value = matrix->values[rowIndex * matrix->width + colIndex];
    return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    ErrorCode errorChecker = matrix_validityCheck(result, lhs, rhs);
    if (errorChecker != ERROR_SUCCESS) {
        return errorChecker;
    }
    else if (rhs->width != lhs->width || rhs->height != lhs->height) {
        return INAPROPRIATE_MATRIX_DIMENSIONS_FOR_ADDING_ERROR;
    }
    else if (lhs->values == NULL || rhs->values == NULL) {
        return NULL_POINTER_ERROR;
    }
    *result = (PMatrix)(malloc)(1 * sizeof(Matrix));
    if (result == NULL) {
        return MEMORY_ALLC_ERROR;
    }
    (*result)->height = lhs->height;
    (*result)->width = lhs->width;
    (*result)->values = (double*)(malloc)((*result)->height * (*result)->width * sizeof(double));
    if ((*result)->values == NULL) {
        return MEMORY_ALLC_ERROR;
    }
    for (uint32_t i = 0; i < (*result)->height * (*result)->width; ++i) {
        (*result)->values[i] = lhs->values[i] + rhs->values[i];
    }
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    ErrorCode errorChecker = matrix_validityCheck(result, lhs, rhs);
    if (errorChecker != ERROR_SUCCESS) {
        return errorChecker;
    }
    else if (lhs->width != rhs->height) {
        return INAPROPRIATE_MATRIX_DIMENSIONS_FOR_MULTIPLICATION_ERROR;
    }
    else if (lhs->values == NULL || rhs->values == NULL) {
        return NULL_POINTER_ERROR;
    }
    *result = (PMatrix)(malloc)(1 * sizeof(Matrix));
    if (result == NULL) {
        return MEMORY_ALLC_ERROR;
    }
    (*result)->height = lhs->height;
    (*result)->width = rhs->width;
    (*result)->values = (double*)(malloc)((*result)->height * (*result)->width * sizeof(double));
    if ((*result)->values == NULL) {
        return MEMORY_ALLC_ERROR;
    }
    for (uint32_t i = 0; i < (*result)->height * (*result)->width; ++i) {
        (*result)->values[i] = 0;
    }
    for (uint32_t i = 0; i < (*result)->height; ++i) {
        for (uint32_t j = 0; j < (*result)->width; ++j) {
            for (uint32_t k = 0; k < lhs->width; ++k) {
                (*result)->values[i * (*result)->width + j] += lhs->values[i * (*result)->width + k] + rhs->values[k * (*result)->width + j];
            }
        }
    }
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {
    if (matrix == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (matrix->height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (matrix->width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    else if (matrix->values == NULL) {
        return NULL_POINTER_ERROR;
    }
    for (uint32_t i = 0; i < matrix->height * matrix->width; ++i) {
        matrix->values[i] *= scalar;
    }
    return ERROR_SUCCESS;
}

ErrorCode matrix_validityCheck(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    if (result == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (lhs == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (rhs == NULL) {
        return NULL_POINTER_ERROR;
    }
    else if (lhs->height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (lhs->width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    else if (rhs->height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (rhs->width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    return ERROR_SUCCESS;
}
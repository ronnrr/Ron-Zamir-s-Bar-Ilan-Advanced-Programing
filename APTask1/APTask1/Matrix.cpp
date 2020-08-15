#include "Matrix.h"
/**
 * @brief Creates a new matrix of a given height an width,
 *  all values are initially zeroes.
 *
 * @param[out] matrix The address of a matrix pointer to receive
 *  the address of the created matrix.
 * @param[in] height Height of the matrix
 * @param[in] width Width of the matrix
 * @return ErrorCode
 */
ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    int i = 0;
    if (matrix == nullptr) {
        return NULL_POINTER_ERROR;
    }
    if (height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    matrix = (PMatrix*)(malloc)(1 * sizeof(PMatrix));
    if (matrix == nullptr) {
        return MEMORY_ALLC_ERROR;
    }
    matrix->height = height;
    matrix->width = width;
    matrix->values = (float**)(calloc)(height, sizeof(float*));
    if (matrix->values == nullptr) {
        return MEMORY_ALLC_ERROR;
    }
    for (i = 0; i < height; i++) {
        matrix->values[i] = (float*)(calloc)(width, sizeof(float));
        if (matrix->values[i] == nullptr) {
            return MEMORY_ALLC_ERROR;
        }
    }
    return ERROR_SUCCESS;
}

/**
 * @brief Creates a new matrix from an old matrix.
 *
 * @param[out] matrix The address of a matrix pointer to receive
 *  the address of the copied matrix.
 * @param[in] source The matrix to copy.
 * @return ErrorCode
 */
ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    int i = 0;
    int j = 0;
    if (result == nullptr) {
        return NULL_POINTER_ERROR;
    }
    if (source.height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (source.width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    result = (PMatrix*)(malloc)(1 * sizeof(PMatrix));
    if (result == nullptr) {
        return MEMORY_ALLC_ERROR;
    }
    result->height = source.height;
    result->width = source.width;
    result->values = (float**)(malloc)(source.height * sizeof(float*));
    if (result->values == nullptr) {
        return MEMORY_ALLC_ERROR;
    }
    for (i = 0; i < source.height; i++) {
        result->values[i] = (float*)(malloc)(source.width * sizeof(float));
        if (result->values[i] == nullptr) {
            return MEMORY_ALLC_ERROR;
        }
    }
    for (i = 0; i < source.height; i++) {
        for (j = 0; j < source.width; j++) {
            result->values[i][j] = source.values[i][j];
        }
    }
    return ERROR_SUCCESS;
}

/**
 * @brief Destroys a matrix.
 *
 * @param matrix the matrix to destroy.
 */
void matrix_destroy(PMatrix matrix) {
    int i = 0;
    for (i = 0; i < matrix.height; i++) {
        free(matrix.values[i]);
    }
    free(matrix.values);
}

/**
 * @brief Returns the height of a give matrix.
 *
 * @param[in] matrix The matrix.
 * @param[out] result On output, contains the height of the matrix.
 * @return ErrorCode
 */
ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    if (result == nullptr) {
        return NULL_POINTER_ERROR;
    }
    if (matrix.height < 1) {
        *result = matrix.height;
        return FAILED_HEIGHT_ERROR;
    }
    *result = matrix.height;
    return ERROR_SUCCESS;
}

/**
 * @brief Returns the width of a give matrix.
 *
 * @param[in] matrix The matrix.
 * @param[out] result On output, contains the height of the matrix.
 * @return ErrorCode
 */
ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
    if (result == nullptr) {
        return NULL_POINTER_ERROR;
    }
    if (matrix.width < 1) {
        *result = matrix.width;
        return FAILED_WIDTH_ERROR;
    }
    *result = matrix.width;
    return ERROR_SUCCESS;
}

/**
 * @brief Sets a value to the matrix.
 *
 * @param[in, out] matrix The matrix to operate on.
 * @param[in] rowIndex Row index of the value to set.
 * @param[in] colIndex Column index of the value to setF.
 * @param[in] value Value to set.
 * @return ErrorCode
 */
ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
    double value) {
    if (matrix.height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (matrix.width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    else if (rowIndex >= matrix.height) {
        return OUT_OF_BOUNDS_ERROR;
    }
    else if (colIndex >= matrix.width) {
        return OUT_OF_BOUNDS_ERROR;
    }
    matrix.values[rowIndex][colIndex] = value;
    return ERROR_SUCCESS;
}

/**
 * @brief Sets a value to the matrix.
 *
 * @param[in] matrix The matrix to operate on.
 * @param[in] rowIndex Row index of the value to get.
 * @param[in] colIndex Column index of the value to get.
 * @param[out] value The address of a double variable to receive
 *  the value from the matrix.
 * @return ErrorCode
 */
ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
    double* value) {
    if (matrix.height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (matrix.width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    else if (rowIndex >= matrix.height) {
        return OUT_OF_BOUNDS_ERROR;
    }
    else if (colIndex >= matrix.width) {
        return OUT_OF_BOUNDS_ERROR;
    }
    *value = matrix.values[rowIndex][colIndex];
    return ERROR_SUCCESS;
}

/**
 * @brief Computes the addition of two matrices.
 *
 * @param[out] result The address of a matrix pointer to receive
 *  the address of the resulting matrix.
 * @param[in] lhs The left hand side of the addition operation.
 * @param[in] rhs The right hand side of the addition operation.
 * @return ErrorCode
 */
ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    int i = 0;
    int j = 0;
    if (result == nullptr) {
        return NULL_POINTER_ERROR;
    }
    else if (lhs.height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (lhs.width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    else if (rhs.height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (rhs.width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    else if (rhs.width != lhs.width || rhs.height != lhs.height) {
        return INAPROPRIATE_MATRIX_DIMENSIONS_FOR_ADDING_ERROR;
    }
    result = (PMatrix*)(malloc)(1 * sizeof(PMatrix));
    if (result == nullptr) {
        return MEMORY_ALLC_ERROR;
    }
    result->height = lhs.height;
    result->width = lhs.width;
    result->values = (float**)(malloc)(result->height * sizeof(float*));
    if (result->values == nullptr) {
        return MEMORY_ALLC_ERROR;
    }
    for (i = 0; i < result->height; i++) {
        result->values[i] = (float*)(malloc)(result->width * sizeof(float));
    }
    for (i = 0; i < result->height; i++) {
        for (j = 0; j < result->width; j++) {
            result->values[i][j] = rhs.values[i][j] + lhs.values[i][j];
        }
    }
    return ERROR_SUCCESS;
}

/**
 * @brief Computes the multiplication of two matrices.
 *
 * @param[out] result The address of a matrix pointer to receive
 *  the address of the resulting matrix.
 * @param[in] lhs The left hand side of the multiplication operation.
 * @param[in] rhs The right hand side of the multiplication operation.
 * @return ErrorCode
 */
ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    int i = 0;
    int j = 0;
    int k = 0;
    if (result == nullptr) {
        return NULL_POINTER_ERROR;
    }
    else if (lhs.height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (lhs.width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    else if (rhs.height < 1) {
        return FAILED_HEIGHT_ERROR;
    }
    else if (rhs.width < 1) {
        return FAILED_WIDTH_ERROR;
    }
    else if (lhs.width != rhs.height) {
        return INAPROPRIATE_MATRIX_DIMENSIONS_FOR_MULTIPLICATION_ERROR;
    }
    result = (PMatrix*)(malloc)(1 * sizeof(PMatrix));
    if (result == nullptr) {
        return MEMORY_ALLC_ERROR;
    }
    result->height = lhs.height;
    result->width = rhs.width;
    result->values = (float**)(malloc)(result->height * sizeof(float*));
    if (result->values == nullptr) {
        return MEMORY_ALLC_ERROR;
    }
    for (i = 0; i < result->height; i++) {
        result->values[i] = (float*)(malloc)(result->width * sizeof(float));
        if (result->values[i] == nullptr) {
            return MEMORY_ALLC_ERROR;
        }
    }
    for (i = 0; i < result->height; i++) {
        for (j = 0; j < result->width; j++) {
            result->values[i][j] = 0;
        }
    }
    for (i = 0; i < result->height; i++) {
        for (j = 0; j < result->width; j++) {
            for (k = 0; k < lhs.width; k++) {
                result->values[i][j] += lhs.values[i][k] + rhs.values[k][j];
            }
        }
    }
    return ERROR_SUCCESS;
}

/**
 * @brief Multiplies a matrix with a scalar and stores the result in
 *  the given matrix.
 *
 * @param[in, out] matrix On input, the matrix to multiply with a scalar.
 *  On output, the result of the multiplication operation.
 * @param[in] scalar The scalar to multiply with.
 * @return ErrorCode
 */
ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {

}
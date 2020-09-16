#include "ErrorCode.h"

const bool error_isSuccess(const ErrorCode code) {
    return code == ERROR_SUCCESS;
}

const char* error_getErrorMessage(const ErrorCode code) {
    if (error_isSuccess(code)) {
        return NULL;
    }
    return "An error has occured.";
}
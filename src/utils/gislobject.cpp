/*!
 * @file GIsLObject.cpp.cc
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief
 * @details 
 * @verbatim
 *
 */

#include "gislobject.h"

namespace GisL {
    bool GisLObject::hasError( ) {
        return mError == MError::NoError;
    }

    std::string GisLObject::errorMessage( ) {
        return mErrorMessage;
    }

    GisLObject::GisLObject( ) {
        mError = MError::NoError;
    }

    GisLObject::~GisLObject( ) = default;
}
/*!
 * @author tau 
 * @date 12/20/20
*/

#ifndef GISL_VECTORLAYER_H
#define GISL_VECTORLAYER_H

#include <string>
#include <vector>
#include <gdal/ogrsf_frmts.h>

#include "spatialreference.h"
#include "../utils/merror.h"
#include "vectorfeature.h"

namespace GisL {
    class VectorLayer {
    public:

        static void seed(int fidInVector);

        explicit VectorLayer(OGRLayer &poLayer);

        VectorLayer &operator=(const VectorLayer &rhs);

        SpatialReference *pmCrs;
        int featureCount;

        bool hasError();

        std::string errorMessage();


        ~VectorLayer();

    private:
        static int fidInLayer;
        int fid;

        MError::GisLError mError;
        std::string mErrorMessage;

        OGRLayer *pmLayer;
        OGREnvelope *pmExtent;

        VectorFeature **pmFeature;

        void getExtent();
    };
}


#endif //GISL_VECTORLAYER_H

/*!
 * @file plottest.cpp
 * @author omega 
 * @date 22/12/2020
 * 
 * @brief test paint
 * @details 
 * @verbatim
 *
 */

#include <string>
#include "../src/gui/sld.h"

int main(int argc, char *argv[]) {
    std::string sldFilename = "../resource/practise_6/qu-style.sld";
    GisL::Sld *sld = new GisL::Sld( sldFilename );
//    sld->loadSldFile(sldFilename);

    printf("%s", sldFilename.c_str());


    return 1;
}


#ifndef RESULTSTRUCT_H
#define RESULTSTRUCT_H

#include "Variant.h"
#include "VariantRectangle.h"
#include <map>

namespace FPA {

struct ResultStruct
{
    unsigned bestWidth = -1;
    unsigned bestHeight = -1;
    std::map<Type*, Variant*> bestCombination;
    std::map<Type*, VariantRectangle*> bestPlacement;
    long long time_microsec = -1;
};

} //namespace FPA

#endif // RESULTSTRUCT_H
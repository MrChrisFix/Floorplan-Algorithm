#ifndef RESULTSTRUCT_H
#define RESULTSTRUCT_H

#include "Variant.h"
#include "VariantRectangle.h"
#include <map>

namespace FPA {

/**
 * Struct for informations about the result of the optimization
*/
struct ResultStruct
{
    unsigned bestWidth = -1;                            /// The best fund width
    unsigned bestHeight = -1;                           /// The best found height
    std::map<Type*, Variant*> bestCombination;          /// The best combination of variants
    std::map<Type*, VariantRectangle*> bestPlacement;   /// The placement of rectangles based on the best combination
    long long time_microsec = -1;                       /// Time the algorithm needed for the optimization

    /**
     * Desctructor
    */
    ~ResultStruct()
    {
        for (auto& el : bestPlacement)
        {
            delete el.second;
            el.second = nullptr;
        }
        bestPlacement.clear();
        bestCombination.clear();
    }
};

} //namespace FPA

#endif // RESULTSTRUCT_H
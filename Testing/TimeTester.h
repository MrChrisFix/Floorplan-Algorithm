#pragma once
#include <vector>
#include "../Algorithm/Type.h"

class TimeTester
{
private:

	void saveCSV(std::vector<std::pair<int, long long>> times, bool multipleTypes, int constAmount);

public:
	//TimeTester();
	//~TimeTester();

	void MultipleTypesConstVaraint(int typesMin, int typesMax, int variantsAmount);

	void ConstTypesMultipleVariants(int typesAmount, int variantsMin, int variantsMax);

	std::vector<FPA::Type*> TypeVectorCreator(int typesAmount, int variantsAmount, bool withRequirements);

};


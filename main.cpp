#include "XMLFileManager.h"
#include <iostream>
#include "AlgorithmManager.h"

int main()
{
	XMLFileManager A;

	auto type = A.ReadFromXML("templateXML.xml");

	AlgorithmManager B;

	B.setTypes(type);
	auto value = B.StartCalculations();
	std::cout << value.first;

	/*for (auto t : type)
	{
		std::cout << "Name of type:" << t->GetName() << std::endl;
		std::cout << "Number of Variants:" << t->GetVariants().size() << std::endl;
	}*/
	return 0;
}
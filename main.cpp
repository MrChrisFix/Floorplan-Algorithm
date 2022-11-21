#include "XMLFileManager.h"
#include <iostream>
#include "AlgorithmManager.h"

int main()
{
	XMLFileManager A;

	auto type = A.ReadFromXML("templateXML2.xml");

	AlgorithmManager B;

	B.setTypes(type);
	auto value = B.StartCalculations();
	std::cout << value.first;

	return 0;
}
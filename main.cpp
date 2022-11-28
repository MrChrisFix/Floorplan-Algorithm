#include "XMLFileManager.h"
#include <iostream>
#include "AlgorithmManager.h"

int main()
{
	XMLFileManager A;

	//XML - square
	//XML2 - a more complex diagram
	//XML3 - uncomplete connections

	auto type = A.ReadFromXML("templateXML3.xml");

	AlgorithmManager B;

	B.setTypes(type);
	auto value = B.StartCalculations();
	std::cout << value.first;

	return 0;
}
#include "XMLFileManager.h"
#include <iostream>
#include "AlgorithmManager.h"

int main()
{
	XMLFileManager A;

	//XML - square
	//XML2 - a more complex diagram
	//XML3 - uncomplete connections

	std::vector<Type*> type;
	try
	{
		type = A.ReadFromXML("templateXML.xml");
		//A.SaveToXML(type, "test.xml");
	}
	catch (const char* message)
	{
		std::cout << message << std::endl;
		return -2;
	}
	catch (...)
	{
		std::cout << "Something went wrong!" << std::endl;
		return -2;
	}

	AlgorithmManager B;

	B.setTypes(type);
	auto value = B.StartCalculations();
	std::cout << value.first;
	return 0;
}
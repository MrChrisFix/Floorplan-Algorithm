#include <iostream>
#include "Algorithm/AlgorithmManager.h"
#include "XML_Management/XMLFileManager.h"

#include "Testing/TimeTester.h"

int main()
{
	TimeTester tester;
	for(int i=1; i< 5; i++)
		tester.ConstTypesMultipleVariants(i, 20, 60);
	/*for(int i=1; i<5; i++)
		tester.MultipleTypesConstVaraint(5, 15, i);*/

	return 0;

	XMLFileManager A;

	//XML - square
	//XML2 - a more complex diagram
	//XML3 - uncomplete connections

	std::vector<Type*> type;
	try
	{
		type = A.ReadFromXML("Big20Types.xml");
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
	return 0;
}
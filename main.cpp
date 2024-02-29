#include <iostream>
#include "Algorithm/AlgorithmManager.h"
#include "XML_Management/XMLFileManager.h"

#include "Testing/TimeTester.h"

void printHelp(std::string filename)
{
	auto dos = filename.rfind('\\');
	auto unix = filename.rfind('/');

	size_t pos = dos != filename.npos ? dos : unix;

	if (pos != filename.npos)
		pos++;

	std::cout << "Usage: " + filename.substr(pos) + " -f <xml file path> [-t <thread count>]" << std::endl;
}

std::string getResultString(FPA::ResultStruct* result)
{
	using namespace std;
	string text;

	text.append("Calculation completed!\n");

	if (result->bestHeight == 0)
	{
		text.append("Couldn't find any correct configuration\n");
		return text;
	}

	text.append("The best found floorplan dimension is of height " + to_string(result->bestHeight) +
		" and width " + to_string(result->bestWidth) + "\n\n");
	for (auto el : result->bestCombination)
	{
		text.append("The type " + el.first->GetName() + " has the variant of height by width: " +
			to_string(el.second->GetHeight()) + 'x' + to_string(el.second->GetWidth()) +
			" with the top left corner on " + result->bestPlacement[el.first]->TopLeft().toString() + '\n');
	}
	return text;
}


int main(int argc, char* argv[])
{
	std::string filePath;
	int threadNum = 1;

	if (argc <= 2 || argc % 2 != 1)
	{
		printHelp(argv[0]);
		return 0;
	}

	for (int i = 1; i < argc; i += 2)
	{
		if (!std::strcmp(argv[i], "-f"))
		{
			filePath = argv[i + 1];
		}
		else if (!std::strcmp(argv[i], "-t"))
		{
			try
			{
				threadNum = std::stoi(argv[i + 1]);
			}
			catch (...)
			{
				printHelp(argv[0]);
				return -1;
			}
			if (threadNum < 1)
				threadNum = 1;
		}
		else
		{
			printHelp(argv[0]);
			return 0;
		}
	}

	XMLFileManager xmlManager;

	std::vector<FPA::Type*> type;
	try
	{
		type = xmlManager.ReadFromXML(filePath);
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

	FPA::AlgorithmManager alg;

	alg.setTypes(type);
	auto result = alg.StartCalculations(threadNum);

	std::cout << getResultString(result);

	delete result;

	return 0;
}
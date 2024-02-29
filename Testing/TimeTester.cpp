#include "TimeTester.h"
#include <ctime>
#include "../Algorithm/Variant.h"
#include "../Algorithm/AlgorithmManager.h"
#include <chrono>
#include <sstream>
#include <fstream>
#include "../XML_Management/XMLFileManager.h"

#pragma warning( disable : 4996)

using namespace FPA;

void TimeTester::saveCSV(std::string name, std::vector<Info> data)
{
	std::stringstream text;
	text << "Threads;Time;isMultithread\n";

	for (auto& elem : data)
	{
		text << elem.threadNum << ";" << elem.time << ";" << elem.multithread << "\n";;
	}

	std::string fileName = name;
	fileName = "Testing/Results/" + fileName + ".csv";

	std::ofstream file;
	file.open(fileName);
	if (file.is_open())
	{
		file << text.rdbuf();
		file.close();
	}
	else throw;
}



void TimeTester::CalculateTimes(std::string pathToXml, std::string outputFileName, int maxThreads, int iterations)
{
	XMLFileManager xml;
	auto types = xml.ReadFromXML(pathToXml);

	std::vector<Info> time;

	for (int j = 0; j < 20; j++)	// iterations
	{
		FPA::AlgorithmManager* man = new FPA::AlgorithmManager();
		man->setTypes(types);
		auto res = man->StartCalculations(4);
		time.push_back(Info(0, res->time_microsec, false));
		delete man;
		delete res;
		for (int i = 1; i <= maxThreads; i++) //threads
		{
			man = new FPA::AlgorithmManager();
			man->setTypes(types);
			res = man->StartCalculations(i);
			time.push_back(Info(i, res->time_microsec, true));
			delete man;
			delete res;
		}
	}

	saveCSV(outputFileName, time);
	time.clear();


	for (auto& t : types)
		delete t;
}

//std::vector<Type*> TimeTester::TypeVectorCreator(int typesAmount, int variantsAmount, bool withRequirements)
//{
//	std::vector<Type*> types;
//
//	std::srand(time(nullptr));
//
//	for (int i = 0; i < typesAmount; i++)
//	{
//		Type* newType = new Type(std::to_string(i));
//		for (int j = 0; j < variantsAmount; j++)
//		{
//			newType->AddVariant(1 + std::rand() % 20, 1 + std::rand() % 20);
//		}
//		types.push_back(newType);
//	}
//
//	if (withRequirements)
//	{
//		int i = 0;
//		for (auto& type : types)
//		{
//			int typeId;
//			do
//			{
//				typeId = rand() % typesAmount;
//			} while (typeId == i);
//
//			auto sasiad = types[typeId];
//
//			SIDE side;
//			if (typeId % 2 == 0) side = SIDE::RIGHT;
//			else if (typeId % 3 == 0) side = SIDE::DOWN;
//			else if (typeId % 5 == 0) side = SIDE::LEFT;
//			else side = SIDE::UP;
//			type->RemoveRequirement(sasiad, true); //A fix if the element is already a neighbour
//			type->AddRequirement(side, sasiad, true);
//			i++;
//		}
//	}
//
//	return types;
//}

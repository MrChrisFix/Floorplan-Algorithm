#include "TimeTester.h"
#include "../Algorithm/Type.h"
#include "../Algorithm/Variant.h"
#include <ctime>
#include "../Algorithm/AlgorithmManager.h"
#include <chrono>
#include <sstream>
#include <fstream>

#pragma warning( disable : 4996)

void TimeTester::saveCSV(std::vector<std::pair<int, long long>> times, bool multipleTypes, int constAmount)
{
	std::string fileName = "";
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string timestamp(25, ' ');
	std::strftime(&timestamp[0], timestamp.size(), "%Y-%m-%d_%H-%M-%S", std::localtime(&now));

	timestamp.erase(std::find(timestamp.begin(), timestamp.end(), '\0'), timestamp.end());
	std::stringstream text;
	text << "Amount of types;Amount of variants;Time\n";

	if (multipleTypes)
	{
		fileName += "MultipleTypes_" + std::to_string(constAmount) + "v " + timestamp;
		
		for (auto& line : times)
		{
			text << line.first << ";" << constAmount << ";" << line.second <<"\n";
		}
	}
	else
	{
		fileName += "ConstTypes" + std::to_string(constAmount) + "t " + timestamp;

		for (auto& line : times)
		{
			text << constAmount << ";" << line.first << ";" << line.second << "\n";;
		}
	}
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

void TimeTester::MultipleTypesConstVaraint(int typesMin, int typesMax, int variantsAmount)
{
	std::vector<Type*> types;
	std::vector<std::pair<int, long long>> times;

	std::srand(time(NULL));

	for (int i = 0; i < typesMin; i++)
	{
		Type* newType = new Type(std::to_string(i));

		for (int j = 0; j < variantsAmount; j++)
		{
			newType->AddVariant(1 + std::rand() % 20, 1 + std::rand() % 20);
		}

		types.push_back(newType);
	}


	AlgorithmManager manager;
	for (int currentTypeAmount = typesMin; currentTypeAmount <= typesMax; currentTypeAmount++)
	{
		manager.setTypes(types);
		ResultStruct result = manager.StartCalculations();

		times.push_back(std::pair<int, long long>(currentTypeAmount, result.time_microsec));

		Type* newType = new Type(std::to_string(currentTypeAmount));

		for (int j = 0; j < variantsAmount; j++)
		{
			newType->AddVariant(1 + std::rand() % 20, 1 + std::rand() % 20);
		}
		types.push_back(newType);
	}

	this->saveCSV(times, true, variantsAmount);
}

void TimeTester::ConstTypesMultipleVariants(int typesAmount, int variantsMin, int variantsMax)
{
	std::vector<Type*> types;
	std::vector<std::pair<int, long long>> times;

	std::srand(time(NULL));

	for (int i = 0; i < typesAmount; i++)
	{
		Type* newType = new Type(std::to_string(i));

		for (int j = 0; j < variantsMin; j++)
		{
			newType->AddVariant(1 + std::rand() % 20, 1 + std::rand() % 20);
		}

		types.push_back(newType);
	}

	
	AlgorithmManager manager;
	for (int currentVarAmount = variantsMin; currentVarAmount <= variantsMax; currentVarAmount++)
	{
		manager.setTypes(types);
		ResultStruct result = manager.StartCalculations();

		times.push_back(std::pair<int, long long>(currentVarAmount, result.time_microsec));

		for(auto& t : types)
			t->AddVariant(1 + std::rand() % 20, 1 + std::rand() % 20);
	}

	this->saveCSV(times, false, typesAmount);

}

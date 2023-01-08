#include "TimeTester.h"
#include <ctime>
#include "../Algorithm/Variant.h"
#include "../Algorithm/AlgorithmManager.h"
#include <chrono>
#include <sstream>
#include <fstream>

#pragma warning( disable : 4996)

using namespace FPA;

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

	types = TypeVectorCreator(typesMin, variantsAmount, false);


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

	types = TypeVectorCreator(typesAmount, variantsMin, false);
	
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

std::vector<Type*> TimeTester::TypeVectorCreator(int typesAmount, int variantsAmount, bool withRequirements)
{
	std::vector<Type*> types;

	std::srand(time(nullptr));

	for (int i = 0; i < typesAmount; i++)
	{
		Type* newType = new Type(std::to_string(i));
		for (int j = 0; j < variantsAmount; j++)
		{
			newType->AddVariant(1 + std::rand() % 20, 1 + std::rand() % 20);
		}
		types.push_back(newType);
	}

	if (withRequirements)
	{
		int i = 0;
		for (auto& type : types)
		{
			int typeId;
			do
			{
				typeId = rand() % typesAmount;
			} while (typeId == i);

			auto sasiad = types[typeId];

			char side;
			if (typeId % 2 == 0) side = 'R';
			else if (typeId % 3 == 0) side = 'D';
			else if (typeId % 5 == 0) side = 'L';
			else side = 'U';

			type->AddRequirement(side, sasiad, true);
			i++;
		}
	}

	return types;
}

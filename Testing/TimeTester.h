#pragma once
#include <vector>
#include "../Algorithm/Type.h"

/// <summary>
/// Class for measuring time at different thread counts
/// </summary>
class TimeTester
{
private:
	struct Info
	{
		int threadNum;
		long long time;
		bool multithread;
		Info(int th, long long time, bool multi) : threadNum(th), time(time), multithread(multi) {};
	};

	void saveCSV(std::string name, std::vector<Info> data);

public:
	//TimeTester();
	//~TimeTester();

	void CalculateTimes(std::string pathToXml, std::string outputFileName, int maxThreads, int iterations = 20);

	//std::vector<FPA::Type*> TypeVectorCreator(int typesAmount, int variantsAmount, bool withRequirements);

};


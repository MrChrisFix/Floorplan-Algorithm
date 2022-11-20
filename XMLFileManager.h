#pragma once
#include <string>
#include "rapidxml-1.13/rapidxml.hpp"
#include <vector>
#include "Type.h"

class XMLFileManager
{
private:
	std::string currentFilePath;

	char* OpenFile();
	void SaveXML();

public:
	XMLFileManager();
	XMLFileManager(std::string filePath);
	~XMLFileManager();

	void setFilePath(std::string path);
	std::vector<Type*> ReadXML();
};


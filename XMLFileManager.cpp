#include "XMLFileManager.h"
#include <fstream>

char* XMLFileManager::OpenFile()
{
	if (this->currentFilePath.empty())
	{
		throw; //TODO: add exception
	}

	std::ifstream file;
	file.open(this->currentFilePath);
	if (!file.is_open())
	{
		throw; //TODO
	}
	file.seekg(0, file.end);
	const auto fileSize = file.tellg();
	file.seekg(0);

	auto fileContext = new char[fileSize];
	file.read(fileContext, fileSize);

	return fileContext;
}

void XMLFileManager::setFilePath(std::string path)
{
	this->currentFilePath = path;
}

std::vector<Type*> XMLFileManager::ReadXML()
{
	std::vector<Type*> types;

	//TODO use rapidXML

	return types;
}

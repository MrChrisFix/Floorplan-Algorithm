#include "XMLFileManager.h"
#include <fstream>

void XMLFileManager::OpenFile(std::string path)
{
	if (path.empty())
	{
		throw; //TODO: add exception
	}
	this->XMLFile = new rapidxml::file<>(path.c_str());
}

XMLFileManager::XMLFileManager()
{
	this->XMLFile = nullptr;
}

void XMLFileManager::SaveToXML(std::vector<Type*> types, std::string path)
{
	std::ofstream file;
	file.open(path);
	if (!file.is_open())
	{
		throw;
	}
	//TODO

	file.close();

}

std::vector<Type*> XMLFileManager::ReadFromXML(std::string path)
{
	using namespace rapidxml;
	std::vector<Type*> types;
	
	this->OpenFile(path);
	xml_document<> document;
	try
	{
		document.parse<0>(this->XMLFile->data());
	}
	catch (...)
	{

	}

	xml_node<>* mainNode = document.first_node();
	for (xml_node<>* typeNode = mainNode->first_node(); typeNode; typeNode = typeNode->next_sibling())
	{
		Type* newType = new Type(typeNode->first_attribute("name")->value());
		xml_node<>* variants = typeNode->first_node("Variants");
		xml_node<>* requirements = typeNode->last_node("Requirements");

		for (xml_node<>* variantNode = variants->first_node(); variantNode; variantNode = variantNode->next_sibling())
		{
			unsigned width = std::atoi(variantNode->first_attribute("width")->value());
			unsigned height = std::atoi(variantNode->last_attribute("height")->value());
			Variant* newVariant = new Variant(height, width, newType);
		}

		for (xml_node<>* reqNode = requirements->first_node(); reqNode; reqNode = reqNode->next_sibling())
		{
			//That will be difficult becouse of the type
			//Idea: do another loop after al types will be read
		}

		types.push_back(newType);
	}

	return types;
}

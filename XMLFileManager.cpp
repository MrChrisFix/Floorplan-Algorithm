#include "XMLFileManager.h"
#include <fstream>
#include <map>

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
		//TODO
	}

	xml_node<>* mainNode = document.first_node("Types");
	if (mainNode->name() == 0)
	{
		throw; //TODO Some information
	}

	std::map <std::string,Type*> TypeByName;

	for (xml_node<>* typeNode = mainNode->first_node(); typeNode; typeNode = typeNode->next_sibling())
	{
		Type* newType = new Type(typeNode->first_attribute("name")->value());
		xml_node<>* variants = typeNode->first_node("Variants");

		for (xml_node<>* variantNode = variants->first_node(); variantNode; variantNode = variantNode->next_sibling())
		{
			unsigned width = std::atoi(variantNode->first_attribute("width")->value());
			unsigned height = std::atoi(variantNode->last_attribute("height")->value());
			newType->AddVariant(width, height);
		}

		TypeByName.emplace(newType->GetName(), newType);
		types.push_back(newType);
	}

	//Adding requiremnets
	for (xml_node<>* typeNode = mainNode->first_node(); typeNode; typeNode = typeNode->next_sibling())
	{
		xml_node<>* requirements = typeNode->last_node("Requirements");

		for (xml_node<>* reqNode = requirements->first_node(); reqNode; reqNode = reqNode->next_sibling())
		{
			auto parTypeName = typeNode->first_attribute("name")->value();
			Type* parType = TypeByName[parTypeName];
			auto childTypeName = reqNode->first_attribute("typeName")->value();
			Type* childType = TypeByName[childTypeName];

			//TODO: chack if type isn't nullptr

			auto direction = reqNode->last_attribute("direction")->value();

			parType->AddRequirement(direction[0], childType, false);
		}
	}
	return types;
}

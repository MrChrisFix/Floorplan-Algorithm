#include "XMLFileManager.h"
#include <fstream>
#include <map>


void XMLFileManager::OpenFile(std::string path)
{
	if (path.empty())
	{
		throw "Path is empty";
	}

	try 
	{
		this->XMLFile = new rapidxml::file<>(path.c_str());
	}
	catch (...)
	{
		throw "Coundn't open file";
	}
}

XMLFileManager::XMLFileManager()
{
	this->XMLFile = nullptr;
}

XMLFileManager::~XMLFileManager()
{
	if(this->XMLFile != nullptr)
		delete this->XMLFile;
}

void XMLFileManager::SaveToXML(std::vector<FPA::Type*> types, std::string path)
{
	using namespace rapidxml;
	xml_document<> document;

	//<Types>
	xml_node<>* TypesNode = document.allocate_node(node_element, "Types");

	for (auto type : types)
	{
		//<Type name="...">
		xml_node <>* TypeNode = document.allocate_node(node_element, "Type");
		xml_attribute <>* TypeName = document.allocate_attribute("name", document.allocate_string(type->GetName().c_str()));
		TypeNode->append_attribute(TypeName);

		//<Variants>
		xml_node <>* VariantsNode = document.allocate_node(node_element, "Variants");

		//<Variant width="..." height="...">
		for (auto var : type->GetVariants())
		{
			xml_node <>* VariantNode = document.allocate_node(node_element, "Variant");
			xml_attribute <>* Width = document.allocate_attribute("width", document.allocate_string(std::to_string(var->GetWidth()).c_str()));
			xml_attribute <>* Height = document.allocate_attribute("height", document.allocate_string(std::to_string(var->GetHeight()).c_str()));

			VariantNode->append_attribute(Width);
			VariantNode->append_attribute(Height);
			VariantsNode->append_node(VariantNode);
		}

		TypeNode->append_node(VariantsNode);

		//<Requirements>
		xml_node <>* Requirements = document.allocate_node(node_element, "Requirements");

		//<Requirement typeName="..." direction="...">
		for (auto dir : type->up)
		{
			xml_node <>* ReqNode = document.allocate_node(node_element, "Requirement");

			xml_attribute <>* typeNameAttr = document.allocate_attribute("typeName", document.allocate_string(dir->GetName().c_str()));
			xml_attribute <>* directionAttr = document.allocate_attribute("direction", "U");
			ReqNode->append_attribute(typeNameAttr);
			ReqNode->append_attribute(directionAttr);
			Requirements->append_node(ReqNode);
		}
		for (auto dir : type->down)
		{
			xml_node <>* ReqNode = document.allocate_node(node_element, "Requirement");

			xml_attribute <>* typeNameAttr = document.allocate_attribute("typeName", document.allocate_string(dir->GetName().c_str()));
			xml_attribute <>* directionAttr = document.allocate_attribute("direction", "D");
			ReqNode->append_attribute(typeNameAttr);
			ReqNode->append_attribute(directionAttr);

			Requirements->append_node(ReqNode);
		}
		for (auto dir : type->left)
		{
			xml_node <>* ReqNode = document.allocate_node(node_element, "Requirement");

			xml_attribute <>* typeNameAttr = document.allocate_attribute("typeName", document.allocate_string(dir->GetName().c_str()));
			xml_attribute <>* directionAttr = document.allocate_attribute("direction", "L");
			ReqNode->append_attribute(typeNameAttr);
			ReqNode->append_attribute(directionAttr);
			Requirements->append_node(ReqNode);
		}
		for (auto dir : type->right)
		{
			xml_node <>* ReqNode = document.allocate_node(node_element, "Requirement");

			xml_attribute <>* typeNameAttr = document.allocate_attribute("typeName", document.allocate_string(dir->GetName().c_str()));
			xml_attribute <>* directionAttr = document.allocate_attribute("direction", "R");
			ReqNode->append_attribute(typeNameAttr);
			ReqNode->append_attribute(directionAttr);
			Requirements->append_node(ReqNode);
		}
		TypeNode->append_node(Requirements);

		TypesNode->append_node(TypeNode);
	}

	document.append_node(TypesNode);

	std::ofstream file;
	file.open(path);
	if (!file.is_open())
	{
		throw "Couldn't open file";
	}
	file << document;
	file.close();
}

std::vector<FPA::Type*> XMLFileManager::ReadFromXML(std::string path)
{
	using namespace rapidxml;
	std::vector<FPA::Type*> types;
	
	xml_document<> document;
	try
	{
		this->OpenFile(path);
		document.parse<0>(this->XMLFile->data());
	}
	catch (...)
	{
		throw;
	}

	xml_node<>* mainNode = document.first_node("Types");
	if (mainNode->name() == 0)
	{
		throw "XML node format is incorrect";
	}

	std::map <std::string, FPA::Type*> TypeByName;

	for (xml_node<>* typeNode = mainNode->first_node(); typeNode; typeNode = typeNode->next_sibling())
	{
		FPA::Type* newType = new FPA::Type(typeNode->first_attribute("name")->value());
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
			FPA::Type* parType = TypeByName[parTypeName];
			auto childTypeName = reqNode->first_attribute("typeName")->value();
			FPA::Type* childType = TypeByName[childTypeName];

			if (childType == nullptr)
			{
				throw "Something went wrong. Try to start over.";
			}

			auto direction = reqNode->last_attribute("direction")->value();
			FPA::SIDE side = FPA::CharToSide(direction[0]);

			parType->AddRequirement(side, childType, false);
		}
	}
	return types;
}

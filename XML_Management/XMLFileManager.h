#pragma once
#include <string>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include <vector>
#include "../Algorithm/Type.h"

class XMLFileManager
{
private:

	rapidxml::file<>* XMLFile;			/// Variable needed for rapidxml node iteration
	/**
	 * Private method for opening xml and setting the XMLFile variable
	 * @param path Filepath of the xml
	*/
	void OpenFile(std::string path);

public:
	/**
	 * Constructor
	*/
	XMLFileManager();

	/**
	 * Destructor
	*/
	~XMLFileManager();

	/**
	 * Extracts types from a xml
	 * @param path Filepath to the xml with types
	 * @return A vector with Types (including variants and requirements)
	*/
	std::vector<FPA::Type*> ReadFromXML(std::string path);

	/**
	 * Saves type vector to a xml
	 * @param types The vector of Types that should be saved
	 * @param path Filepath where the xml should be saved
	*/
	void SaveToXML(std::vector<FPA::Type*> types, std::string path);
};


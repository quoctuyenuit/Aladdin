#include "ResourceFile.h"

ResourceFile*			ResourceFile::__instance = NULL;

ResourceFile::ResourceFile()
{
}

std::vector<int> ResourceFile::ParseLineStringToInt(string line)
{
	std::vector<int> result;
	auto indexOfSpace = line.find(' ');
	while (indexOfSpace != std::string::npos)
	{
		//const char* numberStr = line.substr(0, indexOfSpace).c_str();
		int number = std::atoi(line.substr(0, indexOfSpace).c_str());
		result.push_back(number);
		line = line.substr(indexOfSpace + 1, line.length() - indexOfSpace);
		indexOfSpace = line.find(' ');
	}

	const char* numberStr = line.c_str();
	int number = std::atoi(numberStr);
	result.push_back(number);

	return result;
}


ResourceFile * ResourceFile::Instance()
{
	if (!__instance)
		__instance = new ResourceFile();
	return __instance;
}

std::vector<Rect*> ResourceFile::LoadXML(char * fileName, string key)
{
	std::vector<Rect*> list;
	TiXmlDocument doc(fileName);
	if (!doc.LoadFile())
	{
		return std::vector<Rect*>();
	}

	TiXmlElement* root = doc.RootElement();

	TiXmlElement* child = root->FirstChildElement();
	while (child)
	{
		if (child->Attribute("name")== key)
		{
			TiXmlElement* ele = child->FirstChildElement();
			while (ele)
			{
				float x;
				ele->QueryFloatAttribute("x", &x);
				float y;
				ele->QueryFloatAttribute("y", &y);
				float w;
				ele->QueryFloatAttribute("w", &w);
				float h;
				ele->QueryFloatAttribute("h", &h);

				list.push_back(new Rect(y, x, x + w, y + h));

				ele = ele->NextSiblingElement();
			}
			break;
		}
		child = child->NextSiblingElement();
	}
	

	return list;
}

std::vector<int> ResourceFile::LoadTXT(char * fileName)
{
	std::vector<int> result;
	fstream reader;
	reader.open(fileName);

	while (!reader.eof())
	{
		string line;
		reader >> line;
		const char* numberStr = line.c_str();
		result.push_back(std::atoi(numberStr));
	/*	auto tempList = this->ParseLineStringToInt(line);
		for each (int number in tempList)
			result.push_back(number);*/
	}
	
	return result;
}

ResourceFile::~ResourceFile()
{
}

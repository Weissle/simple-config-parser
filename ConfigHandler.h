#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;


class ConfigHandler {
	map<string, string> config;
	void buildConfig(const char *path);
	char spiltChar;
	bool caseSensitive;
	bool configFileGet;
	stringstream stream;
	template <class str>
	string inputDeal(str input);

public:
	ConfigHandler() {};
	~ConfigHandler() {};
	ConfigHandler(string configFilePath, bool _caseSensitive = false, char _spiltChar = '='):
		spiltChar(_spiltChar), caseSensitive(_caseSensitive){
		buildConfig(configFilePath.c_str());
	}
	ConfigHandler(const char *configFilePath) {
		buildConfig(configFilePath);
	}
	bool buildOK() { return configFileGet; }
	template<class KeyT,class AnsT>
	AnsT getValue(const KeyT key, const AnsT _default);
	template<class KeyT, class AnsT>
	stringstream& operator()(const KeyT key, const AnsT _default);
	template<class KeyT>
	stringstream& operator()(const KeyT);
	
	string getStrValue(const string key, const string _default = string(""));
	int getIntValue(const string key, const int _default = 0);
	double getFloatValue(const string key, const double _default = 0);
	bool getBoolValue(const string key, const bool defaule = false);
	char getCharValue(const string key, const char defaule = '\0');

};


template<class KeyT>
inline stringstream& ConfigHandler::operator()(const KeyT key)
{
	stream.str("");
	auto str = inputDeal(key);
	stream << config[str] << " ";
	return stream;
}
template<class str>
inline string ConfigHandler::inputDeal(str input)
{
	string line = input;
	line.erase(remove_if(line.begin(), line.end(), ::isspace),
		line.end());
	if (line[0] == '#' || line.empty()) return string("");
	if (caseSensitive == false) for (unsigned int i = 0; i < line.size(); ++i) line[i] = tolower(line[i]);
	return line;
}
template<class KeyT, class AnsT>
inline AnsT ConfigHandler::getValue(const KeyT key, const AnsT _default)
{
	stream.str("");
	auto str = inputDeal(key);
	if (config.find(str) == config.end()) return _default;
	else stream << config[str] << " ";
	AnsT answer;
	try {
		stream >> answer;
	}
	catch (int e) {
		answer = _default;
	}
	return answer;

}
template<class KeyT, class AnsT>
inline stringstream& ConfigHandler::operator()(const KeyT key, const AnsT _default)
{
	stream.str("");
	auto str = inputDeal(key);
	if (config.find(str) == config.end()) {
		string defaultStr;
		if (typeid(char) == typeid(AnsT)) defaultStr = string(1, _default);
		else defaultStr = to_string(_default);
		stream << defaultStr << " ";
	}
	else stream << config[str] << " ";
	return stream;
}
void ConfigHandler::buildConfig(const char *path) {
	ifstream cFile(path);
	if (cFile.is_open())
	{
		configFileGet = true;
		std::string line;
		while (getline(cFile, line)) {
			line = inputDeal(line);
			if (line.empty())continue;
			auto delimiterPos = line.find(spiltChar);
			if (delimiterPos == string::npos)continue;
			auto key = line.substr(0, delimiterPos);
			auto value = line.substr(delimiterPos + 1);
			config[key] = value;
		}

	}
	else {
		cerr << "Couldn't open config file for reading.\n";
		configFileGet = false;
	}
}

inline bool ConfigHandler::getBoolValue(const string key, const bool _default)
{
	auto str = inputDeal(key);
	if (config.find(str) == config.end()) return _default;
	for (unsigned int i = 0; i < str.size(); ++i) str[i] = tolower(str[i]);
	return config[str] == "false" ? false : true;
}
inline char ConfigHandler::getCharValue(const string key, const char _default)
{
	auto str = inputDeal(key);
	if (config.find(str) == config.end()) return _default;
	return config[str][0];
}

inline string ConfigHandler::getStrValue(const string key, const string _default)
{
	auto str = inputDeal(key);
	if (config.find(str) == config.end()) return _default;
	return config[str];
}

inline int ConfigHandler::getIntValue(const string key, const int _default)
{
	auto str = inputDeal(key);
	if (config.find(str) == config.end()) return _default;
	return atoi(config[str].c_str());
}

inline double ConfigHandler::getFloatValue(const string key, const double _default)
{
	auto str = inputDeal(key);
	if (config.find(str) == config.end()) return _default;
	return atof(config[str].c_str());
}

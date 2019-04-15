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
	ConfigHandler(string configFilePath, bool _caseSensitive = false, char _spiltChar = '=') :
		spiltChar(_spiltChar), caseSensitive(_caseSensitive) {
		buildConfig(configFilePath.c_str());
	}

	bool buildOK() { return configFileGet; }
	//.getValue(Key,default)
	template<class AnsT>
	AnsT getValue(const string key, const AnsT _default);

	string getValue(const string key, const char* _default);

	//operator() most of them are similar, details are writed at the second function (accept int _default).
	stringstream& operator()(const string key, const string _default);
	stringstream& operator()(const string key, const int _default);
	stringstream& operator()(const string key, const long long _default);
	stringstream& operator()(const string key, const double _default);
	stringstream& operator()(const string key, const char _default);
	stringstream& operator()(const string);

	//basic function
	string getStrValue(const string key, const string _default = string(""));
	int getIntValue(const string key, const int _default = 0);
	double getFloatValue(const string key, const double _default = 0);
	bool getBoolValue(const string key, const bool defaule = false);
	char getCharValue(const string key, const char defaule = '\0');

};


inline stringstream & ConfigHandler::operator()(const string key, const int _default)
{
	//flush steam
	stream.str("");
	auto str = inputDeal(key);
	//if key word not exist in config
	if (config.find(str) == config.end()) {
		//transform default value into string and pass it to stream 
		stream << to_string(_default) << " ";
	}
	//pass value to stream
	else stream << config[str] << " ";
	return stream;
}


inline stringstream & ConfigHandler::operator()(const string key, const long long _default)
{
	stream.str("");
	auto str = inputDeal(key);
	if (config.find(str) == config.end()) {
		stream << to_string(_default) << " ";
	}
	else stream << config[str] << " ";
	return stream;
}


inline stringstream & ConfigHandler::operator()(const string key, const double _default)
{
	stream.str("");
	auto str = inputDeal(key);
	if (config.find(str) == config.end()) {
		stream << to_string(_default) << " ";
	}
	else stream << config[str] << " ";
	return stream;
}


inline stringstream & ConfigHandler::operator()(const string key, const char _default)
{
	stream.str("");
	auto str = inputDeal(key);
	if (config.find(str) == config.end()) {
		stream << string(1,_default) << " ";
	}
	else stream << config[str] << " ";
	return stream;
}


inline string ConfigHandler::getValue(const string key, const char * _default)
{
	stream.str("");
	auto str = inputDeal(key);
	if (config.find(str) == config.end())	return string(_default);
	else return config[str];
}

inline stringstream& ConfigHandler::operator()(const string key)
{
	stream.str("");
	auto str = inputDeal(key);
	stream << config[str] << " ";
	return stream;
}

template<class AnsT>
inline AnsT ConfigHandler::getValue(const string key, const AnsT _default)
{
	stream.str("");
	auto str = inputDeal(key);
	if (config.find(str) == config.end())	return _default;
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

inline stringstream& ConfigHandler::operator()(const string key, const string _default)
{
	stream.str("");
	auto str = inputDeal(key);
	if (config.find(str) == config.end()) {	
		stream << _default << " ";
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

#include<iostream>
#include<random>
#include<string>
#include"ConfigHandler.h"
#include<fstream>
using namespace std;


int main(int argc,char *argv[])
{
	string configFilePath = "test_config.ini";

	ConfigHandler CH(configFilePath);

	//first part tutorial
	cout << "first part tutorial" << endl;
	string str = CH.getStrValue("STRtest");
	int i = CH.getIntValue("inttest");
	double f = CH.getFloatValue("float test");
	char c = CH.getCharValue("char test");
	bool b1 = CH.getBoolValue("bool test 1");
	bool b2 = CH.getBoolValue("bool test 2");

	cout << "str test value:" << str << endl;
	cout << "int test value :" << i << endl;
	cout << "char test value :" << c << endl;
	cout << "bool test 1 value :" << b1 << endl;
	cout << "bool test 2 value :" << b2 << endl;



	//second part tutorial
	cout << "second part tutorial" << endl;
	CH("int test", 50) >> i;
	CH("float test") >> f;
	cout << "int test value :" << i << endl;
	cout << "float test :" << f << endl;

	

	return 0;
}
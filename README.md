# simple-config-parser
Sometimes grogram need numerous parameter to decide what to do and how to run.  
It is tired that if user need to type in so many parameter every time.  
Using config file will be convenient and safe time.  
There is a simple config parser in c++.    
***
### How To Use
    Just inlucde ConfigHandler.h 
### Config File Format
#### Example (Key=Value)
    myName=weissle
    myPet=wata
    AInteger=48
#### Neglect case (Including key and value). You can choose case sensitive or not.(See below)
#### Ignore All Space.    
    my Name = wei ss LE => myname=weissle
    my P e T = w a TA   => mypet=wata
  
## Tutorial
#### Config File
    STR TEST    = hel l o
    int test    = 20
    float test  = 5.3
    char test   = a
    bool test   = true
#### Constructor Function
```c
ConfigHandler(std::string configFilePath, bool caseSensitive = false, char spiltChar = '=');
```
#### Initialize
```c
ConfigHandler CH(configFilePath);
//if you care about the case , the second parameter should be set to'true'
ConfigHandler CH(configFilePath, true);
//if your spiltChar is not  '=' , the third parameter should be set to another char (eg.)
ConfigHandler CH(configFilePath, false, '-');
```
#### Five Fundamental Function
#### Of course, the string you passed will be remove all space and all letter will become lower if you choose case insensitive
    variable = getTypeValue(KeyStr,default_value); //default_value can be omitted
```c
std::string str = CH.getStrValue("STRtest");   //  str="hello"
int i = CH.getIntValue("inttest");        //  i=20;   
double f = CH.getFloatValue("float test");//  f=5.3
char c = CH.getCharValue("char test");    //  c='a'
bool b = CH.getBoolValue("bool test 1");  //  b=true 
```
#### When you pass a default value , I recommand you use below function so that you do not need to specify what type of return you want.
#### Exclude you want a bool value,it always return false.
    getValue(KeyStr,default_value);
```c
c = CH.getValue("A key word not exists",'p');   //c='p'
f = CH.getValue("A key word not exists" , 5.02); //f=5.02
i = CH.getValue("int test",15);                //i=20
str = CH.getValue("int test",std::string("15"));            //str="20"
```
#### There are two convenient functions.
    Just something like cin ;
    CH(KeyStr) >> variable;
    CH(KeyStr,default_value) >> variable;
```c
CH("int test") >> i;// i=20;
CH("int test") >> f;// f=20.0;
CH("int test") >> str;// str="20";
CH("A key word not exists",50) >> i; //i =50;
```
### Warning
    If you want a bool value, I suggest you get a string type return first and then handle it by yourself.
    Because I have not yet figure out a good method to handle bool type.
    For now,getBoolValue function will return false when the key word is not defined or the value is a exact "false" string.
    If anyone have a good solution about that,it would be appreciated if you tell me.

  


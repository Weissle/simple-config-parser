# simple-config-parser
Sometimes grogram need numerous parameter to decide what to do and how to run.  
It is tired that if user need to type in many parameters every time.  
Using config file will be convenient and save time.  
There is a simple config parser in c++.    
***
### How To Use
    Just inlucde ConfigHandler.h 
### Config File Format
#### Example (Key=Value)
    myName=weissle
    myPet=wata
    AInteger=48
#### Neglect case (By default,including key and value). You can choose case sensitive or not.(See below)
#### Ignore All Space.    
    my Name = wei ss LE => myname=weissle
    my P e T = w a TA   => mypet=wata
  
## Tutorial
### Config File
    STR TEST    = hel l o
    int test    = 20
    float test  = 5.3
    char test   = a
    bool test   = true
### Constructor Function
    ConfigHandler(std::string configFilePath, bool caseSensitive = false, char spiltChar = '=');
```c
ConfigHandler CH(configFilePath);
//if you care about the case , the second parameter should be set to'true'
ConfigHandler CH(configFilePath, true);
//if your spiltChar is not  '=' , the third parameter should be set to another char (eg.)
ConfigHandler CH(configFilePath, false, '-');
```
### Variables' Name Used Below And Its' Type
    i-int, d-double, c-char, b-bool, f-float, str-string.
### There Are Two Convenient Functions.
#### Of course, the string you passed will be remove all space and all letter will become lower if you choose case insensitive
    Just something like cin ;
    CH(KeyStr) >> variable;
    CH(KeyStr,default_value) >> variable;
```c
CH("int test") >> i;// i=20;
CH("float test") >> f;// f=5.3;
CH("int test") >> str;// str="20";
CH("A key word not exists",50) >> i; //i =50;
```
### In Case You Want To Assign When You Define A Variable.
    variable = CH.getTypeValue(KeyStr,default_value); //default_value can be omitted
    variable = CH.getValue(KeyStr,defalut_value);     //default_value cannot be omitted,and it does not support get bool value
    Type should be replaced by Int,Float,Str,Char or Bool.
```c
std::string str = CH.getStrValue("STRtest");   //  str="hello"
int i = CH.getIntValue("inttest");        //  i=20;   
double f = CH.getFloatValue("float test", 9.0);//  f=5.3
char c = CH.getCharValue("char test");    //  c='a'
bool b = CH.getBoolValue("bool test ", false);  //  b=true 
c = CH.getValue("A key word not exists",'p');   //c='p'
f = CH.getValue("A key word not exists" , 5.02); //f=5.02
i = CH.getValue("int test",15);                //i=20
str = CH.getValue("int test","15");            //str="20"
```

### Warning
    If you want a bool value, I suggest you get a string type return first and then handle it by yourself.
    Because I have not yet figured out a good method to handle bool type.
    For now,getBoolValue function will return false when the key word is not defined or the value is a exact "false" string.
    If anyone have a good solution about that,it would be appreciated if you tell me.

  


#include <iostream>
#include <string>

#include "EzIni.h"

void ExampleSave()
{
    xe::EzIni ini;
    ini["name"] = "John Smith";
    ini["age"] = std::to_string(27);

    ini.SaveFile("my-file.ini");
}

void ExampleLoad()
{
    xe::EzIni ini;
    ini.OpenFile("my-file.ini");

    std::string name;
    if (ini.Contains("name"));
    {
        name = ini["name"];
    }

    int age;
    if (ini.Contains("age"));
    {
        age = std::stoi(ini["age"]);
    }

    std::cout << name << " is age " << age << std::endl;
}

int main (int argc, char* argv[])
{
    ExampleSave();
    ExampleLoad();
    return 0;
}

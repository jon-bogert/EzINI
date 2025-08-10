# EzINI - Readme

## Description
Simple C++ INI formatter for reading and writing files in the .ini style. `EzIni.h` is the only required file for using this library.

## Example
```cpp
// Save Example
int main()
{
    xe::EzIni ini;
    ini["name"] = "John Smith";
    ini["age"] = std::to_string(27);

    ini.SaveFile("my-file.ini");

    return 0;
}
```
```cpp
// Load Example
int main()
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

    return 0;
}
```

## Repository
This repository uses the [premake5](https://premake.github.io/) build system. Run `generate-vs2022.bat` to generate a Visual Studio 2022 solution.
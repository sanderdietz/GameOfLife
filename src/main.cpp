#include "GameOfLife.h"
#include "Grid.h"
#include "Settings.h"

#include <functional>
#include <string>

typedef std::function<void(Settings&, const std::string&)> ArgHandle;
#include <iostream>

const std::unordered_map<std::string, ArgHandle> Args
{
    {
        "--rows", [](Settings& settings, const std::string& arg)
        {
            settings.rows = std::stoi(arg);
        }
    },
    {
        "--resolution", [](Settings& settings, const std::string& arg)
        {
            int xIndex = arg.find('x');
            settings.resolutionWidth = std::stoi(arg.substr(0, xIndex));
            settings.resolutionHeight = std::stoi(arg.substr(xIndex + 1));
        }
    },
    {
        "--speed", [](Settings& settings, const std::string& arg)
        {
            settings.speed = std::stod(arg);
        }
    }
};

Settings parseSettings(int argc, char* argv[])
{
    Settings settings;
    for (int i = 1; i < argc; i++)
    {
        std::string option = argv[i];
        if (auto j {Args.find(option)}; j != Args.end())
        {
            if(++i < argc)
            {
                j->second(settings, {argv[i]});
            }
        }
    }
    return settings;
}

int main(int argc, char* argv[])
{
    Settings settings = parseSettings(argc, argv);
    GameOfLife gameOfLife(settings);
    std::cout << settings.rows << std::endl;
    std::cout << settings.resolutionWidth << std::endl;
    std::cout << settings.resolutionHeight << std::endl;
    std::cout << settings.speed << std::endl;
    gameOfLife.loop();
    return 0;
}
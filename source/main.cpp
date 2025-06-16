#include <mosaic/application/application.hpp>
#include <mosaic/application/instance.hpp>

#include <mosaic/api/main.hpp>

class MosaicTest : public Mosaic::Application
{
public:
    MosaicTest(Mosaic::Resources& resources)
        : Application(resources)
    {
    }

    void Setup() override
    {
        auto outputID = ApplicationResources.Console.CreateFileOutput("logs.txt");
        auto outputID2 = ApplicationResources.Console.CreateFileOutput("logs.txt");

        ApplicationResources.Console.Log<Mosaic::Console::LogSeverity::Success>(ApplicationResources.Console.TerminalOutputID, "Hello from Mosaic!");

        ApplicationResources.Console.Log<Mosaic::Console::LogSeverity::Success>(outputID2, "Hello from Mosaic, but in a log file!");
    }
};

MOSAIC_DEFINE_MAIN(MosaicTest)
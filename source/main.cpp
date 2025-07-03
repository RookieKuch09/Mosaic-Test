#include <Mosaic/Mosaic.hpp>

#include <log_severities.hpp>
#include <quad_mesh.hpp>

class MosaicTest : public Mosaic::Application
{
public:
    void Setup(Mosaic::InstanceResources& instanceResources) override
    {
        auto& console = instanceResources.Console;
        auto& renderer = instanceResources.Renderer;

        auto outputHandle = console.CreateOutput("file.txt");

        console.Log<ConsoleNotice>(2, "Hello!");
    }
};

MOSAIC_DEFINE_MAIN(MosaicTest)
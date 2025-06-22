#include <Mosaic/Mosaic.hpp>

class MosaicTest : public Mosaic::Application
{
public:
    MosaicTest(Mosaic::InstanceResources& resources)
        : Application(resources)
    {
    }

    void Setup() override
    {
    }
};

MOSAIC_DEFINE_MAIN(MosaicTest)
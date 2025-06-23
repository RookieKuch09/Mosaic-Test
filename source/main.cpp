#include <Mosaic/Mosaic.hpp>

void System(Mosaic::InstanceResources& instanceResources)
{
    auto& eventManager = instanceResources.EventManager;
    auto& ecs = instanceResources.ECSManager;
    auto& console = instanceResources.Console;

    auto view = ecs.QueryView<Mosaic::WindowStateComponent>();

    glm::fvec4 colour;

    for (auto [entity, windowState] : view)
    {
        float px = windowState.Position.x;
        float py = windowState.Position.y;

        float length = std::sqrt(px * px + py * py);

        // console.Log<Mosaic::Console::LogSeverity::Notice>("Position: {}, {}", px, py);

        if (length == 0.0)
        {
            colour.r = 0.0;
            colour.g = 0.0;

            // console.Log<Mosaic::Console::LogSeverity::Notice>("Colour: {}, {}", colour.r, colour.g);
        }
        else
        {
            colour.r = px / length;
            colour.g = py / length;

            // console.Log<Mosaic::Console::LogSeverity::Notice>("Colour: {}, {}", colour.r, colour.g);
        }

        colour.b = 0.0;
        colour.a = 1.0;
    }

    eventManager.Emit<Mosaic::RendererClearColourChangeRequest>(colour);
}

class MosaicTest : public Mosaic::Application
{
public:
    void Setup(Mosaic::InstanceResources& instanceResources) override
    {
        auto& ecs = instanceResources.ECSManager;
        auto& console = instanceResources.Console;

        auto entity = ecs.CreateEntity();

        ecs.AddSystem(System);

        ecs.AddComponent<Mosaic::WindowStateComponent>(entity);
    }
};

MOSAIC_DEFINE_MAIN(MosaicTest)
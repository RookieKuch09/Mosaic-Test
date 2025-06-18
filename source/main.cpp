#include <mosaic/application/application.hpp>
#include <mosaic/application/instance.hpp>

#include <mosaic/api/main.hpp>

struct Component
{
    int a;
    int b;
};

void System(Mosaic::Resources& resources)
{
    auto method = [&resources](Mosaic::ECS::Entity entity, Component& component)
    {
        resources.Console.Log<Mosaic::Debug::Console::LogSeverity::Success>("Result of adding Component values 'a' and 'b' on entity {}: {}", entity.ID, component.a + component.b);
    };

    resources.ECSManager.ForEach<Component>(method);
}

class MosaicTest : public Mosaic::Application
{
public:
    MosaicTest(Mosaic::Resources& resources)
        : Application(resources)
    {
    }

    void Setup() override
    {
        auto& resources = GetApplicationResources();

        auto& console = resources.Console;
        auto& ecsManager = resources.ECSManager;

        ecsManager.AddSystem(System);

        Mosaic::ECS::Entity entity0 = ecsManager.CreateEntity();
        Mosaic::ECS::Entity entity1 = ecsManager.CreateEntity();

        ecsManager.AddComponent<Component>(entity0, Component{.a = 7, .b = 9});
        ecsManager.AddComponent<Component>(entity1, Component{.a = 3, .b = 2});

        console.Log<Mosaic::Debug::Console::LogSeverity::Success>("Hello from Mosaic!");
    }
};

MOSAIC_DEFINE_MAIN(MosaicTest)
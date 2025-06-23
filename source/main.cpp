#include <Mosaic/Mosaic.hpp>

struct Time
{
    float Value;
};

void System(Mosaic::InstanceResources& instanceResources)
{
    auto& eventManager = instanceResources.EventManager;
    auto& ecs = instanceResources.ECSManager;

    auto view = ecs.QueryView<Time>();

    glm::fvec4 colour;

    for (auto [entity, component] : view)
    {
        component.Value += 0.001;

        colour.r = -std::sin(component.Value);
        colour.g = std::cos(component.Value);
        colour.b = std::sin(component.Value);
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

        auto entity = ecs.CreateEntity();

        ecs.AddSystem(System);

        ecs.AddComponent<Time>(entity);
    }
};

MOSAIC_DEFINE_MAIN(MosaicTest)
#include <Mosaic/Mosaic.hpp>

enum class VertexSemantic
{
    Position,
    Colour,
};

using VertexDescriptor = Mosaic::MeshDescriptor<
    Mosaic::MeshAttribute<VertexSemantic::Position, glm::fvec3, 1>,
    Mosaic::MeshAttribute<VertexSemantic::Colour, glm::fvec4, 1>>;

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

        if (length == 0.0)
        {
            colour.r = 0.0;
            colour.g = 0.0;
        }
        else
        {
            colour.r = px / length;
            colour.g = py / length;
        }

        colour.b = 0.0;
        colour.a = 1.0;
    }
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

        Mosaic::Mesh<VertexDescriptor> mesh0;

        Mosaic::MeshSemanticData<VertexSemantic::Position, glm::fvec3, 4> positions;
        Mosaic::MeshSemanticData<VertexSemantic::Colour, glm::fvec4, 4> colours;

        positions.Data = {
            glm::fvec3{0.5, 0.5, 0.0},
            glm::fvec3{-0.5, 0.5, 0.0},
            glm::fvec3{-0.5, -0.5, 0.0},
            glm::fvec3{0.5, -0.5, 0.0},
        };

        colours.Data = {
            glm::fvec4{1.0, 0.0, 0.0, 1.0},
            glm::fvec4{0.0, 1.0, 0.0, 1.0},
            glm::fvec4{0.0, 0.0, 1.0, 1.0},
            glm::fvec4{0.0, 0.0, 0.0, 1.0},
        };

        mesh0.SetMeshData(positions, colours);
    }
};

MOSAIC_DEFINE_MAIN(MosaicTest)
#include <Mosaic/Mosaic.hpp>

#include <Mosaic/Rendering/Mesh/Attributes.hpp>
#include <Mosaic/Rendering/Mesh/Descriptor.hpp>
#include <Mosaic/Rendering/Mesh/Resource.hpp>

enum class QuadMeshSemantic
{
    Position,
    Colour,
};

using QuadMeshPositionAttribute = Mosaic::MeshAttribute<QuadMeshSemantic::Position, glm::fvec3>;
using QuadMeshColourAttribute = Mosaic::MeshAttribute<QuadMeshSemantic::Colour, glm::fvec4>;

using QuadMeshAttributePack = Mosaic::MeshAttributePack<QuadMeshPositionAttribute, QuadMeshColourAttribute>;
using QuadMeshFlags = Mosaic::MeshFlags<Mosaic::MeshPrimitive::Triangles, Mosaic::MeshIndexing::U32>;

using QuadMeshDescriptor = Mosaic::MeshDescriptor<QuadMeshAttributePack, QuadMeshFlags>;

class MosaicTest : public Mosaic::Application
{
public:
    void Setup(Mosaic::InstanceResources& instanceResources) override
    {
        auto& console = instanceResources.Console;
        auto& renderer = instanceResources.Renderer;

        auto& entityManager = instanceResources.EntityManager;
        auto& meshManager = instanceResources.MeshManager;

        // Fixed means this is static data (not heap allocated)
        Mosaic::MeshAttributeDataFixed<QuadMeshSemantic::Position, glm::fvec3, 4> quadPositions = {
            {0.5, 0.5},
            {-0.5, 0.5},
            {-0.5, -0.5},
            {0.5, -0.5},
        };

        // Fixed means this is static data (not heap allocated)
        Mosaic::MeshAttributeDataFixed<QuadMeshSemantic::Colour, glm::fvec4, 4> quadColours = {
            {1.0, 0.0, 0.0, 1.0},
            {0.0, 1.0, 0.0, 1.0},
            {0.0, 0.0, 1.0, 1.0},
            {0.0, 0.0, 0.0, 1.0},
        };

        Mosaic::MeshIndexingDataFixed<glm::uvec3, 2> quadIndices = {
            {0, 1, 2},
            {0, 2, 3},
        };

        auto reflect = QuadMeshDescriptor::Reflect();

        auto meshHandle = meshManager.CreateMesh<QuadMeshDescriptor>(quadIndices, quadPositions, quadColours); // user must track meshHandle, otherwise it'll go unused forever (intentional). initial data must be provided now but can be changed later. indices are optional based on if they were specified in the descriptor

        auto entityHandle = entityManager.CreateEntity<Mosaic::MeshComponent>(meshHandle);      // this entity now references the mesh
        auto otherEntityHandle = entityManager.CreateEntity<Mosaic::MeshComponent>(meshHandle); // this entity now also references the mesh (dont know why you would need to do this but you can)
    }
};

MOSAIC_DEFINE_MAIN(MosaicTest)
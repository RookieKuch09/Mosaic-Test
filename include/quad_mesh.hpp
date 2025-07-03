#pragma once

#include <Mosaic/Mosaic.hpp>

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
#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

    Mesh* CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = false);

    Mesh* CreateDiamond(const std::string &name, glm::vec3 center, float width, float height, float rectWidth,
                                    float rectHeight, glm::vec3 color, bool fill = false);

    Mesh* CreateHexagon(const std::string &name, glm::vec3 center, float height_big, float width_big, glm::vec3 color_big,
                        float height_small, float width_small, glm::vec3 color_small, bool fill = false);

    Mesh* CreateStar(const std::string &name, glm::vec3 center, float size, glm::vec3 color, bool fill = false);

}

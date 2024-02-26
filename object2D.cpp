#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(corner, color));
    vertices.push_back(VertexFormat(corner + glm::vec3(width, 0, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(width, height, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(0, height, 0), color));

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateDiamond(
    const std::string &name,
    glm::vec3 center,
    float width,
    float height,
    float rectWidth,
    float rectHeight,
    glm::vec3 color,
    bool fill)
{

    // Define the vertices for the diamond shape
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(center, color));  //0
    vertices.push_back(VertexFormat(center + glm::vec3(0, height / 2, 0), color)); //1
    vertices.push_back(VertexFormat(center + glm::vec3(width / 2, 0, 0), color)); //2
    vertices.push_back(VertexFormat(center + glm::vec3(0, -height /2, 0), color));  //3
    vertices.push_back(VertexFormat(center + glm::vec3(-width / 2, 0, 0), color));  //4

    glm::vec3 corner = glm::vec3(0, 0 - rectHeight / 2, 0);
    vertices.push_back(VertexFormat(corner, color));  //5
    vertices.push_back(VertexFormat(corner + glm::vec3(rectWidth, 0, 0), color)); //6
    vertices.push_back(VertexFormat(corner + glm::vec3(rectWidth, rectHeight, 0), color)); //7
    vertices.push_back(VertexFormat(corner + glm::vec3(0, rectHeight, 0), color)); //8


    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3,
        0,3,4,
        0,4,1,
        5,7,6,
        5,8,7
    };

    Mesh* diamond = new Mesh(name);

    // Set the draw mode based on whether it should be filled or just the outline
    if (!fill) {
        diamond->SetDrawMode(GL_LINE_LOOP); // Outline
    } else {
        diamond->SetDrawMode(GL_TRIANGLE_FAN); // Filled
    }

    diamond->InitFromData(vertices, indices);

    return diamond;
}


Mesh* object2D::CreateHexagon(
    const std::string &name,
    glm::vec3 center,
    float height_big,
    float width_big,
    glm::vec3 color_big,
    float height_small,
    float width_small,
    glm::vec3 color_small,
    bool fill)
{
    // Define the vertices for the small hexagon shape
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(center, color_small));  //0
    vertices.push_back(VertexFormat(center + glm::vec3(width_small, 0, 0), color_small)); //1
    vertices.push_back(VertexFormat(center + glm::vec3(width_small/ 2, height_small, 0), color_small)); //2
    vertices.push_back(VertexFormat(center + glm::vec3(-width_small / 2, height_small, 0), color_small));  //3
    vertices.push_back(VertexFormat(center + glm::vec3(-width_small, 0, 0), color_small));  //4
    vertices.push_back(VertexFormat(center + glm::vec3(-width_small / 2, -height_small, 0), color_small));  //5
    vertices.push_back(VertexFormat(center + glm::vec3(width_small/ 2, -height_small, 0), color_small));  //6
    // Define the vertices for the big hexagon shape
    vertices.push_back(VertexFormat(center + glm::vec3(width_big, 0, 0), color_big)); //7
    vertices.push_back(VertexFormat(center + glm::vec3(width_big / 2, height_big, 0), color_big)); //8
    vertices.push_back(VertexFormat(center + glm::vec3(-width_big / 2, height_big, 0), color_big));  //9
    vertices.push_back(VertexFormat(center + glm::vec3(-width_big, 0, 0), color_big));  //10
    vertices.push_back(VertexFormat(center + glm::vec3(-width_big / 2, -height_big, 0), color_big));  //11
    vertices.push_back(VertexFormat(center + glm::vec3(width_big / 2, -height_big, 0), color_big));  //12

    std::vector<unsigned int> indices = {
        // small hexagon
        0, 2, 1,
        0, 3, 2,
        0,4,3,
        0,5,4,
        0,6,5,
        0,1,6,
        // big hexagon
        0,8,7,
        0,9,8,
        0,10,9,
        0,11,10,
        0,12,11,
        0,7,12
    };

    Mesh* hexagon = new Mesh(name);

    // Set the draw mode based on whether it should be filled or just the outline
    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP); // Outline
    } else {
        hexagon->SetDrawMode(GL_TRIANGLE_FAN); // Filled
    }

    hexagon->InitFromData(vertices, indices);

    return hexagon;
}

Mesh* object2D::CreateStar(
    const std::string &name,
    glm::vec3 center,
    float size,
    glm::vec3 color,
    bool fill) 
{
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(center, color));  //0
    vertices.push_back(VertexFormat(center + glm::vec3(0.92 * size, 0.32 * size, 0), color)); // 1
    vertices.push_back(VertexFormat(center + glm::vec3(0.25 * size, 0.32 * size, 0), color)); //2
    vertices.push_back(VertexFormat(center + glm::vec3(0, size, 0), color));  //3
    vertices.push_back(VertexFormat(center + glm::vec3(- 0.25 * size, 0.32 * size, 0), color));  //4
    vertices.push_back(VertexFormat(center + glm::vec3(- 0.92 * size, 0.32 * size, 0), color));  //5

    vertices.push_back(VertexFormat(center + glm::vec3(-0.36 * size, -0.03 * size, 0), color)); //6
    vertices.push_back(VertexFormat(center + glm::vec3(- 0.67 * size, -0.76 * size, 0), color)); //7
    vertices.push_back(VertexFormat(center + glm::vec3(0, - 0.29 * size, 0), color)); //8 
    vertices.push_back(VertexFormat(center + glm::vec3(0.67 * size, -0.76 * size, 0), color)); //9 
    vertices.push_back(VertexFormat(center + glm::vec3(0.36 * size, -0.03 * size, 0), color)); //10 

    std::vector<unsigned int> indices = {
        0,2,1,
        0,1,10,
        0,10,9,
        0,9,8,
        0,8,7,
        0,7,6,
        0,6,5,
        0,5,4,
        0,4,3,
        0,3,2
    };

    Mesh* star = new Mesh(name);

    // Set the draw mode based on whether it should be filled or just the outline
    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP); // Outline
    } else {
        star->SetDrawMode(GL_TRIANGLE_FAN); // Filled
    }

    star->InitFromData(vertices, indices);

    return star;
}



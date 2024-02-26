#pragma once

#include "components/simple_scene.h"

struct SquareData {
    float color;  // 1 for green , 2 for red, 3 for white
    float positionX; // translate // left bottom corner
    float positionY; // translate
    std::pair<float, float> center; // center of the square
    bool occupied;

    // Constructor to initialize the struct
    SquareData(
        float color,
        float posX,
        float posY,
        std::pair<float, float> center,
        bool occupied
    )
        : color(color),
          positionX(posX),
          positionY(posY),
          center(center),
          occupied(occupied) {}
};

struct StarData {
    float color;  // 1 for orange, 2 for blue, 3 for yellow, 4 for purple
    float positionX; // translate
    float positionY; // translate
    float size;
    float angularStep; // angular step for the star
    
    // Constructor to initialize the struct
    StarData(
        float color,
        float posX,
        float posY,
        float size,
        float angularStep
    )
        : color(color),
          positionX(posX),
          positionY(posY),
          size(size),
          angularStep(angularStep) {}
};


struct DiamondData {
    float color;  // 1 for orange, 2 for blue, 3 for yellow, 4 for purple
    float positionX; // position of the center
    float positionY; // position of the center
    float scaleX;
    float scaleY;
    bool to_be_deleted; // set to true when the diamond need to be deleted
    int nedeed_stars; // how many stars do you need for using a diamond (1, 2 or 3)
    std::vector<StarData> proiectiles;

    // Constructor to initialize the struct
    DiamondData(
        float color,
        float posX,
        float posY,
        float scaleX,
        float scaleY,
        bool to_be_deleted,
        int needed_stars
    )
        : color(color),
          positionX(posX),
          positionY(posY),
          scaleX(scaleX),
          scaleY(scaleY),
          to_be_deleted(to_be_deleted),
          nedeed_stars(needed_stars) {}
};

struct HexagonData {
    float color;  // 1 for orange, 2 for blue, 3 for yellow, 4 for purple
    float positionX; // position of the center
    float positionY; // position of the center
    int lives; // 3 lives initially
    float scaleX;
    float scaleY;
    bool to_be_deleted; // set to true when the diamond need to be deleted

    // Constructor to initialize the struct
    HexagonData(
        float color,
        float posX,
        float posY,
        int lives,
        float scaleX,
        float scaleY,
        bool to_be_deleted
    )
        : color(color),
          positionX(posX),
          positionY(posY),
          lives(lives),
          scaleX(scaleX),
          scaleY(scaleY),
          to_be_deleted(to_be_deleted) {}
};

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        glm::mat3 modelMatrix;
        int elapsedTime;  // Keep track of elapsed time
        int score;  // Keep track of score
        float radius_star; // radius of the star (for points and for proiectiles)
        float radius_hexagon; // radius of the hexagon (the big one)
        float radius_diamond; // radius of the diamond
        int lives; // lives of the player
        bool drag; // if the player is currently dragging a diamond
        std::vector<SquareData> squares;
        std::vector<DiamondData> diamonds;
        std::vector<DiamondData> diamonds_in_action;
        std::vector<HexagonData> hexagons;
        std::vector<StarData> point_stars; // random stars that give points
        std::vector<int> status_squares; // true means is occupied

    };
}   // namespace m1

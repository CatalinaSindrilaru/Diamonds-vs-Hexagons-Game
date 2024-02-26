#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

float distance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

std::pair<float, float> center_square(float x, float y, int size) {
    float x_center = x + size / 2;
    float y_center = y + size / 2;
    return make_pair(x_center, y_center);
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    
    //------------------------------------SQUARES--------------------------------------------
    Mesh* life_square_mesh = object2D::CreateSquare("life_square_mesh", glm::vec3(0, 0, 0), 70,
                                                     glm::vec3(0.7, 0.3, 0.5), true);
    Mesh* grid_square_mesh = object2D::CreateSquare("grid_square_mesh", glm::vec3(0, 0, 0),
                                                     100, glm::vec3(0.7, 0.5, 0.6), true);
    Mesh* white_square_mesh = object2D::CreateSquare("white_square_mesh", glm::vec3(0, 0, 0),
                                                     100, glm::vec3(1, 1, 1), false);

    AddMeshToList(life_square_mesh);
    AddMeshToList(grid_square_mesh);
    AddMeshToList(white_square_mesh);

    // add grid squares to the vector of squares
    squares.push_back(SquareData(1, 100, 20,center_square(100, 20, 100), false));
    squares.push_back(SquareData(1, 240, 20, center_square(240, 20, 100), false));
    squares.push_back(SquareData(1, 380, 20, center_square(380, 20, 100), false));
    squares.push_back(SquareData(1, 100, 160, center_square(100, 160, 100), false));
    squares.push_back(SquareData(1, 240, 160, center_square(240, 160, 100), false));
    squares.push_back(SquareData(1, 380, 160, center_square(380, 160, 100), false));
    squares.push_back(SquareData(1, 100, 300, center_square(100, 300, 100), false));
    squares.push_back(SquareData(1, 240, 300, center_square(240, 300, 100), false));
    squares.push_back(SquareData(1, 380, 300, center_square(380, 300, 100), false));

    // add white squares to the vector of squares
    squares.push_back(SquareData(3, 70, 600, center_square(70, 600, 70), false));
    squares.push_back(SquareData(3, 240, 600, center_square(240, 600, 70), false));
    squares.push_back(SquareData(3, 410, 600, center_square(410, 600, 70), false));
    squares.push_back(SquareData(3, 580, 600, center_square(580, 600, 70), false));

    //------------------------------------- RECTANGLES----------------------------------------------
    Mesh* rectangle_mesh = object2D::CreateRectangle("rectangle_mesh", glm::vec3(0, 0, 0),
                                                 60, 380, glm::vec3(0.7, 0.3, 0.5), true);
    AddMeshToList(rectangle_mesh);

    //-------------------------------------- DIAMONDS---------------------------------------------
    Mesh *orange_diamond_mesh = object2D::CreateDiamond("orange_diamond_mesh", glm::vec3(0, 0, 3),
                                     40, 80, 40, 30, glm::vec3(0.9, 0.5, 0), true);
    Mesh *blue_diamond_mesh = object2D::CreateDiamond("blue_diamond_mesh", glm::vec3(0, 0, 3), 40,
                                     80, 40, 30, glm::vec3(0, 0, 0.9), true);
    Mesh *yellow_diamond_mesh = object2D::CreateDiamond("yellow_diamond_mesh", glm::vec3(0, 0, 3),
                                     40, 80, 40, 30, glm::vec3(0.9, 0.9, 0), true);
    Mesh *purple_diamond_mesh = object2D::CreateDiamond("purple_diamond_mesh", glm::vec3(0, 0, 3),
                                     40, 80, 40, 30, glm::vec3(0.5, 0, 0.5), true);

    AddMeshToList(orange_diamond_mesh);
    AddMeshToList(blue_diamond_mesh);
    AddMeshToList(yellow_diamond_mesh);
    AddMeshToList(purple_diamond_mesh);

    // add the 4 diamonds presented in the top of the screen to the vector of diamonds
    diamonds.push_back(DiamondData(1, 120, 650, 1, 1,false, 1));
    diamonds.push_back(DiamondData(2, 290, 650, 1, 1, false, 2));
    diamonds.push_back(DiamondData(3, 460, 650, 1, 1, false, 2));
    diamonds.push_back(DiamondData(4, 630, 650, 1, 1, false, 3));

    //---------------------------------------------- HEXAGONS-----------------------------------------------
    Mesh* orange_hexagon_mesh = object2D::CreateHexagon("orange_hexagon_mesh", glm::vec3(0, 0, 0), 25, 30,
                                        glm::vec3(0.9, 0.5, 0.2), 15, 20, glm::vec3(1, 0.7, 0.8), true);

    Mesh* blue_hexagon_mesh = object2D::CreateHexagon("blue_hexagon_mesh", glm::vec3(0, 0, 0), 25, 30,
                                        glm::vec3(0.1, 0.4, 0.9), 15, 20, glm::vec3(1, 0.7, 0.8), true);

    Mesh* yellow_hexagon_mesh = object2D::CreateHexagon("yellow_hexagon_mesh", glm::vec3(0, 0, 0), 25, 30,
                                        glm::vec3(1, 0.9, 0.2), 15, 20, glm::vec3(1, 0.7, 0.8), true);

    Mesh* purple_hexagon_mesh = object2D::CreateHexagon("purple_hexagon_mesh", glm::vec3(0, 0, 0), 25, 30,
                                        glm::vec3(0.5, 0, 0.5), 15, 20, glm::vec3(1, 0.7, 0.8), true);

    AddMeshToList(orange_hexagon_mesh);
    AddMeshToList(blue_hexagon_mesh);
    AddMeshToList(yellow_hexagon_mesh);
    AddMeshToList(purple_hexagon_mesh);

    //------------------------------------------ STARS------------------------------------------------------
    Mesh* pink_star_mesh = object2D::CreateStar("pink_star_mesh",glm::vec3(0, 0, 0), 15,
                                             glm::vec3(1, 0.7, 0.8), true);
    Mesh *point_star_mesh = object2D::CreateStar("point_star_mesh", glm::vec3(0, 0, 4), 27,
                                             glm::vec3(0.9, 0.1, 0.7), true);
    Mesh *proiectile_orange_star_mesh = object2D::CreateStar("proiectile_orange_star_mesh",
                                         glm::vec3(0, 0, 4), 27, glm::vec3(0.9, 0.5, 0), true);
    Mesh *proiectile_blue_star_mesh = object2D::CreateStar("proiectile_blue_star_mesh",
                                             glm::vec3(0, 0, 4), 27, glm::vec3(0, 0, 0.9), true);
    Mesh *proiectile_yellow_star_mesh = object2D::CreateStar("proiectile_yellow_star_mesh",
                                         glm::vec3(0, 0, 4), 27, glm::vec3(0.9, 0.9, 0), true);
    Mesh *proiectile_purple_star_mesh = object2D::CreateStar("proiectile_purple_star_mesh",
                                          glm::vec3(0, 0, 4), 27, glm::vec3(0.5, 0, 0.5), true);

    AddMeshToList(pink_star_mesh);
    AddMeshToList(point_star_mesh);
    AddMeshToList(proiectile_orange_star_mesh);
    AddMeshToList(proiectile_blue_star_mesh);
    AddMeshToList(proiectile_yellow_star_mesh);
    AddMeshToList(proiectile_purple_star_mesh);

    radius_star = 27;
    radius_hexagon = 30;
    radius_diamond = 40;

    elapsedTime = 0;
    score = 5; // intial number of stars (points) displayed below the number of lives
    lives = 3; // intitial number of lives of the player
    drag = false; // status of the dragging action
    status_squares = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // if a grid square is occupied or not
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
    // close the window if the player has no more lives
    if (lives <= 0) {
        window->Close();
    }

    elapsedTime += 1;

    //------------------------------------- HEXAGONS ACTIONS -----------------------------------------

    if (elapsedTime % 400 == 1) {
        // Generates a random index (0, 1, or 2) for the yValues array
        int randomIndex = rand() % 3;
        int yValues[] = {70, 210, 350};
        int randomY = yValues[randomIndex];

        // type of the hexagon (color 1, 2, 3, 4) where 1 = orange, 2 = blue, 3 = yellow, 4 = purple
        int color_hexagon = (rand() % 4) + 1;

        // 1300 is the right margin of the screen and 3 is the initial number of lives
        if (color_hexagon == 1) {
            hexagons.push_back(HexagonData(1, 1300, randomY, 3, 1, 1, false));
        } else if (color_hexagon == 2) {
            hexagons.push_back(HexagonData(2, 1300, randomY, 3, 1, 1, false));
        } else if (color_hexagon == 3) {
            hexagons.push_back(HexagonData(3, 1300, randomY, 3, 1, 1, false));
        } else {
            hexagons.push_back(HexagonData(4, 1300, randomY, 3, 1, 1, false));
        }
    }

    // Update the position of each hexagon in the vector
    for (int i = 0; i < hexagons.size(); i++) {
        hexagons[i].positionX -= 60.0f * deltaTimeSeconds;

        // Check if the hexagon has reached x = 80 (the red rectangular)
        if (hexagons[i].positionX <= 80) {
            // Remove the hexagon from the vector when it reaches x = 80
            // and decrease the number of lives of the player
            hexagons.erase(hexagons.begin() + i); 
            lives--;
        }
    }
    
    for (const auto& hexagon : hexagons) {
        modelMatrix = glm::mat3(1);

        modelMatrix *= transform2D::Translate(hexagon.positionX, hexagon.positionY);
        modelMatrix *= transform2D::Scale(hexagon.scaleX, hexagon.scaleY);


        if (hexagon.color == 1) {
            RenderMesh2D(meshes["orange_hexagon_mesh"], shaders["VertexColor"], modelMatrix);
        } else if (hexagon.color == 2) {
            RenderMesh2D(meshes["blue_hexagon_mesh"], shaders["VertexColor"], modelMatrix);
        } else if (hexagon.color == 3) {
            RenderMesh2D(meshes["yellow_hexagon_mesh"], shaders["VertexColor"], modelMatrix);
        } else {
            RenderMesh2D(meshes["purple_hexagon_mesh"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Verify if a hexagon need to be deleted
    for (int i = 0; i < hexagons.size(); i++) {
        if (hexagons[i].to_be_deleted) {

            // create animation before delete the hexagon
            hexagons[i].scaleX -= 2.0f * deltaTimeSeconds;
            hexagons[i].scaleY -= 2.0f * deltaTimeSeconds;
    
            if (hexagons[i].scaleX <= 0 && hexagons[i].scaleY <= 0) {
                hexagons.erase(hexagons.begin() + i);
            }
        }
    }

    //----------------------------------- SQUARES ACTIONS --------------------------------------------//

    // Render grid and white squares
    for (const auto& square : squares) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(square.positionX, square.positionY);

        if (square.color == 1) {
            RenderMesh2D(meshes["grid_square_mesh"], shaders["VertexColor"], modelMatrix);
        } else {
            RenderMesh2D(meshes["white_square_mesh"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Lives of the player (red squares)
    if (lives > 0) {
        for (int i = 0; i < lives; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(730 + i * 100, 610);
            RenderMesh2D(meshes["life_square_mesh"], shaders["VertexColor"], modelMatrix);
        }
    }

    //----------------------------------- RED RECTANGULAR --------------------------------------------//

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(10, 20);
    RenderMesh2D(meshes["rectangle_mesh"], shaders["VertexColor"], modelMatrix);

    //----------------------------------- DIAMONDS ACTIONS --------------------------------------------------------//

    // Render the 4 diamonds presented in the top of the screen
    for (const auto& diamond : diamonds) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(diamond.positionX, diamond.positionY);

        if (diamond.color == 1) {
            RenderMesh2D(meshes["orange_diamond_mesh"], shaders["VertexColor"], modelMatrix);
        } else if (diamond.color == 2) {
            RenderMesh2D(meshes["blue_diamond_mesh"], shaders["VertexColor"], modelMatrix);
        } else if (diamond.color == 3) {
            RenderMesh2D(meshes["yellow_diamond_mesh"], shaders["VertexColor"], modelMatrix);
        } else {
            RenderMesh2D(meshes["purple_diamond_mesh"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Render the diamonds that are in action (inside of the grid squares) or that are dragged
    for (const auto& diamond : diamonds_in_action) {
        modelMatrix = glm::mat3(1);

        modelMatrix *= transform2D::Translate(diamond.positionX, diamond.positionY);
        modelMatrix *= transform2D::Scale(diamond.scaleX, diamond.scaleY);

        if (diamond.color == 1) {
            RenderMesh2D(meshes["orange_diamond_mesh"], shaders["VertexColor"], modelMatrix);
        } else if (diamond.color == 2) {
            RenderMesh2D(meshes["blue_diamond_mesh"], shaders["VertexColor"], modelMatrix);
        } else if (diamond.color == 3) {
            RenderMesh2D(meshes["yellow_diamond_mesh"], shaders["VertexColor"], modelMatrix);
        } else {
            RenderMesh2D(meshes["purple_diamond_mesh"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Verify if the diamond needs to be deleted, then scale it down until it disappears
    // and remove it from the vector
    for (int i = 0; i < diamonds_in_action.size(); i++) {
        if (diamonds_in_action[i].to_be_deleted) {

            diamonds_in_action[i].scaleX -= 2.0f * deltaTimeSeconds;
            diamonds_in_action[i].scaleY -= 2.0f * deltaTimeSeconds;
    
            if (diamonds_in_action[i].scaleX <= 0 && diamonds_in_action[i].scaleY <= 0) {
                diamonds_in_action.erase(diamonds_in_action.begin() + i);
            }
        }
    }

    // verify if a diamond in action is in collision with an enemy (no matter the color, just to be
    // on the same line) and if so, delete the diamond
    for (int i = 0; i < diamonds_in_action.size(); i++) {

        for (const auto& hexagon : hexagons) {
            if (diamonds_in_action[i].positionY == hexagon.positionY) { // same line

                float distance_between = distance(diamonds_in_action[i].positionX, diamonds_in_action[i].positionY, 
                                                        hexagon.positionX, hexagon.positionY);

                if (distance_between < 50) {  // collision occurs
                    diamonds_in_action[i].to_be_deleted = true;
                }

            }
        }
    }

    // Throw proiectiles from the diamonds in action if there is an enemy on the same line
    for (auto& diamond : diamonds_in_action) {
        int row = diamond.positionY;
        float color = diamond.color;
        bool enemy_exist = false;

        // Verify if a hexagon with the same color exists on the same line with the diamond
        for (int i = 0; i < hexagons.size(); i++) {
            if (hexagons[i].positionY == row && hexagons[i].color == color) {
                enemy_exist = true;
                break;
            }
        }

        // If exists, turn on the proiectiles
        if (enemy_exist) {  
            // Add the first proiectile
            if (diamond.proiectiles.size() == 0) {
                diamond.proiectiles.push_back(StarData(diamond.color, diamond.positionX, diamond.positionY, 10, 0));
            } else {
                // If the distance between the last proiectile and the diamond is greater than 200, add another proiectile
                int size_p = diamond.proiectiles.size();
                int actual_distance = distance(diamond.positionX, diamond.positionY, diamond.proiectiles[size_p - 1].positionX,
                                                 diamond.proiectiles[size_p - 1].positionY);

                if (actual_distance >= 200) {
                    diamond.proiectiles.push_back(StarData(diamond.color, diamond.positionX, diamond.positionY, 10, 0));

                }
            }
        }
    }

    // Render the proiectiles (stars of the same color with the diamond that throw them)
    for (auto& diamond : diamonds_in_action) {
        for (auto& proiectile : diamond.proiectiles) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(proiectile.positionX, proiectile.positionY);

            proiectile.angularStep -= 0.8 * deltaTimeSeconds;
            modelMatrix *= transform2D::Rotate(proiectile.angularStep);

            
            if (proiectile.color == 1) {
                RenderMesh2D(meshes["proiectile_orange_star_mesh"], shaders["VertexColor"], modelMatrix);
            } else if (proiectile.color == 2) {
                RenderMesh2D(meshes["proiectile_blue_star_mesh"], shaders["VertexColor"], modelMatrix);
            } else if (proiectile.color == 3) {
                RenderMesh2D(meshes["proiectile_yellow_star_mesh"], shaders["VertexColor"], modelMatrix);
            } else {
                RenderMesh2D(meshes["proiectile_purple_star_mesh"], shaders["VertexColor"], modelMatrix);
            }
        }
    }

    // Update the position of the proiectiles and verify if a collision occurs with a hexagon
    // of the same color
    for (auto& diamond : diamonds_in_action) {
        for (int i = 0; i < diamond.proiectiles.size(); i++) {
            // update the position of the proiectile
            diamond.proiectiles[i].positionX += 150.0f * deltaTimeSeconds;

            // verify if a collision occurs with a hexagon of the same color
            for (auto& hexagon : hexagons) {
                if (diamond.proiectiles[i].color == hexagon.color && diamond.proiectiles[i].positionY == hexagon.positionY) {
                    // the distance between the center of the proiectile and the center of the hexagon
                    // needs to be smaller than the radius of the star + the radius of the hexagon
                    // to be considered collision   
                    float distance_between = distance(diamond.proiectiles[i].positionX, diamond.proiectiles[i].positionY, 
                                                        hexagon.positionX, hexagon.positionY);

                    if (distance_between < radius_star + radius_hexagon) { // collision occurs
                        // delete the current proiectile and decrease the number of lives for the hexagon
                        diamond.proiectiles.erase(diamond.proiectiles.begin() + i);
                        hexagon.lives--;

                        // delete the hexagon if it remains without lives
                        if (hexagon.lives == 0) {
                            // delete the hexagon
                            hexagon.to_be_deleted = true;
                        }

                    }
                    
                }
            }
        }
    }


    //----------------------------------- STARS -----------------------------------------------------------//
    RenderMesh2D(meshes["pink_star_mesh"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(80, 585)); // orange
    RenderMesh2D(meshes["pink_star_mesh"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(250, 585)); // blue
    RenderMesh2D(meshes["pink_star_mesh"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(280, 585)); // blue
    RenderMesh2D(meshes["pink_star_mesh"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(420, 585)); // yellow
    RenderMesh2D(meshes["pink_star_mesh"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(450, 585)); // yellow
    RenderMesh2D(meshes["pink_star_mesh"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(590, 585)); // purple
    RenderMesh2D(meshes["pink_star_mesh"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(620, 585)); //purple
    RenderMesh2D(meshes["pink_star_mesh"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(650, 585)); //purple

    // put the points on different lines if the number is grater than 15
    int starsPerLine = 15;
    int totalStars = score;
    
    for (int line = 0; totalStars > 0; line++) {
        int starsOnThisLine = std::min(starsPerLine, totalStars);
        totalStars -= starsOnThisLine;

        for (int i = 0; i < starsOnThisLine; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(740 + i * 30, 590 - line * 30);
            RenderMesh2D(meshes["pink_star_mesh"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Random stars that appears on the screen (points to be collected)
    if (elapsedTime % 800 == 1) {
        int randomX_star1 = rand() % 1100 + 20;
        int randomY_star1 = rand() % 600 + 20;
        point_stars.push_back(StarData(1, randomX_star1, randomY_star1, 10, 0));

        int randomX_star2 = rand() % 110 + 20;
        int randomY_star2 = rand() % 600 + 20;
        point_stars.push_back(StarData(1, randomX_star2, randomY_star2, 10, 0));

        int randomX_star3 = rand() % 1100 + 20;
        int randomY_star3 = rand() % 600 + 20;
        point_stars.push_back(StarData(1, randomX_star3, randomY_star3, 10, 0));
    }

    // Render the random stars
    for (const auto& star : point_stars) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(star.positionX, star.positionY);
        RenderMesh2D(meshes["point_star_mesh"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
}


void Tema1::OnKeyRelease(int key, int mods)
{
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{   
    if (drag) {
    // move the last diamond added (the one currently dragged)
        int size = diamonds_in_action.size();
        diamonds_in_action[size - 1].positionX += deltaX;
        diamonds_in_action[size - 1].positionY -= deltaY;
    }
 }

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // get the mouse position in the scene
    int x_scene_mouse = mouseX;
    int y_scene_mouse = 720 - mouseY;

    // verify if the left button of the mouse was pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        //Check if the click was inside a star
        for (int i = 0; i < point_stars.size(); i++) {
            if (distance(x_scene_mouse, y_scene_mouse, point_stars[i].positionX,
                             point_stars[i].positionY) <= radius_star) {
                point_stars.erase(point_stars.begin() + i);
                score++;
            }
        }

        // Check if the click was inside a diamond
        for (int i = 0; i < diamonds.size(); i++) {
            if (distance(x_scene_mouse, y_scene_mouse, diamonds[i].positionX, diamonds[i].positionY) <= radius_diamond) {
                // first check if the player has enough stars to take the diamond
                if (score >= diamonds[i].nedeed_stars) {
                    score -= diamonds[i].nedeed_stars;
                } else {
                    break;
                }
                // add the diamond to the vector of diamonds in action and activate the drag action
                diamonds_in_action.push_back(DiamondData(diamonds[i].color, diamonds[i].positionX, diamonds[i].positionY,
                                             1, 1, false, diamonds[i].nedeed_stars));
                drag = true; // if a dragging is made 
                break;
            }
        }
    }

    // verify if the right button of the mouse was pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        // Verify if the click was inside an occupied grid square and if so, delete the diamond
        for (int i = 0; i < squares.size(); i++) {
            if (squares[i].color == 1) {
                if ((x_scene_mouse >= squares[i].center.first - 50 && x_scene_mouse <= squares[i].center.first + 50)
                    && (y_scene_mouse <= squares[i].center.second + 50 && y_scene_mouse >= squares[i].center.second - 50)
                    && status_squares[i] == 1) {

                    for (int j = 0; j < diamonds_in_action.size(); j++) {
                        if (diamonds_in_action[j].positionX == squares[i].center.first 
                            && diamonds_in_action[j].positionY == squares[i].center.second) {
                            
                            diamonds_in_action[j].to_be_deleted = true;
                            status_squares[i] = 0; // free
                            break;
                        }
                    }  
                }
            }
        }
        
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (drag) {
        drag = false;

        int x_scene_mouse = mouseX;
        int y_scene_mouse = 720 - mouseY;

        int size = diamonds_in_action.size();

        int drop = false;
        
        for (int i = 0; i < squares.size(); i++) {
                if (squares[i].color == 1) {
                    // verify if the mouse was release inside a  grid square
                    if ((x_scene_mouse >= squares[i].center.first - 50 && x_scene_mouse <= squares[i].center.first + 50)
                        && (y_scene_mouse <= squares[i].center.second + 50 && y_scene_mouse >= squares[i].center.second - 50)
                        && status_squares[i] == 0) {
                            diamonds_in_action[size - 1].positionX = squares[i].center.first;
                            diamonds_in_action[size - 1].positionY = squares[i].center.second;
                            status_squares[i] = 1; // occupied
                            drop = true;
                            break;  
                        }
                }
        }

        if (drop == false) { // remove the diamond if was not placed inside a grid square
            diamonds_in_action.erase(diamonds_in_action.begin() + size - 1);
        }
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

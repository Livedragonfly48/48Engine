#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "../../../PseudoEngineModules/ModulesLowLevel/Render/Render.h"
#include "../../../PseudoEngineModules/ModulesLowLevel/Input/Input.h"
#include "../../../PseudoEngineModules/ModulesLowLevel/Math/Vec2.h"
#include "../../../PseudoEngineModules/ModulesLowLevel/Math/MathUtils.h"
#include "../../../PseudoEngineModules/ModulesLowLevel/Physics/PhysicsBody.h"
#include "../../../PseudoEngineModules/ModulesLowLevel/Physics/PhysicsSystem.h"
#include "../../../PseudoEngineModules/ModulesLowLevel/Collision/CollisionSystem.h"








// --- Inspector / Configuración ---
struct GameConfig {
    int AnchoDePantalla = 800;
    int AlturaDePantalla = 600;

    float AnchoDeRaquetas = 20.0f;
    float AltoDeRaquetas = 100.0f;
    float RadioDeLaBola = 10.0f;

    float VelocidadDeLasRaquetas = 400.0f;
    float VelocidadDeLaBola = 400.0f;
    float AumentoDeVelocidad = 250.0f;
    float TiempoEntreAumentoDeVelocidad = 5.0f; // seg

    SDL_Color ColorDePlayer1 = { 255, 255, 255, 255 };
    SDL_Color ColorDePlayer2 = { 255, 255, 255, 255 };
    SDL_Color ColorDeLaBola = { 255, 0, 0, 255 };
    SDL_Color ColorDelFondo = { 0, 0, 0, 255 };
    SDL_Color ColorDelScore = { 0, 255, 0, 255 };
};
GameConfig g_Config;















// --- Globales ---
Render g_Render;
PhysicsSystem g_Physics;

PhysicsBody* leftPaddle;
PhysicsBody* rightPaddle;
PhysicsBody* ball;
SDL_Texture* ballTexture = nullptr; // TEXTURA DE LA PELOTA


int leftScore = 0;
int rightScore = 0;
float timeSinceLastPoint = 0.0f;

// --- Nums para marcador ---
const int digitPatterns[10][5][3] = {
    {{1,1,1},{1,0,1},{1,0,1},{1,0,1},{1,1,1}}, // 0
    {{0,1,0},{1,1,0},{0,1,0},{0,1,0},{1,1,1}}, // 1
    {{1,1,1},{0,0,1},{1,1,1},{1,0,0},{1,1,1}}, // 2
    {{1,1,1},{0,0,1},{0,1,1},{0,0,1},{1,1,1}}, // 3
    {{1,0,1},{1,0,1},{1,1,1},{0,0,1},{0,0,1}}, // 4
    {{1,1,1},{1,0,0},{1,1,1},{0,0,1},{1,1,1}}, // 5
    {{1,1,1},{1,0,0},{1,1,1},{1,0,1},{1,1,1}}, // 6
    {{1,1,1},{0,0,1},{0,1,0},{1,0,0},{1,0,0}}, // 7
    {{1,1,1},{1,0,1},{1,1,1},{1,0,1},{1,1,1}}, // 8
    {{1,1,1},{1,0,1},{1,1,1},{0,0,1},{1,1,1}}  // 9
};
const int colonPattern[5][1] = { {0},{1},{0},{1},{0} };

// --- Funciones marcador ---
void DrawDigit(int number, int x, int y, int size, SDL_Renderer* renderer) {
    if (number < 0) number = 0;
    if (number > 9) number = 9;

    for (int row = 0; row < 5; ++row)
        for (int col = 0; col < 3; ++col)
            if (digitPatterns[number][row][col])
                SDL_RenderFillRect(renderer, &SDL_Rect{ x + col * size, y + row * size, size, size });
}

void DrawColon(int x, int y, int size, SDL_Renderer* renderer) {
    for (int row = 0; row < 5; ++row)
        if (colonPattern[row][0])
            SDL_RenderFillRect(renderer, &SDL_Rect{ x, y + row * size, size, size });
}

void DrawScore(int left, int right, int startX, int startY, int blockSize, SDL_Renderer* renderer) {
    int spacing = 5;
    int digitSpacing = blockSize * 3 + spacing;

    DrawDigit(left / 10, startX, startY, blockSize, renderer);
    DrawDigit(left % 10, startX + digitSpacing, startY, blockSize, renderer);

    DrawColon(startX + 2 * digitSpacing + spacing, startY, blockSize, renderer);

    DrawDigit(right / 10, startX + 2 * digitSpacing + spacing + blockSize + 10, startY, blockSize, renderer);
    DrawDigit(right % 10, startX + 3 * digitSpacing + spacing + blockSize + 10, startY, blockSize, renderer);
}

// --- Funciones físicas ---
void ResetBall() {
    ball->position = Vec2(g_Config.AnchoDePantalla / 2.0f, g_Config.AlturaDePantalla / 2.0f);
    ball->velocity = Vec2((rand() % 2 ? 1.0f : -1.0f) * g_Config.VelocidadDeLaBola,
        ((rand() % 2 ? 1.0f : -1.0f) * g_Config.VelocidadDeLaBola / 2.0f));
    ball->updateColliderPosition();
    timeSinceLastPoint = 0.0f;
}

void Update(float deltaTime) {
    // Input paddles
    if (Input::IsKeyHeld(SDL_SCANCODE_W)) leftPaddle->position.y -= g_Config.VelocidadDeLasRaquetas * deltaTime;
    if (Input::IsKeyHeld(SDL_SCANCODE_S)) leftPaddle->position.y += g_Config.VelocidadDeLasRaquetas * deltaTime;
    if (Input::IsKeyHeld(SDL_SCANCODE_UP)) rightPaddle->position.y -= g_Config.VelocidadDeLasRaquetas * deltaTime;
    if (Input::IsKeyHeld(SDL_SCANCODE_DOWN)) rightPaddle->position.y += g_Config.VelocidadDeLasRaquetas * deltaTime;

    leftPaddle->position.y = Clamp(leftPaddle->position.y, g_Config.AltoDeRaquetas / 2.0f, g_Config.AlturaDePantalla - g_Config.AltoDeRaquetas / 2.0f);
    rightPaddle->position.y = Clamp(rightPaddle->position.y, g_Config.AltoDeRaquetas / 2.0f, g_Config.AlturaDePantalla - g_Config.AltoDeRaquetas / 2.0f);

    leftPaddle->updateColliderPosition();
    rightPaddle->updateColliderPosition();

    g_Physics.update(deltaTime);

    // Colisiones pared
    if (ball->position.y - g_Config.RadioDeLaBola <= 0.0f) {
        ball->position.y = g_Config.RadioDeLaBola;
        ball->velocity.y *= -1.0f;
    }
    if (ball->position.y + g_Config.RadioDeLaBola >= g_Config.AlturaDePantalla) {
        ball->position.y = g_Config.AlturaDePantalla - g_Config.RadioDeLaBola;
        ball->velocity.y *= -1.0f;
    }

    // Colisiones paddles
    CollisionResult resLeft = AABBvsCircle(leftPaddle->aabb, ball->circle);
    if (resLeft.collided) {
        ball->position.x = leftPaddle->aabb.Max().x + g_Config.RadioDeLaBola;
        ball->velocity.x = fabsf(ball->velocity.x);
    }

    CollisionResult resRight = AABBvsCircle(rightPaddle->aabb, ball->circle);
    if (resRight.collided) {
        ball->position.x = rightPaddle->aabb.Min().x - g_Config.RadioDeLaBola;
        ball->velocity.x = -fabsf(ball->velocity.x);
    }

    // Puntos
    if (ball->position.x - g_Config.RadioDeLaBola <= 0.0f) { rightScore++; ResetBall(); }
    if (ball->position.x + g_Config.RadioDeLaBola >= g_Config.AnchoDePantalla) { leftScore++; ResetBall(); }

    // Aumentar velocidad si nadie anota
    timeSinceLastPoint += deltaTime;
    if (timeSinceLastPoint >= g_Config.TiempoEntreAumentoDeVelocidad) {
        float signX = (ball->velocity.x >= 0.0f) ? 1.0f : -1.0f;
        float signY = (ball->velocity.y >= 0.0f) ? 1.0f : -1.0f;
        ball->velocity.x += signX * g_Config.AumentoDeVelocidad * deltaTime;
        ball->velocity.y += signY * g_Config.AumentoDeVelocidad * deltaTime;
    }

    ball->updateColliderPosition();
}

void RenderScene() {
    g_Render.clear();
    SDL_Renderer* renderer = g_Render.getRenderer();

    // Fondo
    SDL_SetRenderDrawColor(renderer, g_Config.ColorDelFondo.r, g_Config.ColorDelFondo.g, g_Config.ColorDelFondo.b, g_Config.ColorDelFondo.a);
    SDL_RenderClear(renderer);

    // Paddles
    SDL_SetRenderDrawColor(renderer, g_Config.ColorDePlayer1.r, g_Config.ColorDePlayer1.g, g_Config.ColorDePlayer1.b, g_Config.ColorDePlayer1.a);
    SDL_RenderFillRect(renderer, &SDL_Rect{ (int)(leftPaddle->position.x - g_Config.AnchoDeRaquetas / 2), (int)(leftPaddle->position.y - g_Config.AltoDeRaquetas / 2), (int)g_Config.AnchoDeRaquetas, (int)g_Config.AltoDeRaquetas });
    SDL_SetRenderDrawColor(renderer, g_Config.ColorDePlayer2.r, g_Config.ColorDePlayer2.g, g_Config.ColorDePlayer2.b, g_Config.ColorDePlayer2.a);
    SDL_RenderFillRect(renderer, &SDL_Rect{ (int)(rightPaddle->position.x - g_Config.AnchoDeRaquetas / 2), (int)(rightPaddle->position.y - g_Config.AltoDeRaquetas / 2), (int)g_Config.AnchoDeRaquetas, (int)g_Config.AltoDeRaquetas });

    // Pelota con su tex
    if (ballTexture) {
        g_Render.drawTexture(ballTexture,
            (int)(ball->position.x - g_Config.RadioDeLaBola),
            (int)(ball->position.y - g_Config.RadioDeLaBola),
            (int)(g_Config.RadioDeLaBola * 2),
            (int)(g_Config.RadioDeLaBola * 2));
    }
    else { 
        SDL_SetRenderDrawColor(renderer, g_Config.ColorDeLaBola.r, g_Config.ColorDeLaBola.g, g_Config.ColorDeLaBola.b, g_Config.ColorDeLaBola.a);
        SDL_Rect ballRect = { (int)(ball->position.x - g_Config.RadioDeLaBola), (int)(ball->position.y - g_Config.RadioDeLaBola), (int)(g_Config.RadioDeLaBola * 2), (int)(g_Config.RadioDeLaBola * 2) };
        SDL_RenderFillRect(renderer, &ballRect);
    }


    // Marcador
    SDL_SetRenderDrawColor(renderer, g_Config.ColorDelScore.r, g_Config.ColorDelScore.g, g_Config.ColorDelScore.b, g_Config.ColorDelScore.a);
    int scoreX = g_Config.AnchoDePantalla / 2 - 50;
    int scoreY = 20;
    int blockSize = 10;
    DrawScore(leftScore, rightScore, scoreX, scoreY, blockSize, renderer);

    g_Render.present();
}

// --- Main ---
int main(int argc, char* argv[]) {
    std::cout << "Tennis for Two iniciado!" << std::endl;

    Input::Init();
    if (!g_Render.init("Tennis for Two", g_Config.AnchoDePantalla, g_Config.AlturaDePantalla)) {
        SDL_Log("No se pudo inicializar Render!");
        return -1;
    }

    // Cargar textura de la bola
    ballTexture = g_Render.loadTexture("C:\\Users\\OctoPC\\Documents\\Ilann Emilio Maya Campos___GitHub\\48Engine\\PseudoEngine48 - Motor\\PseudoEngine\\PseudoEngineProjects\\TennisF2\\Assets\\Textures\\bola.png");
    if (!ballTexture) {
        SDL_Log("No se pudo cargar la textura de la bola, se usará rectángulo");
    }

    // Crear paddles
    leftPaddle = new PhysicsBody(ColliderType::AABB);
    leftPaddle->setAABB(Vec2(50.0f, g_Config.AlturaDePantalla / 2.0f), Vec2(g_Config.AnchoDeRaquetas / 2, g_Config.AltoDeRaquetas / 2));
    leftPaddle->useGravity = false;
    rightPaddle = new PhysicsBody(ColliderType::AABB);
    rightPaddle->setAABB(Vec2(g_Config.AnchoDePantalla - 50.0f, g_Config.AlturaDePantalla / 2.0f), Vec2(g_Config.AnchoDeRaquetas / 2, g_Config.AltoDeRaquetas / 2));
    rightPaddle->useGravity = false;

    // Crear pelota
    ball = new PhysicsBody(ColliderType::Circle);
    ball->setCircle(Vec2(g_Config.AnchoDePantalla / 2.0f, g_Config.AlturaDePantalla / 2.0f), g_Config.RadioDeLaBola);
    ball->useGravity = false;
    ball->velocity = Vec2(g_Config.VelocidadDeLaBola, g_Config.VelocidadDeLaBola / 2.0f);

    g_Physics.addBody(leftPaddle);
    g_Physics.addBody(rightPaddle);
    g_Physics.addBody(ball);

    bool isRunning = true;
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (isRunning) {
        Input::ProcessEvents();
        if (Input::IsKeyPressed(SDL_SCANCODE_ESCAPE)) isRunning = false;

        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        Update(deltaTime);
        RenderScene();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    delete leftPaddle;
    delete rightPaddle;
    delete ball;

    if (ballTexture) SDL_DestroyTexture(ballTexture);

    g_Render.destroy();
    Input::Shutdown();
    return 0;
}


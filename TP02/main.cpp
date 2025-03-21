#include <iostream>
#include <memory>
#include "raylib.h"
#include "Engine.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "Logger.h"
#include "Button.h"
#include "Scene.h"
#include "GameObject.h"
#include "GoPlayer.h"

using namespace LE;

int main()
{
    std::shared_ptr<LE::Logger> logger = std::make_shared<LE::Logger>();
    service_locator.registerService(logger);
    std::shared_ptr<LE::Engine> engine = std::make_shared<LE::Engine>(1000, 1000, "Test Player move", 60);
    service_locator.registerService(engine);

    auto sceneGame = std::make_shared<LE::Scene>("Game");
    auto quitFunc = []() {SendCommand([](Engine& InEngine) {InEngine.SwitchScene("Menu"); }); };
    auto player = std::make_shared<LE::Player>();

    auto imgB = std::make_shared<LE::GameObjectSingleImage>("invalid image name", "Red Square");
    imgB->SetPosition(Vector2{ 150.f,150.f });
    imgB->SetColorTint(RED);
    imgB->SetCollisionMask(3);
    auto funcCollisionOther = [](const CollisionEvent& InCollisionEvent) {
        if (InCollisionEvent._OtherObject != nullptr)
        {
            cout << "Moi aussi je collisionne avec " << InCollisionEvent._OtherObject->GetName() << endl;
        }
        };
    imgB->OnCollisionEvent(funcCollisionOther);
    sceneGame->AddGameObject2D(imgB);


    sceneGame->AddGameObject2D(player);

    engine->RegisterScene(sceneGame);
    engine->SetClearColor(WHITE);
    engine->SetDebugMode(true);
    engine->StartGame("Game");
}


#include <iostream>
#include <memory>
#include "raylib.h"
#include "Global.h"
#include "Engine.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "Logger.h"
#include "Button.h"
#include "CharacterController.h"
#include "Projectile.h"

using namespace std;

int main()
{
    const string ballImgPath = GetWorkingDirectory() + string("\\res\\BeachBall.png");
    const string charImgPath = GetWorkingDirectory() + string("\\res\\TopViewPerson.png");
    const string brickImgPath = GetWorkingDirectory() + string("\\res\\bricksx64.png");
    shared_ptr<LE::Engine> engine = InitLoopEngine(1000, 1000, "Test mouvement");
    shared_ptr<LE::Scene> scene = make_shared<LE::Scene>("Test");

    shared_ptr<LE::Projectile> proj = make_shared<LE::Projectile>(ballImgPath, Vector2{ 500.f,500.f });
    proj->SetScale(1.1f);
    shared_ptr<LE::CharacterController> character = make_shared<LE::CharacterController>(charImgPath, Vector2{ 200.f,200.f });
    character->SetScale(1.5f);

    shared_ptr<LE::Button> btnVelocity = make_shared<LE::Button>(0, 50, 100, 50, "Velocity",
        [&proj]() {
            if (proj)
            {
                proj->SetVelocity(GetRandomValue(0, 400));
            }
        }
    );
    shared_ptr<LE::Button> btnDirection = make_shared<LE::Button>(120, 50, 100, 50, "Direction",
        [&proj]() {
            if (proj)
            {
                proj->SetDirection({ (float)GetRandomValue(-100, 100),(float)GetRandomValue(-100, 100) });
            }
        }
    );
    //Raccourcis est ok car 0 est l'equivalent de false
    if (engine && scene && proj)
    {
        scene->AddGameObject2D(proj);
        scene->AddGameObject2D(btnVelocity);
        scene->AddGameObject2D(btnDirection);
        scene->AddGameObject2D(character);
        engine->SetClearColor(PINK);
        //Scène vide
        engine->RegisterScene(scene);
        engine->StartGame("Test");
    }
}
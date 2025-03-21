#pragma once

#include "GameObject.h"
#include "raylib.h"

namespace LE
{
    class Player : public GameObjectSingleImage
    {
    public:
        Player(const std::string& InImageFileName = "None", const std::string& InName = "Player");

        void PreUpdate() override;
        void LateUpdate() override;
        const float& GetVelocity();
        const bool& GetIsMoveAllowed();
        const Vector2& GetDirection();
        const Vector2& GetOldPosition();
        void SetOldPosition(Vector2 InOldPos);
        void SetIsMoveAllowed(bool InMoveAllow);
        void SetVelocity(float InVelocity);
        void SetDirection(Vector2 InDirection);
        

    private:
        Vector2 _Direction = {0,0};
        Vector2 _OldPosition = { 0,0 };
        float _Velocity = 0.;
        bool _IsMoveAllowed = true;
    };
}



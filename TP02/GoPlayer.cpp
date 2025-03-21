#include "GoPlayer.h"
#include <raymath.h>
#include "Logger.h"

namespace LE
{
    Player::Player(const std::string& InImageFileName, const std::string& InName)
        : GameObjectSingleImage(InImageFileName, InName),
        _Velocity(150.0f)
    {
        SetCollisionMask(2);
        SetPosition({500.0, 500.0});

        auto funcCollision = [this](const CollisionEvent& InCollisionEvent) {
            if (InCollisionEvent._OtherObject != nullptr)
            {
                SetPosition(GetOldPosition());
            }
            };

        this->OnCollisionEvent(funcCollision);
    }


    void Player::PreUpdate()
    {
        float deltaTime = GetFrameTime();
        SetOldPosition(GetPosition());

        Vector2 direction = { 0, 0 };

        if (IsKeyDown(KEY_W)) direction.y -= 1;
        if (IsKeyDown(KEY_S)) direction.y += 1;
        if (IsKeyDown(KEY_A)) direction.x -= 1;
        if (IsKeyDown(KEY_D)) direction.x += 1;

        if (direction.x != 0 || direction.y != 0) {
            SetDirection(direction);
        }

        SetPosition(GetPosition() + Vector2Scale(GetDirection(), GetVelocity() * deltaTime));

        SetDirection({ 0,0 });
    }
    void Player::LateUpdate()
    {
        SetIsMoveAllowed(true);
    }
    const float& Player::GetVelocity()
    {
        return _Velocity;
    }
    const bool& Player::GetIsMoveAllowed() {
        return _IsMoveAllowed;
    }

    const Vector2& Player::GetDirection()
    {
        return _Direction;
    }

    const Vector2& Player::GetOldPosition()
    {
        return _OldPosition;
    }

    void Player::SetVelocity(float InVelocity)
    {
        _Velocity = InVelocity;
    }
    void Player::SetDirection(Vector2 InDirection)
    {
        _Direction = InDirection;
    }
    void Player::SetOldPosition(Vector2 InOldPos)
    {
        _OldPosition = InOldPos;
    }
    void Player::SetIsMoveAllowed(bool InMoveAllow) {
        _IsMoveAllowed = InMoveAllow;
    }
}


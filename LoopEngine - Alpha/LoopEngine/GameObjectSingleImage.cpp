#include "GameObject.h"
#include "ServiceLocator.h"
#include "Logger.h"

namespace LE
{
    GameObjectSingleImage::GameObjectSingleImage(const std::string& InImageFileName, const std::string& InName)
        : GameObject2D(InName), _ImageFileName(InImageFileName), _Scale(1.0f), _RotationInDegree(0.0f), _ColorTint(BLACK)
    {
        if (_ImageFileName.empty())
        {
            LOG("Objet nommé " + GetName() + " a un nom de fichier vide.", eERROR);
        }
    }

    GameObjectSingleImage::~GameObjectSingleImage()
    {
        Unload();
    }

    void GameObjectSingleImage::SetScale(float InScale)
    {
        _Scale = InScale;
    }

    float GameObjectSingleImage::GetScale() const
    {
        return _Scale;
    }

    void GameObjectSingleImage::SetRotation(float InRotationInDegree)
    {
        _RotationInDegree = InRotationInDegree;
    }

    float GameObjectSingleImage::GetRotation() const
    {
        return _RotationInDegree;
    }

    void GameObjectSingleImage::SetColorTint(const Color& InColorTint)
    {
        _ColorTint = InColorTint;
    }

    const Color& GameObjectSingleImage::GetColorTint() const
    {
        return _ColorTint;
    }

    void GameObjectSingleImage::Load()
    {
        if (!(FileExists(_ImageFileName.c_str())))
        {
            LOG("Objet nommé " + GetName() + " réfère un fichier non-existant.", eWARNING);
            return;
        }

        if (_Image.data)
        {
            LOG("Objet nommé " + GetName() + " a déjà chargé son image et ne peut la recharger.", eWARNING);
            return;
        }

        _Image = LoadImage(_ImageFileName.c_str());
        _Texture = LoadTextureFromImage(_Image);
        UnloadImage(_Image);
    }

    void GameObjectSingleImage::Unload()
    {
        if (_Texture.id > 0)
        {
            UnloadTexture(_Texture);
            _Texture = { 0 };
        }
        else
        {
            LOG("Objet nommé " + GetName() + " n'a pas d'image chargé et ne peut la décharger.", eWARNING);
        }
    }

    const Image& GameObjectSingleImage::GetImage() const
    {
        return _Image;
    }

    const Texture& GameObjectSingleImage::GetTexture() const
    {
        return _Texture;
    }

    void GameObjectSingleImage::Draw2D()
    {
        if (_Texture.id > 0)
        {

            DrawTextureEx(GetTexture(), GetPosition(), GetRotation(), GetScale(), GetColorTint());
        }
        else
        {
            DrawRectangle(GetPosition().x, GetPosition().y, GetCollisionBox().x, GetCollisionBox().y, GetColorTint());
            //DrawRectanglePro(GetCollisionAtPosition(), GetPosition(), GetRotation(), GetColorTint());
        }
    }
}
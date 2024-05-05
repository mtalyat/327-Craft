#include "Camera.h"

Camera *Camera::mainCamera = nullptr;

Camera::~Camera()
{
    if (this == mainCamera)
    {
        setMain(nullptr);
    }
}

Camera::Camera()
{
    if (!mainCamera)
    {
        setMain(this);
    }
}

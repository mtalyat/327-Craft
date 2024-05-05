#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "GameObject.h"

// The Camera provides a perspective/offset for all other objects to be rendered.
class Camera
    : public GameObject
{
private:
    // the main camera
    static Camera *mainCamera;

    // TODO: set main camera on enter and exit

public:
    Camera();
    ~Camera();

    static void setMain(Camera *cam) { mainCamera = cam; }
    static Camera *getMain() { return mainCamera; }
};

#endif // __CAMERA_H__
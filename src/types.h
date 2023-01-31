#pragma once

#include <QObject>

enum class UIState : int
{
    Idle               = -1,
    Welcome_Animation  =  0,
    Welcome_Message    =  1,
    Dashboard          =  2,
    FaceRecognition    =  3,
    Branding           =  4

};

enum class UIStateDashboard : int
{
    Current   = 0,
    Power     = 1,
    Lock      = 2,
    Play      = 3,
    Pause     = 4,
    Idle      = 5,
};

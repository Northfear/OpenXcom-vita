#ifndef SDL12GAMEPADMAPPINGS_H
#define SDL12GAMEPADMAPPINGS_H

#ifdef __vita__
#define SDL_CONTROLLER_AXIS_LEFTX 0
#define SDL_CONTROLLER_AXIS_LEFTY 1
#define SDL_CONTROLLER_AXIS_RIGHTX 2
#define SDL_CONTROLLER_AXIS_RIGHTY 3
#define SDL_CONTROLLER_BUTTON_A 2
#define SDL_CONTROLLER_BUTTON_B 1
#define SDL_CONTROLLER_BUTTON_X 3
#define SDL_CONTROLLER_BUTTON_Y 0
#define SDL_CONTROLLER_BUTTON_BACK 10
#define SDL_CONTROLLER_BUTTON_START 11
#define SDL_CONTROLLER_BUTTON_LEFTSHOULDER 4
#define SDL_CONTROLLER_BUTTON_RIGHTSHOULDER 5
#define SDL_CONTROLLER_BUTTON_DPAD_UP 8
#define SDL_CONTROLLER_BUTTON_DPAD_DOWN 6
#define SDL_CONTROLLER_BUTTON_DPAD_LEFT 7
#define SDL_CONTROLLER_BUTTON_DPAD_RIGHT 9
#else
//XBox Series X mapping on Linux. Some buttons aren't working in SDL12
#define SDL_CONTROLLER_AXIS_LEFTX 0
#define SDL_CONTROLLER_AXIS_LEFTY 1
#define SDL_CONTROLLER_AXIS_RIGHTX 3
#define SDL_CONTROLLER_AXIS_RIGHTY 4
#define SDL_CONTROLLER_BUTTON_A 0
#define SDL_CONTROLLER_BUTTON_B 1
#define SDL_CONTROLLER_BUTTON_X 2
#define SDL_CONTROLLER_BUTTON_Y 3
#define SDL_CONTROLLER_BUTTON_BACK 6
#define SDL_CONTROLLER_BUTTON_START 7
#define SDL_CONTROLLER_BUTTON_LEFTSHOULDER 4
#define SDL_CONTROLLER_BUTTON_RIGHTSHOULDER 5
#define SDL_CONTROLLER_BUTTON_DPAD_UP 101
#define SDL_CONTROLLER_BUTTON_DPAD_DOWN 102
#define SDL_CONTROLLER_BUTTON_DPAD_LEFT 103
#define SDL_CONTROLLER_BUTTON_DPAD_RIGHT 104
#endif

#endif

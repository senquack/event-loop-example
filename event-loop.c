// SDL 1.2/2.0 abstraction code here courtesy of Nebuleon
#include <stdio.h>
#include <unistd.h>

#ifdef SDL_2
#  include "SDL2/SDL.h"
#  define JOYSTICK_NAME(Index) SDL_JoystickNameForIndex(Index)
#  define JOYSTICK_INDEX(Joystick) SDL_JoystickInstanceID(Joystick)
#else
#  include "SDL.h"
#  define JOYSTICK_NAME(Index) SDL_JoystickName(Index)
#  define JOYSTICK_INDEX(Joystick) SDL_JoystickIndex(Joystick)
#define SCREEN_W 320
#define SCREEN_H 240
#define SCREEN_BPP   32
#define SCREEN_FLAGS SDL_HWSURFACE | SDL_DOUBLEBUF
#endif //SDL_2

int main()
{
   if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
      printf("ERROR: Unable to initialize SDL:  %s\n", SDL_GetError());
      return 1;
   }

#ifdef SDL_2
   SDL_Window *Screen = SDL_CreateWindow("Input test",
         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
         0, 0,
         SDL_WINDOW_FULLSCREEN_DESKTOP);

   if (Screen == NULL)
   {
      printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
   }
#else
   SDL_Surface *Screen = SDL_SetVideoMode( SCREEN_W, SCREEN_H, SCREEN_BPP, SCREEN_FLAGS );
   SDL_ShowCursor(SDL_DISABLE);						// Disable mouse cursor on gp2x/gcw
#endif //SDL_2

   // Initialise joystick input.
   SDL_JoystickEventState(SDL_ENABLE);
   SDL_Joystick* gcw0_controls = NULL;
   SDL_Joystick* gsensor = NULL;

   printf("SDL reports %d total joysticks available.\n", SDL_NumJoysticks());
   int i;
   for (i = 0; i < SDL_NumJoysticks(); i++)
   {
      printf("Joystick %u: \"%s\"\n", i, JOYSTICK_NAME(i));
      if (strcmp(JOYSTICK_NAME(i), "linkdev device (Analog 2-axis 8-button 2-hat)") == 0) {
         printf("Recognized GCW's controls (buttons, dpad, analog stick)\n");
         gcw0_controls = SDL_JoystickOpen(i);
      } else if (strcmp(JOYSTICK_NAME(i), "mxc6225") == 0) {
         printf("Recognized GCW's g-sensor\n");
         gsensor = SDL_JoystickOpen(i);
      }
   }

   if (!gcw0_controls) {
      printf("ERROR: failed to recognize GCW's controls (buttons, dpad, analog stick)\n");
   }

   if (!gsensor) {
      printf("ERROR: failed to recognize GCW's g-sensor\n");
   }

   printf("Entering event loop, press CTRL-C to exit..\n");
   int quit = 0;
   while (!quit)
   {
      SDL_Event event;
      while (SDL_PollEvent(&event) != 0)
      {
         switch (event.type)
         {
            case SDL_QUIT:
               printf("Exiting..\n");
               quit = 1;
               break;
            case SDL_JOYAXISMOTION:
               printf("JOYAXISMOTION event\n");
               break;
            case SDL_JOYHATMOTION:
               printf("JOYHATMOTION event\n");
               break;
            case SDL_JOYBUTTONDOWN:
               printf("JOYBUTTONDOWN event\n");
               break;
            case SDL_JOYBUTTONUP:
               printf("JOYBUTTONUP event\n");
               break;
            case SDL_MOUSEMOTION:
               printf("MOUSEMOTION event\n");
               break;
            case SDL_MOUSEBUTTONDOWN:
               printf("MOUSEBUTTONDOWN event\n");
               break;
            case SDL_MOUSEBUTTONUP:
               printf("MOUSEBUTTONUP event\n");
               break;
            case SDL_KEYDOWN:
               printf("KEYDOWN event\n");
               break;
            case SDL_KEYUP:
               printf("KEYUP event\n");
               break;
            default:
               printf("UNKNOWN event\n");
               break;
         }
         usleep(10);
      }
   }

   SDL_Quit();

   return 0;
}


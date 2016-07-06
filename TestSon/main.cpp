#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   int continuer = 1;
   SDL_Init(SDL_INIT_VIDEO);
   SDL_Surface *ecran = NULL;
   ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
   SDL_Event event;
   SDL_WM_SetCaption("SDL_Mixer", NULL);
   SDL_Flip(ecran);
   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
   {
      printf("%s", Mix_GetError());
   }
   Mix_AllocateChannels(2);
   Mix_Music *musique;
   musique = Mix_LoadMUS("musique2.mp3");
   Mix_PlayMusic(musique, -1);
   Mix_VolumeMusic (50);
   Mix_Chunk *son;
   son = Mix_LoadWAV("Su3.wav");
   Mix_VolumeChunk(son, 128);
   while(continuer)
   {
      SDL_WaitEvent(&event);
      switch(event.type)
      {
         case SDL_QUIT:
            continuer = 0;
            break;
         case SDL_KEYDOWN:
             switch (event.key.keysym.sym)
             {
                  case SDLK_DOWN:
                  Mix_PlayChannel(1, son, 0);
                  Mix_HaltMusic();

             }
      }
   }
   Mix_FreeMusic(musique);
   Mix_FreeChunk(son);
   Mix_CloseAudio();
   SDL_Quit();
   return EXIT_SUCCESS;
}

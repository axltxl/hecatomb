/*
 * Copyright (C) 2010 Yamagi Burmeister
 * Copyright (C) 1997-2001 Id Software, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * =======================================================================
 *
 * This is the Quake II input system, written in SDL.
 *
 * =======================================================================
 */

 #include "prereqs.h"
 #include "refresh/local.h"
 #include "client/keyboard.h"
 #include "backend/generic/input.h"
 #include "backend/generic/sdl.h"

 #define MOUSE_MAX 3000
 #define MOUSE_MIN 40

 static qboolean mouse_grabbed;
 static cvar_t *windowed_mouse;
 static cvar_t *in_grab;
 static int mouse_x, mouse_y;
 static int old_mouse_x, old_mouse_y;
 static int mouse_buttonstate;
 static int mouse_oldbuttonstate;

 struct
 {
     int key;
     int down;
 } keyq[128];

 int keyq_head = 0;
 int keyq_tail = 0;
 int mx;
 int my;

 Key_Event_fp_t Key_Event_fp;

 static in_state_t *in_state;
 static qboolean mlooking;

 #ifdef HT_WITH_SDL2
 extern SDL_Window *window;
 static unsigned char KeyStates[SDL_NUM_SCANCODES];
 #else
 extern SDL_Surface *surface;
 static unsigned char KeyStates[SDLK_LAST];
 #endif

 static cvar_t *sensitivity;
 static cvar_t *exponential_speedup;
 static cvar_t *lookstrafe;
 static cvar_t *m_side;
 static cvar_t *m_yaw;
 static cvar_t *m_pitch;
 static cvar_t *m_forward;
 static cvar_t *freelook;
 static cvar_t *m_filter;
 static cvar_t *in_mouse;

 cvar_t *vid_fullscreen;

 /*
  * This function translates the SDL keycodes
  * to the internal key representation of the
  * id Tech 2 engine.
  */
 int
 IN_TranslateSDLtoQ2Key ( unsigned int keysym )
 {
     int key = 0;
 #ifdef HT_WITH_SDL2

     switch ( keysym )
     {

         //  SDLK_SPACE    = 32,
     case SDL_SCANCODE_SPACE:
         key = ' ';
         break;

 //  SDLK_QUOTE    = 39,
     case SDL_SCANCODE_APOSTROPHE:
         key = '\'';
         break;

         //  SDLK_COMMA    = 44,
     case SDL_SCANCODE_COMMA:
         key = ',';
         break;

 //  SDLK_MINUS    = 45,
     case SDL_SCANCODE_MINUS:
         key = '-';
         break;

 //  SDLK_PERIOD   = 46,
     case SDL_SCANCODE_PERIOD:
         key = '.';
         break;

 //  SDLK_SLASH    = 47,
     case SDL_SCANCODE_SLASH:
         key = '/';
         break;

 //  SDLK_0      = 48,
     case SDL_SCANCODE_0:
         key = '0';
         break;

 //  SDLK_1      = 49,
     case SDL_SCANCODE_1:
         key = '1';
         break;

 //  SDLK_2      = 50,
     case SDL_SCANCODE_2:
         key = '2';
         break;

 //  SDLK_3      = 51,
     case SDL_SCANCODE_3:
         key = '3';
         break;

 //  SDLK_4      = 52,
     case SDL_SCANCODE_4:
         key = '4';
         break;

 //  SDLK_5      = 53,
     case SDL_SCANCODE_5:
         key = '5';
         break;

 //  SDLK_6      = 54,
     case SDL_SCANCODE_6:
         key = '6';
         break;

 //  SDLK_7      = 55,
     case SDL_SCANCODE_7:
         key = '7';
         break;

 //  SDLK_8      = 56,
     case SDL_SCANCODE_8:
         key = '8';
         break;

 //  SDLK_9      = 57,
     case SDL_SCANCODE_9:
         key = '9';
         break;

 //  SDLK_SEMICOLON    = 59,
     case SDL_SCANCODE_SEMICOLON:
         key = ';';
         break;

 //  SDLK_EQUALS   = 61,
     case SDL_SCANCODE_EQUALS:
         key = '=';
         break;

 //  SDLK_LEFTBRACKET  = 91,
     case SDL_SCANCODE_LEFTBRACKET:
         key = '[';
         break;

 //  SDLK_BACKSLASH    = 92,
     case SDL_SCANCODE_BACKSLASH:
         key = '\\';
         break;

 //  SDLK_RIGHTBRACKET = 93,
     case SDL_SCANCODE_RIGHTBRACKET:
         key = ']';
         break;

 //  SDLK_BACKQUOTE    = 96,
     case SDL_SCANCODE_GRAVE:
         key = '`';
         break;

 //  SDLK_a      = 97,
     case SDL_SCANCODE_A:
         key = 'a';
         break;

 //  SDLK_b      = 98,
     case SDL_SCANCODE_B:
         key = 'b';
         break;

 //  SDLK_c      = 99,
     case SDL_SCANCODE_C:
         key = 'c';
         break;

 //  SDLK_d      = 100,
     case SDL_SCANCODE_D:
         key = 'd';
         break;

 //  SDLK_e      = 101,
     case SDL_SCANCODE_E:
         key = 'e';
         break;

 //  SDLK_f      = 102,
     case SDL_SCANCODE_F:
         key = 'f';
         break;

 //  SDLK_g      = 103,
     case SDL_SCANCODE_G:
         key = 'g';
         break;

 //  SDLK_h      = 104,
     case SDL_SCANCODE_H:
         key = 'h';
         break;

 //  SDLK_i      = 105,
     case SDL_SCANCODE_I:
         key = 'i';
         break;

 //  SDLK_j      = 106,
     case SDL_SCANCODE_J:
         key = 'j';
         break;

 //  SDLK_k      = 107,
     case SDL_SCANCODE_K:
         key = 'k';
         break;

 //  SDLK_l      = 108,
     case SDL_SCANCODE_L:
         key = 'l';
         break;

 //  SDLK_m      = 109,
     case SDL_SCANCODE_M:
         key = 'm';
         break;

 //  SDLK_n      = 110,
     case SDL_SCANCODE_N:
         key = 'n';
         break;

 //  SDLK_o      = 111,
     case SDL_SCANCODE_O:
         key = 'o';
         break;

 //  SDLK_p      = 112,
     case SDL_SCANCODE_P:
         key = 'p';
         break;

 //  SDLK_q      = 113,
     case SDL_SCANCODE_Q:
         key = 'q';
         break;

 //  SDLK_r      = 114,
     case SDL_SCANCODE_R:
         key = 'r';
         break;

 //  SDLK_s      = 115,
     case SDL_SCANCODE_S:
         key = 's';
         break;

 //  SDLK_t      = 116,
     case SDL_SCANCODE_T:
         key = 't';
         break;

 //  SDLK_u      = 117,
     case SDL_SCANCODE_U:
         key = 'u';
         break;

 //  SDLK_v      = 118,
     case SDL_SCANCODE_V:
         key = 'v';
         break;

 //  SDLK_w      = 119,
     case SDL_SCANCODE_W:
         key = 'w';
         break;

 //  SDLK_x      = 120,
     case SDL_SCANCODE_X:
         key = 'x';
         break;

 //  SDLK_y      = 121,
     case SDL_SCANCODE_Y:
         key = 'y';
         break;

 //  SDLK_z      = 122,
     case SDL_SCANCODE_Z:
         key = 'z';
         break;

     case SDL_SCANCODE_PAGEUP:
         key = K_PGUP;
         break;

     case SDL_SCANCODE_KP_9:
         key = K_KP_PGUP;
         break;

     case SDL_SCANCODE_PAGEDOWN:
         key = K_PGDN;
         break;

     case SDL_SCANCODE_KP_3:
         key = K_KP_PGDN;
         break;

     case SDL_SCANCODE_KP_7:
         key = K_KP_HOME;
         break;

     case SDL_SCANCODE_HOME:
         key = K_HOME;
         break;

     case SDL_SCANCODE_KP_1:
         key = K_KP_END;
         break;

     case SDL_SCANCODE_END:
         key = K_END;
         break;

     case SDL_SCANCODE_KP_4:
         key = K_KP_LEFTARROW;
         break;

     case SDL_SCANCODE_LEFT:
         key = K_LEFTARROW;
         break;

     case SDL_SCANCODE_KP_6:
         key = K_KP_RIGHTARROW;
         break;

     case SDL_SCANCODE_RIGHT:
         key = K_RIGHTARROW;
         break;

     case SDL_SCANCODE_KP_2:
         key = K_KP_DOWNARROW;
         break;

     case SDL_SCANCODE_DOWN:
         key = K_DOWNARROW;
         break;

     case SDL_SCANCODE_KP_8:
         key = K_KP_UPARROW;
         break;

     case SDL_SCANCODE_UP:
         key = K_UPARROW;
         break;

     case SDL_SCANCODE_ESCAPE:
         key = K_ESCAPE;
         break;

     case SDL_SCANCODE_KP_ENTER:
         key = K_KP_ENTER;
         break;

     case SDL_SCANCODE_RETURN:
         key = K_ENTER;
         break;

     case SDL_SCANCODE_TAB:
         key = K_TAB;
         break;

     case SDL_SCANCODE_F1:
         key = K_F1;
         break;

     case SDL_SCANCODE_F2:
         key = K_F2;
         break;

     case SDL_SCANCODE_F3:
         key = K_F3;
         break;

     case SDL_SCANCODE_F4:
         key = K_F4;
         break;

     case SDL_SCANCODE_F5:
         key = K_F5;
         break;

     case SDL_SCANCODE_F6:
         key = K_F6;
         break;

     case SDL_SCANCODE_F7:
         key = K_F7;
         break;

     case SDL_SCANCODE_F8:
         key = K_F8;
         break;

     case SDL_SCANCODE_F9:
         key = K_F9;
         break;

     case SDL_SCANCODE_F10:
         key = K_F10;
         break;

     case SDL_SCANCODE_F11:
         key = K_F11;
         break;

     case SDL_SCANCODE_F12:
         key = K_F12;
         break;

     case SDL_SCANCODE_F13:
         key = K_F13;
         break;

     case SDL_SCANCODE_F14:
         key = K_F14;
         break;

     case SDL_SCANCODE_F15:
         key = K_F15;
         break;

     case SDL_SCANCODE_BACKSPACE:
         key = K_BACKSPACE;
         break;

     case SDL_SCANCODE_KP_PERIOD:
         key = K_KP_DEL;
         break;

     case SDL_SCANCODE_DELETE:
         key = K_DEL;
         break;

     case SDL_SCANCODE_PAUSE:
         key = K_PAUSE;
         break;

     case SDL_SCANCODE_LSHIFT:
     case SDL_SCANCODE_RSHIFT:
         key = K_SHIFT;
         break;

     case SDL_SCANCODE_LCTRL:
     case SDL_SCANCODE_RCTRL:
         key = K_CTRL;
         break;

         // We'll see about these
         /*case SDL_SCANCODE_RMETA:
         case SDL_SCANCODE_LMETA:
           key = K_COMMAND;
           break;*/

     case SDL_SCANCODE_RALT:
     case SDL_SCANCODE_LALT:
         key = K_ALT;
         break;

     case SDL_SCANCODE_LGUI:
     case SDL_SCANCODE_RGUI:
         key = K_SUPER;
         break;

     case SDL_SCANCODE_KP_5:
         key = K_KP_5;
         break;

     case SDL_SCANCODE_INSERT:
         key = K_INS;
         break;

     case SDL_SCANCODE_KP_0:
         key = K_KP_INS;
         break;

     case SDL_SCANCODE_KP_MULTIPLY:
         key = K_KP_STAR;
         break;

     case SDL_SCANCODE_KP_PLUS:
         key = K_KP_PLUS;
         break;

     case SDL_SCANCODE_KP_MINUS:
         key = K_KP_MINUS;
         break;

     case SDL_SCANCODE_KP_DIVIDE:
         key = K_KP_SLASH;
         break;

     case SDL_SCANCODE_MODE:
         key = K_MODE;
         break;

         //case SDLK_COMPOSE:
     case SDL_SCANCODE_APPLICATION:
         key = K_COMPOSE;
         break;

     case SDL_SCANCODE_HELP:
         key = K_HELP;
         break;

         //case SDLK_PRINT:
     case SDL_SCANCODE_PRINTSCREEN:
         key = K_PRINT;
         break;

     case SDL_SCANCODE_SYSREQ:
         key = K_SYSREQ;
         break;

         //case SDLK_BREAK:
         /*case SDL_SCANCODE_PAUSE:
            key = K_BREAK;
            break;*/

     case SDL_SCANCODE_MENU:
         key = K_MENU;
         break;

     case SDL_SCANCODE_POWER:
         key = K_POWER;
         break;

         /*case SDL_SCANCODE_EURO:
           key = K_EURO;
           break;*/

     case SDL_SCANCODE_UNDO:
         key = K_UNDO;
         break;

     case SDL_SCANCODE_SCROLLLOCK:
         key = K_SCROLLOCK;
         break;

     case SDL_SCANCODE_NUMLOCKCLEAR:
         key = K_KP_NUMLOCK;
         break;

     case SDL_SCANCODE_CAPSLOCK:
         key = K_CAPSLOCK;
         break;
     }
 #else
     if ( ( keysym >= SDLK_SPACE ) && ( keysym < SDLK_DELETE ) )
     {
         /* These happen to match
            the ASCII chars */
         key = ( int ) keysym;
     }
     else
     {
         switch ( keysym )
         {
         case SDLK_PAGEUP:
             key = K_PGUP;
             break;

         case SDLK_KP9:
             key = K_KP_PGUP;
             break;

         case SDLK_PAGEDOWN:
             key = K_PGDN;
             break;

         case SDLK_KP3:
             key = K_KP_PGDN;
             break;

         case SDLK_KP7:
             key = K_KP_HOME;
             break;

         case SDLK_HOME:
             key = K_HOME;
             break;

         case SDLK_KP1:
             key = K_KP_END;
             break;

         case SDLK_END:
             key = K_END;
             break;

         case SDLK_KP4:
             key = K_KP_LEFTARROW;
             break;

         case SDLK_LEFT:
             key = K_LEFTARROW;
             break;

         case SDLK_KP6:
             key = K_KP_RIGHTARROW;
             break;

         case SDLK_RIGHT:
             key = K_RIGHTARROW;
             break;

         case SDLK_KP2:
             key = K_KP_DOWNARROW;
             break;

         case SDLK_DOWN:
             key = K_DOWNARROW;
             break;

         case SDLK_KP8:
             key = K_KP_UPARROW;
             break;

         case SDLK_UP:
             key = K_UPARROW;
             break;

         case SDLK_ESCAPE:
             key = K_ESCAPE;
             break;

         case SDLK_KP_ENTER:
             key = K_KP_ENTER;
             break;

         case SDLK_RETURN:
             key = K_ENTER;
             break;

         case SDLK_TAB:
             key = K_TAB;
             break;

         case SDLK_F1:
             key = K_F1;
             break;

         case SDLK_F2:
             key = K_F2;
             break;

         case SDLK_F3:
             key = K_F3;
             break;

         case SDLK_F4:
             key = K_F4;
             break;

         case SDLK_F5:
             key = K_F5;
             break;

         case SDLK_F6:
             key = K_F6;
             break;

         case SDLK_F7:
             key = K_F7;
             break;

         case SDLK_F8:
             key = K_F8;
             break;

         case SDLK_F9:
             key = K_F9;
             break;

         case SDLK_F10:
             key = K_F10;
             break;

         case SDLK_F11:
             key = K_F11;
             break;

         case SDLK_F12:
             key = K_F12;
             break;

         case SDLK_F13:
             key = K_F13;
             break;

         case SDLK_F14:
             key = K_F14;
             break;

         case SDLK_F15:
             key = K_F15;
             break;

         case SDLK_BACKSPACE:
             key = K_BACKSPACE;
             break;

         case SDLK_KP_PERIOD:
             key = K_KP_DEL;
             break;

         case SDLK_DELETE:
             key = K_DEL;
             break;

         case SDLK_PAUSE:
             key = K_PAUSE;
             break;

         case SDLK_LSHIFT:
         case SDLK_RSHIFT:
             key = K_SHIFT;
             break;

         case SDLK_LCTRL:
         case SDLK_RCTRL:
             key = K_CTRL;
             break;

         case SDLK_RMETA:
         case SDLK_LMETA:
             key = K_COMMAND;
             break;

         case SDLK_RALT:
         case SDLK_LALT:
             key = K_ALT;
             break;

         case SDLK_LSUPER:
         case SDLK_RSUPER:
             key = K_SUPER;
             break;

         case SDLK_KP5:
             key = K_KP_5;
             break;

         case SDLK_INSERT:
             key = K_INS;
             break;

         case SDLK_KP0:
             key = K_KP_INS;
             break;

         case SDLK_KP_MULTIPLY:
             key = K_KP_STAR;
             break;

         case SDLK_KP_PLUS:
             key = K_KP_PLUS;
             break;

         case SDLK_KP_MINUS:
             key = K_KP_MINUS;
             break;

         case SDLK_KP_DIVIDE:
             key = K_KP_SLASH;
             break;

         case SDLK_MODE:
             key = K_MODE;
             break;

         case SDLK_COMPOSE:
             key = K_COMPOSE;
             break;

         case SDLK_HELP:
             key = K_HELP;
             break;

         case SDLK_PRINT:
             key = K_PRINT;
             break;

         case SDLK_SYSREQ:
             key = K_SYSREQ;
             break;

         case SDLK_BREAK:
             key = K_BREAK;
             break;

         case SDLK_MENU:
             key = K_MENU;
             break;

         case SDLK_POWER:
             key = K_POWER;
             break;

         case SDLK_EURO:
             key = K_EURO;
             break;

         case SDLK_UNDO:
             key = K_UNDO;
             break;

         case SDLK_SCROLLOCK:
             key = K_SCROLLOCK;
             break;

         case SDLK_NUMLOCK:
             key = K_KP_NUMLOCK;
             break;

         case SDLK_CAPSLOCK:
             key = K_CAPSLOCK;
             break;

         default:
             if ( ( keysym >= SDLK_WORLD_0 ) && ( keysym <= SDLK_WORLD_95 ) )
             {
                 key = ( keysym - SDLK_WORLD_0 ) + K_WORLD_0;
             }

             break;
         }
     }
 #endif

     return key;
 }

 /*
  * Input event processing
  */
 void
 IN_GetEvent ( SDL_Event *event )
 {
     unsigned int key;

     switch ( event->type )
     {
         /* The mouse wheel */
     case SDL_MOUSEBUTTONDOWN:
         if ( event->button.button == 4 )
         {
             keyq[keyq_head].key = K_MWHEELUP;
             keyq[keyq_head].down = true;
             keyq_head = ( keyq_head + 1 ) & 127;
             keyq[keyq_head].key = K_MWHEELUP;
             keyq[keyq_head].down = false;
             keyq_head = ( keyq_head + 1 ) & 127;
         }
         else if ( event->button.button == 5 )
         {
             keyq[keyq_head].key = K_MWHEELDOWN;
             keyq[keyq_head].down = true;
             keyq_head = ( keyq_head + 1 ) & 127;
             keyq[keyq_head].key = K_MWHEELDOWN;
             keyq[keyq_head].down = false;
             keyq_head = ( keyq_head + 1 ) & 127;
         }

         break;

     case SDL_MOUSEBUTTONUP:
         break;

         /* The user pressed a button */
     case SDL_KEYDOWN:

         /* Fullscreen switch via Alt-Return */
 #ifdef HT_WITH_SDL2
         if ( ( KeyStates[SDL_SCANCODE_LALT] ||
                 KeyStates[SDL_SCANCODE_RALT] ) &&
                 ( event->key.keysym.scancode == SDL_SCANCODE_RETURN ) )
         {
 #else
         if ( ( KeyStates[SDLK_LALT] ||
                 KeyStates[SDLK_RALT] ) &&
                 ( event->key.keysym.sym == SDLK_RETURN ) )
         {

             SDL_WM_ToggleFullScreen ( surface );
 #endif // HT_WITH_SDL2
 #ifdef HT_WITH_SDL2
             if ( SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN )
             {
 #else
             if ( surface->flags & SDL_FULLSCREEN )
             {
 #endif
                 Cvar_SetValue ( "vid_fullscreen", 1 );
             }
             else
             {
                 Cvar_SetValue ( "vid_fullscreen", 0 );
             }

             vid_fullscreen->modified = false;
             break;
         }

         /* Make Shift+Escape toggle the console. This
            really belongs in Key_Event(), but since
            Key_ClearStates() can mess up the internal
            K_SHIFT state let's do it here instead. */
 #ifdef HT_WITH_SDL2
         if ( ( KeyStates[SDL_SCANCODE_LSHIFT] ||
                 KeyStates[SDL_SCANCODE_RSHIFT] ) &&
                 ( event->key.keysym.scancode == SDL_SCANCODE_ESCAPE ) )
         {
 #else
         if ( ( KeyStates[SDLK_LSHIFT] ||
                 KeyStates[SDLK_RSHIFT] ) &&
                 ( event->key.keysym.sym == SDLK_ESCAPE ) )
         {
 #endif
             Cbuf_ExecuteText ( EXEC_NOW, "toggleconsole" );
             break;
         }

         /* Get the pressed key and add it to the key list */
 #ifdef HT_WITH_SDL2
         KeyStates[event->key.keysym.scancode] = 1;
         key = IN_TranslateSDLtoQ2Key ( event->key.keysym.scancode );
 #else
         KeyStates[event->key.keysym.sym] = 1;
         key = IN_TranslateSDLtoQ2Key ( event->key.keysym.sym );
 #endif

         if ( key )
         {
             keyq[keyq_head].key = key;
             keyq[keyq_head].down = true;
             keyq_head = ( keyq_head + 1 ) & 127;
         }

         break;

         /* The user released a key */
     case SDL_KEYUP:
 #ifdef HT_WITH_SDL2
         if ( KeyStates[event->key.keysym.scancode] )
         {
             KeyStates[event->key.keysym.scancode] = 0;
             /* Get the pressed key and remove it from the key list */
             key = IN_TranslateSDLtoQ2Key ( event->key.keysym.scancode );
 #else
         if ( KeyStates[event->key.keysym.sym] )
         {
             KeyStates[event->key.keysym.sym] = 0;
             /* Get the pressed key and remove it from the key list */
             key = IN_TranslateSDLtoQ2Key ( event->key.keysym.sym );
 #endif // HT_WITH_SDL2
             if ( key )
             {
                 keyq[keyq_head].key = key;
                 keyq[keyq_head].down = false;
                 keyq_head = ( keyq_head + 1 ) & 127;
             }
         }

         break;
     }
 }

 /*
  * Updates the state of the input queue
  */
 void
 IN_Update ( void )
 {
     SDL_Event event;
     static int IN_Update_Flag;
     int bstate;

     /* Protection against multiple calls */
     if ( IN_Update_Flag == 1 )
     {
         return;
     }

     IN_Update_Flag = 1;

     while ( SDL_PollEvent ( &event ) )
     {
         IN_GetEvent ( &event );
     }

     #ifdef HT_WITH_SDL2
     if ( !SDL_GetRelativeMouseMode() && mouse_grabbed ) {
        /* Not supported */
        int center_x = vid.width/2,
            center_y = vid.height/2;
        int abs_x, abs_y;
        SDL_WarpMouseInWindow (window, center_x, center_y);
        SDL_GetMouseState(&abs_x, &abs_y);
        mx = abs_x - center_x;
        my = abs_y - center_y;
     }

     else {
     #endif
       if ( !mx && !my ) {
         SDL_GetRelativeMouseState ( &mx, &my );
      }
     #ifdef HT_WITH_SDL2
     }
     #endif

     /* Mouse button processing. Button 4
        and 5 are the mousewheel and thus
        not processed here. */
     mouse_buttonstate = 0;
     bstate = SDL_GetMouseState ( NULL, NULL );

     if ( SDL_BUTTON ( 1 ) & bstate )
     {
         mouse_buttonstate |= ( 1 << 0 );
     }

     if ( SDL_BUTTON ( 3 ) & bstate )
     {
         mouse_buttonstate |= ( 1 << 1 );
     }

     if ( SDL_BUTTON ( 2 ) & bstate )
     {
         mouse_buttonstate |= ( 1 << 2 );
     }

     if ( SDL_BUTTON ( 6 ) & bstate )
     {
         mouse_buttonstate |= ( 1 << 3 );
     }

     if ( SDL_BUTTON ( 7 ) & bstate )
     {
         mouse_buttonstate |= ( 1 << 4 );
     }

     /* Grab and ungrab the mouse if the
      * console or the menu is opened */
     if ( vid_fullscreen->value )
     {
         if ( !mouse_grabbed )
         {
 #ifdef HT_WITH_SDL2
             SDL_SetWindowGrab (window, SDL_TRUE);
 #else
             SDL_WM_GrabInput ( SDL_GRAB_ON );
 #endif
             mouse_grabbed = true;
         }
     }

     if ( in_grab->value == 0 )
     {
         if ( mouse_grabbed )
         {
 #ifdef HT_WITH_SDL2
             SDL_SetWindowGrab (window, SDL_FALSE);
 #else
             SDL_WM_GrabInput ( SDL_GRAB_OFF );
 #endif
             mouse_grabbed = false;
         }
     }
     else if ( in_grab->value == 1 )
     {
         if ( !mouse_grabbed )
         {
 #ifdef HT_WITH_SDL2
             SDL_SetWindowGrab (window, SDL_TRUE);
 #else
             SDL_WM_GrabInput ( SDL_GRAB_ON );
 #endif
             mouse_grabbed = true;
         }
     }
     else
     {
         if ( windowed_mouse->value )
         {
             if ( !mouse_grabbed )
             {
 #ifdef HT_WITH_SDL2
                 SDL_SetWindowGrab (window, SDL_TRUE);
 #else
                 SDL_WM_GrabInput ( SDL_GRAB_ON );
 #endif
                 mouse_grabbed = true;
             }
         }
         else
         {
             if ( mouse_grabbed )
             {
 #ifdef HT_WITH_SDL2
                 SDL_SetWindowGrab (window, SDL_FALSE);
 #else
                 SDL_WM_GrabInput ( SDL_GRAB_OFF );
 #endif
                 mouse_grabbed = false;
             }
         }
     }

     /* Process the key events */
     while ( keyq_head != keyq_tail )
     {
         in_state->Key_Event_fp ( keyq[keyq_tail].key, keyq[keyq_tail].down );
         keyq_tail = ( keyq_tail + 1 ) & 127;
     }

     IN_Update_Flag = 0;
 }

 /*
  * Closes all inputs and clears
  * the input queue.
  */
 void
 IN_Close ( void )
 {
     keyq_head = 0;
     keyq_tail = 0;
     memset ( keyq, 0, sizeof ( keyq ) );
 }

 /*
  * Gets the mouse state
  */
 void
 IN_GetMouseState ( int *x, int *y, int *state )
 {
     *x = mx;
     *y = my;
     *state = mouse_buttonstate;
 }

 /*
  * Cleares the mouse state
  */
 void
 IN_ClearMouseState()
 {
     mx = my = 0;
 }

 /*
  * Centers the view
  */
 static void
 IN_ForceCenterView ( void )
 {
     in_state->viewangles[PITCH] = 0;
 }

 /*
  * Look up
  */
 static void
 IN_MLookDown ( void )
 {
     mlooking = true;
 }

 /*
  * Look down
  */
 static void
 IN_MLookUp ( void )
 {
     mlooking = false;
     in_state->IN_CenterView_fp();
 }

 /*
  * Keyboard initialisation. Called by the client.
  */
 void
 IN_KeyboardInit ( Key_Event_fp_t fp )
 {
     Key_Event_fp = fp;
     /* SDL stuff. Moved here from IN_BackendInit because
      * this must be done after video is initialized. */
 #ifdef HT_WITH_SDL2
 #else
     SDL_EnableUNICODE ( 0 );
     SDL_EnableKeyRepeat ( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );
 #endif
 #ifdef HT_WITH_SDL2
     if ( SDL_GetWindowGrab (window) )
     {
 #else
     if ( SDL_WM_GrabInput ( SDL_GRAB_QUERY ) == SDL_GRAB_ON )
     {
 #endif
         mouse_grabbed = true;
     }
     else
     {
         mouse_grabbed = false;
     }
 }

 /*
  * Initializes the backend
  */
 void
 IN_BackendInit ( in_state_t *in_state_p )
 {
     in_state = in_state_p;
     m_filter = Cvar_Get ( "m_filter", "0", CVAR_ARCHIVE );
     in_mouse = Cvar_Get ( "in_mouse", "0", CVAR_ARCHIVE );
     freelook = Cvar_Get ( "freelook", "1", 0 );
     lookstrafe = Cvar_Get ( "lookstrafe", "0", 0 );
     sensitivity = Cvar_Get ( "sensitivity", "3", 0 );
     exponential_speedup = Cvar_Get ( "exponential_speedup", "0", CVAR_ARCHIVE );
     m_pitch = Cvar_Get ( "m_pitch", "0.022", 0 );
     m_yaw = Cvar_Get ( "m_yaw", "0.022", 0 );
     m_forward = Cvar_Get ( "m_forward", "1", 0 );
     m_side = Cvar_Get ( "m_side", "0.8", 0 );
     Cmd_AddCommand ( "+mlook", IN_MLookDown );
     Cmd_AddCommand ( "-mlook", IN_MLookUp );
     Cmd_AddCommand ( "force_centerview", IN_ForceCenterView );
     mouse_x = mouse_y = 0.0;
     windowed_mouse = Cvar_Get ( "windowed_mouse", "1",
                                 CVAR_USERINFO | CVAR_ARCHIVE );
     in_grab = Cvar_Get ( "in_grab", "2", CVAR_ARCHIVE );
     vid_fullscreen = Cvar_Get ( "vid_fullscreen", "0", CVAR_ARCHIVE );
     VID_Printf ( PRINT_ALL, "Input initialized.\n" );
 }

 /*
  * Shuts the backend down
  */
 void
 IN_BackendShutdown ( void )
 {
     Cmd_RemoveCommand ( "+mlook" );
     Cmd_RemoveCommand ( "-mlook" );
     Cmd_RemoveCommand ( "force_centerview" );
     VID_Printf ( PRINT_ALL, "Input shut down.\n" );
 }

 /*
  * Mouse button handling
  */
 void
 IN_BackendMouseButtons ( void )
 {
     int i;
     IN_GetMouseState ( &mouse_x, &mouse_y, &mouse_buttonstate );

     for ( i = 0; i < 3; i++ )
     {
         if ( ( mouse_buttonstate & ( 1 << i ) ) && ! ( mouse_oldbuttonstate & ( 1 << i ) ) )
         {
             in_state->Key_Event_fp ( K_MOUSE1 + i, true );
         }

         if ( ! ( mouse_buttonstate & ( 1 << i ) ) && ( mouse_oldbuttonstate & ( 1 << i ) ) )
         {
             in_state->Key_Event_fp ( K_MOUSE1 + i, false );
         }
     }

     if ( ( mouse_buttonstate & ( 1 << 3 ) ) && ! ( mouse_oldbuttonstate & ( 1 << 3 ) ) )
     {
         in_state->Key_Event_fp ( K_MOUSE4, true );
     }

     if ( ! ( mouse_buttonstate & ( 1 << 3 ) ) && ( mouse_oldbuttonstate & ( 1 << 3 ) ) )
     {
         in_state->Key_Event_fp ( K_MOUSE4, false );
     }

     if ( ( mouse_buttonstate & ( 1 << 4 ) ) && ! ( mouse_oldbuttonstate & ( 1 << 4 ) ) )
     {
         in_state->Key_Event_fp ( K_MOUSE5, true );
     }

     if ( ! ( mouse_buttonstate & ( 1 << 4 ) ) && ( mouse_oldbuttonstate & ( 1 << 4 ) ) )
     {
         in_state->Key_Event_fp ( K_MOUSE5, false );
     }

     mouse_oldbuttonstate = mouse_buttonstate;
 }

 /*
  * Move handling
  */
 void
 IN_BackendMove ( usercmd_t *cmd )
 {
     IN_GetMouseState ( &mouse_x, &mouse_y, &mouse_buttonstate );

     if ( m_filter->value )
     {
         if ( ( mouse_x > 1 ) || ( mouse_x < -1 ) )
         {
             mouse_x = ( mouse_x + old_mouse_x ) * 0.5;
         }

         if ( ( mouse_y > 1 ) || ( mouse_y < -1 ) )
         {
             mouse_y = ( mouse_y + old_mouse_y ) * 0.5;
         }
     }

     old_mouse_x = mouse_x;
     old_mouse_y = mouse_y;

     if ( mouse_x || mouse_y )
     {
         if ( !exponential_speedup->value )
         {
             mouse_x *= sensitivity->value;
             mouse_y *= sensitivity->value;
         }
         else
         {
             if ( ( mouse_x > MOUSE_MIN ) || ( mouse_y > MOUSE_MIN ) ||
                     ( mouse_x < -MOUSE_MIN ) || ( mouse_y < -MOUSE_MIN ) )
             {
                 mouse_x = ( mouse_x * mouse_x * mouse_x ) / 4;
                 mouse_y = ( mouse_y * mouse_y * mouse_y ) / 4;

                 if ( mouse_x > MOUSE_MAX )
                 {
                     mouse_x = MOUSE_MAX;
                 }
                 else if ( mouse_x < -MOUSE_MAX )
                 {
                     mouse_x = -MOUSE_MAX;
                 }

                 if ( mouse_y > MOUSE_MAX )
                 {
                     mouse_y = MOUSE_MAX;
                 }
                 else if ( mouse_y < -MOUSE_MAX )
                 {
                     mouse_y = -MOUSE_MAX;
                 }
             }
         }

         /* add mouse X/Y movement to cmd */
         if ( ( *in_state->in_strafe_state & 1 ) ||
                 ( lookstrafe->value && mlooking ) )
         {
             cmd->sidemove += m_side->value * mouse_x;
         }
         else
         {
             in_state->viewangles[YAW] -= m_yaw->value * mouse_x;
         }

         if ( ( mlooking || freelook->value ) &&
                 ! ( *in_state->in_strafe_state & 1 ) )
         {
             in_state->viewangles[PITCH] += m_pitch->value * mouse_y;
         }
         else
         {
             cmd->forwardmove -= m_forward->value * mouse_y;
         }

         IN_ClearMouseState();
     }
 }

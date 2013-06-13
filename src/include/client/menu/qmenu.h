/*
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
 * USA.
 *
 * =======================================================================
 *
 * The header file for the generic part of the menu system
 *
 * =======================================================================
 */

 #ifndef CL_MENU_QMENU_H
 #define CL_MENU_QMENU_H

 #include "prereqs.h"

 #define MAXMENUITEMS 64

 #define MTYPE_SLIDER 0
 #define MTYPE_LIST 1
 #define MTYPE_ACTION 2
 #define MTYPE_SPINCONTROL 3
 #define MTYPE_SEPARATOR 4
 #define MTYPE_FIELD 5

 #define QMF_LEFT_JUSTIFY 0x00000001
 #define QMF_GRAYED 0x00000002
 #define QMF_NUMBERSONLY 0x00000004

 typedef struct _tag_menuframework {
   q_int32_t x, y;
   q_int32_t cursor;

   q_int32_t nitems;
   q_int32_t nslots;
   void *items[64];

   const char *statusbar;

   void ( *cursordraw ) ( struct _tag_menuframework *m );
 } menuframework_s;

 typedef struct {
   q_int32_t type;
   const char *name;
   q_int32_t x, y;
   menuframework_s *parent;
   q_int32_t cursor_offset;
   q_int32_t localdata[4];
   q_uint32_t flags;

   const char *statusbar;

   void ( *callback ) ( void *self );
   void ( *statusbarfunc ) ( void *self );
   void ( *ownerdraw ) ( void *self );
   void ( *cursordraw ) ( void *self );
 } menucommon_s;

 typedef struct {
   menucommon_s generic;

   char buffer[80];
   q_int32_t cursor;
   q_int32_t length;
   q_int32_t visible_length;
   q_int32_t visible_offset;
 } menufield_s;

 typedef struct {
   menucommon_s generic;

   float minvalue;
   float maxvalue;
   float curvalue;

   float range;
 } menuslider_s;

 typedef struct {
   menucommon_s generic;

   q_int32_t curvalue;

   const char **itemnames;
 } menulist_s;

 typedef struct {
   menucommon_s generic;
 } menuaction_s;

 typedef struct {
   menucommon_s generic;
 } menuseparator_s;

 qboolean Field_Key ( menufield_s *field, q_int32_t key );

 void Menu_AddItem ( menuframework_s *menu, void *item );
 void Menu_AdjustCursor ( menuframework_s *menu, q_int32_t dir );
 void Menu_Center ( menuframework_s *menu );
 void Menu_Draw ( menuframework_s *menu );
 void *Menu_ItemAtCursor ( menuframework_s *m );
 qboolean Menu_SelectItem ( menuframework_s *s );
 void Menu_SetStatusBar ( menuframework_s *s, const char *string );
 void Menu_SlideItem ( menuframework_s *s, q_int32_t dir );
 q_int32_t Menu_TallySlots ( menuframework_s *menu );

 void Menu_DrawString ( q_int32_t, q_int32_t, const char * );
 void Menu_DrawStringDark ( q_int32_t, q_int32_t, const char * );
 void Menu_DrawStringR2L ( q_int32_t, q_int32_t, const char * );
 void Menu_DrawStringR2LDark ( q_int32_t, q_int32_t, const char * );

 #endif /* CL_MENU_QMENU_H */

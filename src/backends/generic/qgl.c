/*
 * Copyright (C) 2013 Alejandro Ricoveri
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
 * This file implements the operating system binding of GL to QGL function
 * pointers.  When doing a port of Quake2 you must implement the following
 * two functions:
 *
 * QGL_Init() - loads libraries, assigns function pointers, etc.
 * QGL_Shutdown() - unloads libraries, NULLs function pointers
 *
 * This implementation should work for Windows and unixoid platforms,
 * other platforms may need an own implementation.
 *
 * =======================================================================
 */

 #include "prereqs.h"
 #include "system.h"
 #include "filesystem.h"
 #include "refresh/local.h"

 /*
  * GL extensions
  */
 PFNGLPOINTPARAMETERFEXTPROC qglPointParameterfEXT;
 PFNGLPOINTPARAMETERFVEXTPROC qglPointParameterfvEXT;
 PFNGLCOLORTABLEEXTPROC qglColorTableEXT;
 PFNGLLOCKARRAYSEXTPROC qglLockArraysEXT;
 PFNGLUNLOCKARRAYSEXTPROC qglUnlockArraysEXT;
 void ( APIENTRY *qglMTexCoord2fSGIS ) ( GLenum, GLfloat, GLfloat );
 void ( APIENTRY *qglSelectTextureSGIS ) ( GLenum );
 PFNGLACTIVETEXTUREARBPROC qglActiveTextureARB;
 PFNGLCLIENTACTIVETEXTUREARBPROC qglClientActiveTextureARB;

 /* ========================================================================= */
 void
 QGL_Shutdown ( void )
 {
   qglLockArraysEXT = NULL;
   qglUnlockArraysEXT = NULL;
   qglPointParameterfEXT = NULL;
   qglPointParameterfvEXT = NULL;
   qglColorTableEXT = NULL;
   qglSelectTextureSGIS = NULL;
   qglMTexCoord2fSGIS = NULL;
   qglActiveTextureARB = NULL;
   qglClientActiveTextureARB = NULL;
 }

 /* ========================================================================= */
 void QGL_SetupExtensions ( void )
 {
   /* grab extensions */
   VID_Printf ( PRINT_ALL, "\n\nGLEW_VERSION: %s\n", glewGetString(GLEW_VERSION) );
   VID_Printf ( PRINT_ALL, "Probing for OpenGL extensions:\n==============\n" );

   /* GL_EXT_compiled_vertex_array GL_SGI_compiled_vertex_array */
   if ( GLEW_EXT_compiled_vertex_array
        || glewIsSupported ("GL_SGI_compiled_vertex_array") )
   {
     VID_Printf ( PRINT_ALL, "Using GL_EXT_compiled_vertex_array\n" );
     qglLockArraysEXT = ( PFNGLLOCKARRAYSEXTPROC )
       QGL_GetProcAddress ( "glLockArraysEXT" );
     qglUnlockArraysEXT = ( PFNGLUNLOCKARRAYSEXTPROC )
       QGL_GetProcAddress ( "glUnlockArraysEXT" );
   }
   else {
     VID_Printf ( PRINT_ALL, "GL_EXT_compiled_vertex_array not found\n" );
   }

   /* GL_EXT_point_parameters */
   if ( GLEW_EXT_point_parameters )
   {
     if ( gl_ext_pointparameters->value ) {
       VID_Printf ( PRINT_ALL, "Using GL_EXT_point_parameters\n" );
       qglPointParameterfEXT = ( PFNGLPOINTPARAMETERFEXTPROC )
                               QGL_GetProcAddress ( "glPointParameterfEXT" );
       qglPointParameterfvEXT = ( PFNGLPOINTPARAMETERFVEXTPROC )
                                QGL_GetProcAddress ( "glPointParameterfvEXT" );
     }
     else {
       VID_Printf ( PRINT_ALL, "Ignoring GL_EXT_point_parameters\n" );
     }
   }
   else {
     VID_Printf ( PRINT_ALL, "GL_EXT_point_parameters not found\n" );
   }

   /* GL_EXT_paletted_texture GL_EXT_shared_texture_palette */
   if ( !qglColorTableEXT
        && GLEW_EXT_paletted_texture && GLEW_EXT_shared_texture_palette)
   {
     if ( gl_ext_palettedtexture->value ) {
       VID_Printf ( PRINT_ALL, "Using GL_EXT_shared_texture_palette\n" );
       qglColorTableEXT =
         ( PFNGLCOLORTABLEEXTPROC ) QGL_GetProcAddress ( "glColorTableEXT" );
     }
     else {
       VID_Printf ( PRINT_ALL, "Ignoring GL_EXT_shared_texture_palette\n" );
     }
   }
   else {
     VID_Printf ( PRINT_ALL, "GL_EXT_shared_texture_palette not found\n" );
   }

   /* GL_ARB_multitexture */
   if ( GLEW_ARB_multitexture )
   {
     if ( gl_ext_multitexture->value ) {
       VID_Printf ( PRINT_ALL, "Using GL_ARB_multitexture\n" );
       qglMTexCoord2fSGIS = ( void * )
         QGL_GetProcAddress ( "glMultiTexCoord2fARB" );
       qglActiveTextureARB = ( PFNGLACTIVETEXTUREARBPROC )
         QGL_GetProcAddress ( "glActiveTextureARB" );
       qglClientActiveTextureARB = ( PFNGLCLIENTACTIVETEXTUREARBPROC )
         QGL_GetProcAddress ( "glClientActiveTextureARB" );
       QGL_TEXTURE0 = GL_TEXTURE0_ARB;
       QGL_TEXTURE1 = GL_TEXTURE1_ARB;
     }
     else {
       VID_Printf ( PRINT_ALL, "Ignoring GL_ARB_multitexture\n" );
     }
   }
   else {
     VID_Printf ( PRINT_ALL, "GL_ARB_multitexture not found\n" );
   }

   /* GL_SGIS_multitexture */
   if ( glewIsSupported("GL_SGIS_multitexture") )
   {
     if ( qglActiveTextureARB ) {
       VID_Printf ( PRINT_ALL,
         "GL_SGIS_multitexture deprecated in favor of ARB_multitexture\n" );
     }
     else if ( gl_ext_multitexture->value ) {
       VID_Printf ( PRINT_ALL, "Using GL_SGIS_multitexture\n" );
       qglMTexCoord2fSGIS = ( void * )
         QGL_GetProcAddress ( "glMTexCoord2fSGIS" );
       qglSelectTextureSGIS = ( void * )
         QGL_GetProcAddress ( "glSelectTextureSGIS" );
       QGL_TEXTURE0 = GL_TEXTURE0_SGIS;
       QGL_TEXTURE1 = GL_TEXTURE1_SGIS;
     }
     else {
       VID_Printf ( PRINT_ALL, "Ignoring GL_SGIS_multitexture\n" );
     }
   }
   else {
     VID_Printf ( PRINT_ALL, "GL_SGIS_multitexture not found\n" );
   }

   gl_config.anisotropic = false;

   /* GL_EXT_texture_filter_anisotropic */
   if ( GLEW_EXT_texture_filter_anisotropic )
   {
     VID_Printf ( PRINT_ALL, "Using GL_EXT_texture_filter_anisotropic\n" );
     gl_config.anisotropic = true;
     qglGetFloatv ( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &gl_config.max_anisotropy );
     Cvar_SetValue ( "gl_anisotropic_avail", gl_config.max_anisotropy );
   }
   else {
     VID_Printf ( PRINT_ALL, "GL_EXT_texture_filter_anisotropic not found\n" );
     gl_config.anisotropic = false;
     gl_config.max_anisotropy = 0.0;
     Cvar_SetValue ( "gl_anisotropic_avail", 0.0 );
   }

   gl_config.mtexcombine = false;

   /* GL_ARB_texture_env_combine */
   if ( GLEW_ARB_texture_env_combine )
   {
     if ( gl_ext_mtexcombine->value ) {
       VID_Printf ( PRINT_ALL, "Using GL_ARB_texture_env_combine\n" );
       gl_config.mtexcombine = true;
     }
     else {
       VID_Printf ( PRINT_ALL, "Ignoring GL_ARB_texture_env_combine\n" );
     }
   }
   else {
     VID_Printf ( PRINT_ALL, "GL_ARB_texture_env_combine not found\n" );
   }

   /* GL_EXT_texture_env_combine */
   if ( !gl_config.mtexcombine ) {
     if ( strstr ( gl_config.extensions_string, "GL_EXT_texture_env_combine" ) )
     {
       if ( gl_ext_mtexcombine->value ) {
         VID_Printf ( PRINT_ALL, "Using GL_EXT_texture_env_combine\n" );
         gl_config.mtexcombine = true;
       }
       else {
         VID_Printf ( PRINT_ALL, "Ignoring GL_EXT_texture_env_combine\n" );
       }
     }
     else {
       VID_Printf ( PRINT_ALL, "GL_EXT_texture_env_combine not found\n" );
     }
   }
 }

 /* ========================================================================= */
 void *
 QGL_GetProcAddress ( char *proc )
 {
   return GLimp_GetProcAddress ( proc );
 }

 /* ========================================================================= */
 qboolean
 QGL_Init (void)
 {
   qglLockArraysEXT = NULL;
   qglUnlockArraysEXT = NULL;
   qglPointParameterfEXT = NULL;
   qglPointParameterfvEXT = NULL;
   qglColorTableEXT = NULL;
   qglSelectTextureSGIS = NULL;
   qglMTexCoord2fSGIS = NULL;
   qglActiveTextureARB = NULL;
   qglClientActiveTextureARB = NULL;
   return true;
 }

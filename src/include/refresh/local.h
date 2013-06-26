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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * =======================================================================
 *
 * Local header for the refresher.
 *
 * =======================================================================
 */

 #ifndef REF_LOCAL_H
 #define REF_LOCAL_H

 #include "prereqs.h"
 #include "backend/generic/gl.h"
 #include "client/ref.h"
 #include "backend/generic/qgl.h"

 #ifndef GL_COLOR_INDEX8_EXT
 #define GL_COLOR_INDEX8_EXT GL_COLOR_INDEX
 #endif

 #ifndef GL_EXT_texture_filter_anisotropic
 #define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
 #define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
 #endif

 #ifndef GL_ARB_multitexture
 #define GL_TEXTURE0_ARB 0x84C0
 #define GL_TEXTURE1_ARB 0x84C1
 #endif

 #ifndef GL_VERSION_1_3
 #define GL_TEXTURE1 0x84C1
 #endif

 #define TEXNUM_LIGHTMAPS 1024
 #define TEXNUM_SCRAPS 1152
 #define TEXNUM_IMAGES 1153
 #define MAX_GLTEXTURES 1024
 #define MAX_SCRAPS 1
 #define BLOCK_WIDTH 128
 #define BLOCK_HEIGHT 128
 #define REF_VERSION "Yamagi Quake II OpenGL Refresher"
 #define MAX_LBM_HEIGHT 480
 #define BACKFACE_EPSILON 0.01
 #define DYNAMIC_LIGHT_WIDTH 128
 #define DYNAMIC_LIGHT_HEIGHT 128
 #define LIGHTMAP_BYTES 4
 #define MAX_LIGHTMAPS 128
 #define GL_LIGHTMAP_FORMAT GL_RGBA

 /* up / down */
 #define PITCH 0

 /* left / right */
 #define YAW 1

 /* fall over */
 #define ROLL 2

 char *strlwr ( char *s );

 extern viddef_t vid;

 /*
  * skins will be outline flood filled and mip mapped
  * pics and sprites with alpha will be outline flood filled
  * pic won't be mip mapped
  *
  * model skin
  * sprite frame
  * wall texture
  * pic
  */
 typedef enum {
   it_skin,
   it_sprite,
   it_wall,
   it_pic,
   it_sky
 } imagetype_t;

 typedef struct image_s {
   char name[MAX_QPATH];               /* game path, including extension */
   imagetype_t type;
   q_int32_t width, height;                  /* source image */
   q_int32_t upload_width, upload_height;    /* after power of two and picmip */
   q_int32_t registration_sequence;          /* 0 = free */
   struct msurface_s *texturechain;    /* for sort-by-texture world drawing */
   q_int32_t texnum;                         /* gl texture binding */
   float sl, tl, sh, th;               /* 0,0 - 1,1 unless part of the scrap */
   qboolean scrap;
   qboolean has_alpha;

   qboolean paletted;
 } image_t;

 #include "refresh/model.h"

 typedef enum {
   rserr_ok,

   rserr_invalid_fullscreen,
   rserr_invalid_mode,

   rserr_unknown
 } rserr_t;

 void GL_BeginRendering ( q_int32_t *x, q_int32_t *y, q_int32_t *width, q_int32_t *height );
 void GL_EndRendering ( void );

 void R_SetDefaultState ( void );

 extern float gldepthmin, gldepthmax;

 typedef struct {
   float x, y, z;
   float s, t;
   float r, g, b;
 } glvert_t;

 extern image_t gltextures[MAX_GLTEXTURES];
 extern q_int32_t numgltextures;

 extern image_t *r_notexture;
 extern image_t *r_particletexture;
 extern entity_t *currententity;
 extern model_t *currentmodel;
 extern q_int32_t r_visframecount;
 extern q_int32_t r_framecount;
 extern cplane_t frustum[4];
 extern q_int32_t c_brush_polys, c_alias_polys;
 extern q_int32_t gl_filter_min, gl_filter_max;

 /* view origin */
 extern vec3_t vup;
 extern vec3_t vpn;
 extern vec3_t vright;
 extern vec3_t r_origin;

 /* screen size info */
 extern refdef_t r_newrefdef;
 extern q_int32_t r_viewcluster, r_viewcluster2, r_oldviewcluster, r_oldviewcluster2;

 extern cvar_t *gl_norefresh;
 extern cvar_t *gl_lefthand;
 extern cvar_t *gl_farsee;
 extern cvar_t *gl_msaa_samples;
 extern cvar_t *gl_drawentities;
 extern cvar_t *gl_drawworld;
 extern cvar_t *gl_speeds;
 extern cvar_t *gl_fullbright;
 extern cvar_t *gl_novis;
 extern cvar_t *gl_nocull;
 extern cvar_t *gl_lerpmodels;

 extern cvar_t *gl_lightlevel;
 extern cvar_t *gl_overbrightbits;

 extern cvar_t *gl_vertex_arrays;

 extern cvar_t *gl_ext_swapinterval;
 extern cvar_t *gl_ext_palettedtexture;
 extern cvar_t *gl_ext_multitexture;
 extern cvar_t *gl_ext_pointparameters;
 extern cvar_t *gl_ext_compiled_vertex_array;
 extern cvar_t *gl_ext_mtexcombine;

 extern cvar_t *gl_particle_min_size;
 extern cvar_t *gl_particle_max_size;
 extern cvar_t *gl_particle_size;
 extern cvar_t *gl_particle_att_a;
 extern cvar_t *gl_particle_att_b;
 extern cvar_t *gl_particle_att_c;

 extern cvar_t *gl_nosubimage;
 extern cvar_t *gl_bitdepth;
 extern cvar_t *gl_mode;

 extern cvar_t *gl_customwidth;
 extern cvar_t *gl_customheight;

 #ifdef HT_WITH_RETEXTURE
 extern cvar_t *gl_retexturing;
 #endif

 extern cvar_t *gl_lightmap;
 extern cvar_t *gl_shadows;
 extern cvar_t *gl_stencilshadow;
 extern cvar_t *gl_dynamic;
 extern cvar_t *gl_nobind;
 extern cvar_t *gl_round_down;
 extern cvar_t *gl_picmip;
 extern cvar_t *gl_skymip;
 extern cvar_t *gl_showtris;
 extern cvar_t *gl_finish;
 extern cvar_t *gl_ztrick;
 extern cvar_t *gl_zfix;
 extern cvar_t *gl_clear;
 extern cvar_t *gl_cull;
 extern cvar_t *gl_poly;
 extern cvar_t *gl_texsort;
 extern cvar_t *gl_polyblend;
 extern cvar_t *gl_flashblend;
 extern cvar_t *gl_lightmaptype;
 extern cvar_t *gl_modulate;
 extern cvar_t *gl_playermip;
 extern cvar_t *gl_drawbuffer;
 extern cvar_t *gl_3dlabs_broken;
 extern cvar_t *gl_swapinterval;
 extern cvar_t *gl_anisotropic;
 extern cvar_t *gl_anisotropic_avail;
 extern cvar_t *gl_texturemode;
 extern cvar_t *gl_texturealphamode;
 extern cvar_t *gl_texturesolidmode;
 extern cvar_t *gl_saturatelighting;
 extern cvar_t *gl_lockpvs;

 extern cvar_t *vid_fullscreen;
 extern cvar_t *vid_gamma;

 extern cvar_t *intensity;

 extern q_int32_t gl_lightmap_format;
 extern q_int32_t gl_solid_format;
 extern q_int32_t gl_alpha_format;
 extern q_int32_t gl_tex_solid_format;
 extern q_int32_t gl_tex_alpha_format;

 extern q_int32_t c_visible_lightmaps;
 extern q_int32_t c_visible_textures;

 extern float r_world_matrix[16];

 void R_TranslatePlayerSkin ( q_int32_t playernum );
 void R_Bind ( q_int32_t texnum );
 void R_MBind ( GLenum target, q_int32_t texnum );
 void R_TexEnv ( GLenum value );
 void R_EnableMultitexture ( qboolean enable );
 void R_SelectTexture ( GLenum );

 void R_LightPoint ( vec3_t p, vec3_t color );
 void R_PushDlights ( void );

 extern model_t *r_worldmodel;
 extern q_uint32_t d_8to24table[256];
 extern q_int32_t registration_sequence;

 void V_AddBlend ( float r, float g, float b, float a, float *v_blend );

 void R_RenderView ( refdef_t *fd );
 void R_ScreenShot ( void );
 void R_DrawAliasModel ( entity_t *e );
 void R_DrawBrushModel ( entity_t *e );
 void R_DrawSpriteModel ( entity_t *e );
 void R_DrawBeam ( entity_t *e );
 void R_DrawWorld ( void );
 void R_RenderDlights ( void );
 void R_DrawAlphaSurfaces ( void );
 void R_RenderBrushPoly ( msurface_t *fa );
 void R_InitParticleTexture ( void );
 void Draw_InitLocal ( void );
 void R_SubdivideSurface ( msurface_t *fa );
 qboolean R_CullBox ( vec3_t mins, vec3_t maxs );
 void R_RotateForEntity ( entity_t *e );
 void R_MarkLeaves ( void );

 glpoly_t *WaterWarpPolyVerts ( glpoly_t *p );
 void R_EmitWaterPolys ( msurface_t *fa );
 void R_AddSkySurface ( msurface_t *fa );
 void R_ClearSkyBox ( void );
 void R_DrawSkyBox ( void );
 void R_MarkLights ( dlight_t *light, q_int32_t bit, mnode_t *node );

 void COM_StripExtension ( char *in, char *out );

 void R_SwapBuffers ( q_int32_t );

 q_int32_t Draw_GetPalette ( void );

 void R_ResampleTexture ( q_uint32_t *in, q_int32_t inwidth, q_int32_t inheight,
                          q_uint32_t *out, q_int32_t outwidth, q_int32_t outheight );

 void LoadPCX ( char *filename, byte **pic, byte **palette,
                q_int32_t *width, q_int32_t *height );
 image_t *LoadWal ( char *name );
 void LoadJPG ( char *origname, byte **pic, q_int32_t *width, q_int32_t *height );
 void LoadTGA ( char *origname, byte **pic, q_int32_t *width, q_int32_t *height );
 void GetWalInfo ( char *name, q_int32_t *width, q_int32_t *height );
 void GetPCXInfo ( char *filename, q_int32_t *width, q_int32_t *height );
 image_t *R_LoadPic ( char *name, byte *pic, q_int32_t width, q_int32_t realwidth,
                      q_int32_t height, q_int32_t realheight, imagetype_t type, q_int32_t bits );
 image_t *R_FindImage ( char *name, imagetype_t type );
 void R_TextureMode ( char *string );
 void R_ImageList_f ( void );

 void R_SetTexturePalette ( q_uint32_t palette[256] );

 void R_InitImages ( void );
 void R_ShutdownImages ( void );

 void R_FreeUnusedImages ( void );

 void R_TextureAlphaMode ( char *string );
 void R_TextureSolidMode ( char *string );
 q_int32_t Scrap_AllocBlock ( q_int32_t w, q_int32_t h, q_int32_t *x, q_int32_t *y );

 /* GL extension emulation functions */
 void R_DrawParticles2 ( q_int32_t n,
                         const particle_t particles[],
                         const q_uint32_t colortable[768] );

 /*
  * GL config stuff
  */

 typedef struct {
   q_int32_t renderer;
   const char *renderer_string;
   const char *vendor_string;
   const char *version_string;
   const char *extensions_string;

   qboolean allow_cds;
   qboolean mtexcombine;

   qboolean anisotropic;
   float max_anisotropy;
 } glconfig_t;

 typedef struct {
   float inverse_intensity;
   qboolean fullscreen;

   q_int32_t prev_mode;

   q_uint8_t *d_16to8table;

   q_int32_t lightmap_textures;

   q_int32_t currenttextures[2];
   q_int32_t currenttmu;

   float camera_separation;
   qboolean stereo_enabled;

   qboolean hwgamma;

   q_uint8_t originalRedGammaTable[256];
   q_uint8_t originalGreenGammaTable[256];
   q_uint8_t originalBlueGammaTable[256];
 } glstate_t;

 typedef struct {
   q_int32_t internal_format;
   q_int32_t current_lightmap_texture;

   msurface_t *lightmap_surfaces[MAX_LIGHTMAPS];

   q_int32_t allocated[BLOCK_WIDTH];

   /* the lightmap texture data needs to be kept in
      main memory so texsubimage can update properly */
   byte lightmap_buffer[4 * BLOCK_WIDTH *BLOCK_HEIGHT];
 } gllightmapstate_t;

 extern glconfig_t gl_config;
 extern glstate_t gl_state;

 /*
  * Initializes the SDL OpenGL context
  */
 q_int32_t GLimp_Init ( void );

 /*
  * Shuts the SDL render backend down
  */
 void GLimp_Shutdown ( void );

 /*
  * Changes the video mode
  */
 q_int32_t GLimp_SetMode ( q_int32_t *pwidth, q_int32_t *pheight, q_int32_t mode, qboolean fullscreen );

 /*
  * Returns the address of the GL function proc,
  * or NULL if the function is not found.
  */
 void *GLimp_GetProcAddress ( const char *proc );

 #endif

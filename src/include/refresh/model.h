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
 * Header for the model stuff.
 *
 * =======================================================================
 */

 #ifndef REF_MODEL_H
 #define REF_MODEL_H

 #include "prereqs.h"

 #define SIDE_FRONT 0
 #define SIDE_BACK 1
 #define SIDE_ON 2

 #define SURF_PLANEBACK 2
 #define SURF_DRAWSKY 4
 #define SURF_DRAWTURB 0x10
 #define SURF_DRAWBACKGROUND 0x40
 #define SURF_UNDERWATER 0x80
 #define VERTEXSIZE 7

 /* in memory representation */
 typedef struct {
   vec3_t position;
 } mvertex_t;

 typedef struct {
   vec3_t mins, maxs;
   vec3_t origin; /* for sounds or lights */
   float radius;
   q_int32_t headnode;
   q_int32_t visleafs; /* not including the solid leaf 0 */
   q_int32_t firstface, numfaces;
 } mmodel_t;

 typedef struct {
   q_uint16_t v[2];
   q_uint32_t cachededgeoffset;
 } medge_t;

 typedef struct mtexinfo_s {
   float vecs[2][4];
   q_int32_t flags;
   q_int32_t numframes;
   struct mtexinfo_s *next; /* animation chain */
   image_t *image;
 } mtexinfo_t;

 typedef struct glpoly_s {
   struct  glpoly_s *next;
   struct  glpoly_s *chain;
   q_int32_t numverts;
   q_int32_t flags; /* for SURF_UNDERWATER (not needed anymore?) */
   float verts[4][VERTEXSIZE]; /* variable sized (xyz s1t1 s2t2) */
 } glpoly_t;

 typedef struct msurface_s {
   q_int32_t visframe; /* should be drawn when node is crossed */

   cplane_t *plane;
   q_int32_t flags;

   q_int32_t firstedge;          /* look up in model->surfedges[], negative numbers */
   q_int32_t numedges;           /* are backwards edges */

   q_int16_t texturemins[2];
   q_int16_t extents[2];

   q_int32_t light_s, light_t;           /* gl lightmap coordinates */
   q_int32_t dlight_s, dlight_t;         /* gl lightmap coordinates for dynamic lightmaps */

   glpoly_t *polys;                /* multiple if warped */
   struct  msurface_s *texturechain;
   struct  msurface_s *lightmapchain;

   mtexinfo_t *texinfo;

   /* lighting info */
   q_int32_t dlightframe;
   q_int32_t dlightbits;

   q_int32_t lightmaptexturenum;
   byte styles[MAXLIGHTMAPS];
   float cached_light[MAXLIGHTMAPS];       /* values currently used in lightmap */
   byte *samples;                          /* [numstyles*surfsize] */
 } msurface_t;

 typedef struct mnode_s {
   /* common with leaf */
   q_int32_t contents;               /* -1, to differentiate from leafs */
   q_int32_t visframe;               /* node needs to be traversed if current */

   float minmaxs[6];           /* for bounding box culling */

   struct mnode_s *parent;

   /* node specific */
   cplane_t *plane;
   struct mnode_s *children[2];

   q_uint16_t firstsurface;
   q_uint16_t numsurfaces;
 } mnode_t;

 typedef struct mleaf_s {
   /* common with node */
   q_int32_t contents;               /* wil be a negative contents number */
   q_int32_t visframe;               /* node needs to be traversed if current */

   float minmaxs[6];           /* for bounding box culling */

   struct mnode_s *parent;

   /* leaf specific */
   q_int32_t cluster;
   q_int32_t area;

   msurface_t **firstmarksurface;
   q_int32_t nummarksurfaces;
 } mleaf_t;

 /* Whole model */
 typedef enum {mod_bad, mod_brush, mod_sprite, mod_alias} modtype_t;

 typedef struct model_s {
   char name[MAX_QPATH];

   q_int32_t registration_sequence;

   modtype_t type;
   q_int32_t numframes;

   q_int32_t flags;

   /* volume occupied by the model graphics */
   vec3_t mins, maxs;
   float radius;

   /* solid volume for clipping */
   qboolean clipbox;
   vec3_t clipmins, clipmaxs;

   /* brush model */
   q_int32_t firstmodelsurface, nummodelsurfaces;
   q_int32_t lightmap; /* only for submodels */

   q_int32_t numsubmodels;
   mmodel_t *submodels;

   q_int32_t numplanes;
   cplane_t *planes;

   q_int32_t numleafs; /* number of visible leafs, not counting 0 */
   mleaf_t *leafs;

   q_int32_t numvertexes;
   mvertex_t *vertexes;

   q_int32_t numedges;
   medge_t *edges;

   q_int32_t numnodes;
   q_int32_t firstnode;
   mnode_t *nodes;

   q_int32_t numtexinfo;
   mtexinfo_t *texinfo;

   q_int32_t numsurfaces;
   msurface_t *surfaces;

   q_int32_t numsurfedges;
   q_int32_t *surfedges;

   q_int32_t nummarksurfaces;
   msurface_t **marksurfaces;

   dvis_t *vis;

   byte *lightdata;

   /* for alias models and skins */
   image_t *skins[MAX_MD2SKINS];

   q_int32_t extradatasize;
   void *extradata;
 } model_t;

 void Mod_Init ( void );
 void Mod_ClearAll ( void );
 model_t *Mod_ForName ( char *name, qboolean crash );
 mleaf_t *Mod_PointInLeaf ( float *p, model_t *model );
 byte *Mod_ClusterPVS ( q_int32_t cluster, model_t *model );
 void Mod_Modellist_f ( void );
 void Mod_FreeAll ( void );
 void Mod_Free ( model_t *mod );

 #endif

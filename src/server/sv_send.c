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
 * Message sending and multiplexing.
 *
 * =======================================================================
 */

 #include "prereqs.h"
 #include "filesystem.h"
 #include "server.h"

 char sv_outputbuf[SV_OUTPUTBUF_LENGTH];

 /* ========================================================================= */
 void
 SV_FlushRedirect ( q_int32_t sv_redirected, char *outputbuf )
 {
   if ( sv_redirected == RD_PACKET ) {
     Netchan_OutOfBandPrint ( NS_SERVER, net_from, "print\n%s", outputbuf );
   } else if ( sv_redirected == RD_CLIENT ) {
     MSG_WriteByte ( &sv_client->netchan.message, svc_print );
     MSG_WriteByte ( &sv_client->netchan.message, PRINT_HIGH );
     MSG_WriteString ( &sv_client->netchan.message, outputbuf );
   }
 }

 /* ========================================================================= */
 void
 SV_ClientPrintf ( client_t *cl, q_int32_t level, char *fmt, ... )
 {
   va_list argptr;
   char string[1024];

   if ( level < cl->messagelevel ) {
     return;
   }

   va_start ( argptr, fmt );
   vsprintf ( string, fmt, argptr );
   va_end ( argptr );
   MSG_WriteByte ( &cl->netchan.message, svc_print );
   MSG_WriteByte ( &cl->netchan.message, level );
   MSG_WriteString ( &cl->netchan.message, string );
 }

 /* ========================================================================= */
 void
 SV_BroadcastPrintf ( q_int32_t level, char *fmt, ... )
 {
   va_list argptr;
   char string[2048];
   client_t *cl;
   q_int32_t i;
   va_start ( argptr, fmt );
   vsprintf ( string, fmt, argptr );
   va_end ( argptr );

   /* echo to console */
   if ( dedicated->value ) {
     char copy[1024];
     q_int32_t i;

     /* mask off high bits */
     for ( i = 0; i < 1023 && string[i]; i++ ) {
       copy[i] = string[i] & 127;
     }

     copy[i] = 0;
     Com_Printf ( "%s", copy );
   }

   for ( i = 0, cl = svs.clients; i < maxclients->value; i++, cl++ ) {
     if ( level < cl->messagelevel ) {
       continue;
     }

     if ( cl->state != cs_spawned ) {
       continue;
     }

     MSG_WriteByte ( &cl->netchan.message, svc_print );
     MSG_WriteByte ( &cl->netchan.message, level );
     MSG_WriteString ( &cl->netchan.message, string );
   }
 }

 /* ========================================================================= */
 void
 SV_BroadcastCommand ( char *fmt, ... )
 {
   va_list argptr;
   char string[1024];

   if ( !sv.state ) {
     return;
   }

   va_start ( argptr, fmt );
   vsprintf ( string, fmt, argptr );
   va_end ( argptr );
   MSG_WriteByte ( &sv.multicast, svc_stufftext );
   MSG_WriteString ( &sv.multicast, string );
   SV_Multicast ( NULL, MULTICAST_ALL_R );
 }

 /* ========================================================================= */
 void
 SV_Multicast ( vec3_t origin, multicast_t to )
 {
   client_t *client;
   byte *mask;
   q_int32_t leafnum = 0, cluster;
   q_int32_t j;
   qboolean reliable;
   q_int32_t area1, area2;
   reliable = false;

   if ( ( to != MULTICAST_ALL_R ) && ( to != MULTICAST_ALL ) ) {
     leafnum = CM_PointLeafnum ( origin );
     area1 = CM_LeafArea ( leafnum );
   } else {
     area1 = 0;
   }

   /* if doing a serverrecord, store everything */
   if ( svs.demofile ) {
     SZ_Write ( &svs.demo_multicast, sv.multicast.data, sv.multicast.cursize );
   }

   switch ( to ) {
   case MULTICAST_ALL_R:
     reliable = true; /* intentional fallthrough */

   case MULTICAST_ALL:
     mask = NULL;
     break;

   case MULTICAST_PHS_R:
     reliable = true; /* intentional fallthrough */

   case MULTICAST_PHS:
     leafnum = CM_PointLeafnum ( origin );
     cluster = CM_LeafCluster ( leafnum );
     mask = CM_ClusterPHS ( cluster );
     break;

   case MULTICAST_PVS_R:
     reliable = true; /* intentional fallthrough */

   case MULTICAST_PVS:
     leafnum = CM_PointLeafnum ( origin );
     cluster = CM_LeafCluster ( leafnum );
     mask = CM_ClusterPVS ( cluster );
     break;

   default:
     mask = NULL;
     Com_Error ( ERR_FATAL, "SV_Multicast: bad to:%i", to );
   }

   /* send the data to all relevent clients */
   for ( j = 0, client = svs.clients; j < maxclients->value; j++, client++ ) {
     if ( ( client->state == cs_free ) || ( client->state == cs_zombie ) ) {
       continue;
     }

     if ( ( client->state != cs_spawned ) && !reliable ) {
       continue;
     }

     if ( mask ) {
       leafnum = CM_PointLeafnum ( client->edict->s.origin );
       cluster = CM_LeafCluster ( leafnum );
       area2 = CM_LeafArea ( leafnum );

       if ( !CM_AreasConnected ( area1, area2 ) ) {
         continue;
       }

       if ( mask && ( ! ( mask[cluster >> 3] & ( 1 << ( cluster & 7 ) ) ) ) ) {
         continue;
       }
     }

     if ( reliable ) {
       SZ_Write ( &client->netchan.message, sv.multicast.data,
                  sv.multicast.cursize );
     } else {
       SZ_Write ( &client->datagram, sv.multicast.data, sv.multicast.cursize );
     }
   }

   SZ_Clear ( &sv.multicast );
 }

 /* ========================================================================= */
 void
 SV_StartSound ( vec3_t origin, edict_t *entity, q_int32_t channel, q_int32_t soundindex,
                 float volume, float attenuation, float timeofs )
 {
   q_int32_t sendchan;
   q_int32_t flags;
   q_int32_t i;
   q_int32_t ent;
   vec3_t origin_v;
   qboolean use_phs;

   if ( ( volume < 0 ) || ( volume > 1.0 ) ) {
     Com_Error ( ERR_FATAL, "SV_StartSound: volume = %f", volume );
   }

   if ( ( attenuation < 0 ) || ( attenuation > 4 ) ) {
     Com_Error ( ERR_FATAL, "SV_StartSound: attenuation = %f", attenuation );
   }

   if ( ( timeofs < 0 ) || ( timeofs > 0.255 ) ) {
     Com_Error ( ERR_FATAL, "SV_StartSound: timeofs = %f", timeofs );
   }

   ent = NUM_FOR_EDICT ( entity );

   if ( channel & 8 ) { /* no PHS flag */
     use_phs = false;
     channel &= 7;
   } else {
     use_phs = true;
   }

   sendchan = ( ent << 3 ) | ( channel & 7 );
   flags = 0;

   if ( volume != DEFAULT_SOUND_PACKET_VOLUME ) {
     flags |= SND_VOLUME;
   }

   if ( attenuation != DEFAULT_SOUND_PACKET_ATTENUATION ) {
     flags |= SND_ATTENUATION;
   }

   /* the client doesn't know that bmodels have
      weird origins the origin can also be
      explicitly set */
   if ( ( entity->svflags & SVF_NOCLIENT ) ||
        ( entity->solid == SOLID_BSP ) ||
        origin ) {
     flags |= SND_POS;
   }

   /* always send the entity number for channel overrides */
   flags |= SND_ENT;

   if ( timeofs ) {
     flags |= SND_OFFSET;
   }

   /* use the entity origin unless it is a bmodel or explicitly specified */
   if ( !origin ) {
     origin = origin_v;

     if ( entity->solid == SOLID_BSP ) {
       for ( i = 0; i < 3; i++ ) {
         origin_v[i] = entity->s.origin[i] + 0.5f *
                       ( entity->mins[i] + entity->maxs[i] );
       }
     } else {
       VectorCopy ( entity->s.origin, origin_v );
     }
   }

   MSG_WriteByte ( &sv.multicast, svc_sound );
   MSG_WriteByte ( &sv.multicast, flags );
   MSG_WriteByte ( &sv.multicast, soundindex );

   if ( flags & SND_VOLUME ) {
     MSG_WriteByte ( &sv.multicast, volume * 255 );
   }

   if ( flags & SND_ATTENUATION ) {
     MSG_WriteByte ( &sv.multicast, attenuation * 64 );
   }

   if ( flags & SND_OFFSET ) {
     MSG_WriteByte ( &sv.multicast, timeofs * 1000 );
   }

   if ( flags & SND_ENT ) {
     MSG_WriteShort ( &sv.multicast, sendchan );
   }

   if ( flags & SND_POS ) {
     MSG_WritePos ( &sv.multicast, origin );
   }

   /* if the sound doesn't attenuate,send it to everyone
      (global radio chatter, voiceovers, etc) */
   if ( attenuation == ATTN_NONE ) {
     use_phs = false;
   }

   if ( channel & CHAN_RELIABLE ) {
     if ( use_phs ) {
       SV_Multicast ( origin, MULTICAST_PHS_R );
     } else {
       SV_Multicast ( origin, MULTICAST_ALL_R );
     }
   } else {
     if ( use_phs ) {
       SV_Multicast ( origin, MULTICAST_PHS );
     } else {
       SV_Multicast ( origin, MULTICAST_ALL );
     }
   }
 }

 /* ========================================================================= */
 qboolean
 SV_SendClientDatagram ( client_t *client )
 {
   byte msg_buf[MAX_MSGLEN];
   sizebuf_t msg;
   SV_BuildClientFrame ( client );
   SZ_Init ( &msg, msg_buf, sizeof ( msg_buf ) );
   msg.allowoverflow = true;
   /* send over all the relevant entity_state_t
      and the player_state_t */
   SV_WriteFrameToClient ( client, &msg );

   /* copy the accumulated multicast datagram
      for this client out to the message
      it is necessary for this to be after the WriteEntities
      so that entity references will be current */
   if ( client->datagram.overflowed ) {
     Com_Printf ( "WARNING: datagram overflowed for %s\n", client->name );
   } else {
     SZ_Write ( &msg, client->datagram.data, client->datagram.cursize );
   }

   SZ_Clear ( &client->datagram );

   if ( msg.overflowed ) {
     /* must have room left for the packet header */
     Com_Printf ( "WARNING: msg overflowed for %s\n", client->name );
     SZ_Clear ( &msg );
   }

   /* send the datagram */
   Netchan_Transmit ( &client->netchan, msg.cursize, msg.data );
   /* record the size for rate estimation */
   client->message_size[sv.framenum % RATE_MESSAGES] = msg.cursize;
   return true;
 }

 /* ========================================================================= */
 void
 SV_DemoCompleted ( void )
 {
   if ( sv.demofile ) {
     FS_FCloseFile ( ( size_t ) sv.demofile );
     sv.demofile = NULL;
   }

   SV_Nextserver();
 }

 /*
  * Returns true if the client is over its current
  * bandwidth estimation and should not be sent another packet
  */
 qboolean
 SV_RateDrop ( client_t *c )
 {
   q_int32_t total;
   q_int32_t i;

   /* never drop over the loopback */
   if ( c->netchan.remote_address.type == NA_LOOPBACK ) {
     return false;
   }

   total = 0;

   for ( i = 0; i < RATE_MESSAGES; i++ ) {
     total += c->message_size[i];
   }

   if ( total > c->rate ) {
     c->surpressCount++;
     c->message_size[sv.framenum % RATE_MESSAGES] = 0;
     return true;
   }

   return false;
 }

 /* ========================================================================= */
 void
 SV_SendClientMessages ( void )
 {
   q_int32_t i;
   client_t *c;
   q_int32_t msglen;
   byte msgbuf[MAX_MSGLEN];
   size_t r;
   msglen = 0;

   /* read the next demo message if needed */
   if ( sv.demofile && ( sv.state == ss_demo ) ) {
     if ( sv_paused->value ) {
       msglen = 0;
     } else {
       /* get the next message */
       r = FS_FRead ( &msglen, 4, 1, ( size_t ) sv.demofile );

       if ( r != 4 ) {
         SV_DemoCompleted();
         return;
       }

       msglen = LittleLong ( msglen );

       if ( msglen == -1 ) {
         SV_DemoCompleted();
         return;
       }

       if ( msglen > MAX_MSGLEN ) {
         Com_Error ( ERR_DROP,
                     "SV_SendClientMessages: msglen > MAX_MSGLEN" );
       }

       r = FS_FRead ( msgbuf, msglen, 1, ( size_t ) sv.demofile );

       if ( r != msglen ) {
         SV_DemoCompleted();
         return;
       }
     }
   }

   /* send a message to each connected client */
   for ( i = 0, c = svs.clients; i < maxclients->value; i++, c++ ) {
     if ( !c->state ) {
       continue;
     }

     /* if the reliable message
        overflowed, drop the
        client */
     if ( c->netchan.message.overflowed ) {
       SZ_Clear ( &c->netchan.message );
       SZ_Clear ( &c->datagram );
       SV_BroadcastPrintf ( PRINT_HIGH, "%s overflowed\n", c->name );
       SV_DropClient ( c );
     }

     if ( ( sv.state == ss_cinematic ) ||
          ( sv.state == ss_demo ) ||
          ( sv.state == ss_pic ) ) {
       Netchan_Transmit ( &c->netchan, msglen, msgbuf );
     } else if ( c->state == cs_spawned ) {
       /* don't overrun bandwidth */
       if ( SV_RateDrop ( c ) ) {
         continue;
       }

       SV_SendClientDatagram ( c );
     } else {
       /* just update reliable if needed */
       if ( c->netchan.message.cursize ||
            ( curtime - c->netchan.last_sent > 1000 ) ) {
         Netchan_Transmit ( &c->netchan, 0, NULL );
       }
     }
   }
 }

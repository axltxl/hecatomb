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
 * Corresponding header for crc.c
 *
 * =======================================================================
 */

 #ifndef CO_CRC_H
 #define CO_CRC_H

 #include "prereqs.h"

 void CRC_Init ( q_uint16_t *crcvalue );
 void CRC_ProcessByte ( q_uint16_t *crcvalue, byte data );
 q_uint16_t CRC_Value ( q_uint16_t crcvalue );
 q_uint16_t CRC_Block ( byte *start, q_int32_t count );

 #endif /* CO_CRC_H */

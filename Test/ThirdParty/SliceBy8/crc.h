/*++
 *
 * Copyright (c) 2004-2006 Intel Corporation - All Rights Reserved
 * 
 * This software program is licensed subject to the BSD License, 
 * available at http://www.opensource.org/licenses/bsd-license.html
 *
 --*/

#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED

#define MODE_BEGIN	0
#define	MODE_CONT	1
#define	MODE_END	2
#define	MODE_BODY	3
#define	MODE_ALIGN	4

#ifdef __cplusplus
extern "C"
{
#endif	/* __cplusplus */

#include <stdint.h> // uint8_t, uint32_t

/**
 *
 * Routine Description:
 *
 * Computes the CRC32 checksum for the specified buffer using the slicing by 8 
 * algorithm over 64 bit quantities.                      
 *
 * Arguments:
 *
 *		p_running_crc - pointer to the initial or final remainder value 
 *						used in CRC computations. It should be set to 
 *						non-NULL if the mode argument is equal to CONT or END
 *		p_buf - the packet buffer where crc computations are being performed
 *		length - the length of p_buf in bytes
 *		init_bytes - the number of initial bytes that need to be procesed before
 *					 aligning p_buf to multiples of 4 bytes
 *		mode - can be any of the following: BEGIN, CONT, END, BODY, ALIGN 
 *
 * Return value:
 *		
 *		The computed CRC32 value
 */
uint32_t
crc32_sb8_64_bit(
	uint32_t* p_running_crc,
    const uint8_t*	p_buf,
    const uint32_t length,
	const uint32_t init_bytes,
	uint8_t			mode);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	//CRC_H_INCLUDED


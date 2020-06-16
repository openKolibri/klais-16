/*
 *  Project     Segmented LED Display - ASCII Library
 *  @author     David Madison
 *  @link       github.com/dmadison/Segmented-LED-Display-ASCII
 *  @license    MIT - Copyright (c) 2017 David Madison
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef _SEG_ASCII_H
#define _SEG_ASCII_H

#include <stdint.h>
#define _DP 0x10000
#define _U  0x08000
#define _T  0x04000
#define _S  0x02000
#define _R  0x01000
#define _P  0x00800
#define _N  0x00400
#define _M  0x00200
#define _K  0x00100
#define _H  0x00080
#define _G  0x00040
#define _F  0x00020
#define _E  0x00010
#define _D  0x00008
#define _C  0x00004
#define _B  0x00002
#define _A  0x00001
 
const uint32_t SixteenSegmentASCII[96] = {
	 0                                                                  , /* (space) */
	 _DP                                                |_D |_C         , /* ! */
	                             _M                         |_C         , /* " */
	     _U     |_S     |_P     |_M             |_F |_E |_D |_C         , /* # */
	     _U     |_S     |_P     |_M     |_H     |_F |_E |_D     |_B |_A , /* $ */
	     _U |_T |_S     |_P |_N |_M     |_H         |_E |_D         |_A , /* % */
	     _U         |_R         |_M |_K     |_G |_F |_E             |_A , /* & */
	                             _M                                     , /* ' */
	                 _R     |_N                                         , /* ( */
	         _T                     |_K                                 , /* ) */
	     _U |_T |_S |_R |_P |_N |_M |_K                                 , /* * */
	     _U     |_S     |_P     |_M                                     , /* + */
	         _T                                                         , /* , */
	     _U             |_P                                             , /* - */
	 _DP                                                                , /* . */
	         _T             |_N                                         , /* / */
	         _T             |_N         |_H |_G |_F |_E |_D |_C |_B |_A , /* 0 */
	                         _N                         |_D |_C         , /* 1 */
	     _U             |_P                 |_G |_F |_E     |_C |_B |_A , /* 2 */
	                     _P                     |_F |_E |_D |_C |_B |_A , /* 3 */
	     _U             |_P             |_H             |_D |_C         , /* 4 */
	     _U         |_R                 |_H     |_F |_E         |_B |_A , /* 5 */
	     _U             |_P             |_H |_G |_F |_E |_D     |_B |_A , /* 6 */
	                                                     _D |_C |_B |_A , /* 7 */
	     _U             |_P             |_H |_G |_F |_E |_D |_C |_B |_A , /* 8 */
	     _U             |_P             |_H     |_F |_E |_D |_C |_B |_A , /* 9 */
	             _S             |_M                                     , /* : */
	         _T                 |_M                                     , /* ; */
	     _U         |_R     |_N                                         , /* < */
	     _U             |_P                     |_F |_E                 , /* = */
	         _T         |_P         |_K                                 , /* > */
	 _DP        |_S     |_P                                 |_C |_B |_A , /* ? */
	                     _P     |_M     |_H |_G |_F |_E     |_C |_B |_A , /* @ */
	     _U             |_P             |_H |_G         |_D |_C |_B |_A , /* A */
	             _S     |_P     |_M             |_F |_E |_D |_C |_B |_A , /* B */
	                                     _H |_G |_F |_E         |_B |_A , /* C */
	             _S             |_M             |_F |_E |_D |_C |_B |_A , /* D */
	     _U                             |_H |_G |_F |_E         |_B |_A , /* E */
	     _U                             |_H |_G                 |_B |_A , /* F */
	                     _P             |_H |_G |_F |_E |_D     |_B |_A , /* G */
	     _U             |_P             |_H |_G         |_D |_C         , /* H */
	             _S             |_M             |_F |_E         |_B |_A , /* I */
	                                         _G |_F |_E |_D |_C         , /* J */
	     _U         |_R     |_N         |_H |_G                         , /* K */
	                                     _H |_G |_F |_E                 , /* L */
	                         _N     |_K |_H |_G         |_D |_C         , /* M */
	                 _R             |_K |_H |_G         |_D |_C         , /* N */
	                                     _H |_G |_F |_E |_D |_C |_B |_A , /* O */
	     _U             |_P             |_H |_G             |_C |_B |_A , /* P */
	                 _R                 |_H |_G |_F |_E |_D |_C |_B |_A , /* Q */
	     _U         |_R |_P             |_H |_G             |_C |_B |_A , /* R */
	     _U             |_P             |_H     |_F |_E |_D     |_B |_A , /* S */
	             _S             |_M                             |_B |_A , /* T */
	                                     _H |_G |_F |_E |_D |_C         , /* U */
	         _T             |_N         |_H |_G                         , /* V */
	         _T     |_R                 |_H |_G         |_D |_C         , /* W */
	         _T     |_R     |_N     |_K                                 , /* X */
	     _U             |_P             |_H     |_F |_E |_D |_C         , /* Y */
	         _T             |_N                 |_F |_E         |_B |_A , /* Z */
	             _S             |_M                 |_E         |_B     , /* [ */
	                 _R             |_K                                 , /* \ */
	             _S             |_M             |_F                 |_A , /* ] */
	         _T     |_R                                                 , /* ^ */
	                                             _F |_E                 , /* _ */
	                                 _K                                 , /* ` */
	     _U     |_S                         |_G |_F |_E                 , /* a */
	     _U     |_S                     |_H |_G |_F                     , /* b */
	     _U                                 |_G |_F                     , /* c */
	             _S     |_P                         |_E |_D |_C         , /* d */
	     _U |_T                             |_G |_F                     , /* e */
	     _U     |_S     |_P     |_M                             |_B     , /* f */
	     _U     |_S             |_M     |_H     |_F                 |_A , /* g */
	     _U     |_S                     |_H |_G                         , /* h */
	             _S                                                     , /* i */
	             _S             |_M         |_G |_F                     , /* j */
	             _S |_R     |_N |_M                                     , /* k */
	                                     _H |_G                         , /* l */
	     _U     |_S     |_P                 |_G         |_D             , /* m */
	     _U     |_S                         |_G                         , /* n */
	     _U     |_S                         |_G |_F                     , /* o */
	     _U                     |_M     |_H |_G                     |_A , /* p */
	     _U     |_S             |_M     |_H                         |_A , /* q */
	     _U                                 |_G                         , /* r */
	     _U     |_S                     |_H     |_F                 |_A , /* s */
	     _U                             |_H |_G |_F                     , /* t */
	             _S                         |_G |_F                     , /* u */
	         _T                             |_G                         , /* v */
	         _T     |_R                     |_G         |_D             , /* w */
	         _T     |_R     |_N     |_K                                 , /* x */
	                     _P     |_M                 |_E |_D |_C         , /* y */
	     _U |_T                                 |_F                     , /* z */
	     _U     |_S             |_M                 |_E         |_B     , /* { */
	             _S             |_M                                     , /* | */
	             _S     |_P     |_M             |_F                 |_A , /* } */
	     _U |_T         |_P |_N                                         , /* ~ */
	 0                                                                  , /* (del) */
};

#endif /* _SEG_ASCII_H */
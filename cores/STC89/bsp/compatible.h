/*
  compatible.h - Definitions for compatible with sdcc
  Copyright (c) 2019 huaweiwx@sina.com.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _compatible_h_
#define _compatible_h_

//#include "binary.h"
#include "intrins.h"

#ifdef  COMPATIBLE
#define bit       __bit
#define idata     __idata
#define pdata     __pdata
#define xdata     __xdata
#define data      __data
#define code      __code
#define interrupt __interrupt
#define reentrant __reentrant
#define _push_    __push   /* keil intrins.h */
#define _pop_     __pop    /* keil intrins.h */
#endif

#if defined(__SDCC_mcs51) /*for sdcc c51 */
	#define IDATA(t,v)	__idata	t v
	#define PDATA(t,v)	__pdata	t v
	#define XDATA(t,v)	__xdata	t v
	#define DATA(t,v)	__data	t v
	#define CODE(t,v)	__code	t v
#elif defined(__CX51__)  /* for keil c51 */
	#define IDATA(t,v)	t __idata	v
	#define PDATA(t,v)	t __pdata	v
	#define XDATA(t,v)	t __xdata	v
	#define DATA(t,v)	t __data	v
	#define CODE(t,v)	t __code	v
#else                    /*other for stm8/pic */
	#define IDATA(t,v)	t v
	#define PDATA(t,v)	t v
	#define XDATA(t,v)	t v
	#define DATA(t,v)	t v
	#define CODE(t,v)	const t v
#endif 

// SDCC defines a special bool type, use that if available
#ifdef __bool_true_false_are_defined
  #define TRUE  true
  #define FALSE false
#else
  typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#endif
  typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus, BitAction;
  typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
  typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;



#ifndef UNUSED
#define UNUSED(x)  (void)x
#endif

#endif //_compatible_h_

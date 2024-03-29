/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - gcop1_w.c                                               *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2002 Hacktarux                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>

#include "assemble.h"
#include "interpret.h"
#include "r4300/cp1_private.h"
#include "r4300/ops.h"
#include "r4300/r4300.h"
#include "r4300/recomph.h"

void gencvt_s_w(void)
{
#ifdef INTERPRET_CVT_S_W
   gencallinterp((unsigned int)cached_interpreter_table.CVT_S_W, 0);
#else
   gencheck_cop1_unusable();
   mov_eax_memoffs32((unsigned int*) (&g_state.regs.cp1_s[dst->f.cf.fs]));
   fild_preg32_dword(EAX);
   mov_eax_memoffs32((unsigned int*) (&g_state.regs.cp1_s[dst->f.cf.fd]));
   fstp_preg32_dword(EAX);
#endif
}

void gencvt_d_w(void)
{
#ifdef INTERPRET_CVT_D_W
   gencallinterp((unsigned int)cached_interpreter_table.CVT_D_W, 0);
#else
   gencheck_cop1_unusable();
   mov_eax_memoffs32((unsigned int*) (&g_state.regs.cp1_s[dst->f.cf.fs]));
   fild_preg32_dword(EAX);
   mov_eax_memoffs32((unsigned int*) (&g_state.regs.cp1_d[dst->f.cf.fd]));
   fstp_preg32_qword(EAX);
#endif
}


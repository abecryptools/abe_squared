/* 
 * This file is part of the ABE Squared (https://github.com/abecryptools/abe_squared).
 * Copyright (c) 2022 Antonio de la Piedra, Marloes Venema and Greg Alpár
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BENCH_DEFS_H
#define BENCH_DEFS_H

#include <assert.h>
#include <sched.h>
#include <stdbool.h>
#include <unistd.h>

#include "lib/zp_arith.h"
#include "lib/structures.h"
#include "lib/pairing_arith.h"
#include "lib/gt_arith.h"
#include "lib/g1_arith.h"

#include "legacy/l_zattributelist.h"  
#include "legacy/l_zconstants.h"      
#include "legacy/l_zinteger.h"  
#include "legacy/l_zpolicy.h"
#include "legacy/l_zbytestring.h"     
#include "legacy/l_zfunctioninput.h"  
#include "legacy/l_zobject.h"

#include "legacy/arith/l_zgroup.h"
#include "legacy/arith/l_zelement_bp.h"
#include "legacy/lsss/l_zlsss.h"

extern "C" {                                                                    
  #include "legacy/arith/l_zelement.h"
}

/* NTESTS is the number of tests per operation during the measurement process. */

#define NTESTS 10000 

#endif

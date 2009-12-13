/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/****************************************************************************

   Copyright (C) 2008, 2009 William Hart
   
*****************************************************************************/

#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"

void _fmpz_poly_sub(fmpz_poly_t res, const fmpz_poly_t poly1, const fmpz_poly_t poly2)
{
   ulong longer = FLINT_MAX(poly1->length, poly2->length);
	ulong shorter = FLINT_MIN(poly1->length, poly2->length);

   ulong i;
   for (i = 0; i < shorter; i++) // subtract up to the length of the shorter poly
      fmpz_sub(res->coeffs + i, poly1->coeffs + i, poly2->coeffs + i);   
   
   if (poly1 != res) // copy any remaining coefficients from poly1
      for (i = shorter; i < poly1->length; i++)
         fmpz_set(res->coeffs + i, poly1->coeffs + i);

   // careful, it is *always* necessary to negate coeffs from poly2, even if this is already res
	for (i = shorter; i < poly2->length; i++) 
      fmpz_neg(res->coeffs + i, poly2->coeffs + i);

   _fmpz_poly_set_length(res, longer);
   _fmpz_poly_normalise(res); // there may have been cancellation
}

void fmpz_poly_sub(fmpz_poly_t res, const fmpz_poly_t poly1, const fmpz_poly_t poly2)
{
   ulong longer = FLINT_MAX(poly1->length, poly2->length);

	fmpz_poly_fit_length(res, longer);
   
	_fmpz_poly_sub(res, poly1, poly2);
}

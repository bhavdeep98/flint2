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

   Copyright (C) 2009 William Hart

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "ulong_extras.h"

int main(void)
{
   int result;
   printf("sub....");
   fflush(stdout);
   
   fmpz_poly_randinit();
   
   // check a - b = a + neg(b)
   for (ulong i = 0; i < 10000UL; i++) 
   {
      fmpz_poly_t a, b, c, d;

      fmpz_poly_init(a);
      fmpz_poly_init(b);
      fmpz_poly_init(c);
      fmpz_poly_init(d);
      fmpz_poly_randtest(a, n_randint(100), n_randint(200));
      fmpz_poly_randtest(b, n_randint(100), n_randint(200));
      
      fmpz_poly_sub(c, a, b);
      fmpz_poly_neg(b, b);
      fmpz_poly_add(d, a, b);

      result = (fmpz_poly_equal(d, d));
      if (!result)
      {
         printf("Error:\n");
         fmpz_poly_print(a); printf("\n\n");
         fmpz_poly_print(b); printf("\n\n");
         fmpz_poly_print(c); printf("\n\n");
         fmpz_poly_print(d); printf("\n\n");
         abort();
      }

      fmpz_poly_clear(a);
      fmpz_poly_clear(b);
      fmpz_poly_clear(c);
      fmpz_poly_clear(d);
   }

   // check aliasing of a and c
   for (ulong i = 0; i < 10000UL; i++) 
   {
      fmpz_poly_t a, b, c;

      fmpz_poly_init(a);
      fmpz_poly_init(b);
      fmpz_poly_init(c);
      fmpz_poly_randtest(a, n_randint(100), n_randint(200));
      fmpz_poly_randtest(b, n_randint(100), n_randint(200));
      
      fmpz_poly_sub(c, a, b);
      fmpz_poly_sub(a, a, b);

      result = (fmpz_poly_equal(a, c));
      if (!result)
      {
         printf("Error:\n");
         fmpz_poly_print(a); printf("\n\n");
         fmpz_poly_print(b); printf("\n\n");
         fmpz_poly_print(c); printf("\n\n");
         abort();
      }

      fmpz_poly_clear(a);
      fmpz_poly_clear(b);
      fmpz_poly_clear(c);
   }

   // check aliasing of b and c
   for (ulong i = 0; i < 10000UL; i++) 
   {
      fmpz_poly_t a, b, c;

      fmpz_poly_init(a);
      fmpz_poly_init(b);
      fmpz_poly_init(c);
      fmpz_poly_randtest(a, n_randint(100), n_randint(200));
      fmpz_poly_randtest(b, n_randint(100), n_randint(200));
      
      fmpz_poly_sub(c, a, b);
      fmpz_poly_sub(b, a, b);

      result = (fmpz_poly_equal(b, c));
      if (!result)
      {
         printf("Error:\n");
         fmpz_poly_print(a); printf("\n\n");
         fmpz_poly_print(b); printf("\n\n");
         fmpz_poly_print(c); printf("\n\n");
         abort();
      }

      fmpz_poly_clear(a);
      fmpz_poly_clear(b);
      fmpz_poly_clear(c);
   }

   fmpz_poly_randclear();
      
   _fmpz_cleanup();
   printf("PASS\n");
   return 0;
}

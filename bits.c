/* 
 * CS:APP Data Lab 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#include "btest.h"
#include <limits.h>

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
team_struct team =
{
   "blah", 
   "gah",
   "",
   ""
};

#if 0
/*
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
#endif

/*
 * STEP 3: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest test harness to check that your solutions produce 
 *      the correct answers. Watch out for corner cases around Tmin and Tmax.
 */
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
/* 
 *!0 = 0x01
 *!(x != 0) = 0x00
 */  
int isZero(int x) {
  
  return !x;
}


/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
/* 
 * -1 = 11111111 11111111 11111111 11111111 = -2^{31} + 2^{30} + ... + 1 = -2^{31} + 2^{31} - 1 = -1
 *  0 = 00000000 00000000 00000000 00000000
 *  => ~0 = -1
 */
int minusOne(void) {
  
  return ~0x00;
}


/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 2
 */
/*
 * xor truth table:
 *                     
 *	    | a | b | a^b | ~(a&b) = c | (~a)&(~b) | ~((~a)&(~b)) = d | c & d |
 *	    ----+---+-----+------------+-----------+------------------+-------+
 *     	      1 | 1 |  0  |  0         |  0        |  1               |  0
 *            1 | 0 |  1  |  1         |  0        |  1               |  1
 * 	      0 | 1 |  1  |  1         |  0        |  1               |  1
 *	      0 | 0 |  0  |  1         |  1        |  0               |  0
 *                     ^                                                 ^
 *                     |_________________________________________________|
 */
int bitXor(int x, int y) {
  
  return (~(x&y)) & (~( (~x)&(~y) ));
}


/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
/*
 * x = 0 => ~0 = -1, ~0 + 1 = 0
 * x > 0 (b_31 = 0, k < 30) => ~x = ~(b_0 * 1 + b_1 * 2 + b_2 * 2^2 + ... + b_k * 2^k) 
 *     	       	      	       	  = 2^(k+1) - 1 - (any (b_i = 0) terms) 
 *     	       	       	  = -2^31 + 2^30 + ... + 2^(k+1) + (any (b_i = 0) terms)
 * 			  = 2^(k+1) ( -2^{30-k} + 2^{29-k} + ... + 1) + (any (b_i = 0) terms)
 *			  = 2^(k+1) ( -2^{30-k} + 2^{30-k} - 1) + (any (b_i = 0) terms)
 *			  = -2^(k+1) + (any (b_i = 0) terms)
 *		so ====> ~x = -x - 1, thus ~x + 1 = -x
 * 	for x < 0, read the above backwards!
 */
int negate(int x) {
  
  return ((~x) + 1);
}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */

int divpwr2(int x, int n) {
  /* all 1s when x is neg, else all zeros */
  int neg_mask = x >> 31;

  /* when x < 0
   * neg_bias = 2^{n} - 1
   * why? b.c. we need to round toward zero, meaning up for negative numbers
   * since << just truncates, we always round down. so we want to add
   * some amount s.t. any number divisible by 2^n is unchanged but
   * all others end up at (quotient+1).
   *         (x < 0)
   *         x = q(2^n) + r so x >> n = q  (q < 0)
   *         but we wanted x >> n = q + 1
   *
   *         
   *         so let bias = 2^n - 1
   *         x+2^n-1 = q(2^n) + r + 2^n - 1 = q(2^n) + 2^n + r - 1
   *         = (q + 1)2^n + r - 1
   * 
   *	    so if r = 0, x + bias = (q+1)2^n - 1 = q(2^n) + 2^n - 1
   *  	       and (x+bias) >> n = q
   *        but if r > 0, x + bias >= (q+1)2^n
   *           and so (x+bias) >> n = q+1 just like we wanted! 
   */
  int neg_bias = ((0x01 << n) + ~0x00)&neg_mask;

  /*
   * when n = 0 just return x/1 = x
   * so mask out divided x
   * have to do this because of the neg_bias
   * i.e. divpwr2(-2345, 0) returns (-2345 + neg_bias) without this.
   */
  int zero_n_mask = (~(!n) << 31) >> 31;

  /* neg_bias is zero if x >= 0 */
  int x_div_2pown = ((x + neg_bias) >> n);

        /* masked out if n = 0 */    /* masked out if n != 0 */
  return (x_div_2pown & zero_n_mask) | (x& (~zero_n_mask));
}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
/* range of a signed n-bit integer x is 
 * -2^{n-1} <= x <= (2^{n-1} - 1)
 * so we must simply check if x is in this range
 */
int fitsBits(int x, int n) {
  /* right shift by (n - 1) */
  int shifted = x >> (n + (~0x00));
  int enough_bits;

  /*      bit 31 = -2^{31}
   *      all 1's from 30 to (n-1) and then all 0's  
   *            => x = -2^{31} + 2^{30} + ... + 2^{n-1} = 2^{n-1}(-2^{32-n} + 2^{31-n} + ... + 1) 
   *                 = 2^{n-1}(-2^{32-n} + 2^{32-n} - 1) = 2^{n-1}(-1) 
   *                 = -2^{n-1}
   *                  ^minimum for all 1's from 31 -> n-1 + other bits
   *      in order for x >= -2^(n-1) all ones from bit 31 to bit n - 1 must be 1s
   *          shift >> (n - 1) to see if we get 0xffffffff
   *           .>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>+
   * if (1111 1111 0000 0000 0000 0000 0000 0000) >> (n - 1) = 0xffffffff => fits!
   */
  enough_bits = !(~shifted);

  /*
   * in order for x < 2^(n-1) we must not have any 1
   * at or to the left of n-1
   */
  enough_bits = enough_bits | !shifted;
    
  return  enough_bits;
}

/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
/*
 * use xor because it essentially tests if 2 bits are the same.
 * bits same => 0
 * bits diff => 1
 */
int isNotEqual(int x, int y) {
  return !!(x^y);
}

/* 
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x) {
  
  return (((0xffU << 24) & x) >> 24) | (((0xffU << 16) & x) >> 8) | (((0xffU << 8) & x) << 8) | (((0xffU) & x) << 24);
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
#if 0
export rand1=$(ruby -e 'print rand(0xffffffff).to_s(16)'); export rand2=$(ruby -e 'print rand(0xffffffff).to_s(16)'); cantora cc --util-binary  -i bits.h -i bits.c  "int x = 0x$rand1; int y = 0x$rand2; y = x; print32bits(x); puts(\"\"); print32bits(y); puts(\"\");  print32bits(x-y); puts(\"\"); print32bits(EXPR(x,y) ); /*puts(\"\"); print32bits(EXPR2(x,y)); puts(\"\"); print32bits(EXPR2(x,y) | ( ~EXPR2(x,y) & EXPR(x,y) ));*/" --cc-opts ' -iquote. -DEXPR\(a,b\)="( ~((b + (~a + 1)) >> 31 ) )" -DEXPR2\(a,b\)="( ( (a ^ b) & (a & (0x01 << 31) ) ) >> 31 )" '
#endif
/*
 * cases:
 *    x >=0, y >= 0: return 1 if y - x >= 0 else return 0   <--------same test!
 *    x < 0, y < 0 : return 1 if y - x >= 0 else return 0   <--------^
 *    x < 0, y >= 0: return 1
 *    x >= 0, y < 0: return 0
 */
int isLessOrEqual(int x, int y) {
  /* all 1's if opposite polarity, else all 0's */
  int opp_pol = ((x ^ y) >> 31);
  /* all 1's if x < 0, else all 0's */
  int x_neg = x >> 31;
  /* all 1's if opposite polarity and x < 0, else all 0's */
  /*int x_neg_opp_pol = ( ( (x ^ y) & (x & (0x01 << 31) ) ) >> 31 );*/
  /* all 1's if x,y have same polarity and y - x is not less than 0 */
  int diff = ( ~ ((y + (~x + 1)) >> 31 ) ); /* not(sign_bit(y - x)) extended to 32 bits */
  
  /* if polarity is opposite and x < 0,
   * mask out result of diff 
   * return !!(x_neg_opp_pol | ( ~x_neg_opp_pol & diff ) );
   */
         /* opp polarity */    /* same polarity */
  return (!!(x_neg&opp_pol)) | ( !!(diff&(~opp_pol) ) );
}

/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
/* 1st attempt: return (0xffffffff >> (33 + (~((highbit+(~lowbit))+2)))) << lowbit; */

int bitMask(int highbit, int lowbit) {
  /* logically shift 1111....1 by 31 - highbit, i.e. shift in a bunch
   * of zeros to position of highbit + 1 
   */
  int high_mask = (~0x00U) >> (31 + ((~highbit)+1));
  
  /* logically shift 11...111 left by lowbit. ie shift in zeros up to lowbit - 1 */
  int low_mask = (~0x00U) << lowbit;

  return high_mask & low_mask;
}

/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* if x != 0, subtract 1 from 0 => 0xffffffff
   * else if x = 0, subtract 1 from 1 => 0x00000000
   */
  int mask = (!x + ~0x00);

  /* if x was non-zero, mask out z, 
   * if it was zero, mask out y 
   */
  return ((~mask) & z) | ((mask) & y);
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
/*
export rand1=$(ruby -e 'print rand(0xff).to_s(16)'); export rand2=$(ruby -e 'print rand(0xff).to_s(16)'); cantora cc --util-binary -I stdint.h   "uint8_t x = 0x$rand1; pb(x, 7,0); putchar(0x0a); x ^= (x >> 4); pb(x, 3,0); putchar(0x0a); x ^= (x >> 2); pb(x, 1,0); putchar(0x0a); x ^= (x >> 1); pb(x, 0, 0);"
*/
/* the magic of XOR!!!
 * for any 2 bit vectors b_0, ..., b_k and v_0, ..., v_k
 * we have B ^ V = W
 * the # of on bits in W is the same parity as
 * (# on in B) + (# on in V)
 *
 * so split x in half,
 * x[0..15] ^ x[16..31] = a[0..16] => a has same parity as x
 * a[0..7] ^ a[8..15] = b[0..7] => b has same partiy as a
 * b[0..3] ^ b[4..7] = c[0..3] => c has same parity as b
 * c[0..1] ^ c[2..3] = d[0..1] => d has same parity as c
 * d[0] ^ d[1] = 0 or 1 => 0 means x had even parity, 1 means odd
 * so return (d[0] ^ d[1]) bit
 */
int bitParity(int x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;

  return x & 0x01;
}

/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 60
 *   Rating: 4
 */
/*export rando=$(ruby -e 'print rand(0xff).to_s(16)'); cantora cc --util-binary  -i bits.h -i bits.c  "int x = 0x$rando; int y = 1 << 31; print32bits(x); puts(\"\"); print32bits(EXPR(x)); puts(\"\"); print32bits(y); puts(\"\"); print32bits(EXPR(y));" --cc-opts ' -iquote. -DEXPR\(a\)="( !(( ~( a & (~a + 1)) | (0x01 << 31) ) & a) ) " ' 
*/
/* 
 * any power of 2 will be a 32 bits s.t. 31 are all zero and a single bit is set
 * the trick here is the expression x & (-x) = x & (~x + 1)
 * b.c. ~x will have 1's from b_0 up to the first bit in x that is a 1,
 * if we add 1 to this number, it will carry all the way up to the first
 * zero in ~x, which is the first 1 in x. thus every bit in (~x + 1) is
 * exactly opposite of x, except for the first 1 in x, which is the same
 * in (~x + 1). now when we and the two we have a number with 31 0's and
 * a 1 at the first 1 in x. 
 * now if we ~ this to have all 1s and a zero, and & that with x, we will
 * have all zeros if x only have that single 1 in that position. 
 * 
 */ 
int isPower2(int x) {
  /* all 0s if x is zero, all 1s if x is non zero */
  int is_zero = (!x << 31) >> 31;
  
  /* all 0s if x only has a single bit set (not counting the sign bit) 
   * else all 1s
   */
  int x_has_only_a_single_one = ( ~( x & (~x + 1)) | (0x01 << 31) ) & x;
 
          /* return 1 if all 0s, else 0 */    /* mask out to zero if x is zero */
  return (!x_has_only_a_single_one)       &    (~is_zero);
}

/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */

/* cmd: export rando=$(ruby -e 'print rand(0xff).to_s(16)'); cantora cc --util-binary  -i bits.h -i bits.c  "int x = 0x$rando; print32bits(x); puts(\"\"); print32bits(EXPR(x)); puts(\"\"); print32bits(EXPR(0));" --cc-opts ' -iquote. -DEXPR\(a\)="( ( ( a | (~a + 1)) >> 31) & 0x01) " ' */
int isNonZero(int x) {
  /* if x and -x are the same thing, we have zero 
   * otherwise we must have the sign bit on, so shift it down to 
   * the first bit and return the sign bit
   */
  return ( ( x | (~x + 1)) >> 31) & 0x01;
}

/*
 * div5 - returns 1 if x is a power of 5, and 0 otherwise for numbers 0..65535
 *   Examples: div5(4) = 0, div5(5) = 1, div5(6) = 1, div5(2000)=400
 *   Note that no negative number is a power of 5.
 *   Legal ops: ! ~ & ^ | + - << >>
 *   Max ops: 220
 *   Rating: 4
 */
/* 
 * y = x/5 = x*(1/5) ~ x*(0.00110011001100110011001100110100) = x*(00110011001100110011001100110100.0)*2^(-32)
 */
int div5(int x) {

  long long int longx = x;
  long long int product = 0;
  int neg_mask = x >> 31;
  long long int neg_bias = 0x01 & neg_mask;
  
  /* five inverse is a 48 bit fixed point 1/5.0 */
  /* 0000000000000000001100110011001100110011001100110011001100110100 */


  neg_bias = ((neg_bias << (32))) + ((~0x00)&neg_mask);
  product += neg_bias;

  longx <<= 2;                   /* 0 */
                                 /* 0 */
  product += longx; longx <<= 1; /* 1 */
  longx <<= 1;                   /* 0 */

  product += longx; longx <<= 1; /* 1 */
  product += longx; longx <<= 1; /* 1 */
  longx <<= 2;                   /* 0 */
  	    			 /* 0 */

  product += longx; longx <<= 1; /* 1 */
  product += longx; longx <<= 1; /* 1 */
  longx <<= 2; 	    	      	 /* 0 */
  	    			 /* 0 */

  product += longx; longx <<= 1; /* 1 */
  product += longx; longx <<= 1; /* 1 */
  longx <<= 2;	    	         /* 0 */
  	    			 /* 0 */

  product += longx; longx <<= 1; /* 1 */
  product += longx; longx <<= 1; /* 1 */
  longx <<= 2;	    	      	 /* 0 */
  	    			 /* 0 */

  product += longx; longx <<= 1; /* 1 */
  product += longx; longx <<= 1; /* 1 */
  longx <<= 2;	    	      	 /* 0 */
  	    			 /* 0 */

  product += longx; longx <<= 1; /* 1 */
  product += longx; longx <<= 1; /* 1 */
  longx <<= 2;	    	      	 /* 0 */
  	    			 /* 0 */

  product += longx; longx <<= 1; /* 1 */
  product += longx; longx <<= 1; /* 1 */
  	     	    	      	 /* 0 */
				 /* 0 */

  return (product >> 32);
} 

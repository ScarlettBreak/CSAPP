/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
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
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
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

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
   /*
   * De Morgan's laws
  */
  return ~(~x | ~y);
}

/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {

  return x>>(n<<3)&0xff;

}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int y = 32 + ~n;
  // return (x>>n) & (1<<(y+1)-1);
  return (x>>n)&((1<<y) + (1<<y) + (~0)); //考虑溢出：n=0->y=31->1<<32
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  // int ans = x & 1 + x >> 1 & 1;
  int mask1 = 0x55555555; // 01010101010101010101010101010101
  int mask2 = 0x33333333; // 00110011001100110011001100110011
  int mask3 = 0x0f0f0f0f;// 00001111000011110000111100001111
  int mask4 = 0x00ff00ff;// 00000000111111110000000011111111
  int mask5 = 0x0000ffff;// 00000000000000001111111111111111

  x = (x & mask1) + ((x>>1) & mask1);
  x = (x & mask2) + ((x>>2) & mask2);
  x = (x & mask3) + ((x>>4) & mask3);
  x = (x & mask4) + ((x>>8) & mask4);
  x = (x & mask5) + ((x>>16) & mask5);
  return x;
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  // when x!=0, x and -x will have a highest signal '1'
  // while x=0, x and -x will always have a highest signal '0'
  return (~((x | (~x+1))>>31)) & 1;
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
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
int fitsBits(int x, int n) {
  // 如果在 n 位补码的范围内，32位的 x 右移 n-1 位，应该全为0或全为1
  // +1，为1或0，右移1位，为0
  return !(((x >> (n + (~0))) +1)>>1);
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
  // 补码除法（向上舍入）：(x+(1<<k)-1)>>k
  // 补码除法（向下舍入）：x >> k
  int bias = (x>>31)&((1<<n)+(~0)); // 如果 x<0，加上偏移量，否则不加
  return (x + bias) >> n;
    // return (x + (((x >> 31) & 1) << n) + (~0) + (!((x >> 31) & 1))) >> n;
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
}

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */

int isPositive(int x) {
  // 最高位是否为1，x 是否为0
  return !(((x>>31)&1)|!x);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int signx = (x>>31)&1;
  int signy = (y>>31)&1;
  int signdiff = (!signy) & signx; // 符号相同时为0，符号不同，仅当 y>0,x<0时为1
  int signsame = (!(signx^signy)) & (!(((y+((~x)+1))>>31)&1)); //仅当符号相同时进行减法
  return signdiff | signsame;
}

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  // log2(x)就是x二进制里最高位的1在哪里
  // 二分查找
  int ans = 0;
  ans = (!!(x >> 16)) << 4; 
  ans = ans + ((!!(x >> (8 + ans))) << 3); 
  ans = ans + ((!!(x >> (4 + ans))) << 2);
  ans = ans + ((!!(x >> (2 + ans))) << 1);
  ans = ans + ((!!(x >> (1 + ans))) << 0);

  return ans;
}

/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  unsigned result = uf & 0x7fffffff;
  if (result > 0x7f800000) return uf;
  return uf^0x80000000;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) { // x = 0xfefffffa = 1111 1110 1111 1111 1111 1111 1111 1010
  int Bias = 127;
  int sign = (x >> 31) & 1;

  if(x == 0) 
    return x; // 
  else{
    if(sign) x = -x; // -x = 0000 0001 0000 0000 0000 0000 0000 0110
    // 计算最高有效位的位置
    int valid_num = 31;
    while(!((1 << valid_num) & x)) valid_num = valid_num - 1;  //valid_num = 24

    int e = valid_num + Bias;

    int coarse_M = x & (~(1 << valid_num)); //去除符号位和最高有效位的尾数（待规范到23位） coarse_M = 0000 0000 0000 0000 0000 0000 0000 0110
    int M;
    if(valid_num <= 23) // 尾数位数 < 23：全部保留，左移，缺的位数补 0
      M = coarse_M << (23 - valid_num);
    else { // 尾数位数 > 23：右移，向偶数舍入
      int surplus_num = valid_num - 23; // surplus_num = 1
      M = (coarse_M >> surplus_num); // M = 0011

      int surplus = coarse_M << (31-surplus_num); // surplus = 1100 

      if((surplus & 0x7fffffff) > 0x40000000) // 被移除的最高位为1，进位
          M = M+1; 
      else if((surplus & 0xe0000000) == 0xc0000000) // 未被移除的最低位X和被移除的最高位形成X10的结构，向偶数舍入，M + 1
          M = M+1;
      
      if(M & (1 << 23)) {
        e = e + 1;// 如果进位导致最高位进位，即有效位数+1，则 e+1
        M = M & 0x007fffff;
      }
    }
    return (sign << 31) | (e << 23) | M;
  }
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  if((uf & 0x7f800000) == 0) // 非规格化：阶码全为0，此时 uf*2 <=> 尾数左移1位
    uf = (uf & 0x80000000) | ((uf & 0x007fffff) << 1);
  else if((uf & 0x7f800000) != 0x7f800000) // 规格化：阶码+1
    uf = uf + (1 << 23);
  return uf;
}

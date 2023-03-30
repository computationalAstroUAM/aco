//=====================================================================
// test01
//
// the aim of this exercise is to convince about the usage of stdint.h
//
// fprintf():
//  - PRIuXX: unsigned XX-bit integer
//  - PRIiXX: signed XX-bit integer
//
// fscanf():
//  - SCNiXX: (un-)signed XX-bit integer
//
// the exercise also shows:
//  - the use of sizeof()
//  - casting of variables
//  - bit-shifting
//
//=====================================================================
#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

// this is needed to actually print 128bit integer numbers
void print_uint128(__uint128_t n)
{
  if (n == 0) {
    return;
  }
  
  print_uint128(n/10);
  putchar(n%10+'0');    // we have to add n%10 to the ASCII code of the character '0'
}

//=====================================================
//                       MAIN
//=====================================================
int main(void)
{
  int32_t      *ia8;
  int64_t       i64;
  uint64_t      u64;
  __uint128_t ui128; // the __int128_t and __uint128_t types are non standard C/C++ extensions supported by Clang and GCC
  

  //=====================================================
  // stdint.h and sizeof()
  //=====================================================
  fprintf(stderr,"int:                %d bytes\n",sizeof(int));
  fprintf(stderr,"unsigend int:       %d bytes\n",sizeof(unsigned int));
  fprintf(stderr,"long:               %d bytes\n",sizeof(long));
  fprintf(stderr,"unsigend long:      %d bytes\n",sizeof(unsigned long));
  fprintf(stderr,"long long:          %d bytes\n",sizeof(long long));
  fprintf(stderr,"unsigend long long: %d bytes\n\n",sizeof(unsigned long long));

  fprintf(stderr," int8_t:            %d bytes\n",sizeof(int8_t));
  fprintf(stderr,"uint8_t:            %d bytes\n",sizeof(uint8_t));
  fprintf(stderr," int16_t:           %d bytes\n",sizeof(int16_t));
  fprintf(stderr,"uint16_t:           %d bytes\n",sizeof(uint16_t));
  fprintf(stderr," int32_t:           %d bytes\n",sizeof(int32_t));
  fprintf(stderr,"uint32_t:           %d bytes\n",sizeof(uint32_t));
  fprintf(stderr," int64_t:           %d bytes\n",sizeof(int64_t));
  fprintf(stderr,"uint64_t:           %d bytes\n\n",sizeof(uint64_t));
  
  // int128_t?
  fprintf(stderr," __int128_t:        %d bytes\n",sizeof(__int128_t));
  fprintf(stderr,"__uint128_t:        %d bytes\n\n",sizeof(__uint128_t));
  
  
  //=====================================================
  // bitshifts and type-casting issues
  //=====================================================
  //u64 = 1 << 63;            // this will not be compiled: '1' will be assumed to be 4bytes
  //u64 = (uint64_t)1 << 64;  // this will not be compiled: the compiler compares against the number 64 and not checking whether it overflows!
  u64 = (uint64_t)2 << 63;  // this will be compiled even though it overflows u64!
  
  //=====================================================
  // inttypes.h: how to print these integers
  // PRIxBITS   print integer of type x (i=signed, u=unsigned) that contains BITS bits
  // SCNiBITS   scan for integer that contains BITS bits (no signed/unsigned distinction)
  //=====================================================
  fprintf(stderr,"u64 =      %"PRIu64"\n",u64);
  
  fprintf(stderr,"\nplease give an integer number: ");
  fscanf(stdin,"%"SCNi64,&u64);
  fprintf(stderr,"u64 =      %"PRIu64"\n",u64);
  
  // there is nothing for 128bit integers (yet): use tailor-made print function from above
  ui128 = (__uint128_t)u64;
//  ui128 = (__uint128_t)1 << 120;
  print_uint128(ui128);
  fflush(stdout);
  fprintf(stderr,"\n\n");

  
  //=====================================================
  // careful with sizeof() for arrays
  //=====================================================
  ia8    = calloc(10, sizeof(int8_t));
  ia8[0] = 12;
  ia8[9] = 27;
  fprintf(stderr,"ia8[] is an array of 10 int8_t elements, but sizeof(ia8)=%d\n\n", sizeof(ia8) );

  
  return(1);
}

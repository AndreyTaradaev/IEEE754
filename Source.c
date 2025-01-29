// ConsoleApplication2.cpp : ���� ���� �������� ������� "main". ����� ����������
// � ������������� ���������� ���������.
//

#include <stdio.h>
#include "array.h"


typedef unsigned long long ull;
typedef unsigned int ui;


typedef union _mydouble {
  ull k;
  double fd;
  struct { ///
    ull mant : 52;
    ull exp : 11;
    ull sing : 1;
  };
} mydouble , *ptrmydouble ;

 
void printfBinary(ull v, int len ) {
  if (len <= 0)
    printf("0");
  for (int i = len - 1; i >= 0; i--) {
    ull var = (ull)1<<i;    
    var &= v;
    printf("%x", var == 0 ? 0 : 1);
  }

  #ifdef  _DEBUG 
  printf("b\t (%lldd)",v);
  #endif
}

ull cel(ull k, int p) // ����� �����
{
  ull a = 52 - p;
  k >>= a;
  return k;
}



ull drob(ull k, int p) {
 ull b = k;
  if (p >= 0) {
    b <<= 12 + p; // 41=9+32.
    b >>= 12 + p;
  }
  return b;
}

unsigned char getSign(ull d) {
  d >>= 63;
  return (unsigned char)d;
}

ull getExp(ull d) { d &= 0x7FF0000000000000;
  d >>= 52;
  return d;
}

ull getMant(ull d) {
  d &= 0xFFFFFFFFFFFFF;
  return d;
}


void Variant(double v) {    
   printf("\n\n \t Variant 2:\n without union\n");
  ull *i = (ull *)&v;
   printfBinary(*i, sizeof(unsigned long long) * 8);
  printf("\n");

  printf("sing -- ");
  unsigned short sign = getSign(*i);
  printfBinary(sign, 1);
#ifdef _DEBUG
  printf("\t (%c)", sign == 0 ? '+' :'-');
#endif // DEBUG1
  printf("\n");

   // ��������������
  ull exp = getExp(*i);
  printf("exp -- ");
  printfBinary(exp, 11);
  printf("\n");

  // ��������
  ull mant = getMant(*i);
  printf("mant -- ");
  printfBinary(mant, 52);
  printf("\n");
  // ���������  1 � �������� � �������� �������
    mant |= 0x10000000000000;
#ifdef _DEBUG
  printf("add 1 -- ");
    printfBinary(mant, 52);
    printf("\n");
  // printf("myvar.k  %p\n", &test.sing);
#endif // _DEBUG
       // �����
    int schift = exp - 1023;
    printf("schift = %d\n", schift);

     printf("integer binary : ");
    printfBinary(cel(mant, schift), schift + 1);
    printf("\n");
    // printf("%lld \n",cel(myint,schift));

    /*for (int i = 52; i >= 52 - schift; i--) {
      unsigned long long var = 1 << i;
      var &= myint;
      printf("%x", var == 0 ? 0 : 1);
    }*/
    printf("divide binary : ");
    int counter = 52 - schift;
    ull b = drob(mant, schift);

    printfBinary(b, counter);
    printf("\n");

    while (b != 0) {
      b = b * 10;
      ull a = b;
      a >>= 52 - schift; // �������� �����
      printf("%lld", a);
      b <<= 12 + schift; // ��������� ������� �����
      b >>= 12 + schift;
    }
    printf("\n");
    printf("%10.40lf\n", v);
}


int main() {



uint1088_t r;
  clear_1088(&r);
set_1088(&r, 0xFFFFFFFFFFFFFFFF);
  shift_left_1088(&r, 12);
shift_left_1088(&r, 108);
  printBinary_1088(&r,194);
  shift_left_1088(&r, -131);
  printf("\n");
  printBinary_1088(&r, 128);
  printf("\n");
  shift_right_1088(&r, -11);
  printBinary_1088(&r,128);
  printf("\n");

  add_1088(&r, 0xFFFFFF);
  printBinary_1088(&r, 64);

    printf("\n\n\n realization\n");


  mydouble test ;
  ull mymant = 0x10000000000000;

  test.fd =  1000000.95;

    clear_1088(&r);
  set_1088(&r, test.k);
    printf("representation double in memory:\t");
    printBinary_1088(&r, sizeof(unsigned long long) * 8);
    printf("\n");

    printf("sing -- ");
    printfBinary(test.sing,1);    
    printf("\n");

    // ��������������
    printf("exp -- ");
    printfBinary(test.exp, 11);
    printf("\n");

    // ��������
    printf("mant -- ");
    printfBinary(test.mant, 52);
    printf("\n");

     // �����
    int schift = (int)test.exp - 1023; // ��� ��������� �����
    printf("schift = %d\n", schift);  
    printf("\n");
    mymant += test.mant;

    printf("integer binary : ");
    printfBinary(cel(mymant, schift), schift + 1);
    printf("\n");

    printf("integer binary  1088: ");
    clear_1088(&r);
    set_1088(&r, mymant);
    printBinary_1088(&r, 53);

    
    //// ��������� ���������
    
    printf("integer binary : ");
    clear_1088(&r);
    set_1088(&r, mymant);
    //// 1   ����� ������ 52 
    if (schift )
    
    printf("\n");





    

    //printfBinary(cel(mymant, schift), schift + 1);
    //printf("\n");

    return 0;
        //  unsigned long long *ptrint = (unsigned long long *)&test.fd;

  // ��� � ������
  printfBinary(test.k, sizeof(unsigned long long) * 8);
  printf("\n");

  // ����
  printf("sing -- ");
  printfBinary(test.sing, 1);
  printf("\n");

  // ��������������
  printf("exp -- ");
  printfBinary(test.exp, 11);
  printf("\n");

  //��������
  printf("mant -- ");
  printfBinary(test.mant, 52);
  printf("\n");
#ifdef _DEBUG
  printf("myvar  %p\n", &test);
  printf("myvar.k  %p\n", &test.k);
  //printf("myvar.k  %p\n", &test.sing);
#endif // _DEBUG



  //�����
   schift =(int) test.exp - 1023;
  printf("schift = %d\n", schift);   

  // ��������� 1 � ��������
  mymant += test.mant;
  //������ ������
  printf("integer binary : ");
  printfBinary(cel(mymant, schift), schift + 1);
  printf("\n");
  //printf("%lld \n",cel(myint,schift));

  /*for (int i = 52; i >= 52 - schift; i--) {
    unsigned long long var = 1 << i;
    var &= myint;
    printf("%x", var == 0 ? 0 : 1);
  }*/
  printf("divide binary : ");
  int counter = 52 - schift;
  ull b = drob(mymant, schift);

  printfBinary(b, counter);
  printf("\n");
  
     while (b != 0) {
    b = b * 10;
    ull a = b;
    a >>= 52 - schift; // �������� ����� 
    printf("%lld", a);
    b <<= 12 + schift; // ��������� ������� �����
    b >>= 12 + schift;
  }
 printf("\n");

 printf("%10.40lf\n", test.fd);
 Variant(test.fd);
}



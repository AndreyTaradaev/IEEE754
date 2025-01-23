// ConsoleApplication2.cpp : ���� ���� �������� ������� "main". ����� ����������
// � ������������� ���������� ���������.
//

#include <stdio.h>

#define LEN  1024


typedef unsigned long long ull;
typedef unsigned int ui;
#define COUNT 8

typedef union _myvar {
  ull k;
  double fd;
  struct { ///
    ull mant : 52;
    ull exp : 11;
    ull sing : 1;
  };
} myvar , *pmyvar ;

typedef union {
  ull array[COUNT];
  ui arint[COUNT*2];
}uint1024_t ;


//  ���������������

//uint1024_t *shift_right(uint1024_t *v, short shiftcount) {
//  int128_t result;
//  result.low = (v.low >> shiftcount) | (v.high << (64 - shiftcount));
//  result.high = v.high >> shiftcount;
//  return result;
//}

uint1024_t *shift_left_1024(uint1024_t *v, short shiftcount);

void clear_1024(uint1024_t *s) {
  for (size_t i = 1; i < COUNT; i++)
    s->array[i] = 0;
}


uint1024_t *shift_right_1024(uint1024_t *v, short shiftcount) {
   if (shiftcount < 0)
    return shift_left_1024(v, -1 * shiftcount);
  if (shiftcount > 1023) {
    clear_1024(v);
    return v;
  }
  while (shiftcount > 0) {
    short tempSchift = shiftcount > 63 ? 63 : shiftcount;

    for (size_t i =  0; i <COUNT-1;
         i++) { // ������� ������� � ������� �������
      ull t = v->array[i];
      t = t >> tempSchift; // �������� ������� ����
      ull u = v->array[i +1]; // �������� ������ �������� �����
      u = u << (64 - tempSchift);
      t = t | u;
      v->array[i] = t;
    }
    v->array[COUNT-1] = v->array[COUNT-1] >> tempSchift;
    shiftcount -= tempSchift;
  }
  return v;
}





uint1024_t * set_1024(uint1024_t *s, ull v) {
  clear_1024(s);
  s->array[0] = v;
  return s;
}


uint1024_t *shift_left_1024(uint1024_t *v,  short  shiftcount) {
  if (shiftcount < 0)
      return shift_right_1024(v, -1 * shiftcount);
  if (shiftcount > 1023) {
    clear_1024(v);
    return v;
  }
  while (shiftcount > 0) {  
    short tempSchift = shiftcount > 63 ? 63 : shiftcount;

    for (size_t i = COUNT - 1; i > 0;         i--) { // ������� ������� � ������� �������
      ull t = v->array[i];
      t = t << tempSchift;   // �������� ������� ����
      ull u = v->array[i-1];  //�������� ������ �������� ����� 
      u = u >> (64 - tempSchift); 
      t = t | u;
      v->array[i] = t;
    }
    v->array[0] = v->array[0] << tempSchift;
    shiftcount -= tempSchift;
  }
  return v;
  }

uint1024_t *add_1024(uint1024_t *st, ui v) { 
   ull res = 0;
  ui pernos=0;
  res = (ull)st->arint[0]+v;
  st->arint[0] = res & 0xFFFFFFFF;
  pernos = res >> 32;

  for (size_t i = 1; i < COUNT*2; i++) {
    if (pernos == 0) break;
     res = st->arint[i] + pernos;
     st->arint[i] = res & 0xFFFFFFFF;
     pernos = res >> 32;
  }
  return st;
}

void printBinary_1024(uint1024_t *v, unsigned short len) {
    if (len > 1023)
      return;  

    for (int i = len; i >=0; i--) {
      unsigned short b = i / (sizeof(ull)*8);
      unsigned short offset = i % (sizeof(ull) * 8);
      ull printull = v->array[b]; // �������� �����  ��������
      ull prBt = ((ull)1 << offset); // ����� ����      
      printf("%c", (printull & prBt) == 0 ? '0' : '1');
    }
}
    


  //int128_t result;



/*  result.high = (v.high << shiftcount) | (v.low >> (64 - shiftcount));
  result.low = v.low << shiftcount;
  return result;*/
//}












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

//
// double pow_neg(int exp) {
//	double res=1.0;
//	if (exp == 0) return res;
//	for (int i = -1; i>=exp ; i--)
//	{
//		res /= 2;
//	}
//	return res;
//}

// unsigned long long mantisa(unsigned long long k) {
//	return  (k & 0x7FFFFFFFFFFFF) | 0x10000000000000;
// }

ull drob(ull k, int p) {
 ull b = k;
  if (p >= 0) {
    b <<= 12 + p; // 41=9+32.
    b >>= 12 + p;
  }
  return b;
}

unsigned short getSign(ull d) {
  d >>= 63;
  return d;
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



uint1024_t r;
  clear_1024(&r);
set_1024(&r, 0xFFFFFE0123);
  shift_left_1024(&r, 12);
shift_left_1024(&r, 120);
  printBinary_1024(&r,194);
  shift_left_1024(&r, -131);
  printf("\n");
  printBinary_1024(&r, 64);

  add_1024(&r, 0xFFFFFF);
  printBinary_1024(&r, 64);

  return 0;


  myvar test ;
  ull mymant = 0x10000000000000;

  test.fd =  -1000000.9;

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
  int schift = test.exp - 1023;
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

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ �
//   ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� �����
//   �������", ����� ������� ����� ����, ��� "������" > "�������� ������������
//   �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" >
//   "�������" > "������" � �������� SLN-����.

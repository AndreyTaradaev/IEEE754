// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается
// и заканчивается выполнение программы.
//

#include <stdio.h>

typedef unsigned long long ull;

typedef union _myvar {
  ull k;
  double fd;
  struct { ///
    ull mant : 52;
    ull exp : 11;
    ull sing : 1;
  };
} myvar , *pmyvar ;

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

ull cel(ull k, int p) // целая часть
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
  b <<= 12 + p; // 41=9+32.
  b >>= 12 + p;
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

   // характеристика
  ull exp = getExp(*i);
  printf("exp -- ");
  printfBinary(exp, 11);
  printf("\n");

  // мантисса
  ull mant = getMant(*i);
  printf("mant -- ");
  printfBinary(mant, 52);
  printf("\n");
  // добавляем  1 к мантиссе к старшему разряду
    mant |= 0x10000000000000;
#ifdef _DEBUG
  printf("add 1 -- ");
    printfBinary(mant, 52);
    printf("\n");
  // printf("myvar.k  %p\n", &test.sing);
#endif // _DEBUG
       // сдвиг
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
      a >>= 52 - schift; // получаем число
      printf("%lld", a);
      b <<= 12 + schift; // вычисляем дробную часть
      b >>= 12 + schift;
    }
    printf("\n");
    printf("%10.40lf\n", v);
}


int main() {

  myvar test ;
  ull mymant = 0x10000000000000;

  test.fd =  -1000000.9;

//  unsigned long long *ptrint = (unsigned long long *)&test.fd;

  // вид в памяти
  printfBinary(test.k, sizeof(unsigned long long) * 8);
  printf("\n");

  // знак
  printf("sing -- ");
  printfBinary(test.sing, 1);
  printf("\n");

  // характеристика
  printf("exp -- ");
  printfBinary(test.exp, 11);
  printf("\n");

  //мантисса
  printf("mant -- ");
  printfBinary(test.mant, 52);
  printf("\n");
#ifdef _DEBUG
  printf("myvar  %p\n", &test);
  printf("myvar.k  %p\n", &test.k);
  //printf("myvar.k  %p\n", &test.sing);
#endif // _DEBUG



  //сдвиг
  int schift = test.exp - 1023;
  printf("schift = %d\n", schift);   

  // добавляем 1 к мантиссе
  mymant += test.mant;
  //печать целого
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
    a >>= 52 - schift; // получаем число 
    printf("%lld", a);
    b <<= 12 + schift; // вычисляем дробную часть
    b >>= 12 + schift;
  }
 printf("\n");

 printf("%10.40lf\n", test.fd);
 Variant(test.fd);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и
//   другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый
//   элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий
//   элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" >
//   "Открыть" > "Проект" и выберите SLN-файл.

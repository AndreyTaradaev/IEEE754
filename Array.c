// 
// 
// 

#include "Array.h"
#include <stdio.h>

void clear_1088(uint1088_t *s) {
  for (size_t i = 0; i < COUNT; i++)
    s->array[i] = 0;
}
//--------------------------------------------------------------------------------
uint1088_t *shift_right_1088(uint1088_t *v, short shiftcount) {
  if (shiftcount < 0)
    return shift_left_1088(v, -1 * shiftcount);
  if (shiftcount > 1088) {
    clear_1088(v);
    return v;
  }
  while (shiftcount > 0) {
    short tempSchift = shiftcount > 63 ? 63 : shiftcount;

    for (size_t i = 0; i < COUNT - 1;
         i++) { // старшие разряды в большем индексе
      ull t = v->array[i];
      t = t >> tempSchift; // сдвинули младший Байт
      ull u = v->array[i + 1]; // получили данные старшего байта
      u = u << (64 - tempSchift);
      t = t | u;
      v->array[i] = t;
    }
    v->array[COUNT - 1] = v->array[COUNT - 1] >> tempSchift;
    shiftcount -= tempSchift;
  }
  return v;
}

unsigned char IsNull_1088(uint1088_t *v) {  
  for (size_t i = 0; i < COUNT ; i--) {
      if (v->array[i] != 0)
      return 1;
  }
  return 0;
}

////////===================================================

uint1088_t *set_1088(uint1088_t *s, ull v) {  
  s->array[0] = v;
  return s;
}

////////===================================================
uint1088_t *shift_left_1088(uint1088_t *v, short shiftcount) {
  if (shiftcount == 0)
    return v;
  if (shiftcount < 0)
    return shift_right_1088(v, -1 * shiftcount);
  if (shiftcount > 1088) {
    clear_1088(v);
    return v;
  }
  
  while (shiftcount > 0) {
    short tempSchift = shiftcount > 63 ? 63 : shiftcount;

    for (size_t i = COUNT - 1; i > 0;
         i--) { // старшие разрады в большем индексе
      ull t = v->array[i];
      t = t << tempSchift; // сдвинули старший байт
      ull u = v->array[i - 1]; // получили данные ьладшего байта
      u = u >> (64 - tempSchift);
      t = t | u;
      v->array[i] = t;
    }
    v->array[0] = v->array[0] << tempSchift;
    shiftcount -= tempSchift;
  }
  return v;
}

////////===================================================
uint1088_t *add_1088(uint1088_t *st, ull v) {
  size_t i = 0;
  ull perenos = v;
  do {
    if (ULONG_MAX - perenos >
        st->array[i]) { // проверяем на перенос если от макс лонг отнять
                        // добавляемое число и оно больше числа в массиве то
                        // переноса нет складываем и выходим
      st->array[i] += perenos;
      break;
    } else               // иначе  перенос есть
      st->array[i] += v; // тут не понятно какое поведение при переполнении
                         // переполнения не будет результат будет по модулю 2^64
                         // то есть старшие биты отбрасываются
    perenos = 1;
    i++;
  } while (i < COUNT);
  return st;
}

uint1088_t *add_1088str(uint1088_t *v1, uint1088_t *v2) { 
    uint1088_t res;
  clear_1088(&res);
  ull perenos = 0;
  for (size_t i = 0; i < COUNT; i++) {
    if (ULONG_MAX - (v1->array[i]) - perenos > v2->array[i]) {
      res.array[i] = v1->array[i] + v2->array[i] + perenos;
     perenos = 0;            
    }  
      else {      
      res.array[i] = v1->array[i] + v2->array[i] + perenos;
      perenos = 1;
    }    
  }
  // copy
  for (size_t i = 0; i < COUNT; i++) {
    v1->array[i] = res.array[i];
  }
return v1;
}



uint1088_t *multy10_1088str(uint1088_t *res, uint1088_t *v) {
//copy to res
  for (size_t i = 0; i < COUNT; i++) {
  res->array[i] = v->array[i];
  }

  for (size_t i = 0; i < 9; i++) 
  {
    add_1088str(res, v);
  }

  return res;
}

void copy_1088(uint1088_t *dest, uint1088_t *src) {
    for (size_t i = 0; i < COUNT; i++) {
      dest->array[i] = src->array[i];
    }
}

////////===================================================
void printBinary_1088(uint1088_t *v, unsigned short len) {
  if (len > 1087)
    return;

  for (int i = (len % 1088)-1; i >= 0; i--) {
    unsigned short b =
        (unsigned int)i /       
        (sizeof(ull) * 8); // число битов в лонге , получаем какой байт смотреть
    unsigned short offset = i % (sizeof(ull) * 8); // какой бит
    ull printull = *(v->array + b); // получаем номер  элемента
    ull prBt = ((ull)1 << offset); // маска Бита
    printf("%c", (printull & prBt) == 0 ? '0' : '1');
  }
}
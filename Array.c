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
  if (shiftcount > 1023) {
    clear_1088(v);
    return v;
  }
  while (shiftcount > 0) {
    short tempSchift = shiftcount > 63 ? 63 : shiftcount;

    for (size_t i = 0; i < COUNT - 1;
         i++) { // ������� ������� � ������� �������
      ull t = v->array[i];
      t = t >> tempSchift; // �������� ������� ����
      ull u = v->array[i + 1]; // �������� ������ �������� �����
      u = u << (64 - tempSchift);
      t = t | u;
      v->array[i] = t;
    }
    v->array[COUNT - 1] = v->array[COUNT - 1] >> tempSchift;
    shiftcount -= tempSchift;
  }
  return v;
}
////////===================================================

uint1088_t *set_1088(uint1088_t *s, ull v) {
  clear_1088(s);
  s->array[0] = v;
  return s;
}

////////===================================================
uint1088_t *shift_left_1088(uint1088_t *v, short shiftcount) {
  if (shiftcount == 0)
    return v;
  if (shiftcount < 0)
    return shift_right_1088(v, -1 * shiftcount);
  if (shiftcount > 1023) {
    clear_1088(v);
    return v;
  }
  
  while (shiftcount > 0) {
    short tempSchift = shiftcount > 63 ? 63 : shiftcount;

    for (size_t i = COUNT - 1; i > 0;
         i--) { // ������� ������� � ������� �������
      ull t = v->array[i];
      t = t << tempSchift; // �������� ������� ����
      ull u = v->array[i - 1]; // �������� ������ �������� �����
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
        st->array[i]) { // ��������� �� ������� ���� �� ���� ���� ������
                        // ����������� ����� � ��� ������ ����� � ������� ��
                        // �������� ��� ���������� � �������
      st->array[i] += perenos;
      break;
    } else               // �����  ������� ����
      st->array[i] += v; // ��� �� ������� ����� ��������� ��� ������������
                         // ������������ �� ����� ��������� ����� �� ������ 2^64
                         // �� ���� ������� ���� �������������
    perenos = 1;
    i++;
  } while (i < COUNT);
  return st;
}
////////===================================================
void printBinary_1088(uint1088_t *v, unsigned short len) {
  if (len > 1087)
    return;

  for (int i = (len % 1088)-1; i >= 0; i--) {
    unsigned short b =
        (unsigned int)i /       
        (sizeof(ull) * 8); // ����� ����� � ����� , �������� ����� ���� ��������
    unsigned short offset = i % (sizeof(ull) * 8); // ����� ���
    ull printull = *(v->array + b); // �������� �����  ��������
    ull prBt = ((ull)1 << offset); // ����� ����
    printf("%c", (printull & prBt) == 0 ? '0' : '1');
  }
}
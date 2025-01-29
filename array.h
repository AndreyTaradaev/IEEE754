#ifndef  ARRAY_H 
#define ARRAY_H 

#define LEN 1088
#define ULONG_MAX 0xFFFFFFFFFFFFFFFF
#define COUNT 17

typedef unsigned long long ull;

//старший разряд имеет старший индекс

typedef struct _uint1088 {
  ull array[COUNT];
  // ui arint[COUNT*2];
} uint1088_t, *ptruint1088;

/// <summary>
/// сдвиг влево
/// </summary>
/// <param name="v">Array</param>
/// <param name="shiftcount"> count shift</param>
/// <returns>array</returns>
uint1088_t *shift_left_1088(uint1088_t *v, short shiftcount);
uint1088_t *shift_right_1088(uint1088_t *v, short shiftcount);

unsigned char  IsNull_1088(uint1088_t *v);

/// <summary>
/// очистка массива
/// </summary>
/// <param name="s"></param>
void clear_1088(uint1088_t *s);

/// <summary>
/// загрузка в массив числа
/// </summary>
/// <param name="s"></param>
/// <param name="v"></param>
/// <returns></returns>
uint1088_t *set_1088(uint1088_t *s, ull v);

/// <summary>
/// сложение числа с массивом
/// </summary>
/// <param name="v"></param>
/// <param name="shiftcount"></param>
/// <returns></returns>
uint1088_t *add_1088(uint1088_t *st, ull v);


uint1088_t *add_1088str(uint1088_t *v1, uint1088_t *v2);

uint1088_t *multy10_1088str(uint1088_t *res, uint1088_t *v);

void copy_1088(uint1088_t *dest, uint1088_t *src);

/// <summary>
/// вывод массива с определеного места
/// </summary>
/// <param name="v"></param>
/// <param name="len"></param>
/// 

void printBinary_1088(uint1088_t *v, unsigned short len);






#endif // ! ARRAY_H 

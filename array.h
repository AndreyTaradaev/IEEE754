#ifndef  ARRAY_H 
#define ARRAY_H 

#define LEN 1088
#define ULONG_MAX 0xFFFFFFFFFFFFFFFF
#define COUNT 9

typedef unsigned long long ull;

//������� ������ ����� ������� ������

typedef struct _uint1088 {
  ull array[COUNT];
  // ui arint[COUNT*2];
} uint1088_t, *ptruint1088;

/// <summary>
/// ����� �����
/// </summary>
/// <param name="v">Array</param>
/// <param name="shiftcount"> count shift</param>
/// <returns>array</returns>
uint1088_t *shift_left_1088(uint1088_t *v, short shiftcount);
uint1088_t *shift_right_1088(uint1088_t *v, short shiftcount);

/// <summary>
/// ������� �������
/// </summary>
/// <param name="s"></param>
void clear_1088(uint1088_t *s);

/// <summary>
/// �������� � ������ �����
/// </summary>
/// <param name="s"></param>
/// <param name="v"></param>
/// <returns></returns>
uint1088_t *set_1088(uint1088_t *s, ull v);

/// <summary>
/// �������� ����� � ��������
/// </summary>
/// <param name="v"></param>
/// <param name="shiftcount"></param>
/// <returns></returns>
uint1088_t *add_1088(uint1088_t *st, ull v);
/// <summary>
/// ����� ������� � ������������ �����
/// </summary>
/// <param name="v"></param>
/// <param name="len"></param>

void printBinary_1088(uint1088_t *v, unsigned short len);






#endif // ! ARRAY_H 

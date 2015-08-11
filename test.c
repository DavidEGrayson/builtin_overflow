/** Tests for a compiler's implementation of __builtin_add_overflow,
 * __builtin_sub_overflow, and __builtin_mul_overflow. **/

/* To make sure we cover all the important cases, we should list out
 * the dimensions and then methodically explore many combinations of
 * those dimensions.  The dimensions are:
 *
 * 1) Operation: add, sub, mul
 * 2) Types of the two inputs
 * 3) Type of the output
 * 4) Values of the inputs
 *
 * Integer types should be ordered by their maximum value, like this:
 *   bool, int8_t, uint8_t, int16_t, uint16_t, ... uint128_t
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>

static void error(const char * format, ...) __attribute__((format (printf, 1, 2)));

void error(const char * format, ...)
{
  va_list ap;
  va_start(ap, format);
  fprintf(stderr, "error: ");
  vfprintf(stderr, format, ap);
  fprintf(stderr, "\n");
  va_end(ap);
}

#define TEST_ADD_1(a, b, res, ovf) \
  { \
    typeof(res) r; \
    if (ovf != __builtin_add_overflow((a), (b), &r)) \
      error("add error at line %d", __LINE__); \
    if (r != res) \
      error("incorrect add result at line %d", __LINE__); \
  }

#define TEST_ADD(a, b, res, ovf) \
  TEST_ADD_1(a, b, res, ovf) \
  TEST_ADD_1(b, a, res, ovf)

void x(int, int, int);

static void test_errors()
{
  int x;
  float f;

  //__builtin_add_overflow();            // too few args
  //__builtin_add_overflow(1, 2, 3, 4);  // too many args
  //__builtin_add_overflow(1.2, 1, &x);  // 1st arg bad
  //__builtin_add_overflow(1, "a", &x);  // 2nd arg bad
  //__builtin_add_overflow(1, 1, 3);     // 3rd arg bad
  //__builtin_add_overflow(1, 1, &f);    // 3rd arg bad
}

static void test_add()
{
  // bool + bool -> bool
  TEST_ADD((bool)0,            (bool)0,            (bool)0,            0);
  TEST_ADD((bool)0,            (bool)1,            (bool)1,            0);
  TEST_ADD((bool)1,            (bool)1,            (bool)1,            1);

  TEST_ADD((int32_t)1,         (int32_t)2,         (int32_t)3,         0);
  TEST_ADD((int32_t)INT_MAX,   (int32_t)0,         (int32_t)INT_MAX,   0);
  TEST_ADD((int32_t)INT_MAX,   (int32_t)1,         (int32_t)INT_MIN,   1);

  TEST_ADD((uint32_t)1,        (uint32_t)2,        (uint32_t)3,         0);
  TEST_ADD((uint32_t)UINT_MAX, (uint32_t)0,        (uint32_t)UINT_MAX,  0);
  TEST_ADD((uint32_t)UINT_MAX, (uint32_t)1,        (uint32_t)0,         1);

  //TEST_ADD((uint32_t)1,        (int32_t)2,         (uint32_t)3,         0);
}

int main()
{
  test_errors();
  test_add();
  return 0;
}

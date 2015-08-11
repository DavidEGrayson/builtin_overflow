/** Tests for a compiler's implementation of __builtin_add_overflow,
 * __builtin_sub_overflow, and __builtin_mul_overflow. **/

#include <stdio.h>
#include <stdint.h>
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
  //__builtin_add_overflow();  // too few arguments to function call, expected 3, have 0
  //__builtin_add_overflow(1, 2, 3, 4);  // too many arguments to function call, expected 3, have 4
}

static void test_add()
{
  TEST_ADD((int32_t)1,         (int32_t)2,         (int32_t)3,         0);
  TEST_ADD((int32_t)INT_MAX,   (int32_t)0,         (int32_t)INT_MAX,   0);
  TEST_ADD((int32_t)INT_MAX,   (int32_t)1,         (int32_t)INT_MIN,   1);

  TEST_ADD((uint32_t)1,        (uint32_t)2,        (uint32_t)3,         0);
  TEST_ADD((uint32_t)UINT_MAX, (uint32_t)0,        (uint32_t)UINT_MAX,  0);
  TEST_ADD((uint32_t)UINT_MAX, (uint32_t)1,        (uint32_t)0,         1);
}

int main()
{
  test_errors();
  test_add();
  return 0;
}

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void m_printf(const char* fmt, ...);
const char* convert(int x, int b);
void prepend(char* s, char t);

int main()
{
  m_printf("%s: %c, %d, %o, %x\n", "test", 'B', 10, 8, 10);

  m_printf("Testing with strings: %s\n", "example string");
  m_printf("Testing with chars  : %c\n", 'Z');
  m_printf("Testing with decimal: %d\n", 31);
  m_printf("Testing with octal  : %o\n", 31);
  m_printf("Testing with hex    : %x\n", 31);
  m_printf("Testing with percent: %%\n", 31);

  m_printf("Printing a bunch of numbers in several bases:\n");
  int i;
  for (i = 0; i <= 0x20; i++)
    m_printf("dec: %d, oct: %o, hex: %x\n", i, i, i);

  return 0;
}

void m_printf(const char* fmt, ...)
{
  va_list args;

  va_start(args, fmt);

  int i = 0;
  int len = strlen(fmt);
  for (i = 0; i < len; i++)
  {
    while (fmt[i] != '\0' && fmt[i] != '%')
    {
      putchar(fmt[i]);
      i++;
    }

    if (fmt[i] == '\0')
      return;

    i++;

    switch (fmt[i])
    {
      case 'd':
        fputs(convert(va_arg(args, int), 10), stdout);
        break;
      case 'x':
        fputs(convert(va_arg(args, int), 16), stdout);
        break;
      case 'o':
        fputs(convert(va_arg(args, int), 8), stdout);
        break;
      case 'c':
        putchar(va_arg(args, unsigned int));
        break;
      case 's':
        fputs(va_arg(args, const char*), stdout);
        break;
      case '%':
        putchar('%');
        break;
      case '\0':
        break;
      default:
        putchar('\n');
        fputs("Error: bad formatter: `", stdout);
        putchar(fmt[i]);
        fputs("`\n", stdout);
        return;
    }
  }

  va_end(args);

  return;
}

const char* convert(int x, int b)
{
  char* buffer = (char*)malloc(sizeof(char) * 80);
  buffer[0] = '\0';

  if (x == 0)
  {
    prepend(buffer, 0x30);
    return buffer;
  }

  int start;

  int n;
  while (x > 0)
  {
    n = x % b;
    x /= b;

    if (n >= 10)
    {
      n -= 10;
      start = 0x41;
    }
    else
    {
      start = 0x30;
    }

    prepend(buffer, n + start);
  }
  return buffer;
}

void prepend(char* s, char t)
{
  memmove(s + 1, s, strlen(s) + 1);
  s[0] = t;
  return;
}

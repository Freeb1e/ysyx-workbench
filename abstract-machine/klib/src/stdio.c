#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
// static 表示该函数仅在当前文件内可见
// 返回值是写入数字后的下一个字符地址
static char* itoa(int n, char *s) {
    char tmp[12]; // 32位整数最大10位，加负号和缓冲区足够了
    int i = 0;
    unsigned int num;

    // 1. 特殊处理 0
    if (n == 0) {
        *s++ = '0';
        return s;
    }

    // 2. 处理负数符号
    if (n < 0) {
        *s++ = '-';
        // 强制转为无符号数再取反，防止 -2147483648 溢出
        num = (unsigned int)-(n + 1) + 1; 
        // 或者更简单的写法：num = (unsigned int)-n; 
        // 但在某些严谨的编译器下，上面的写法更安全
    } else {
        num = (unsigned int)n;
    }

    // 3. 提取数字到临时数组（此时是逆序的）
    while (num > 0) {
        tmp[i++] = (num % 10) + '0';
        num /= 10;
    }

    // 4. 将临时数组反向拷贝回目标字符串 s
    while (i > 0) {
        *s++ = tmp[--i];
    }

    return s;
}
int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  //panic("Not implemented");
  char *p_out = out;
    const char *p_fmt = fmt;

    while (*p_fmt) {
        if (*p_fmt == '%') {
            p_fmt++; // 移动到格式字符（s 或 d）
            switch (*p_fmt) {
                case 's': {
                    char *s = va_arg(ap, char *);
                    if (s == NULL) s = "(null)";
                    while (*s) *p_out++ = *s++; // 拷贝字符串
                    break;
                }
                case 'd': {
                    int val = va_arg(ap, int);
                    // 调用 itoa，并自动更新 p_out 指针
                    p_out = itoa(val, p_out); 
                    break;
                }
                default:
                    // 无法识别则原样输出
                    *p_out++ = '%';
                    *p_out++ = *p_fmt;
                    break;
            }
        } else {
            *p_out++ = *p_fmt;
        }
        p_fmt++;
    }

    *p_out = '\0'; // 封口
    return p_out - out; // 返回总长度
}

int sprintf(char *out, const char *fmt, ...) {
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = vsprintf(out, fmt, ap);
    va_end(ap);
    return n;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif

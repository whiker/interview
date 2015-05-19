#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "qh_string.h"

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

typedef void (*TestCase)();

// 基本功能测试
void testcase_1()
{
    // 构造函数 string(const char* s)
    const char *Test = "123456";
    qh::string str(Test);
    assert(strcmp(str.data(), Test) == 0);
    assert(str.size() == strlen(Test));
    for (int i = strlen(Test)-1; i >= 0; i--)
        assert(*str[i] == Test[i]);

    // 拷贝构造函数
    qh::string str1(str);
    assert(strcmp(str1.data(), str.data()) == 0);

    // 赋值运算符
    const char *Test1 = "789";
    qh::string str2(Test1);
    assert(strcmp(str.data(), str2.data()) < 0);
    str1 = str = str2;
    assert(strcmp(str.data(), str2.data()) == 0);
    assert(strcmp(str1.data(), str2.data()) == 0);

    str = str;
    assert(strcmp(str.data(), Test1) == 0);
}

// 测试构造函数 string(const char* s)
void testcase_2()
{
    qh::string str(NULL);
    assert(str.data() == NULL);
    assert(str.size() == 0);
    assert(str[0] == NULL);
}

// 测试构造函数 string(const char*s, size_t len)
void testcase_3()
{
    const char *Test = "123456";
    int len = strlen(Test);

    qh::string str1(Test, (len>>1));
    assert(strncmp(str1.data(), Test, (len>>1)) == 0);

    qh::string str2(Test, (len<<1));
    assert(strcmp(str2.data(), Test) == 0);

    qh::string str3(Test, 0);
    assert(str3.data() == NULL);

    qh::string str4(Test, -1);
    assert(strcmp(str4.data(), Test) == 0);
}

int main(int argc, char* argv[])
{
    TestCase cases[] = {
        testcase_1, testcase_2,
        testcase_3
    };

    int nCase = H_ARRAYSIZE(cases);
    for (int i = 0; i < nCase; i++)
        cases[i]();

#ifdef WIN32
    system("pause");
#endif

    return 0;
}

#include <stdlib.h>
#include "qh_vector.h"


int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。

    qh::vector<int> num_vect;
    num_vect.push_back(1);
    assert(num_vect.size() == 1);
    assert(num_vect[0] == 1);

    num_vect.reserve(50);
    assert(num_vect.size() == 1);
    num_vect.resize(50);
    assert(num_vect.size() == 50);

    num_vect[1] = 2;
    num_vect[2] = 3;
    qh::vector<int> v1(num_vect);
    assert(v1.size() == num_vect.size());
    for (int i = 0; i < 3; i++)
    	assert(v1[i] == num_vect[i]);

    qh::vector<int> v2;
    assert(v2.size() == 0);
    v2 = num_vect;
    assert(v2.size() == num_vect.size());
    for (int i = 0; i < 3; i++)
    	assert(v2[i] == num_vect[i]);

#ifdef WIN32
    system("pause");
#endif

	return 0;
}


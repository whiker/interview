#include <stdlib.h>
#include "qh_vector.h"


int main(int argc, char* argv[])
{
    //TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
    //TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�

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


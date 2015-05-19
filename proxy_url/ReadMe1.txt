设URL长度n，待查询的key个数是m。
算法时间复杂度是O(n+log(m))
空间复杂度是O(n)

每个循环中取出 &...& 之间的字符串expr，再从expr中取出'='之前的字符串key。key非空时，判断key是否是keys的一个元素，若是则获取value，这一步时间复杂度是O(log(m))。

由于用了string类来存储字符串，在string对象析构时会释放内存，因此不存在内存泄露。

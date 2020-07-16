target=a
code=src/inner_test.cpp sdk/layers/inner_product_layer.cpp sdk/math/matrix_operation.cpp
a:src/inner_test.cpp sdk/layers/inner_product_layer.cpp sdk/math/matrix_operation.cpp
	g++ -o $@ $^ -I./inc

atom:src/atom_test.cpp
	g++ -o $@ $^ -I./inc

b:src/inner_test.cpp
	g++ -o $@ $^ -I./inc

#我有点困惑，我创建了一个class A，然后在一个函数f里，参数是const A* a
#然后想通过a去修改a的成员变量，报错
#这个const的范围不应该仅限于地址吗？

#同时，如果不能修改a的内容，那么是因为这会传入的是一个a的拷贝？

#math_code=matrix_operation_base.cpp
math_code=matrix_operation_lessmul.cpp

code=matrix_mul_compare.cpp ../sdk/math/${math_code}
include = -I../inc

target=a

${target} : ${code}
	g++ -O3 -o $@ $^ ${include}

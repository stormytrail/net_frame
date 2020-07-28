math_code=matrix_operation.cpp

code=matrix_mul_compare.cpp ../sdk/math/${math_code}
include = -I../inc

target=a

${target} : ${code}
	g++ -o $@ $^ ${include}

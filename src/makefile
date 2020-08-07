#math_code=matrix_operation_base.cpp
#math_code=matrix_operation_version1_row_first.cpp
math_code=matrix_operation_version1_col_first.cpp

include = -I../inc

all:efficiency accuracy

efficiency : matrix_mul_compare.cpp ../sdk/math/${math_code}
	g++ -O3 -o $@ $^ ${include}

accuracy : matrix_one.cpp ../sdk/math/${math_code}
	g++ -O3 -o $@ $^ ${include}

clean:
	rm efficiency accuracy

target=a
code=src/main_forward.cpp sdk/layers/inner_product_layer.cpp sdk/math/matrix_operation.cpp
${target}:${code}
	g++ -o $@ $^ -I./inc

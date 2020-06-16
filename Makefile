target=a
code=src/main_forward.cpp sdk/layers/inner_product_layer.cpp
${target}:${code}
	g++ -o $@ $^ -I./inc

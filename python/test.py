import numpy as np
x = np.array([[1,1],[-1,-1],[2,1]])
w = np.array([[0,1],[2,3]])

h1 = x.dot(w)

print(h1)

softmax = []
for cur in range(len(h1)):
	exp_val = [np.exp(i) for i in h1[cur]]
	sum_exp = sum(exp_val)
	cur_softmax = [i/sum_exp for i in exp_val]
	softmax.append(cur_softmax)
softmax = np.array(softmax)

print(softmax)

label = np.array([[1,0],[0,1],[1,0]])
loss = []
for i in range(len(h1)):
	cur = 0
	for j in range(len(h1[0])):
		cur = cur + label[i][j] * np.log(softmax[i][j])
	cur = 0 - cur
	loss.append(cur)
loss = np.array(loss)
print(loss)

grad_softmax = []
for i in range(len(loss)):
	cur = []
	for j in range(2):
		cur.append(0-label[i][j] / softmax[i][j])
	grad_softmax.append(cur)
grad_softmax = np.array(grad_softmax)
print(grad_softmax)

grad_h1 = []
for i in range(3):
	cur = []
	grad_y = np.array([0-label[i][0] / softmax[i][0],0-label[i][1]/softmax[i][1]])
	matrix = []
	for j in range(2):
		row = []
		for k in range(2):
			if j == k:
				val = softmax[i][j] * (1 -softmax[i][j])
			else:
				val = 0 - softmax[i][0] * softmax[i][1]
			row.append(val)
		matrix.append(row)
	matrix = np.array(matrix)
	print(matrix)
	print()
	cur_grad = grad_y.dot(matrix)
	grad_h1.append(cur_grad)
grad_h1 = np.array(grad_h1)
print(grad_h1)

print(x.T.dot(grad_h1))


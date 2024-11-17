def multiply_matrix(matrix1, matrix2):
    result = [[0, 0], [0, 0]]
    for i in range(2):
        for j in range(2):
            for k in range(2):
                result[i][j] += matrix1[i][k] * matrix2[k][j]
                result[i][j] %= 10000
    return result

def power_matrix(matrix, n):
    if n == 1:
        return matrix
    elif n % 2 == 0:
        half_power = power_matrix(matrix, n // 2)
        return multiply_matrix(half_power, half_power)
    else:
        half_power = power_matrix(matrix, n // 2)
        return multiply_matrix(multiply_matrix(half_power, half_power), matrix)

while True:
    n = int(input())
    if n == -1:
        break
    if n == 0:
        print(0)
    else:
        base_matrix = [[1, 1], [1, 0]]
        powered_matrix = power_matrix(base_matrix, n)
        print(powered_matrix[0][1])

import csv
import math

# Открываем файл на чтение
with open('./data_files/TIME.csv', 'r') as file:
    # Создаем объект csv.reader
    reader = csv.reader(file)
    # Создаем список из чисел, записанных в строки через запятую
    numbers = []
    for row in reader:
        for number in row:
            numbers.append(float(number))

# Считаем среднее и стандартное отклонение
mean = sum(numbers) / len(numbers)
std_dev = math.sqrt(sum((x - mean) ** 2 for x in numbers) / len(numbers))

# Eps = 0.005
# Max_relative = 0.03

# if abs(std_dev/mean - Max_relative) < Eps:    
# Печатаем результаты в консоль
print('\033[32m' + f'Среднее: {mean:.2f}' + '\033[0m')
print('\033[32m' + f'Стандартное отклонение: {std_dev:.2f}' + '\033[0m')

with open('./data_files/TIME.csv', 'w') as file:
    data = []
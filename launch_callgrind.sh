# !/bin/bash

# Удаляем все файлы, начинающиеся с callgrind.out
rm -f callgrind.out*

# Спрашиваем аргументы
echo Enter cmd_args
read -p "./hash_table " args

# Запускаем valgrind с указанными аргументами
valgrind --tool=callgrind ./hash_table $args 2>&1 >./logs/callgrind_logs.txt

# Сохраняем имя скомпилированного отчёта, начинающегося с callgrind.out
name=$(ls -1 callgrind.out* | tail -n 1) 2>&1 >./logs/kcachegrind_logs.txt

# Запускаем kachegrind с указанным именем отчёта
kcachegrind $name 2>&1 >nul
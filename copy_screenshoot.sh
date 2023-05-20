# Запрашиваем имя файла у пользователя
echo "Введите имя скриншота:"
read file_name

# Проверяем, содержит ли имя файла расширение .png
if [[ $file_name != *".png" ]]; then
  # Если не содержит, добавляем расширение .png
  file_name="$file_name.png"
fi

path_1="/home/timasok/Pictures/Screenshots/"
path_2="/home/timasok/progs/hash_table/callgrind/"

# Открываем папку path_1
cd /home/timasok/Pictures/Screenshots/

# Находим последний созданный файл
latest_file=$(ls -t | head -1)

mv "$latest_file" $file_name.png

# Копируем его в папку path_2
cp $file_name $path_2

echo "Файл" "$path_2"$file_name "успешно сохранён!"
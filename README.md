# Мастерская №1: "Real Game"

## Сборка проекта
### Install requirements
```
sudo apt install g++ cmake mesa-common-dev freeglut3-dev libasio-dev
```
Важно. Для сборки нужен g++ >= 7.0

Для работы также нужен собранный движок Real Engine. Путь к нему должен быть записан в переменную окружения REAL_ENGINE_DIR. 
```
export REAL_ENGINE_DIR=<path to real engine>
```
Для того, чтобы не писать много раз, нужно прописать эту строчку в .bashrc


### Сборка
Проект собирается с помощью cmake. Тестировалось все на ubuntu 16.04. Для сборки нужно выполнить следующие команды.
```
mkdir build
cd build
cmake ..
make
```
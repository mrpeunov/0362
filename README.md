# Правила работы с Git

тест

## Полезные ссылки

[Классное руководство по работе с Git](https://githowto.com/ru)

## Изначальная настройка 

### Шаг 1

После установки переходим в директорию, куда хотим клонировать репозиторий и запускаем Git Bash, нажав правую клавишу мыши:

![Первый шаг](/image/step1.png)

В результате откроется консоль

![Консоль](/image/console.PNG)

### Шаг 2.

Клонируем репозиторий с помощью команды

```
git clone https://github.com/mrpeunov/0362.git
```

Проверим получилось ли с помощью команды:

```
ls
```

Результат:

![Второй шаг](/image/step.PNG)

### Шаг 3.

Перейдем внутрь репозитория с помощью команды 

```
cd 0362
```

Результат:

![Третий шаг](/image/step3.PNG)

### Шаг 4. 

Как видно на предыдущем скриншоте мы оказались на основной ветке master. Создадим собственную ветку, в качестве названия используем свою фамилию:

```
git checkout -b peunov
```

В результате будет создана ветка peunov и произойдёт переключение на неё же

![Четвёртый шаг](/image/step4.PNG)

### Шаг 5.

Создадим директорию, названную по фамилии,  либо с помощью файлового менеджера либо с помощью следующей команды: 

```
mkdir
```

И проверим, создалась ли она:

```
ls
```

![Пятый шаг](/image/step5.PNG)

### Шаг 6. 

Перейдём внутрь директории с помощью команды:

```
peunov
```

Изначальная настройка завершена. В следующем разделе будет описано добавление ответов на задание.

## Постоянная работа


## Полезные команды

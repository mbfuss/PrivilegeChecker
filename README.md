# Тестовое задание для ООО Эврика Би Пи О

Необходимо написать простое web-приложение с использованием node.js+node-addon-api (C++)+WinAPI для проверки привилегии пользователя (например, Администратор/Пользователь/Гость) в списке пользователей операционной системы Windows.

**Приложение должно работать по следующему сценарию**
 
1. Пользователь запускает web-сервер из корня проекта:
server.bat

3. Автоматически открывается браузер с начальной web страницей, на которой отображаются
   
- поле ввода имени пользователя
  
- кнопка "Проверить"
  
3. Пользователь вводит любое имя пользователя и нажимает на "проверить"
   
5. Если введённый пользователь в списке пользователей имеет привилегию Администратор/Пользователь/Гость, отображается страница с надписью "Пользователь имя_введённого_пользователя имеет привилегию привилегия_введённого пользователя", иначе "Пользователя имя_введённого_пользователя нет". Под надписью есть кнопка "Назад", при нажатии на которую происходит возврат на начальную страницу.
   
7. Проверку привилегий осуществлять через WinAPI.
 
# Требования

- Node.js (включая npm).

# Инструкция по запуску

**1. Клонируйте репозиторий**
   
```
https://github.com/mbfuss/UserPrivilegeChecker.git
```

**2. Установите node-gyp глобально через npm**

```
npm install -g node-gyp
```

**3. Перейдите в репозиторий с проектом**
   
```
cd .../UserPrivilegeChecker
```

**4. Инициализируйте проект**

```
npm init -y
```

**5. Установите необходимые зависимости для проекта**

```
npm install node-addon-api
```

**6. Скомпилируйте и соберите проект**

```
node-gyp configure build
```

**7. Запустите server.bat**




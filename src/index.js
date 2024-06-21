const express = require('express');  // Подключение модуля Express для создания сервера
const path = require('path');        // Подключение модуля path для работы с путями файловой системы
const { exec } = require('child_process');  // Подключение метода exec из модуля child_process для выполнения команд
const addon = require('../build/Release/addon');  // Подключение node-addon, экспортированного из C++

const app = express();  // Создание экземпляра приложения Express
const port = 3000;      // Указание порта для запуска сервера

// Middleware для обслуживания статических файлов из папки public
app.use(express.static(path.join(__dirname, '../public')));
app.use(express.json());  // Middleware для разбора JSON в запросах

// Обработчик POST запроса на маршрут '/check'
app.post('/check', (req, res) => {
    const userName = req.body.userName;  // Извлечение имени пользователя из тела запроса
    const result = addon.checkUserPrivilege(userName);  // Вызов функции из node-addon для проверки привилегий
    res.json(result);  // Отправка JSON ответа с результатом проверки
});

// Запуск сервера на указанном порту
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);  // Вывод сообщения о запуске сервера в консоль

    // Автоматическое открытие браузера при запуске сервера
    exec(`start http://localhost:${port}`, (err, stdout, stderr) => {
        if (err) {
            console.error(`Error opening browser: ${err}`);
            return;
        }
        console.log('Browser opened successfully.');
    });
});

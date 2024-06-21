#include <napi.h>       // Включение заголовочного файла для Node.js API
#include <windows.h>    // Включение заголовочного файла для функций Windows API
#include <lm.h>         // Включение заголовочного файла для функций управления пользователями

#pragma comment(lib, "netapi32.lib")   // Директива для автоматической ссылки на библиотеку netapi32.lib

// Функция CheckUserPrivilege, вызываемая из JavaScript
Napi::Object CheckUserPrivilege(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env(); // Получение среды выполнения Node.js

    // Извлечение имени пользователя из аргументов функции
    std::string userName = info[0].As<Napi::String>().Utf8Value();

    // Преобразование имени пользователя в формат wide string для использования в WinAPI функциях
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &userName[0], (int)userName.size(), NULL, 0);
    std::wstring userNameW(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &userName[0], (int)userName.size(), &userNameW[0], size_needed);

    USER_INFO_1* userInfo = NULL;
    // Вызов WinAPI функции для получения информации о пользователе
    NET_API_STATUS status = NetUserGetInfo(NULL, userNameW.c_str(), 1, (LPBYTE*)&userInfo);

    // Создание объекта для возвращаемого результата
    Napi::Object result = Napi::Object::New(env);

    if (status == NERR_Success) {   // Если операция успешна
        std::string privilege;
        // Определение привилегии пользователя на основе полученных данных
        if (userInfo->usri1_priv == USER_PRIV_ADMIN) {
            privilege = u8"Администратор";
        }
        else if (userInfo->usri1_priv == USER_PRIV_USER) {
            privilege = u8"Пользователь";
        }
        else {
            privilege = u8"Гость";
        }
        NetApiBufferFree(userInfo); // Освобождение выделенной памяти
        result.Set("found", Napi::Boolean::New(env, true));  // Установка свойства found в true
        result.Set("privilege", Napi::String::New(env, privilege));  // Установка свойства privilege с указанием привилегии
    }
    else {
        result.Set("found", Napi::Boolean::New(env, false)); // Установка свойства found в false при неудаче
    }

    return result;  // Возвращение объекта с результатом выполнения операции
}

// Инициализация модуля Node.js
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // Регистрация функции CheckUserPrivilege для экспорта в JavaScript
    exports.Set(Napi::String::New(env, "checkUserPrivilege"), Napi::Function::New(env, CheckUserPrivilege));
    return exports; // Возврат экспортируемого объекта
}

// Определение модуля Node.js
NODE_API_MODULE(addon, Init)

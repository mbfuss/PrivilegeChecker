#include <napi.h>       // ��������� ������������� ����� ��� Node.js API
#include <windows.h>    // ��������� ������������� ����� ��� ������� Windows API
#include <lm.h>         // ��������� ������������� ����� ��� ������� ���������� ��������������

#pragma comment(lib, "netapi32.lib")   // ��������� ��� �������������� ������ �� ���������� netapi32.lib

// ������� CheckUserPrivilege, ���������� �� JavaScript
Napi::Object CheckUserPrivilege(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env(); // ��������� ����� ���������� Node.js

    // ���������� ����� ������������ �� ���������� �������
    std::string userName = info[0].As<Napi::String>().Utf8Value();

    // �������������� ����� ������������ � ������ wide string ��� ������������� � WinAPI ��������
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &userName[0], (int)userName.size(), NULL, 0);
    std::wstring userNameW(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &userName[0], (int)userName.size(), &userNameW[0], size_needed);

    USER_INFO_1* userInfo = NULL;
    // ����� WinAPI ������� ��� ��������� ���������� � ������������
    NET_API_STATUS status = NetUserGetInfo(NULL, userNameW.c_str(), 1, (LPBYTE*)&userInfo);

    // �������� ������� ��� ������������� ����������
    Napi::Object result = Napi::Object::New(env);

    if (status == NERR_Success) {   // ���� �������� �������
        std::string privilege;
        // ����������� ���������� ������������ �� ������ ���������� ������
        if (userInfo->usri1_priv == USER_PRIV_ADMIN) {
            privilege = u8"�������������";
        }
        else if (userInfo->usri1_priv == USER_PRIV_USER) {
            privilege = u8"������������";
        }
        else {
            privilege = u8"�����";
        }
        NetApiBufferFree(userInfo); // ������������ ���������� ������
        result.Set("found", Napi::Boolean::New(env, true));  // ��������� �������� found � true
        result.Set("privilege", Napi::String::New(env, privilege));  // ��������� �������� privilege � ��������� ����������
    }
    else {
        result.Set("found", Napi::Boolean::New(env, false)); // ��������� �������� found � false ��� �������
    }

    return result;  // ����������� ������� � ����������� ���������� ��������
}

// ������������� ������ Node.js
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // ����������� ������� CheckUserPrivilege ��� �������� � JavaScript
    exports.Set(Napi::String::New(env, "checkUserPrivilege"), Napi::Function::New(env, CheckUserPrivilege));
    return exports; // ������� ��������������� �������
}

// ����������� ������ Node.js
NODE_API_MODULE(addon, Init)

const express = require('express');  // ����������� ������ Express ��� �������� �������
const path = require('path');        // ����������� ������ path ��� ������ � ������ �������� �������
const { exec } = require('child_process');  // ����������� ������ exec �� ������ child_process ��� ���������� ������
const addon = require('../build/Release/addon');  // ����������� node-addon, ����������������� �� C++

const app = express();  // �������� ���������� ���������� Express
const port = 3000;      // �������� ����� ��� ������� �������

// Middleware ��� ������������ ����������� ������ �� ����� public
app.use(express.static(path.join(__dirname, '../public')));
app.use(express.json());  // Middleware ��� ������� JSON � ��������

// ���������� POST ������� �� ������� '/check'
app.post('/check', (req, res) => {
    const userName = req.body.userName;  // ���������� ����� ������������ �� ���� �������
    const result = addon.checkUserPrivilege(userName);  // ����� ������� �� node-addon ��� �������� ����������
    res.json(result);  // �������� JSON ������ � ����������� ��������
});

// ������ ������� �� ��������� �����
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);  // ����� ��������� � ������� ������� � �������

    // �������������� �������� �������� ��� ������� �������
    exec(`start http://localhost:${port}`, (err, stdout, stderr) => {
        if (err) {
            console.error(`Error opening browser: ${err}`);
            return;
        }
        console.log('Browser opened successfully.');
    });
});

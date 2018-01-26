/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief  Headfile of mainwindow.cpp
 *
 *
 * \author
 *      Waterplus Corporation: http://www.waterplus.cn \n
 *      Programmer: Ye Lu
 *
 * $Revision: 1 $
 * $Date: 2018-01-25 16:52 $  \n
 *
 * Copyright (C) <2018>, <Waterplus Corporation>.
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QTextCodec>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QDebug>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QSerialPort* sptCom;

    QComboBox* cboComName;
    QComboBox* cboBaudRate;
    QPushButton* btnSptSwitch;

    QPushButton* btnBrowserClear;
    QPushButton* btnBrowserSwitch;
    QCheckBox* chkShowHex;
    QCheckBox* chkAutoClear;
    QCheckBox* chkHeadCheck;
    QLineEdit* ledtHeadCheck;
    QPushButton* btnSaveRxData;

    QTextEdit* tedtRxBrowser;

    QPushButton* btnManualSend;
    QPushButton* btnTxEditClear;
    QCheckBox* chkSendHex;
    QCheckBox* chkAutoSend;
    QCheckBox* chkChecksum;
    QLineEdit* ledtSendCycle;

    QTextEdit* tedtTxEdit;

    QLabel* lblStatus;
    QLabel* lblTxCounter;
    QLabel* lblRxCounter;
    QPushButton* btnCounterClear;

    QTimer* timCounter;

    qint32 txCounter;   // 发送总数计数寄存器
    qint32 rxCounter;   // 接收总数计数寄存器

    void initSerialPort();

private slots:
    void on_sptCom_readyRead();
    void on_btnSptSwitch_clicked();
    void on_btnRxSaveData_clicked();
    void on_btnBrowserClear_clicked();
    void on_btnBrowserSwitch_clicked();
    void on_btnManualSend_clicked();
    void on_btnTxEditClear_clicked();
    void on_timCounter_timeout();
    void on_chkAutoSend_stateChanged();
    void on_chkAutoClear_stateChanged();
    void on_btnCounterClear_clicked();
};

#endif // MAINWINDOW_H

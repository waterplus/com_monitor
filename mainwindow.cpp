/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief  Program about main window
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
#include "mainwindow.h"


/*! \brief MainWindow类的构造函数
 *
 *  构造窗体，连接信号量于槽函数
 *
 *  \param  QWidget *parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{   
    QList<QString> listBaudRate;
    listBaudRate<<"1200"<<"2400"<<"4800"<<"9600"<<"19200"<<"38400"<<"57600"<<"115200";

    txCounter = 0;      // 初始化发送总数计数器
    rxCounter = 0;      // 初始化接收总数计数器

    setWindowIcon(QIcon(":/new/src/icon/logo.ico"));
    setWindowTitle("WATERPLUS串口调试助手");

    QWidget* centralWidget = new QWidget(this);     // 实例化一个Widget作为中心部件

    QGroupBox* grpBasicSetting = new QGroupBox(tr("串口设置"));

    QLabel* lblComName = new QLabel(tr("串口号："));
    lblComName->setMinimumWidth(60);
    cboComName = new QComboBox(this);
    QLabel* lblBaudRate = new QLabel(tr("波特率："));
    lblBaudRate->setMinimumWidth(60);
    cboBaudRate = new QComboBox(this);
    cboBaudRate->addItems(listBaudRate);
    cboBaudRate->setCurrentIndex(7);

    btnSptSwitch = new QPushButton(tr("打开串口"));

    QGridLayout* gridBasicSetting = new QGridLayout(grpBasicSetting);

    gridBasicSetting->addWidget(lblComName,0,0);
    gridBasicSetting->addWidget(cboComName,0,1);
    gridBasicSetting->addWidget(lblBaudRate,1,0);
    gridBasicSetting->addWidget(cboBaudRate,1,1);
    gridBasicSetting->addWidget(btnSptSwitch,2,0,1,2);
    gridBasicSetting->setSizeConstraint(QLayout::SetFixedSize);

    QGroupBox* grpRxSetting = new QGroupBox(tr("接收设置"));
    btnBrowserClear = new QPushButton(tr("清空"));
    btnBrowserClear->setMaximumWidth(60);
    btnBrowserSwitch = new QPushButton(tr("停止显示"));
    btnBrowserSwitch->setMaximumWidth(60);
    chkShowHex = new QCheckBox(tr("十六进制显示"));
    chkAutoClear = new QCheckBox(tr("滚动显示"));
    chkHeadCheck = new QCheckBox(tr("协议头检查"));
    QLabel* lblProtocolHead = new QLabel(tr("协议头："));
    ledtHeadCheck = new QLineEdit(tr("55 AA"));
    ledtHeadCheck->setMaximumWidth(62);
    btnSaveRxData = new QPushButton(tr("保存接收数据"));

    QGridLayout* gridRxSetting = new QGridLayout(grpRxSetting);
    gridRxSetting->addWidget(btnBrowserClear,0,0);
    gridRxSetting->addWidget(btnBrowserSwitch,0,1);
    gridRxSetting->addWidget(chkShowHex,1,0,1,2);
    gridRxSetting->addWidget(chkAutoClear,2,0,1,2);
    gridRxSetting->addWidget(chkHeadCheck,3,0,1,2);
    gridRxSetting->addWidget(lblProtocolHead,4,0,1,1);
    gridRxSetting->addWidget(ledtHeadCheck,4,1,1,1);
    gridRxSetting->addWidget(btnSaveRxData,5,0,1,2);
    gridRxSetting->setSizeConstraint(QLayout::SetFixedSize);

    QGroupBox* grpTxSetting = new QGroupBox(tr("串口发送"));
    btnTxEditClear = new QPushButton(tr("清空"));
    btnTxEditClear->setMaximumWidth(60);
    btnManualSend = new QPushButton(tr("手动发送"));
    btnManualSend->setMaximumWidth(60);
    btnManualSend->setEnabled(false);
    chkSendHex = new QCheckBox(tr("十六进制发送"));
    chkChecksum = new QCheckBox(tr("添加校验和"));
    chkAutoSend = new QCheckBox(tr("自动发送"));
    chkAutoSend->setEnabled(false);
    QLabel* lblSendCycle = new QLabel(tr("发送周期："));
    ledtSendCycle = new QLineEdit(tr("1000"));
    ledtSendCycle->setMaximumWidth(40);
    QLabel* lblCycleUnit = new QLabel(tr("ms"));
    lblCycleUnit->setMaximumWidth(16);

    QGridLayout* gridTxSetting = new QGridLayout(grpTxSetting);
    gridTxSetting->addWidget(btnTxEditClear,0,0,1,3);
    gridTxSetting->addWidget(btnManualSend,0,3,1,3);
    gridTxSetting->addWidget(chkSendHex,1,0,1,6);
    gridTxSetting->addWidget(chkChecksum,2,0,1,6);
    gridTxSetting->addWidget(chkAutoSend,3,0,1,6);
    gridTxSetting->addWidget(lblSendCycle,4,0,1,3);
    gridTxSetting->addWidget(ledtSendCycle,4,3,1,2);
    gridTxSetting->addWidget(lblCycleUnit,4,5,1,1);
    gridTxSetting->setSizeConstraint(QLayout::SetFixedSize);

    tedtRxBrowser = new QTextEdit(this);
    tedtRxBrowser->setMinimumWidth(620);
    tedtRxBrowser->setWordWrapMode(QTextOption::NoWrap);

    tedtTxEdit = new QTextEdit(this);
    tedtTxEdit->setMaximumHeight(145);

    lblStatus = new QLabel(this);
    lblStatus->setFrameShape(QFrame::Panel);            // 设置label的样式，默认样式不添加文字的时候是无法看到的。
    lblStatus->setFrameShadow(QFrame::Sunken);
    lblStatus->setText("请选择要打开的串口");

    lblRxCounter = new QLabel(this);
    lblRxCounter->setFrameShape(QFrame::Panel);
    lblRxCounter->setFrameShadow(QFrame::Sunken);
    lblRxCounter->setText("接收字节数：0");

    lblTxCounter = new QLabel(this);
    lblTxCounter->setFrameShape(QFrame::Panel);
    lblTxCounter->setFrameShadow(QFrame::Sunken);
    lblTxCounter->setText("发送字节数：0");

    btnCounterClear = new QPushButton(tr("清零"));
    btnCounterClear->setMaximumWidth(40);

    QGridLayout* gridCentral = new QGridLayout(centralWidget);
    gridCentral->addWidget(grpBasicSetting,0,0,4,2);
    gridCentral->addWidget(grpRxSetting,4,0,6,2);
    gridCentral->addWidget(tedtRxBrowser,0,2,10,8);
    gridCentral->addWidget(grpTxSetting,10,0,6,2);
    gridCentral->addWidget(tedtTxEdit,10,2,6,8);
    gridCentral->addWidget(lblStatus,16,0,1,5);
    gridCentral->addWidget(lblRxCounter,16,5,1,2);
    gridCentral->addWidget(lblTxCounter,16,7,1,2);
    gridCentral->addWidget(btnCounterClear,16,9,1,1);
    gridCentral->setSizeConstraint(QLayout::SetFixedSize);

    this->setCentralWidget(centralWidget);

    this->setFixedSize(792, 486);

    initSerialPort();

    timCounter = new QTimer(this);

    // 连接信号量
    connect(timCounter,SIGNAL(timeout()), this, SLOT(on_timCounter_timeout()));
    connect(btnSptSwitch, SIGNAL(clicked(bool)), this, SLOT(on_btnSptSwitch_clicked()));
    connect(btnSaveRxData,SIGNAL(clicked(bool)), this, SLOT(on_btnRxSaveData_clicked()));
    connect(btnBrowserClear,SIGNAL(clicked(bool)), this, SLOT(on_btnBrowserClear_clicked()));
    connect(btnBrowserSwitch,SIGNAL(clicked(bool)), this, SLOT(on_btnBrowserSwitch_clicked()));
    connect(btnTxEditClear,SIGNAL(clicked(bool)), this, SLOT(on_btnTxEditClear_clicked()));
    connect(btnManualSend,SIGNAL(clicked(bool)), this, SLOT(on_btnManualSend_clicked()));
    connect(chkAutoSend,SIGNAL(stateChanged(int)),this, SLOT(on_chkAutoSend_stateChanged()));
    connect(chkAutoClear,SIGNAL(stateChanged(int)),this,SLOT(on_chkAutoClear_stateChanged()));
    connect(btnCounterClear,SIGNAL(clicked(bool)),this,SLOT(on_btnCounterClear_clicked()));
}



/*! \brief MainWindow类的析构函数
 *
 *  在窗体析构的过程中关闭串口
 *
 */
MainWindow::~MainWindow()
{
    sptCom->close();
}


/*! \brief 初始化串口
 *
 *  利用QSerialPortInfo类获取全部串口信息，初始化串口选择Combo
 *
 */
void MainWindow::initSerialPort()
{
    sptCom = new QSerialPort(this);
    connect(sptCom, SIGNAL(readyRead()),this,SLOT(on_sptCom_readyRead()));

    QList<QSerialPortInfo> listSptInfos = QSerialPortInfo::availablePorts();
    if (listSptInfos.isEmpty())
    {
        return;
    }
    else
    {
        foreach (QSerialPortInfo info, listSptInfos)
        {
            this->cboComName->addItem(info.portName());
            qDebug() << info.description();
        }
    }
}


/*! \brief 打开串口按键槽函数
 *
 *  用于打开指定串口，并在lblStatus中显示串口状态
 *
 */
void MainWindow::on_btnSptSwitch_clicked()
{
    if ("打开串口" == btnSptSwitch->text())
    {
        sptCom->setPortName(cboComName->currentText());

        if (sptCom->open(QIODevice::ReadWrite))
        {
            sptCom->setBaudRate(cboBaudRate->currentText().toInt());
            sptCom->setDataBits(QSerialPort::Data8);
            sptCom->setParity(QSerialPort::NoParity);
            sptCom->setStopBits(QSerialPort::OneStop);
            sptCom->setFlowControl(QSerialPort::NoFlowControl);

            btnSptSwitch->setText("关闭串口");
            lblStatus->setText(QString("%1, %2bps, 'N', 8, 1").arg(sptCom->portName()).arg(sptCom->baudRate()));

            qDebug() << sptCom->portName();
            qDebug() << sptCom->baudRate();
            qDebug() << sptCom->parity();
            qDebug() << sptCom->stopBits();
            qDebug() << sptCom->flowControl();

            cboBaudRate->setEnabled(false);
            cboComName->setEnabled(false);

            btnManualSend->setEnabled(true);
            chkAutoSend->setEnabled(true);
        }
        else
        {
            lblStatus->setText("串口打开失败，可能该串口已经被占用");
            cboBaudRate->setEnabled(true);
            cboComName->setEnabled(true);
            btnManualSend->setEnabled(false);
            chkAutoSend->setEnabled(false);
        }
    }
    else
    {
        sptCom->close();
        cboBaudRate->setEnabled(true);
        cboComName->setEnabled(true);
        lblStatus->setText("串口已关闭");
        btnSptSwitch->setText("打开串口");
        btnManualSend->setEnabled(false);
        chkAutoSend->setEnabled(false);
    }

    return;
}


/*! \brief 保存接收数据按键槽函数
 *
 *  使用QFileDialog、QTextDocumentWriter对接收浏览框中的数据保存为TXT文件
 *
 */
void MainWindow::on_btnRxSaveData_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存接收到的数据"), "data", tr("Config Files (*.txt)"));
    if (fileName.isEmpty())
    {
        qDebug()<<"false";
        return;
    }

    QTextDocumentWriter documentWriter(fileName);
    documentWriter.write(tedtRxBrowser->document());

    return;
}


/*! \brief 接收清空按键槽函数
 *
 *  用于清空接收显示区
 *
 */
void MainWindow::on_btnBrowserClear_clicked()
{
    tedtRxBrowser->clear();
    return;
}


/*! \brief 停止显示按键槽函数
 *
 *  改变按键显示的文字，利用文字信息匹配阻断接收浏览框更新数据
 *
 */
void MainWindow::on_btnBrowserSwitch_clicked()
{
    if ("停止显示" == btnBrowserSwitch->text())
    {
        btnBrowserSwitch->setText("继续显示");
    }
    else
    {
         btnBrowserSwitch->setText("停止显示");
    }
    return;
}


/*! \brief 手动发送按键槽函数
 *
 *  读取发送编辑框中的数据，安装用户选择的方式进行发送
 *
 */
void MainWindow::on_btnManualSend_clicked()
{
    QString strSend;
    QString strChange;
    QByteArray baSend;
    qint32 count = 0;
    quint8 checksum = 0;
    bool ok;

    strSend = tedtTxEdit->toPlainText();

    if (!strSend.isEmpty())
    {
        if (chkSendHex->isChecked())
        {
            strSend.remove(QRegExp("\\s"));     // 使用正则表达式清除空格、换行、回车等符号。
            for (count = 0; count < strSend.size(); count += 2)
            {
                baSend.append(strSend.mid(count, 2).toInt(&ok,16)); // 每次提取两个数据转换为16进制整形
                if (!ok)
                {
                    qDebug()<<"The character is illegal";           // 如果转换失败，说明输入内容中有非法字符
                    QMessageBox::information(this, tr("错误提示"), tr("发送内容中包含非法字符！"));
                    return;
                }
            }

            if (chkChecksum->isChecked())          // 计算校验和
            {
                for (count = 0; count < baSend.size(); count++)
                {
                    checksum += baSend.at(count);
                    qDebug("%x",checksum);
                }

                baSend.append(checksum);
            }
        }
        else
        {
            baSend.append(strSend.toLatin1());
        }

        sptCom->write(baSend);

        txCounter += baSend.size();
        lblTxCounter->setText(QString("发送字节数：%1").arg(txCounter));
    }

    return;
}


/*! \brief 清空发送编辑框的按键槽函数
 *
 *  清空发送编辑框
 *
 */
void MainWindow::on_btnTxEditClear_clicked()
{
    tedtTxEdit->clear();
    return;
}


/*! \brief 串口接收数据槽函数
 *
 *  按tedtRxBrowser宽度、用户设置自动编辑接收到的内容，在tedtRxBrowser中更新
 *
 */
void MainWindow::on_sptCom_readyRead()
{
    QByteArray baSptRx;
    QString strShow;
    QString strPlainText;
    QString strHead;
    qint32 count = 0;
    qint32 strPlainText_size = 0;
    qint32 headIndex = 0;

    baSptRx = sptCom->readAll();

    rxCounter += baSptRx.size();
    lblRxCounter->setText(QString("接收字节数：%1").arg(rxCounter));

    strPlainText = tedtRxBrowser->toPlainText();

    if(chkShowHex->isChecked())
    {
        // 将接收到的整形数据按照十六进制转换为字符串，再转换为大写，不足两位的前端补0，用空格隔开。
        for (count = 0; count < baSptRx.size(); count++)
        {
            strShow += QString::number((0xFF & baSptRx.at(count)),16).toUpper().rightJustified(2,'0') + tr(" ");
        }

        if (chkHeadCheck->isChecked())
        {
            strHead.append(ledtHeadCheck->text());

            while (true)
            {
                headIndex = strShow.indexOf(strHead, headIndex);        // 查找协议头在QString中的位置，在匹配位置插入回车符。

                if (headIndex >= 0)
                {
                    strShow.insert(headIndex, '\r');
                    headIndex += 2;                                     // 移动检查操作的起始点。
                }
                else
                {
                    break;
                }
            }
        }
        strPlainText.append(strShow);
    }
    else
    { 
        strShow.append(baSptRx);
        strPlainText.append(strShow);
    }

    strPlainText_size = strPlainText.size();

    // 从队尾反向检查换行符号的位置。
    for (count = strPlainText_size; count > 0; count--)
    {
        if (('\r' == strPlainText.at(count - 1)) || ('\n' == strPlainText.at(count - 1)))
        {
            break;
        }
    }

    // 如果本行长度超标，则在行最大长度处加入回车符。
    if ((strPlainText_size - count) > 98)
    {
        strPlainText.insert(count+99,'\r');
    }

    if ("停止显示" == btnBrowserSwitch->text())
    {
        tedtRxBrowser->setText(strPlainText);
        tedtRxBrowser->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    }

    return;
}


/*! \brief 定时器超时槽函数
 *
 *  定时器超时时调用手动发送槽函数
 *
 */
void MainWindow::on_timCounter_timeout()
{
    on_btnManualSend_clicked();
    return;
}


/*! \brief 自动发送复选框变更槽函数
 *
 *  将label中的字符转换为整形作为定时参数启动定时器，或终止定时器
 *
 */
void MainWindow::on_chkAutoSend_stateChanged()
{
    bool ok;
    qint32 cycle = 0;

    if (chkAutoSend->isChecked())
    {
        cycle = ledtSendCycle->text().toInt(&ok);
        if (!ok)
        {
            QMessageBox::information(this, tr("错误提示"), tr("周期数值中包含非法字符！"));
            chkAutoSend->setChecked(false);
        }
        timCounter->start(cycle);
    }
    else
    {
        timCounter->stop();
    }
    return;
}


/*! \brief 滚动显示复选框变更槽函数
 *
 *  设置QtextEdit类成员document的最大段落数
 *
 */
void MainWindow::on_chkAutoClear_stateChanged()
{
    if (chkAutoClear->isChecked())
    {
        tedtRxBrowser->document()->setMaximumBlockCount(19);
    }
    else
    {
        tedtRxBrowser->document()->setMaximumBlockCount(0);
    }
    return;
}


/*! \brief 清零(发送、接收计数器)按键槽函数
 *
 *  清空计数寄存器值
 *
 */
void MainWindow::on_btnCounterClear_clicked()
{
    txCounter = 0;
    rxCounter = 0;
    lblTxCounter->setText(QString("发送字节数：%1").arg(txCounter));
    lblRxCounter->setText(QString("接收字节数：%1").arg(rxCounter));
    return;
}

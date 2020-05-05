#include "standarddialog.h"
#include "ui_standarddialog.h"
#include <QDebug>
#include <QRect>

#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>
#include <QErrorMessage>

StandardDialog::StandardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StandardDialog)
{
    ui->setupUi(this);
    errordlg = new QErrorMessage(this);
}

StandardDialog::~StandardDialog()
{
    delete ui;
}

//为“退出”按钮添加信号和槽，使得点击按钮时，弹出问题消息对话框，确认是否退出。若确认，则结束程序。
void StandardDialog::on_pushButton_exit_clicked()
{
    int ret =
            QMessageBox::question(this,"退出","是否要退出程序？",QMessageBox::Yes,QMessageBox::No);
    if(ret == QMessageBox::Yes)
        exit(0);
}

// 为“修改内容”按钮添加信号和槽，使得点击按钮时，
//弹出输入对话框，并将输入的内容显示在standarddialog的文本框中。
void StandardDialog::on_pushButton_text_clicked()
{
    bool ok;
    //获得字符串
    QString str =
            QInputDialog::getText(this,"输入对话框","请输入文本",QLineEdit::Normal,"",&ok);
    if(ok)
        ui->textEdit->setText(str);
}

//为“改变颜色”按钮添加信号和槽
void StandardDialog::on_pushButton_colour_clicked()
{
     QColorDialog dlg(Qt::red,this);
     dlg.setOption(QColorDialog::ShowAlphaChannel);
     int ret = dlg.exec();
     QColor color = dlg.currentColor();
     ui->textEdit->setTextColor(color);
     if(ret == 1){
         QMessageBox::information(this,"提示","颜色修改成功",QMessageBox::Ok);
     }
}

//为“改变字体”按钮添加信号和槽
void StandardDialog::on_pushButton_type_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok){
        ui->textEdit->setFont(font);
    }
    else {
        QMessageBox::warning(this,"警告","没有选择任何字体",QMessageBox::Ok);
    }
}

//为“保存”按钮添加信号和槽
void StandardDialog::on_pushButton_save_clicked()
{
    if(ui->textEdit->document()->isEmpty()){
        errordlg->setWindowTitle("错误");
        errordlg->showMessage("内容为空！");
    }
    else {
        QString fileName = QFileDialog::getSaveFileName(this,"保存当前文件","","文本文件(*.txt)");

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::critical(this,"错误","文件打开失败！",QMessageBox::Ok);
        }
        else
        {/*
            QTextStream stream(&file);
            stream << ui->textEdit->setPlainText(fileName);
            stream.flush();
            file.close();*/
            ui->textEdit->setPlainText(fileName);
        }
    }
}

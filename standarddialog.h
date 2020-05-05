#ifndef STANDARDDIALOG_H
#define STANDARDDIALOG_H

#include <QDialog>

class QErrorMessage;
namespace Ui {
class StandardDialog;
}

class StandardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StandardDialog(QWidget *parent = nullptr);
    ~StandardDialog();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_text_clicked();

    void on_pushButton_colour_clicked();

    void on_pushButton_type_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::StandardDialog *ui;

    QErrorMessage *errordlg;
};

#endif // STANDARDDIALOG_H

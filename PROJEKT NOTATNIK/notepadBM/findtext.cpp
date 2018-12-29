#include "findtext.h"
#include "ui_findtext.h"

FindText::FindText(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindText)
{
    ui->setupUi(this);
}

FindText::~FindText()
{
    delete ui;
}

void FindText::on_pushButton_clicked()//FIND
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","Line Edit is empty");
    }

    QString return_world = ui->lineEdit->text();
    emit copy_world(return_world);
}

void FindText::on_pushButton_2_clicked()//OK
{
    FindText::close();
    emit close_new_dialog();
}

void FindText::closeEvent(QCloseEvent *event)//przyda sie na pozniej
{
    emit close_new_dialog();
    event->accept();
}

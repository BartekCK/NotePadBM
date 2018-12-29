#ifndef FINDTEXT_H
#define FINDTEXT_H

#include <QDialog>
#include <QMessageBox>

#include <QCloseEvent>

namespace Ui {
class FindText;
}

class FindText : public QDialog
{
    Q_OBJECT

public:
    explicit FindText(QWidget *parent = nullptr);
    ~FindText();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void closeEvent(QCloseEvent *event);


private:
    Ui::FindText *ui;


signals:
    void copy_world(QString return_world);
    void close_new_dialog();
};

#endif // FINDTEXT_H

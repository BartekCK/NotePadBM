#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QDirModel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QDebug>
#include <QFont>
#include <QFontDialog>
#include <QCloseEvent>
#include <QIcon>

#include <QPrinter>
#include <QPrintDialog>





#include "highlighter.h"
#include "codeeditor.h"
#include "findtext.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tabWidget_tabCloseRequested(int index);

    void on_actionNew_triggered();

    void on_dir_make_clicked();

    void on_dir_delete_clicked();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();

    void on_actionRename_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionSelect_All_triggered();

    void on_actionClear_triggered();

    void on_actionFind_text_triggered();
    void get_world(QString return_world);
    void return_default_font();


    void on_actionFont_triggered();

    void on_actionAbout_us_triggered();

    void closeEvent (QCloseEvent *event);


private:
    Ui::MainWindow *ui;
    QDirModel *model;

    void setupEditor();
    Highlighter *highlighter;
    FindText *findtext;


};

#endif // MAINWINDOW_H

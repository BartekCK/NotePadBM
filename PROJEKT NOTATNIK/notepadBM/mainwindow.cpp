#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupEditor();
    model = new QDirModel(this);
    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
    ui->treeView->setModel(model);

    QModelIndex index = model->index("C://");

    ui->treeView->expand(index);
    ui->treeView->scrollTo(index);
    ui->treeView->setCurrentIndex(index);
    ui->treeView->resizeColumnToContents(0);



}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::setupEditor()//Kolorowanie skladni
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);


    ui->plainTextEdit->setFont(font);

    highlighter = new Highlighter(ui->plainTextEdit->document());

    QFile file("mainwindow.h");
    if (file.open(QFile::ReadOnly | QFile::Text))
        ui->plainTextEdit->setPlainText(file.readAll());
}



void MainWindow::on_tabWidget_tabCloseRequested(int index)//zamykanie obecnego tab
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionNew_triggered()
{
    ui->plainTextEdit = new CodeEditor;
    ui->tabWidget->addTab(ui->plainTextEdit,QString("Tab %0").arg(ui->tabWidget->count()+1));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    setupEditor();
}

void MainWindow::on_dir_make_clicked()// Tworzenie nowego folderu
{
    //make dir
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;

    QString name = QInputDialog::getText(this,"Name","Enter a name");
    if(name.isEmpty()) return;

    model->mkdir(index,name);
}

void MainWindow::on_dir_delete_clicked()// Usuwanie wybranego folderu
{
    //delete dir
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()) return;
    if(model->fileInfo(index).isDir())
        model->rmdir(index);
    else {
        model->remove(index);
    }
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)//Pobieranie zawartosci wybranego pliku z treeView
{
    //open file
    QFile name_file(model->filePath(index));
    if(!name_file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Title","File not open");
    }
    MainWindow::on_actionNew_triggered();//Otwarcie w nowym oknie
    QTextStream in(&name_file);
    QString text = in.readAll();
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),model->filePath(index));
    ui->plainTextEdit->setPlainText(text);
    name_file.close();

}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open the file"),"",
                                                    tr("All types (*.*);;Normal text file (*.txt);;C++ source file (*.cpp);;C source file (*.c)"));
    QFile file(filename);
    MainWindow::on_actionNew_triggered();//Otwarcie w nowym oknie
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),filename);
    if(filename.isEmpty())
        return;
    if(!file.open(QIODevice::ReadOnly |  QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot open file :"+ file.errorString());
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);
    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save as","", tr("Normal text file (*.txt);;C++ source file (*.cpp);;C source file (*.c)"));
    QFile file(filename);
    if(filename.isEmpty())
        return;
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot save file :"+ file.errorString());
        return;
    }
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),filename);
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out<< text;
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    if(!file.exists())
    {

        MainWindow::on_actionSave_As_triggered();
        return;
    }

    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot save file :"+ file.errorString());
        return;
    }
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out<< text;
    file.close();
}

void MainWindow::on_actionRename_triggered()
{
    QFile file_path(ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    if(file_path.exists())
    {
        QString name = file_path.fileName();
        QString file_path_2 = QFileDialog::getSaveFileName(this,"Save as",name, tr("Normal text file (*.txt);;C++ source file (*.cpp);;C source file (*.c)"));
        if(file_path_2.isNull())
            return;
        file_path.remove();

        QFile file(file_path_2);
        if(!file.open(QIODevice::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this,"Warning","Cannot save file :"+ file.errorString());
            return;
        }
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),file_path_2);
        QTextStream out(&file);
        QString text = ui->plainTextEdit->toPlainText();
        out<< text;

        model = new QDirModel(this);/*Odświeżenie treeView*/
        model->setReadOnly(false);
        model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
        ui->treeView->setModel(model);
    }
    else
    {
        QMessageBox::warning(this,"Warning","File not exist");
    }
    file_path.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog printDlg (&printer,this);
    if(printDlg.exec() == QDialog::Accepted)
    {
       ui->plainTextEdit->print(&printer);
    }
}

void MainWindow::on_actionExit_triggered()
{
    MainWindow::close();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();

}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->plainTextEdit->selectAll();
}

void MainWindow::on_actionClear_triggered()
{
    ui->plainTextEdit->clear();
}


void MainWindow::return_default_font()
{
    //setupEditor();
    QString text;
    ui->plainTextEdit->font().defaultFamily();
    text = ui->plainTextEdit->toPlainText();
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setPlainText(text);

}


void MainWindow::get_world(QString searchString)
{
    qDebug()<<searchString;
    return_default_font();

    QTextDocument *document = ui->plainTextEdit->document();
    bool found = false;
    //document->undo();

    if (searchString.isEmpty()) {
        QMessageBox::information(this, tr("Empty Search Field"),
                                 tr("The search field is empty. "
                                    "Please enter a word and click Find."));
    } else
    {
        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);

        cursor.beginEditBlock();


        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setForeground(Qt::red);

        while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
            highlightCursor = document->find(searchString, highlightCursor,
                                             QTextDocument::FindWholeWords);

            if (!highlightCursor.isNull()) {
                found = true;
                highlightCursor.movePosition(QTextCursor::WordRight,
                                             QTextCursor::KeepAnchor);
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }


        cursor.endEditBlock();


        if (found == false) {
            QMessageBox::information(this, tr("Word Not Found"),
                                     tr("Sorry, the word cannot be found."));
        }
    }
}


void MainWindow::on_actionFind_text_triggered()
{

    findtext = new FindText(this);
    connect(findtext, &FindText::copy_world,this, &MainWindow::get_world);
    connect(findtext, &FindText::close_new_dialog,this, &MainWindow::return_default_font);
    findtext->show();

}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->plainTextEdit->setFont(font);
    }else
    {
        return;
    }
}

void MainWindow::on_actionAbout_us_triggered()
{
    QMessageBox::about(this, tr("About Application"),
             tr("The <b>NotePad BM</b> was made by <b>Bartłomiej Kotarski</b> and <b>Marcin Kozłowski</b>. "
                "We are students of Kielce University of Technology. The notebook was made as a class project <i>Programowanie w języku C 2. </i>"
                "We are from group 2ID12B. "
                ));
}



void MainWindow::closeEvent (QCloseEvent *event)
{
    if(!ui->plainTextEdit->document()->isEmpty())
    {
        qDebug()<<"Close without save";

        QMessageBox::StandardButton oki = QMessageBox::question( this, "NotePad BM",
                                                                    tr("Do you want to save changes?\n"),
                                                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (oki == QMessageBox::Yes) {
            on_actionSave_As_triggered();
            event->accept();
        } else if(oki == QMessageBox::No)
        {
            event->accept();
        }else {
            event->ignore();
        }

    }
    else
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "NotePad BM",
                                                                    tr("Are you sure?\n"),
                                                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (resBtn != QMessageBox::Yes) {
            event->ignore();
        } else {
            event->accept();
        }

    }
}

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "csvtablemodel.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_row_clicked();

    void on_drop_row_clicked();

    void on_dump_btn_clicked();

    void on_load_btn_clicked();

private:
    Ui::MainWindow *ui;
    QString current_file;
    CSVTableModel *model;
};
#endif // MAINWINDOW_HPP

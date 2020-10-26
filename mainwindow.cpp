#include <QAbstractItemView>
#include <QFileDialog>
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "csvtablemodel.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new CSVTableModel(this);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_row_clicked()
{
    model->insertRows(model->rowCount(), 1);
}

void MainWindow::on_drop_row_clicked()
{
    /*
     * O(n*m) complexity for random deletions of
     * m rows from a table of size n
     * O(m) for deletions from the end
     */
    auto list = ui->tableView->selectionModel()->selectedRows();
    while (!list.empty()) {
        auto index = list.at(0);
        model->removeRows(index.row(), 1);
        list = ui->tableView->selectionModel()->selectedRows();
    }
}

void MainWindow::on_dump_btn_clicked()
{
    auto current_file = QFileDialog::getOpenFileName(this,
        tr(u8"Выберите файл"), "", tr("*.csv"));
    if (!current_file.isEmpty())
        model->dumpToFile(current_file);
}

void MainWindow::on_load_btn_clicked()
{
    auto current_file = QFileDialog::getOpenFileName(this,
        tr(u8"Выберите файл"), "", tr("*.csv"));
    if (!current_file.isEmpty())
        model->loadFromFile(current_file);
}

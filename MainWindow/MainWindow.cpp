//
// Created by _Fedor_F on 06.03.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include <iostream>
#include <map>
#include <ranges>
#include "ui_MainWindow.h"
#include "ColorUtils.h"
using namespace ColorUtils;

const std::map<QString, double (*)(const Lab &, const Lab &)> algorithms = {
    {"DeltaE 2000", delta_e_ciede_2000},
    {"DeltaE 94", delta_e_cie_94},
    {"DeltaE cmc", delta_e_cmc},
    {"DeltaE 76", delta_e_cie_76},

};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    for (const auto &key: std::views::keys(algorithms)) {
        ui->AlgoritmComboBox->addItem(key);
    }
    CalculateDeltaE();
    connect(ui->ColorWidget1, &ColorWidget::colorChanged, this, &MainWindow::CalculateDeltaE);
    connect(ui->ColorWidget2, &ColorWidget::colorChanged, this, &MainWindow::CalculateDeltaE);
    connect(ui->AlgoritmComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::CalculateDeltaE);
}

void MainWindow::CalculateDeltaE() const {
    const auto value = algorithms.at(ui->AlgoritmComboBox->currentText())(ui->ColorWidget1->lab, ui->ColorWidget2->lab);
    ui->DeltaETextBrowser->setText(QString::number(value, 'f', 10));
}

MainWindow::~MainWindow() {
    delete ui;
}

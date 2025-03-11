//
// Created by _Fedor_F on 04.03.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ColorWidget.h" resolved

#include "ColorWidget.h"

#include <iostream>

#include "ui_ColorWidget.h"
#include "ColorUtils.h"
#include <random>

const QRegularExpression hexRegex(R"(#?[A-Fa-f0-9]{6}$)");

ColorWidget::ColorWidget(QWidget *parent): QWidget(parent), ui(new Ui::ColorWidget) {
    ui->setupUi(this);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dist(0, 255);

    const auto *validator = new QRegularExpressionValidator(hexRegex, ui->HEX_value);
    ui->HEX_value->setValidator(validator);

    rgb = RGB(dist(gen), dist(gen), dist(gen));
    update_rgb();
    update_from_rgb();
    update_colorframe();

    connect(ui->RGB_R, &QSpinBox::valueChanged, this, &update_from_rgb);
    connect(ui->RGB_G, &QSpinBox::valueChanged, this, &update_from_rgb);
    connect(ui->RGB_B, &QSpinBox::valueChanged, this, &update_from_rgb);

    connect(ui->Lab_L, &QDoubleSpinBox::valueChanged, this, &update_from_lab);
    connect(ui->Lab_a, &QDoubleSpinBox::valueChanged, this, &update_from_lab);
    connect(ui->Lab_b, &QDoubleSpinBox::valueChanged, this, &update_from_lab);

    connect(ui->LCh_L, &QDoubleSpinBox::valueChanged, this, &update_from_lch);
    connect(ui->LCh_C, &QDoubleSpinBox::valueChanged, this, &update_from_lch);
    connect(ui->LCh_h, &QDoubleSpinBox::valueChanged, this, &update_from_lch);

    connect(ui->HEX_value, &QLineEdit::textChanged, this, &update_from_hex);
}


void ColorWidget::update_from_rgb() {
    rgb.R = ui->RGB_R->value();
    rgb.G = ui->RGB_G->value();
    rgb.B = ui->RGB_B->value();
    lab = Lab(rgb);
    lch = LCh(lab);
    hex = HEX(rgb);
    update_lab();
    update_lch();
    update_hex();
    update_colorframe();
    emit colorChanged();
}

void ColorWidget::update_from_lab() {
    lab.L = ui->Lab_L->value();
    lab.a = ui->Lab_a->value();
    lab.b = ui->Lab_b->value();
    rgb = RGB(lab);
    lch = LCh(lab);
    hex = HEX(rgb);
    update_rgb();
    update_lch();
    update_hex();
    update_colorframe();
    emit colorChanged();
}

void ColorWidget::update_from_lch() {
    lch.L = ui->LCh_L->value();
    lch.C = ui->LCh_C->value();
    lch.h = ui->LCh_h->value();
    rgb = RGB(lch);
    lab = Lab(lch);
    hex = HEX(rgb);
    update_rgb();
    update_lab();
    update_hex();
    update_colorframe();
    emit colorChanged();
}

void ColorWidget::update_from_hex() {
    if (not hexRegex.match(ui->HEX_value->text()).hasMatch()) {
        return;
    }
    hex = HEX(ui->HEX_value->text().toStdString());
    rgb = RGB(hex);
    lab = Lab(rgb);
    lch = LCh(lab);
    update_rgb();
    update_lab();
    update_lch();
    update_colorframe();
    emit colorChanged();
}


void ColorWidget::update_rgb() const {
    ui->RGB_R->blockSignals(true);
    ui->RGB_G->blockSignals(true);
    ui->RGB_B->blockSignals(true);
    ui->RGB_R->setValue(rgb.R);
    ui->RGB_G->setValue(rgb.G);
    ui->RGB_B->setValue(rgb.B);
    ui->RGB_R->blockSignals(false);
    ui->RGB_G->blockSignals(false);
    ui->RGB_B->blockSignals(false);
}

void ColorWidget::update_lab() const {
    ui->Lab_L->blockSignals(true);
    ui->Lab_a->blockSignals(true);
    ui->Lab_b->blockSignals(true);
    ui->Lab_L->setValue(lab.L);
    ui->Lab_a->setValue(lab.a);
    ui->Lab_b->setValue(lab.b);
    ui->Lab_L->blockSignals(false);
    ui->Lab_a->blockSignals(false);
    ui->Lab_b->blockSignals(false);
}

void ColorWidget::update_lch() const {
    ui->LCh_L->blockSignals(true);
    ui->LCh_C->blockSignals(true);
    ui->LCh_h->blockSignals(true);
    ui->LCh_L->setValue(lch.L);
    ui->LCh_C->setValue(lch.C);
    ui->LCh_h->setValue(lch.h);
    ui->LCh_L->blockSignals(false);
    ui->LCh_C->blockSignals(false);
    ui->LCh_h->blockSignals(false);
}

void ColorWidget::update_hex() const {
    ui->HEX_value->blockSignals(true);
    ui->HEX_value->setText(QString::fromStdString(hex.toString()));
    ui->HEX_value->blockSignals(false);
}

void ColorWidget::set_color(const RGB &rgb) {
    this->rgb = rgb;
    update_from_rgb();
}

void ColorWidget::set_color(const Lab &lab) {
    this->lab = lab;
    update_from_lab();
}

void ColorWidget::set_color(const LCh &lch) {
    this->lch = lch;
    update_from_lch();
}


void ColorWidget::update_colorframe() const {
    const QString color = QString("QFrame { background-color: rgb(%1, %2, %3); }").arg(rgb.R).arg(rgb.G).arg(rgb.B);
    ui->ColorFrame->setStyleSheet(color);
}

ColorWidget::~ColorWidget() {
    delete ui;
}

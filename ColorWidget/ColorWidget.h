//
// Created by _Fedor_F on 04.03.2025.
//

#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include "ColorUtils.h"
using namespace ColorUtils;

QT_BEGIN_NAMESPACE

namespace Ui {
    class ColorWidget;
}

QT_END_NAMESPACE

class ColorWidget : public QWidget {
    Q_OBJECT
signals:
    void colorChanged();

public:
    RGB rgb{};
    Lab lab{};
    LCh lch{};
    HEX hex{};

    explicit ColorWidget(QWidget *parent = nullptr);

    void set_color(const RGB &rgb);

    void set_color(const Lab &lab);

    void set_color(const LCh &lch);

    ~ColorWidget() override;

private:
    Ui::ColorWidget *ui;

    void update_from_rgb();

    void update_from_lab();

    void update_from_lch();

    void update_from_hex();

    void update_rgb() const;

    void update_lab() const;

    void update_lch() const;

    void update_hex() const;

    void update_colorframe() const;
};


#endif //COLORWIDGET_H

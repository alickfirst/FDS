#ifndef SCALEBACKGROUNDWIDGET_H
#define SCALEBACKGROUNDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

class ScalableBackgroundWidget : public QWidget {
public:
    ScalableBackgroundWidget(QWidget *parent = nullptr)
        : QWidget(parent) {
        background.load("");
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);

        // 关键：缩放图片到当前窗口大小（忽略宽高比，允许变形）
        QPixmap scaled = background.scaled(
            this->size(),
            Qt::IgnoreAspectRatio,  // 允许变形
            Qt::SmoothTransformation // 平滑缩放
        );

        // 绘制缩放后的图片（单张填充，不平铺）
        painter.drawPixmap(0, 0, scaled);
    }

private:
    QPixmap background;
};

#endif // SCALEBACKGROUNDWIDGET_H

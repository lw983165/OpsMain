#ifndef QGAUGE_H
#define QGAUGE_H

#include <QWidget>

class QGauge : public QWidget
{
    Q_OBJECT
public:
    explicit QGauge(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    QString background, pointer;
    float minValue, maxValue, value;
};

#endif // QGAUGE_H

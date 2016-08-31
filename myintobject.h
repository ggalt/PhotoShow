#ifndef MYINTOBJECT_H
#define MYINTOBJECT_H

#include <QObject>

class myIntObject : public QObject
{
    Q_OBJECT
public:
    explicit myIntObject(QObject *parent = 0);
    Q_PROPERTY(int blurVal READ getBlurVal WRITE setBlurVal)

    int getBlurVal(void) const { return m_blurVal; }

    void setBlurVal(int t) { m_blurVal = t; }

signals:

public slots:
private:
    int m_blurVal;
};

#endif // MYINTOBJECT_H

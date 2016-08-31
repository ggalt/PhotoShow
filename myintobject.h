#ifndef MYINTOBJECT_H
#define MYINTOBJECT_H


class myIntObject : public QObject
{
    Q_OBJECT
public:
    explicit myIntObject(QObject *parent = 0);
    Q_PROPERTY(int blurVal READ blurVal WRITE setBlurVal)

signals:

public slots:
private:
    int m_blurVal;
};

#endif // MYINTOBJECT_H

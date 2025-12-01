#pragma once

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    Q_INVOKABLE void playSong();

signals:
};

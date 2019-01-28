#include "clickableqlabel.h"

#include <QDebug>

ClickableQLabel::ClickableQLabel(QWidget *parent, Qt::WindowFlags f): QLabel(parent)
{

}

ClickableQLabel::~ClickableQLabel() {}

void ClickableQLabel::enterEvent(QEvent* e)
{
    setStyleSheet("QLabel { background-color : transparent; color : #00FF00; }");
    qDebug() << "enterEvent()";
}

void ClickableQLabel::leaveEvent(QEvent* e)
{
    setStyleSheet("QLabel { background-color : transparent; color : #FFF; }");
    qDebug() << "leaveEvent()";
}

void ClickableQLabel::mousePressEvent(QMouseEvent* e)
{
    qDebug() << "mousePressEvent()";
}

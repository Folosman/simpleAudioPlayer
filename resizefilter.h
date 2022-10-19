#ifndef RESIZEFILTER_H
#define RESIZEFILTER_H

#include <QObject>
#include <QTabWidget>
#include <QEvent>

class ResizeFilter : public QObject
{
    QTabWidget *target;
public:
    ResizeFilter(QTabWidget *target) : QObject(target), target(target) {}

    bool eventFilter(QObject *object, QEvent *event)
    {
        if (event->type() == QEvent::Resize)
        {
            // The width of each tab is the width of the tab widget / # of tabs.
            target->setStyleSheet(QString("QTabBar::tab { width: %1px; } ")
                      .arg(target->size().width()/target->count()-1));
        }
        return false;
    }
};

#endif // RESIZEFILTER_H

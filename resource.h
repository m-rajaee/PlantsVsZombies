#ifndef RESOURCE_H
#define RESOURCE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
class Resource : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum ResourceType {
        Sun, Brain
    };
    Resource(ResourceType type);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void collected();
private slots:
    void destroy();
private:
    QTimer* timer;
};

#endif // RESOURCE_H

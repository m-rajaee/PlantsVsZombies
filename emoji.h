#ifndef EMOJI_H
#define EMOJI_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Emoji : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum EmojiType {
        Laugh, Poker, Rage, SunGlass
    };
    Emoji(EmojiType type);
    EmojiType type;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void emojiSelected(Emoji*);
};

#endif // EMOJI_H

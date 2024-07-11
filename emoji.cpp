#include "emoji.h"
#include <QGraphicsSceneMouseEvent>
Emoji::Emoji(EmojiType type) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    this->type = type;
    if (type == Laugh){
        setPixmap(QPixmap(":/image/laugh.png"));
        setScale(0.09);
    }
    else if (type == Poker){
        setPixmap(QPixmap(":/image/poker.png"));
        setScale(0.05);
    }else if (type == Rage){
        setPixmap(QPixmap(":/image/rage.png"));
        setScale(0.07);
    }else if (type == SunGlass){
        setPixmap(QPixmap(":/image/sunglass.png"));
        setScale(0.08);
    }
}

void Emoji::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit emojiSelected(this);
}

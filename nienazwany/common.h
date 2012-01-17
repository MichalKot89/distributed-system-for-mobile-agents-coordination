#ifndef COMMON_H
#define COMMON_H

#include <QObject>
#include <vector>

enum mode {Start, Stop, Path};

struct coord
{
    qreal x;
    qreal y;
    coord(){x=0; y=0;}
    coord(qreal cx, qreal cy){x=cx; y=cy;}
};

#endif // COMMON_H

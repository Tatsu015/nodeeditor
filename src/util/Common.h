#ifndef COMMON_H
#define COMMON_H

#include <QString>

extern QString btos(bool value);
extern bool    stob(const QString& value);

enum EPosition:int{
    Top,
    Right,
    Bottom,
    Left,
};

enum BugType:int{
    Error,
    Warning,
};

#endif // COMMON_H

#ifndef APPCONFIGS_HPP
#define APPCONFIGS_HPP

#include <QString>
#include <QDebug>
#include "Macros.hpp"

GroupStart(StyleSheet)
AddConst(QString, normal,
    "QWidget { background: grey; }"
    "QPushButton { background-color: green; }")
GroupEnd

GroupStart(Defaults)
Add(QString, privateApiKey, "")
Add(QString, publicSiteKey, "")
Add(QString, server, "")
GroupEnd

#endif // APPCONFIGS_HPP

#ifndef UTILITIES_H
#define UTILITIES_H
#include <QObject>
#include <QFileInfo>
#include <QDir>
#include "vdf_parser.hpp"

namespace Utilities {
QString getSteamGamePath() {

    QString gamePath="";

    QString home = QDir::homePath();

    QString possible_steam_roots[] = {home + "/.local/share/Steam",
                                      home + "/.steam/root",
                                      home + "/.steam/steam",
                                      home + "/.steam/debian-installation"};

    QString steam_root = "";

    for (QString possible_root : possible_steam_roots) {
        if (QFileInfo::exists(possible_root + "/config/config.vdf") &&
            QFileInfo::exists(possible_root + "/config/libraryfolders.vdf"))
        {
            steam_root = possible_root;
            break;
        }

    }

    // Checks if distro Steam is installed

    if (steam_root != "") {

        std::ifstream file(steam_root.toStdString() + "/config/libraryfolders.vdf");
        auto root = tyti::vdf::read(file);


        for (auto& child : root.childs) {
            if (root.childs[child.first]->childs["apps"]->attribs.find("271590") !=
                root.childs[child.first]->childs["apps"]->attribs.end())
            {
                gamePath = QString::fromStdString(root.childs[child.first]->attribs["path"] +
                                                  "/steamapps/common/Grand Theft Auto V");
                break;
            }
        }

    }



    // Checks if Steam flatpak is installed

    if (QFileInfo::exists(home + "/.var/app/com.valvesoftware.Steam/data/Steam/config/config.vdf") &&
        QFileInfo::exists(home + "/.var/app/com.valvesoftware.Steam/data/Steam/config/libraryfolders.vdf"))
    {
        std::ifstream file(home.toStdString() +
                           "/.var/app/com.valvesoftware.Steam/data/Steam/config/libraryfolders.vdf");

        auto root = tyti::vdf::read(file);

        for (auto& child : root.childs) {
            if (root.childs[child.first]->childs["apps"]->attribs.find("271590") !=
                root.childs[child.first]->childs["apps"]->attribs.end())
            {
                gamePath = QString::fromStdString(root.childs[child.first]->attribs["path"] +
                                                  "/steamapps/common/Grand Theft Auto V");
                break;
            }
        }

    }

    // Checks if Steam snap is installed

    if (QFileInfo::exists(home + "/snap/steam/common/.steam/root/config/config.vdf") &&
        QFileInfo::exists(home + "/snap/steam/common/.steam/root/config/libraryfolders.vdf"))
    {
        std::ifstream file(home.toStdString() +
                           "/snap/steam/common/.steam/root/config/libraryfolders.vdf");

        auto root = tyti::vdf::read(file);

        for (auto& child : root.childs) {
            if (root.childs[child.first]->childs["apps"]->attribs.find("271590") !=
                root.childs[child.first]->childs["apps"]->attribs.end())
            {
                gamePath = QString::fromStdString(root.childs[child.first]->attribs["path"] +
                                                  "/steamapps/common/Grand Theft Auto V");
                break;
            }
        }

    }

    return gamePath;
}
}
#endif // UTILITIES_H

/*
 * author       :  YangLi
 * date         :  2023-07-18
 * description  :  DataManager类有一个静态函数，用来获取图片的信息并保存在QList容器中
 */
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QList>
#include <QFileInfo>

#include "imagedatainfo.h"


class DataManager
{
public:
    DataManager();

    static QList<ImageDataInfo> GetImageInfoList(int page);
};

#endif // DATAMANAGER_H

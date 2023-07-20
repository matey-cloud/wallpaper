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
#include <QDir>

#include "imagedatainfo.h"

class DataManager
{
public:
    DataManager();


    void getImages(); //从数据库中读出来的所有壁纸
    QList<ImageDataInfo> getImagesOfPage(int page);//从mImageList中读对应页的壁纸

    int curPage() const;

    int totalPage() const;

    QList<ImageDataInfo> imagesList() const;

    void setCurPage(int newCurPage);

private:
    int mCurPage;
    int mTotalPage;
    QList<ImageDataInfo> mImagesList; // 存储从数据库中读出来的所有壁纸
};

#endif // DATAMANAGER_H

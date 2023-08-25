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

    void getImages(int num); //从文件夹中读出来的所有壁纸
    QList<ImageDataInfo> getImagesOfPage(int page);//从mImageList中读对应页的壁纸

    void setCurPage(int newCurPage);
    int curPage() const;
    int totalPage() const;
    void clear(); // 清空mFileList的数据

    void setPageImageNum(int newPageImageNum);

    QFileInfoList fileList() const;

private:
    int mCurPage; // 当前显示页
    int mTotalPage;// 一共多少页图片
    int mTotalImage; // 一共多少张图片
    int mPageImageNum; // 一页有多少张图片
    QFileInfoList mFileList; // 存储从文件夹中读取出的所有文件信息， QList<QFileInfo>
};

#endif // DATAMANAGER_H

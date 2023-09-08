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

//// 描述主菜单的状态
//enum class MainMenu{
//    HomePage,
//    CollectPage
//};

class DataManager
{
public:
    inline static const QString smHomePath = "D:\\CandC++\\C++\\wallpaper\\images";
    inline static const QString smColloetPath = "D:\\CandC++\\C++\\wallpaper\\collect";

    DataManager();

    void getImages(int num); //从文件夹中读出来的所有图片
    QList<ImageDataInfo> getImagesOfPage(int page);//从mImageList中读对应页的图片

    void getClassflyImages(const QString& str);
    QList<ImageDataInfo> getClassflyImagesOfPage(int page);


    void setCurPage(int newCurPage) { mCurPage = newCurPage; } // 设置当前显示页
    int curPage() const { return mCurPage; } // 获取当前显示页
    int totalPage() const { return mTotalPage; } // 获取一共多少页
    void setPageImageNum(int newPageImageNum){ mPageImageNum = newPageImageNum; }
    QFileInfoList fileList() const{ return mFileList; }

    int classflyTotalPage() const { return mClassflyTotalPage; }// 获取当前分类一共多少页

    // 计算图片数量和页数量
    void CalculateImageAndPageCount();
    QSize imageSize() const { return mImageSize; }
    void setImageSize(const QSize &newImageSize) { mImageSize = newImageSize; }

private:
    QSize mImageSize;

    int mCurPage; // 当前显示页
    int mTotalPage;// 一共多少页图片
    int mTotalImage; // 一共多少张图片
    int mPageImageNum; // 一页有多少张图片
    QFileInfoList mFileList; // 存储从文件夹中读取出的所有文件信息， QList<QFileInfo>

    int mClassflyCurPage; // 当前分类显示页
    int mClassflyTotalPage;// 当前分类一共多少页图片
    int mClassflyTotalImage; // 当前分类一共多少张图片
    QFileInfoList mFileClassflyList; // 分类按钮点击后，启用
};

#endif // DATAMANAGER_H

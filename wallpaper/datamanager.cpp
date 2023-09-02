/*
 * author       :  YangLi
 * date         :  2023-07-18
 * description  :
 */
#include "datamanager.h"
#include <QDebug>

const static QString homePath = "D:\\CandC++\\C++\\wallpaper\\images";
const static QString colloetPath = "D:\\CandC++\\C++\\wallpaper\\collect";


DataManager::DataManager()
    : mCurPage(1),
      mTotalPage(0)
{

}

void DataManager::getImages(int num)
{
    clear();
    QString folderPath;
    if(num == 1){
         folderPath = homePath;
    }
    else if(num == 2){
        folderPath = colloetPath;
    }
    // 读取文件夹中的文件
    QDir directory(folderPath);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg"; // 图片文件的扩展名
    directory.setNameFilters(filters);
    mFileList = directory.entryInfoList(); // 存储从文件夹中读取出的所有文件信息

    // 一共的图片数量
    mTotalImage = mFileList.count();
    qDebug() << "num " <<  num << "mTotalImage" << mTotalImage;
    // 计算页数
    if((mTotalImage / mPageImageNum) == 0){
        mTotalPage = mTotalImage / mPageImageNum;
    } else {
        mTotalPage = (mTotalImage / mPageImageNum) + 1;
    }

    // 如果不足mPageImageNum张图片，即一页
    if(mTotalImage == 0){
        mTotalPage += 1;
    }
}

QList<ImageDataInfo> DataManager::getImagesOfPage(int page)
{
    QList<ImageDataInfo> imageItemList;

    // 要获取的那一页壁纸的索引
    int endIndex = page * mPageImageNum;
    int startIndex = endIndex - (mPageImageNum-1) ;

    // 如果最后一页少于mPageImageNum个，QList将越界，所以需要把结束索引修改为容器的大小
    if (endIndex > mTotalImage){
        endIndex = mTotalImage;
    }
    // 需要哪一页图片就加载哪一页的图片
    for(int i = startIndex; i <= endIndex; ++i){
        ImageDataInfo info;
        QString imageName = mFileList[i - 1].baseName();// 文件名没有后缀
        info.setPath(mFileList[i - 1].filePath());
        info.setPhotoName(imageName);
        imageItemList.push_back(info);
    }
    return imageItemList;
}

void DataManager::setCurPage(int newCurPage)
{
    mCurPage = newCurPage;
}

int DataManager::curPage() const
{
    return mCurPage;
}

int DataManager::totalPage() const
{
    return mTotalPage;
}

void DataManager::clear()
{
    mTotalPage = 0;
    mTotalImage = 0;
    mFileList.clear();
}

void DataManager::setPageImageNum(int newPageImageNum)
{
    mPageImageNum = newPageImageNum;
}

QFileInfoList DataManager::fileList() const
{
    return mFileList;
}






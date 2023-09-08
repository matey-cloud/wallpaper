/*
 * author       :  YangLi
 * date         :  2023-07-18
 * description  :
 */
#include "datamanager.h"
#include <QDebug>


DataManager::DataManager()
    : mCurPage(1)
    , mTotalPage(0)
    , mTotalImage(0)
    , mPageImageNum(0)
    , mClassflyCurPage(1)
    , mClassflyTotalPage(0)
    , mClassflyTotalImage(0)
{

    mFileList.clear();
    mFileClassflyList.clear();
}

void DataManager::getImages(int num)
{
    QString folderPath;
    if(num == 1){
        folderPath = smHomePath;
    }
    else if(num == 2){
        folderPath = smColloetPath;
    }
    // 读取文件夹中的文件
    QDir folderDir(folderPath);
    folderDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList folderList = folderDir.entryInfoList();
    foreach(const QFileInfo& folderInfo, folderList)
    {
        QString folderPath = folderInfo.absoluteFilePath();
        // 遍历分类文件夹中的图片
        QDir imagesDir(folderPath);
        imagesDir.setFilter(QDir::Files);
        imagesDir.setNameFilters(QStringList() << "*.jpg" << "*.png" << "*.jpeg"); // 添加对应的图片格式过滤条件
        QFileInfoList imageList = imagesDir.entryInfoList();
        foreach(const QFileInfo& imageInfo, imageList)
        {
            mFileList.push_back(imageInfo);
        }
    }
    CalculateImageAndPageCount();
}

void DataManager::CalculateImageAndPageCount(){
    // 一共的图片数量
    mTotalImage = mFileList.count();
    // 计算页数
    if(mTotalImage < mPageImageNum){
        mTotalPage = 1;
    } else if(mTotalImage / mPageImageNum == 0){
        mTotalPage = mTotalImage / mPageImageNum;
    } else{
        mTotalPage = (mTotalImage / mPageImageNum) + 1;
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
        info.setSize(mImageSize); // 设置图片的大小

        imageItemList.push_back(info);
    }
    return imageItemList;
}

void DataManager::getClassflyImages(const QString &str)
{
    mFileClassflyList.clear();
    for(const auto& image : mFileList){
        // 对当前文件的绝对路径处理
        QString classflyName = image.absolutePath();
        QStringList res = classflyName.split('/');
        // res.back()就是该图片的分类名称，即这张图片在这个文件夹下
        if(res.back().contains(str) || image.baseName().contains(str)){
            qDebug() << res.back();
            mFileClassflyList.push_back(image);
        }

    }

    // 一共的图片数量
    mClassflyTotalImage = mFileClassflyList.count();
    // 计算页数
    if(mClassflyTotalImage < mPageImageNum){
        mClassflyTotalPage = 1;
    } else if(mClassflyTotalImage % mPageImageNum == 0){ // 如果能被整除
        mClassflyTotalPage = mClassflyTotalImage / mPageImageNum;
    } else{
        mClassflyTotalPage = (mClassflyTotalImage / mPageImageNum) + 1;
    }
}

QList<ImageDataInfo> DataManager::getClassflyImagesOfPage(int page)
{
    QList<ImageDataInfo> imageItemList;
    // 要获取的那一页壁纸的索引
    int endIndex = page * mPageImageNum;
    int startIndex = endIndex - (mPageImageNum-1) ;

    // 如果最后一页少于mPageImageNum个，QList将越界，所以需要把结束索引修改为容器的大小
    if (endIndex > mClassflyTotalImage){
        endIndex = mClassflyTotalImage;
    }

    // 需要哪一页图片就加载哪一页的图片
    for(int i = startIndex; i <= endIndex; ++i){
        ImageDataInfo info;
        QString imageName = mFileClassflyList.at(i-1).baseName();// 文件名没有后缀
        info.setPath(mFileClassflyList.at(i-1).filePath());
        info.setPhotoName(imageName);
        imageItemList.push_back(info);
    }
    return imageItemList;
}







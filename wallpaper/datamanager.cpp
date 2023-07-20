/*
 * author       :  YangLi
 * date         :  2023-07-18
 * description  :
 */
#include "datamanager.h"

DataManager::DataManager()
    : mCurPage(1),
      mTotalPage(0),
      mImagesList() //定义并初始化图片列表
{
    getImages(); // 获取图片和页数
}

void DataManager::getImages()
{
//    QStringList imagePathList;

    QString folderPath = "D:\\CandC++\\C++\\wallpaper\\images";
    // 读取文件夹中的文件
    QDir directory(folderPath);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg"; // 图片文件的扩展名
    directory.setNameFilters(filters);
    QFileInfoList fileList = directory.entryInfoList();
    foreach (QFileInfo fileInfo, fileList) {
        // 使用QImageReader加载图片
//        imagePathList.append(fileInfo.filePath());
        QString imageName = fileInfo.fileName();
        ImageDataInfo info;
        info.setPath(fileInfo.filePath());
        qDebug() << "文件路径" << fileInfo.filePath();
        info.setPhotoName(imageName);
        mImagesList.push_back(info);

    }

    // 遍历图片路径列表获取图片名和图片路径，并添加到 QList中
//    foreach (const QString &imagePath, imagePathList) {
//        QFileInfo fileInfo(imagePath);
//        QString imageName = fileInfo.fileName();
//        ImageDataInfo info;
//        info.setPath(imagePath);
//        info.setPhotoName(imageName);
//        mImagesList.push_back(info);
//    }

    // 获取壁纸
    // 执行查询语句，获取图片数据
//    QSqlQuery query;
//    query.prepare("SELECT data FROM images WHERE name = :name");
//    query.bindValue(":name", "myimage.jpg");
//    query.exec();
//    if (query.next()) {
//        ImageDataInfo info;
//        info.mImageData = query.value(0).toByteArray();
//        info.mPhotoName = query.value(1).toQString();

//        // 加载图片数据并显示在 QLabel 上
//        QPixmap pixmap;
//        pixmap.loadFromData(imageData);
//        ui->label->setPixmap(pixmap);

//        // 将从数据库中读取的图片信息封装到ImageDataInfo插入到smImageList
//        smImagesList.push_back(info);
//    }

    // 计算页数
    if((mImagesList.count() / 6) == 0){
        mTotalPage = mImagesList.count() / 6;
    } else {
        mTotalPage = (mImagesList.count() / 6) + 1;
    }
}

QList<ImageDataInfo> DataManager::getImagesOfPage(int page)
{
    QList<ImageDataInfo> imageItemList;

    // 要获取的那一页壁纸的索引
    int endIndex = page * 6;
    int startIndex = endIndex - 5;

    // 如果最后一页少于6个，QList将越界，所以需要把结束索引修改为容器的大小
    if (endIndex > mImagesList.size()){
        endIndex = mImagesList.size();
    }
    for(int i = startIndex; i <= endIndex; ++i){
        if(mImagesList.size()){
            imageItemList.push_back(mImagesList[i-1]); //
        }
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

QList<ImageDataInfo> DataManager::imagesList() const
{
    return mImagesList;
}




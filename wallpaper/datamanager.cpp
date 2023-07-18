/*
 * author       :  YangLi
 * date         :  2023-07-18
 * description  :
 */
#include "datamanager.h"

DataManager::DataManager()
{

}

QList<ImageDataInfo> DataManager::GetImageInfoList(int page)
{
    QList<ImageDataInfo> imageItemList;

    // 图片路径列表
    QStringList imagePathList = {
        "D:/CandC++/C++/wallpaper/images/Itachi.jpg",
        "D:\\CandC++\\C++\\wallpaper\\images\\Naruto.jpg",
        "D:\\CandC++\\C++\\wallpaper\\images\\Obitu.jpg"
    };

    // 遍历图片路径列表获取图片名和图片路径，并添加到 QMap 中
    foreach (const QString &imagePath, imagePathList) {
        QFileInfo fileInfo(imagePath);
        QString imageName = fileInfo.fileName();
        ImageDataInfo info;
        info.setPath(imagePath);
        info.setPhotoName(imageName);
        imageItemList.push_back(info);
    }

    // 打印 QList中的 ImageInfoItem ,图片名和图片路径
    QListIterator<ImageDataInfo> it(imageItemList);
    while (it.hasNext()) {
        const ImageDataInfo& item = it.next();
        qDebug() << "Image Name:" << item.getPhotoName() << "Image Path:" << item.getPath();
    }

    return imageItemList;
}


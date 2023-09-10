/*
 * author       :  YangLi
 * date         :  2023-07-18
 * description  :  ImageDataInfo对图片信息进行封装，有setter和getter方法设置并读取属性
 */
#ifndef IMAGEDATAINFO_H
#define IMAGEDATAINFO_H

#include <QString>
#include <QSize>
class ImageDataInfo
{
public:
    ImageDataInfo();
    QString getImageName() const{ return mImageName; }
    QString getPath() const { return mPath; }
    void setImageName(const QString &newImageName){ mImageName = newImageName; }
    void setPath(const QString &newPath){ mPath = newPath; }


    QSize size() const { return mSize; }
    void setSize(const QSize &newSize) { mSize = newSize; }

private:
    QByteArray mImageData; // 图片的二进制数据
    QString mImageName;
    QString mPath;
    QSize mSize; // 图片的大小
};

#endif // IMAGEDATAINFO_H

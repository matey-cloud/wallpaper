/*
 * author       :  YangLi
 * date         :  2023-07-18
 * description  :  ImageInfoItem是对QListWidget中的Item进行封装
 *                 该Item中显示图片，并设置了图片的鼠标事件：触碰、左击、右击
 */
#ifndef IMAGEINFOITEM_H
#define IMAGEINFOITEM_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QFont>
#include <QMenu>
#include <QAction>
#include <QGuiApplication>
#include <QSettings>
#include <Windows.h>

#include "imagedatainfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ImageInfoItem; }
QT_END_NAMESPACE

class ImageInfoItem : public QWidget
{
    Q_OBJECT
public:
    explicit ImageInfoItem(QWidget *parent = nullptr);
    ~ImageInfoItem();

    void addImage(ImageDataInfo &info);

    QString path() const{ return mPath; }

    QString imageName() const{ return mImageName; }

    // 设置当前图片为桌面壁纸
    void setWallPaper();

    void addImage();
    void contextMenuEvent(QContextMenuEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);

    void RightClickMenu(int num);
signals:
    void clickCollectMenu(ImageInfoItem*);

private:
    Ui::ImageInfoItem *ui;

    QMenu mMenu;
    QAction *mAction1;
    QAction *mAction2;

    QPixmap mImagePixmap;
    QLabel *mImageInfo; // 显示图片信息
    QString mImageName;//当前图片的名称
    QString mPath;//当前图片的路径
    QSize mSize;
};

#endif // IMAGEINFOITEM_H

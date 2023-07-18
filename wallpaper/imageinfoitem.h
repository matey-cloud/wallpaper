
#ifndef IMAGEINFOITEM_H
#define IMAGEINFOITEM_H
/*
 * author       :  YangLi
 * date         :  2023-07-18
 * description  :  ImageInfoItem是对QListWidget中的Item进行封装
 *                 该Item中显示图片，并设置了图片的鼠标事件：触碰、左击、右击
 */
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

private:
    void addImage();
    void contextMenuEvent(QContextMenuEvent *event);
    void setWallPaper();

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);

private:
    Ui::ImageInfoItem *ui;

    QPixmap mImagePixmap;
    QLabel *mImageInfo; // 显示图片信息
    QString mImageName;//当前图片的名称
    QString mPath;//当前图片的路径
};

#endif // IMAGEINFOITEM_H

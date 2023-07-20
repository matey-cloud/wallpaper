/*
 * author       : YangLi
 * date         :
 * description  :
 */

#include "imageinfoitem.h"
#include "ui_imageInfoItem.h"

ImageInfoItem::ImageInfoItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ImageInfoItem)
    , mImageInfo(nullptr)
{
    ui->setupUi(this);

}

ImageInfoItem::~ImageInfoItem()
{
    delete mImageInfo;
    delete ui;
}

void ImageInfoItem::addImage(ImageDataInfo &info)
{
    //    QString curPhoto = "图片名称 " + info.getPhotoName();
    mImageName = info.getPhotoName();
    mPath = info.getPath();
    ui->frame->setFrameStyle(QFrame::Box);
//    ui->frame->setStyleSheet("QFrame { border: 2px solid green; }");
    // 加载图片
//    QPixmap image(info.getPath());
//    // 调整图片大小适应 QLabel 大小
//    QPixmap scaledImage = mImage.scaled(ui->photo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    // 将图片设置为 QLabel 的内容
//    ui->photo->setPixmap(scaledImage);
//    // 根据需要设置 QLabel 的对齐方式
//    ui->photo->setAlignment(Qt::AlignCenter);
//    // 显示 QFrame
//    ui->frame->show();
    addImage();
}

void ImageInfoItem::addImage()
{
    // 加载图片
    QPixmap image(mPath);
    if( image.isNull()){

        // 添加一个加载失败的图片
    }
    // 调整图片大小适应 QLabel 大小
    QPixmap scaledImage = image.scaled(ui->image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mImagePixmap = scaledImage;

    // 清空
    ui->image->clear();
    ui->image->setStyleSheet("");
    // 将图片设置为 QLabel 的内容
    ui->image->setPixmap(mImagePixmap);
    // 根据需要设置 QLabel 的对齐方式
    ui->image->setAlignment(Qt::AlignCenter);

    // 添加图片信息
    mImageInfo = new QLabel(ui->image); // 在图片上创建嵌套的文本标签
    // 设置字体和大小
    QFont font("微软雅黑 ", 15); // 创建字体对象，Arial 字体，大小为 12
    mImageInfo->setFont(font);
    mImageInfo->setStyleSheet("color: gray;");
    mImageInfo->setText(mImageName); // 设置嵌套文本
    mImageInfo->setGeometry(0, 160, 250, 30); // 设置嵌套标签的位置和大小
    mImageInfo->setAlignment(Qt::AlignLeft); // 设置对齐方式
    mImageInfo->setVisible(false); // 当鼠标触碰才会看见

    // 显示 QFrame
    ui->frame->show();
}

//右击图片
void ImageInfoItem::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this); // 创建菜单

    QAction *action1 = menu.addAction("设置为壁纸"); // 添加菜单项
    QAction *action2 = menu.addAction("添加到我的");

    QAction *selectedAction = menu.exec(event->globalPos()); // 在鼠标位置弹出菜单

    if (selectedAction == action1) {
        setWallPaper();
    } else if (selectedAction == action2) {
        // 处理 Action 2 的操作
    }
}

void ImageInfoItem::setWallPaper()
{
    // 壁纸注册表

    QSettings wallpaperSettings("HKEY_CURRENT_USER\\Control Panel\\Desktop", QSettings::NativeFormat);

    wallpaperSettings.setValue("Wallpaper", mPath);
    wallpaperSettings.setValue("WallpaperStyle", 2);  // 2 表示拉伸平铺
    wallpaperSettings.setValue("TileWallpaper", 0);
    wallpaperSettings.sync();

    std::wstring wPath = mPath.toStdWString();
    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID)wPath.c_str(), SPIF_UPDATEINIFILE);
//    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)mPath.toStdString().c_str(), SPIF_UPDATEINIFILE);
//    qDebug() << "要设置为壁纸的文件路径" << (PVOID)mPath.toStdString().c_str();
}

//重写鼠标按下事件
void ImageInfoItem::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        ui->image->setStyleSheet("border:2px solid yellow;"
                                 " border-radius:25px;");
    }
}

//鼠标释放
void ImageInfoItem::mouseReleaseEvent(QMouseEvent *event)
{
    ui->image->setStyleSheet("");
    QWidget::mouseReleaseEvent(event);
}

// 鼠标触碰
void ImageInfoItem::enterEvent(QEnterEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    mImageInfo->setVisible(true);
    ui->image->setPixmap(mImagePixmap.scaled(mImagePixmap.size() * 1.2)); // 这里简单地将图片尺寸放大20%
//    ui->image->setStyleSheet("border:2px solid red;"
//                             " border-radius:25px;");
    QWidget::enterEvent(event);
}

void ImageInfoItem::leaveEvent(QEvent *event){
    unsetCursor();
    mImageInfo->setVisible(false);
    ui->image->setPixmap(mImagePixmap);
    ui->image->setStyleSheet("");
    QWidget::leaveEvent(event);
}






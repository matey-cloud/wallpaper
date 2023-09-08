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
    , mMenu(this) // 创建菜单
    , mAction1(nullptr)
    , mAction2(nullptr)
    , mImageInfo(nullptr)
{
    ui->setupUi(this);
}

ImageInfoItem::~ImageInfoItem()
{
    delete mImageInfo;
    delete mAction2;
    delete mAction1;
    delete ui;
}

void ImageInfoItem::addImage(ImageDataInfo &info)
{
    //    QString curPhoto = "图片名称 " + info.getPhotoName();
    mImageName = info.getPhotoName();
    mPath = info.getPath();
    mSize = info.size();
    qDebug() << "mSize = " << mSize;
    addImage();
}

void ImageInfoItem::addImage()
{
    // 加载图片
    QPixmap image(mPath);
    if( image.isNull()){
        // A null pixmap has zero width, zero height and no contents. You cannot draw in a null pixmap.
    }
    // 需要调整图片大小适应 QLabel 大小
    // 第二个参数为填满， 为默认参数
    QPixmap scaledImage = image.scaled(mSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

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
    QFont font("微软雅黑 ", 15); // 创建字体对象字体，大小
    mImageInfo->setFont(font);
    mImageInfo->setStyleSheet("color: white;"
                              "background-color: rgba(53, 54, 55, 40%)");// 设置背景为深色且透明度
    mImageInfo->setText(mImageName); // 设置嵌套文本
    mImageInfo->setGeometry(20, 130, 0, 0); // 设置嵌套标签的位置和大小

    mImageInfo->adjustSize();
    mImageInfo->setAlignment(Qt::AlignLeft); // 设置对齐方式
    mImageInfo->setVisible(false); // 当鼠标触碰才会看见

    // 显示 QFrame
    ui->image->show();
}

void ImageInfoItem::RightClickMenu(int num){
    mMenu.clear();
    mAction1 = mMenu.addAction("设置为壁纸"); // 添加菜单项

    if(num == 1) // 首页 需要添加收藏功能
        mAction2 = mMenu.addAction("添加到收藏");
    else if(num == 2) // 收藏页 需要移除收藏功能
        mAction2 = mMenu.addAction("从收藏中移除");

}

//右击图片
void ImageInfoItem::contextMenuEvent(QContextMenuEvent *event) {

    QAction *selectedAction = mMenu.exec(event->globalPos()); // 在鼠标位置弹出菜单

    if (selectedAction == mAction1) {
        setWallPaper();
    } else if (selectedAction == mAction2) {
        // 处理 Action 2 的操作
        emit clickCollectMenu(this);
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
    if(event->buttons() == Qt::MouseEventCreatedDoubleClick){
        setWallPaper();
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
    QWidget::enterEvent(event);
}

void ImageInfoItem::leaveEvent(QEvent *event){
    unsetCursor();
    mImageInfo->setVisible(false);
    ui->image->setPixmap(mImagePixmap);
    ui->image->setStyleSheet("");
    QWidget::leaveEvent(event);
}






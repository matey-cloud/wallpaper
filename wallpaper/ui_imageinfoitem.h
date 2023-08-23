/********************************************************************************
** Form generated from reading UI file 'imageinfoitem.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEINFOITEM_H
#define UI_IMAGEINFOITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageInfoItem
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *image;

    void setupUi(QWidget *ImageInfoItem)
    {
        if (ImageInfoItem->objectName().isEmpty())
            ImageInfoItem->setObjectName("ImageInfoItem");
        ImageInfoItem->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(ImageInfoItem);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame = new QFrame(ImageInfoItem);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName("horizontalLayout");
        image = new QLabel(frame);
        image->setObjectName("image");

        horizontalLayout->addWidget(image);


        verticalLayout_2->addWidget(frame);


        retranslateUi(ImageInfoItem);

        QMetaObject::connectSlotsByName(ImageInfoItem);
    } // setupUi

    void retranslateUi(QWidget *ImageInfoItem)
    {
        ImageInfoItem->setWindowTitle(QCoreApplication::translate("ImageInfoItem", "Form", nullptr));
        image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ImageInfoItem: public Ui_ImageInfoItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEINFOITEM_H

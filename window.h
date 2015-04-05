#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QSpinBox>
#include <QScrollArea>
#include <QColorDialog>
#include <QPushButton>
#include <QString>
#include <QFileDialog>
#include <QDoubleSpinBox>

#include "Core.h"
#include "Scene.h"
#include "WoodTexture.h"
#include "MarbleTexture.h"
#include "CellTexture.h"
#include "CloudTexture.h"

namespace Ui {
class window;
}

class window : public QWidget
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = 0);
    ~window();

private slots:
    void textureChanged();
    void sizeChanged();
    void colorChanged();
    void savePressed();
    void distChanged();
    void combChanged();
    void resetPressed();

private:
    void renderImg();

    Ui::window *ui;

    QLabel * TextureLabel;
    QComboBox * TextureBox;

    QImage * render;
    QLabel * renderLabel;

    QLabel * sizeYLabel;
    QLabel * sizeXLabel;
    QSpinBox * sizeY;
    QSpinBox * sizeX;

    QColorDialog * colorSelector;

    QLabel * DistanceLabel;
    QComboBox * DistanceBox;
    QLabel * CombineLabel;
    QComboBox * CombineBox;

    QDoubleSpinBox * scale;
    QLabel * scaleLabel;

    QLabel * seedLabel;
    QSpinBox * seed;

    QPushButton * saveButton;
    QPushButton * resetButton;

    Texture * myTexture;
    Color baseColor;
    int myDist;
    int myComb;
};

#endif // WINDOW_H

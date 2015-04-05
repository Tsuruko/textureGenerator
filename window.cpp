#include "window.h"
#include "ui_window.h"

window::window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::window)
{
    ui->setupUi(this);

    //texture selection
    TextureBox = new QComboBox;
    TextureBox->addItem(tr("Cell (custom)"));
    TextureBox->addItem(tr("Cloud"));
    TextureBox->addItem(tr("Lava"));
    TextureBox->addItem(tr("Marble"));
    TextureBox->addItem(tr("Wood"));
    TextureLabel = new QLabel(tr("Texture:"));

    //size selection
    sizeX = new QSpinBox();
    sizeY = new QSpinBox();
    sizeX->setMinimum(0);
    sizeY->setMinimum(0);
    sizeX->setMaximum(10000);
    sizeY->setMaximum(10000);
    sizeX->setValue(500);
    sizeY->setValue(500);
    sizeXLabel = new QLabel(tr("X size:"));
    sizeYLabel = new QLabel(tr("Y size:"));

    //render image
    render = new QImage(500, 500, QImage::Format_RGB32);
    renderLabel = new QLabel();
    renderLabel->setPixmap(QPixmap::fromImage(*render));
    QScrollArea *renderScrollArea = new QScrollArea;
    renderScrollArea->setWidget(renderLabel);

    //color selection
    colorSelector = new QColorDialog();
    colorSelector->setOption(QColorDialog::DontUseNativeDialog, true);
    colorSelector->setOption(QColorDialog::NoButtons, true);
    colorSelector->setCustomColor(0, 0xc99968);
    colorSelector->setCustomColor(1, 0xCCE5FF);
    colorSelector->setCustomColor(2, 0xb2daed);
    colorSelector->setCustomColor(3, 0x8e1b1b);
    colorSelector->setCustomColor(4, 0x7906131);
    baseColor.FromInt(0xc99968);

    //save image
    saveButton = new QPushButton("save", this);

    //distance selection
    DistanceBox = new QComboBox;
    DistanceBox->addItem(tr("Euclidian"));
    DistanceBox->addItem(tr("Manhattan"));
    DistanceBox->addItem(tr("Chebyshev"));
    DistanceLabel = new QLabel(tr("Distance:"));
    myDist = WorleyNoise::EUCLIDIAN;

    //combination selection
    CombineBox = new QComboBox;
    CombineBox->addItem(tr("D1"));
    CombineBox->addItem(tr("D2"));
    CombineBox->addItem(tr("D3"));
    CombineLabel = new QLabel(tr("Combine:"));
    myComb = WorleyNoise::D1;

    //scale selection
    scale = new QDoubleSpinBox();
    scale->setMinimum(0);
    scale->setMaximum(10000);
    scale->setValue(10);
    scaleLabel = new QLabel(tr("Scale:"));

    //seed selection
    seed = new QSpinBox();
    seed->setMinimum(0);
    seed->setMaximum(10000);
    seed->setValue(1305);
    seedLabel = new QLabel(tr("Seed:"));

    //reset button
    resetButton = new QPushButton("reset", this);

    //add all widgets to layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(TextureLabel, 0, 0, Qt::AlignRight);
    mainLayout->addWidget(TextureBox, 0, 1, Qt::AlignLeft);

    mainLayout->addWidget(sizeXLabel, 0, 2, Qt::AlignRight);
    mainLayout->addWidget(sizeX, 0, 3, Qt::AlignLeft);

    mainLayout->addWidget(sizeYLabel, 0, 4, Qt::AlignRight);
    mainLayout->addWidget(sizeY, 0, 5, Qt::AlignLeft);

    mainLayout->addWidget(scaleLabel, 0, 6, Qt::AlignRight);
    mainLayout->addWidget(scale, 0, 7, Qt::AlignLeft);

    mainLayout->addWidget(DistanceLabel, 1, 3, Qt::AlignRight);
    mainLayout->addWidget(DistanceBox, 1, 4, Qt::AlignLeft);

    mainLayout->addWidget(CombineLabel, 1, 5, Qt::AlignRight);
    mainLayout->addWidget(CombineBox, 1, 6, Qt::AlignLeft);

    mainLayout->addWidget(seedLabel, 1, 7, Qt::AlignRight);
    mainLayout->addWidget(seed, 1, 8, Qt::AlignLeft);

    mainLayout->addWidget(resetButton, 2, 5, Qt::AlignLeft);
    mainLayout->addWidget(saveButton, 2, 6, Qt::AlignLeft);

    mainLayout->addWidget(renderScrollArea, 3, 0, 7, 7, Qt::AlignLeft);
    mainLayout->addWidget(colorSelector, 3, 8, 4, 4, Qt::AlignLeft);

    //connect widgets to actions
    connect(TextureBox, SIGNAL(activated(int)), this, SLOT(textureChanged()));
    connect(sizeX, SIGNAL(valueChanged(int)), this, SLOT(sizeChanged()));
    connect(sizeY, SIGNAL(valueChanged(int)), this, SLOT(sizeChanged()));
    connect(colorSelector, SIGNAL(currentColorChanged(QColor)), this, SLOT(colorChanged()));
    connect(DistanceBox, SIGNAL(activated(int)), this, SLOT(distChanged()));
    connect(CombineBox, SIGNAL(activated(int)), this, SLOT(combChanged()));
    connect(scale, SIGNAL(valueChanged(double)), this, SLOT(textureChanged()));
    connect(seed, SIGNAL(valueChanged(int)), this, SLOT(textureChanged()));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(savePressed()));
    connect(resetButton, SIGNAL(clicked(bool)), this, SLOT(resetPressed()));

    //initialize image
    myTexture = new CellTexture(scale->value(), seed->value(), myDist, myComb);
    renderImg();

    setLayout(mainLayout);
}

window::~window()
{
    delete ui;
}

void window::distChanged() {
    int idx = DistanceBox->currentIndex();
    if (idx == 0) {
        myDist = WorleyNoise::EUCLIDIAN;
    } else if (idx == 1) {
        myDist = WorleyNoise::MANHATTAN;
    } else if (idx == 2) {
        myDist = WorleyNoise::CHEBYSHEV;
    }
    renderImg();
}

void window::combChanged() {
    int idx = CombineBox->currentIndex();
    if (idx == 0) {
        myComb = WorleyNoise::D1;
    } else if (idx == 1) {
        myComb = WorleyNoise::D2;

    } else if (idx == 2) {
        myComb = WorleyNoise::D3;
    }
    renderImg();
}

void window::resetPressed() {
    int idx = TextureBox->currentIndex();

    if (idx == 0) {
        seed->setValue(1305);
        scale->setValue(10.0);
        DistanceBox->setCurrentIndex(0);
        myDist = WorleyNoise::EUCLIDIAN;
        CombineBox->setCurrentIndex(0);
        myComb = WorleyNoise::D1;
        baseColor.FromInt(0xc99968);
    } else if (idx == 1) {
        baseColor.FromInt(0xCCE5FF);
    } else if (idx == 2) {
        seed->setValue(5550);
        scale->setValue(10.0);
        DistanceBox->setCurrentIndex(1);
        myDist = WorleyNoise::MANHATTAN;
        CombineBox->setCurrentIndex(2);
        myComb = WorleyNoise::D3;
        baseColor.FromInt(0x8e1b1b);
    } else if (idx == 3) {
        scale->setValue(40.0);
        baseColor.FromInt(0xb2daed);
    } else if (idx == 4) {
        baseColor.FromInt(0x7906131);
    }

    colorSelector->setCurrentColor(QColor(baseColor.getRed(), baseColor.getGreen(), baseColor.getBlue()));
    textureChanged();
}

void window::savePressed() {
    QString imagePath = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                     tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));
    render->save(imagePath);
}

void window::sizeChanged() {
    render = new QImage(sizeX->value(), sizeY->value(), QImage::Format_RGB32);
    renderImg();
}

void window::colorChanged() {
    QColor c = colorSelector->currentColor();
    baseColor.Set(c.red()/255.0, c.green()/255.0, c.blue()/255.0);
    renderImg();
}

void window::textureChanged() {
    int idx = TextureBox->currentIndex();

    seed->hide();
    DistanceBox->hide();
    CombineBox->hide();
    scale->show();
    if (idx == 0) {
        seed->show();
        DistanceBox->show();
        CombineBox->show();
        myTexture = new CellTexture(scale->value(), seed->value(), myDist, myComb);
    } else if (idx == 1) {
        myTexture = new CloudTexture();
    } else if (idx == 2) {
        myTexture = new CellTexture(scale->value(), 5550, WorleyNoise::MANHATTAN, WorleyNoise::D3);
    } else if (idx == 3) {
        myTexture = new MarbleTexture(scale->value());
    } else if (idx == 4) {
        scale->hide();
        myTexture = new WoodTexture();
    }

    renderImg();
}

void window::renderImg() {
    int xRes = render->width();
    int yRes = render->height();

    for(int y = 0; y < yRes; y++) {
        for(int x = 0; x < xRes; x++) {
            Color pixCol = baseColor;

            float n = myTexture->getTexture(Vector3(1.0f*x/xRes, 1.0f*y/yRes, 1.0f));
            Color d = baseColor.Difference(Color::WHITE);
            d.Scale(n);
            pixCol.Add(d);

            render->setPixel(x, y, pixCol.ToInt());
        }
    }
    renderLabel->setPixmap(QPixmap::fromImage(*render));
}

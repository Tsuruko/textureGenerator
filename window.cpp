#include "window.h"
#include "ui_window.h"

window::window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::window)
{
    ui->setupUi(this);

    TextureBox = new QComboBox;
    TextureBox->addItem(tr("Cell"));
    TextureBox->addItem(tr("Cloud"));
    TextureBox->addItem(tr("Marble"));
    TextureBox->addItem(tr("Wood"));
    TextureLabel = new QLabel(tr("Texture"));

    sizeX = new QSpinBox();
    sizeY = new QSpinBox();
    sizeX->setMinimum(0);
    sizeY->setMinimum(0);
    sizeX->setMaximum(10000);
    sizeY->setMaximum(10000);
    sizeX->setValue(500);
    sizeY->setValue(500);
    sizeXLabel = new QLabel(tr("X size"));
    sizeYLabel = new QLabel(tr("Y size"));

    render = new QImage(500, 500, QImage::Format_RGB32);
    renderLabel = new QLabel();
    renderLabel->setPixmap(QPixmap::fromImage(*render));

    QScrollArea *renderScrollArea = new QScrollArea;
    renderScrollArea->setWidget(renderLabel);

    colorSelector = new QColorDialog();
    colorSelector->setOption(QColorDialog::DontUseNativeDialog, true);
    colorSelector->setOption(QColorDialog::NoButtons, true);
    colorSelector->setCustomColor(0, 0xc99968);
    colorSelector->setCustomColor(1, 0xCCE5FF);
    colorSelector->setCustomColor(2, 0xb2daed);
    colorSelector->setCustomColor(3, 0x8e1b1b);
    colorSelector->setCustomColor(4, 0x7906131);
    baseColor.FromInt(0xc99968);

    saveButton = new QPushButton("save", this);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(TextureLabel, 0, 0, Qt::AlignRight);
    mainLayout->addWidget(TextureBox, 0, 1, Qt::AlignLeft);

    mainLayout->addWidget(sizeXLabel, 0, 2, Qt::AlignRight);
    mainLayout->addWidget(sizeX, 0, 3, Qt::AlignLeft);

    mainLayout->addWidget(sizeYLabel, 0, 4, Qt::AlignRight);
    mainLayout->addWidget(sizeY, 0, 5, Qt::AlignLeft);

    mainLayout->addWidget(saveButton, 0, 6, Qt::AlignLeft);

    mainLayout->addWidget(colorSelector, 1, 11);

    mainLayout->addWidget(renderScrollArea, 1, 0, 10, 10, Qt::AlignLeft);

    connect(TextureBox, SIGNAL(activated(int)), this, SLOT(textureChanged()));
    connect(sizeX, SIGNAL(valueChanged(int)), this, SLOT(sizeChanged()));
    connect(sizeY, SIGNAL(valueChanged(int)), this, SLOT(sizeChanged()));
    connect(colorSelector, SIGNAL(currentColorChanged(QColor)), this, SLOT(colorChanged()));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(savePressed()));

    //initialize image
    textureChanged();

    setLayout(mainLayout);
}

window::~window()
{
    delete ui;
}

void window::savePressed() {
    QString imagePath = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                     tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));
    render->save(imagePath);
}

void window::sizeChanged() {
    render = new QImage(sizeX->value(), sizeY->value(), QImage::Format_RGB32);
    textureChanged();
}

void window::colorChanged() {
    QColor c = colorSelector->currentColor();
    baseColor.Set(c.red()/255.0, c.green()/255.0, c.blue()/255.0);
    textureChanged();
}

void window::textureChanged() {
    int idx = TextureBox->currentIndex();

    if (idx == 0) {
        myTexture = new CellTexture(1.0f, 1305, WorleyNoise::EUCLIDIAN, WorleyNoise::D1);
    } else if (idx == 1) {
        myTexture = new CloudTexture();
    } else if (idx == 2) {
        myTexture = new MarbleTexture(40.0f);
    } else if (idx == 3) {
        myTexture = new CellTexture(10.0f, 5550, WorleyNoise::MANHATTAN, WorleyNoise::D3);
    } else if (idx == 4) {
        myTexture = new WoodTexture();
    }

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

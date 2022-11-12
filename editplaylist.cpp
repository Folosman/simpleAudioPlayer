#include "editplaylist.h"
#include "ui_editplaylist.h"

#include <QPushButton>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <QFileDialog>

EditPlaylist::EditPlaylist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPlaylist)
{
    ui->setupUi(this);

    m_musicListModel = new QStandardItemModel(this);
    ui->musicList->setModel(m_musicListModel);

    connect(ui->addBtn, &QPushButton::clicked, this, &EditPlaylist::addBtn);
}

EditPlaylist::~EditPlaylist()
{
    QListView m_musicList;
    delete ui;
}

void EditPlaylist::addBtn()
{
    QFile file("../SimpleAudioPlayer/Music/playlist/conf.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QStringList files = QFileDialog::getOpenFileNames(this, tr("Selected"), QString(), tr("Audio files (*.mp3)"));

        foreach (QString filePath, files)
        {

            QList <QStandardItem *> items;
            items.append(new QStandardItem(QDir(filePath).dirName()));
            m_musicListModel->appendRow(items);
            QTextStream out(&file);
            out << filePath + "\n";
        }

        file.close();
    }
}

void EditPlaylist::removeBtn()
{

}

void EditPlaylist::renameBtn()
{

}

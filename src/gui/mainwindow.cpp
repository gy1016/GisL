#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"
//#include "../ui/ui_backup.h"

#include <src/gui/command/command.h>
#include <src/gui/command/commandhistory.h>
#include <src/gui/command/openvectorcommand.h>
#include <src/gui/command/opensldcommand.h>
#include <QFileDialog>
#include <QMessageBox>
#include "../utils/ptroperate.h"

MainWindow::MainWindow( QWidget *parent )
        : QMainWindow( parent ), ui( new Ui::MainWindow ) {
    pCommandHistory = GisL::CommandHistory::getCommandHistory();
    ui->setupUi( this );
    setWindowTitle( tr( "GisL" ));

    initAction();

    setStatusMessage( tr( "yes" ));
    manualConnect();
}

void MainWindow::initAction( ) {
    ui->actionCodecvtDecodeDecode->setEnabled( false );
    ui->actionCodecvtEncodeEncode->setEnabled( false );
    ui->actionCodecvtDecodeSave->setEnabled( false );
    ui->actionCodecvtEncodeSave->setEnabled( false );

    ui->actionVectorSave->setEnabled( false );
    ui->actionVectorSldSave->setEnabled( false );

    ui->actionRasterSave->setEnabled( false );
}

void MainWindow::manualConnect( ) {
    QObject::connect( ui->actionVectorOpen, &QAction::triggered, this, &MainWindow::on_actionVectorOpen_triggered );
    QObject::connect( ui->actionVectorSldOpen, &QAction::triggered, this,
                      &MainWindow::on_actionVectorSldOpen_triggered );
    QObject::connect( ui->actionCodecvtDecodeOpen, &QAction::triggered, this,
                      &MainWindow::on_actionCodecvtDecodeOpen_triggered );
    QObject::connect( ui->actionCodecvtDecodeDecode, &QAction::triggered, this,
                      &MainWindow::on_actionCodecvtDecodeDecode_triggered );
    QObject::connect( ui->actionCodecvtDecodeSave, &QAction::triggered, this,
                      &MainWindow::on_actionCodecvtDecodeSave_triggered );
    QObject::connect( ui->actionCodecvtEncodeOpen, &QAction::triggered, this,
                      &MainWindow::on_actionCodecvtEncodeOpen_triggered );
    QObject::connect( ui->actionCodecvtEncodeEncode, &QAction::triggered, this,
                      &MainWindow::on_actionCodecvtEncodeEncode_triggered );
    QObject::connect( ui->actionCodecvtEncodeSave, &QAction::triggered, this,
                      &MainWindow::on_actionCodecvtEncodeSave_triggered );
    QObject::connect( ui->actionUndo, &QAction::triggered, this, &MainWindow::on_actionUndo_triggered );
    QObject::connect( ui->actionRedo, &QAction::triggered, this, &MainWindow::on_actionRedo_triggered );

}

void MainWindow::on_actionUndo_triggered( ) {
    pCommandHistory->rollBack( 1 );
}

void MainWindow::on_actionRedo_triggered( ) {

}

void MainWindow::on_actionVectorOpen_triggered( ) {
    GisL::Command *p = new GisL::OpenVectorCommand;
    p->execute( this );
    pCommandHistory->push( p, tr( "Open " ).toStdString() + p->output());
    ui->actionVectorSave->setEnabled( true );
    ui->actionVectorSldSave->setEnabled( true );
}

void MainWindow::on_actionVectorSldOpen_triggered( ) {
    GisL::Command *p = new GisL::OpenSldCommand;
    p->execute( this );
    pCommandHistory->push( p, tr( "Open " ).toStdString() + p->output());
    ui->actionVectorSldSave->setEnabled( true );
}

void MainWindow::on_actionCodecvtDecodeOpen_triggered( ) {
    QString openFileName = QFileDialog::getOpenFileName(
            nullptr,
            tr( "open an decode file." ),
            "../",
            tr( "Decode File(*.da);;All files(*.*)" ));
    if ( openFileName.isEmpty()) {
        QMessageBox::warning( nullptr, tr( "Warning!" ), tr( "Cancel to open the file!" ));
    } else {
        GisL::PtrOperate::clear( pDecoder );
        pDecoder = new GisL::DaDecoder( openFileName.toStdString());
        ui->actionCodecvtDecodeDecode->setEnabled( true );
        ui->actionCodecvtDecodeSave->setEnabled( true );
    }
}

void MainWindow::on_actionCodecvtDecodeDecode_triggered( ) {
    pDecoder->decode();
    QString qDecodeText = QString::fromStdString( pDecoder->getTextInOrder());
    QMessageBox::information( this, "text", qDecodeText );
}

void MainWindow::on_actionCodecvtDecodeSave_triggered( ) {
    QString outFilename = QFileDialog::getSaveFileName(
            this,
            tr( "Save File as txt" ),
            "../",
            tr( "Text(*.txt);;all(*.*)" ));
    if ( outFilename.isEmpty()) {
        QMessageBox::warning( this, tr( "Warning!" ), tr( "Cancel to open the file!" ));
    } else {
        pDecoder->writeTextFile( outFilename.toStdString());
    }
}

void MainWindow::on_actionCodecvtEncodeOpen_triggered( ) {
    QString openFileName = QFileDialog::getOpenFileName(
            this,
            tr( "open an decode file." ),
            "../",
            tr( "Decode File(*.da);;All files(*.*)" ));
    if ( openFileName.isEmpty()) {
        QMessageBox::warning( this, tr( "Warning!" ), tr( "Cancel to open the file!" ));
    } else {
        GisL::PtrOperate::clear( pDecoder );
        pDecoder = new GisL::DaDecoder( openFileName.toStdString());
        ui->actionCodecvtDecodeDecode->setEnabled( true );
        ui->actionCodecvtDecodeSave->setEnabled( true );
    }
}

void MainWindow::on_actionCodecvtEncodeEncode_triggered( ) {
    QString qText = QString::fromStdString( pEncoder->getTextInOrder());
    QMessageBox::information( this, "text", qText );
    pEncoder->encode();
}

void MainWindow::on_actionCodecvtEncodeSave_triggered( ) {
    QString outFilename = QFileDialog::getSaveFileName(
            this,
            tr( "Save File as decode" ),
            "../",
            tr( "decode(*.da);;all(*.*)" ));
    if ( outFilename.isEmpty()) {
        QMessageBox::warning( this, tr( "Warning!" ), tr( "Cancel to open the file!" ));
    } else {
        pEncoder->writeBinaryFile( outFilename.toStdString());
    }
}

void MainWindow::setStatusMessage( const QString &s, int timeout ) {
    ui->statusBar->showMessage( s, timeout );
}

MainWindow::~MainWindow( ) = default;


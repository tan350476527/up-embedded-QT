#include "myprocess.h"

myProcess::myProcess(QWidget *parent) : QProcess(parent)
{
    Init();
}


//---function
//private
void myProcess::Init(){
    playList.clear();
}
int myProcess::playVideo(const QString filename, quint64 winid){
    int ret=0;
    this->close();
    QString mplayerPath = "/usr/bin/mplayer";
    QStringList argList;
    //播放的文件
    argList << filename;
    //指定到窗口上播放
    argList << "-wid";
    argList << QString::number(winid);
    //软件缩放
    argList << "-zoom";
    this->start(mplayerPath, argList);
    return ret;
}


//public
void myProcess::OpenFile(quint64 winid){
    QFileDialog *dialog = new QFileDialog(0, "打开视频文件",
                         "/home/uplooking/视频","video(*.mp4 *.wav)");
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    dialog->setFileMode(QFileDialog::ExistingFiles);
    int ret = dialog->exec();
    if(ret !=QDialog::Accepted){
        delete dialog;
        return;
    }
    playList.clear();
    QStringList filenames = dialog->selectedFiles();
    playList = filenames;
    delete dialog;

    //调用播放函数
    playVideo(playList.at(0),winid);
}
//end

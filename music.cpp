#include "music.h"
#include "ui_music.h"

music::music(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::music)
{
    ui->setupUi(this);
    init();
    setstylesheet();




}

music::~music()
{
    delete ui;
}

void music::init(){//初始化
    //按钮初始化
    playbtn = new QPushButton(this);
    pausebtn = new QPushButton(this);
    nextsongbtn = new QPushButton(this);
    presongbtn = new QPushButton(this);
    fileselectbtn = new QPushButton(this);
    playmodebtn = new QPushButton(this);
    //设置按钮图标
    playbtn->setIcon(QIcon(":/image/music/play.png"));
    pausebtn->setIcon(QIcon(":/image/music/pause.png"));
    nextsongbtn->setIcon(QIcon(":/image/music/nextsong.png"));
    presongbtn->setIcon(QIcon(":/image/music/presong.png"));
    fileselectbtn->setIcon(QIcon(":/image/music/file.png"));
    playmodebtn->setIcon(QIcon(":/image/music/seqplay.png"));
    //设置按钮位置
    playbtn->setGeometry(565,700,70,70);
    playbtn->setIconSize(QSize(60,60));
    pausebtn->setGeometry(565,700,70,70);
    pausebtn->setIconSize(QSize(60,60));
    nextsongbtn->setGeometry(640,700,70,70);
    nextsongbtn->setIconSize(QSize(60,60));
    presongbtn->setGeometry(490,700,70,70);
    presongbtn->setIconSize(QSize(60,60));
    playmodebtn->setGeometry(40,700,70,70);
    playmodebtn->setIconSize(QSize(60,60));
    fileselectbtn->setGeometry(1100,700,70,70);
    fileselectbtn->setIconSize(QSize(60,60));
    //设置播放器和模式
    playlist = new QMediaPlaylist;
    player = new QMediaPlayer;
    playlist->setPlaybackMode(QMediaPlaylist::Sequential);//默认设置顺序播放
    playmode = 1;//1代表顺序播放
    player->setPlaylist(playlist);
    playbtn->hide();
    pausebtn->show();
    //信号与槽
    connect(fileselectbtn,&QPushButton::clicked,this,&music::set_musicfilepath);//设置文件夹路径
    connect(ui->musiclistwidget,&QListWidget::itemDoubleClicked,this,&music::playmusiclistitem);//双击播放
    connect(pausebtn,&QPushButton::clicked,this,&music::playmusic);//播放
    connect(playbtn,&QPushButton::clicked,this,&music::pausemusic);//暂停
    connect(nextsongbtn,&QPushButton::clicked,this,&music::nextsong);//下一首
    connect(presongbtn,&QPushButton::clicked,this,&music::presong);//上一首
    connect(playmodebtn,&QPushButton::clicked,this,&music::setplaymode);//设置播放模式
    connect(playlist,&QMediaPlaylist::currentMediaChanged,this,&music::show_current_musicname);//显示当前音乐名称


}

void music::set_musicfilepath(){
    QString folderpath = QFileDialog::getExistingDirectory(this,"请选择音乐文件的路径:");
    if(!folderpath.isEmpty()){
        musicpath = folderpath;
    }
    else{
        QMessageBox::warning(this,"警告","添加失败！");
    }
    get_musicfile();
}

void music::get_musicfile(){
    QDir dir(musicpath);
    QStringList filter;
    filter<<"*.mp3";//筛选后缀名
    musicfilelist = dir.entryInfoList(filter,QDir::Files);

    foreach (QFileInfo file, musicfilelist) {
        playlist->addMedia(QUrl::fromLocalFile(file.absoluteFilePath()));//添加进播放列表
        QString name = file.fileName();
        filelist<<name;//添加进音乐名称列表
    }

    ui->musiclistwidget->clear();//清除音乐显示列表
    foreach(QFileInfo file,musicfilelist){
        ui->musiclistwidget->addItem(file.fileName());//添加音乐显示列表
    }
}

void music::playmusiclistitem(QListWidgetItem *item){
    playbtn->show();
    pausebtn->hide();
    int index = ui->musiclistwidget->row(item);
    playlist->setCurrentIndex(index);//设置当前双击音乐
    player->play();
}

void music::playmusic(){
    if(ui->musiclistwidget->count()!=0){
        playbtn->show();
        pausebtn->hide();
        player->setPlaylist(playlist);
        player->play();
    }
    else{
        QMessageBox::warning(this,"警告","音乐列表为空！");
    }
}

void music::pausemusic(){
    player->stop();
    playbtn->hide();
    pausebtn->show();
}

void music::nextsong(){
    playlist->next();
    if(playbtn->isHidden()){
        playbtn->show();
        pausebtn->hide();
    }
    player->play();
}

void music::presong(){
    playlist->previous();
    if(playbtn->isHidden()){
        playbtn->show();
        pausebtn->hide();
    }
    player->play();
}

void music::setplaymode(){
    if(playmode==1){
        playmode=2;
        playmodebtn->setIcon(QIcon(":/image/music/randplay.png"));
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        qDebug()<<"设置随机播放成功";
    }
    else if(playmode==2){
        playmode=1;
        playmodebtn->setIcon(QIcon(":/image/music/seqplay.png"));
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
        qDebug()<<"设置顺序播放成功";
    }
}

void music::show_current_musicname(){
    ui->currentmusic_name->setPlainText("当前播放：");
    ui->currentmusic_name->appendPlainText((filelist.at(playlist->currentIndex()).section(QRegExp("[/.]"),-2,-2)));
}

void music::setstylesheet(){
    setStyleSheet("background-color: white;");
    //使用css样式表设置外观样式！！！

}


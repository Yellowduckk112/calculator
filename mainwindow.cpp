#include<QMainWindow>
#include<QShortcut>
#include<stack>
#include<math.h>
#include<map>
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include "mybutton.h"
#include "painter.h"

const double pi=3.1415926536,e=2.718281846;
std::map<char,int>cast;
QString MainWindow::lable2;

void painter::mousePressEvent(QMouseEvent *event){
    Clicked=1;
    Start=event->pos();
    Last=Start;
    setCursor(Qt::ClosedHandCursor);
}

void painter::mouseMoveEvent(QMouseEvent *event){
    if(Clicked){
        QPoint a=event->pos(),Delta=a-Last;
        Last=a;
        move_x+=Delta.x();
        move_y+=Delta.y();
        update();
    }
}

void painter::mouseReleaseEvent(QMouseEvent *event){
    Clicked=0;
    update();
    setCursor(Qt::ArrowCursor);
}

void painter::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Left:
        move_x+=40;
        break;
    case Qt::Key_Right:
        move_x-=40;
        break;
    case Qt::Key_Up:
        move_y+=40;
        break;
    case Qt::Key_Down:
        move_y-=40;
        break;
    }
    this->update();
}

double max(double a,double b){
    return a>b?a:b;
}

double min(double a,double b){
    return a<b?a:b;
}

void painter::paintEvent(QPaintEvent *event)
{
    QPainter Painter(this);
    if(der){
        Painter.setRenderHint(QPainter::Antialiasing,1);
        Painter.fillRect(rect(),Qt::white);

        const int width=800,height=600,margin=50;
        const int plotwidth=700,plotheight=500;

        Painter.setPen(QPen(Qt::black,2));
        Painter.drawLine(0,height/2+move_y,width,height/2+move_y);
        Painter.drawLine(width/2+move_x,0,width/2+move_x,height);

        Painter.drawText(width-20,height/2-10+move_y,"X");
        Painter.drawText(width/2+10+move_x,15,"Y");

        Painter.setPen(QPen(Qt::gray,1));
        for(int i=1;i<40;i++)Painter.drawLine(i*20,0,i*20,height);
        for(int i=1;i<30;i++)Painter.drawLine(0,i*20,width,i*20);

        Painter.setFont(QFont("Arial",6));
        Painter.setPen(QPen(Qt::black));
        for(int i=1;i<40;i++)if(i-move_x/20!=20)(i%2)?Painter.drawText(i*20-5,min(max(height/2-5+move_y,-10),590),QString::number((i-20-move_x/20)*muti,'f',2)):Painter.drawText(i*20-5,min(max(height/2+10+move_y,10),610),QString::number((i-20-move_x/20)*muti,'f',2));
        for(int i=1;i<30;i++)if(i-move_y/20!=15)Painter.drawText(min(max(width/2+5+move_x,4),770),i*20,QString::number((15-i+move_y/20)*muti,'f',2));
        Painter.drawText(width/2-10+move_x,height/2+12+move_y,"0");

        Painter.setPen(QPen(Qt::blue,2));
        QVector <QPointF> points;
        const double xMin = 0.02;
        for(double screen_x=-(width/2);screen_x<=(width/2);screen_x+=xMin){
            double x=muti*(screen_x-move_x) / 20;
            long long u=x*100000;
            x=u/100000.0;
            if(x>-0.01&&x<0.01)continue;
            double y1=this->calculate(x-0.001*muti),y2=this->calculate(x+0.001*muti),y=(y2-y1)/(0.002*muti);
            //  qDebug() << x<<" "<<y<<"\n";
            double screen_y = y * 20/muti-move_y;
            points.append(QPointF(screen_x+width/2,-screen_y+height/2));
        }
        int size=points.size();
        for(int i=0;i<size-1;i++)
            Painter.drawLine(points[i],points[i+1]);
        return;
    }
    Painter.setRenderHint(QPainter::Antialiasing,1);
    Painter.fillRect(rect(),Qt::white);

    const int width=800,height=600,margin=50;
    const int plotwidth=700,plotheight=500;

    Painter.setPen(QPen(Qt::black,2));
    Painter.drawLine(0,height/2+move_y,width,height/2+move_y);
    Painter.drawLine(width/2+move_x,0,width/2+move_x,height);

    Painter.drawText(width-20,height/2+20+move_y,"X");
    Painter.drawText(width/2-20+move_x,15,"Y");

    Painter.setPen(QPen(Qt::gray,1));
    for(int i=1;i<40;i++)Painter.drawLine(i*20,0,i*20,height);
    for(int i=1;i<30;i++)Painter.drawLine(0,i*20,width,i*20);

    Painter.setFont(QFont("Arial",6));
    Painter.setPen(QPen(Qt::black));
    for(int i=1;i<40;i++)if(i-move_x/20!=20)(i%2)?Painter.drawText(i*20-5,min(max(height/2-5+move_y,-10),590),QString::number((i-20-move_x/20)*muti,'f',2)):Painter.drawText(i*20-5,min(max(height/2+10+move_y,10),610),QString::number((i-20-move_x/20)*muti,'f',2));
    for(int i=1;i<30;i++)if(i-move_y/20!=15)Painter.drawText(min(max(width/2+5+move_x,4),770),i*20,QString::number((15-i+move_y/20)*muti,'f',2));
    Painter.drawText(width/2-10+move_x,height/2+12+move_y,"0");

    Painter.setPen(QPen(Qt::blue,2));
    QVector <QPointF> points;
    const double xMin = 0.02;
    for(double screen_x=-(width/2);screen_x<=(width/2);screen_x+=xMin){
        double x=muti*(screen_x-move_x)/20;
        long long ui=x*100000;
        x=ui/100000.0;
        double y=this->calculate(x);
        double screen_y=y*20/muti-move_y;
        points.append(QPointF(screen_x+width/2,-screen_y+height/2));
    }
    int size=points.size();
    for(int i=0;i<size-1;i++)
        if(abs(points[i].y()-points[i+1].y())<10000)
        Painter.drawLine(points[i],points[i+1]);
}

void painter::derivative(){
    delete L;
    L=nullptr;
    der=1;
    this->update();
}

void painter::wheelEvent(QWheelEvent *event){
    double y=event->angleDelta().y();
    if(y>0)muti/=1.2;
    else muti*=1.2;
    update();
}

MainWindow *windo;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),which(0)
    , ui(new Ui::MainWindow),ans(0)
{
    windo = this;
    calculate_end=0;
    cast['+']=cast['-']=0;
    cast['*']=cast['/']=cast['m']=1;
    cast['^']=2;
    cast['a']=cast['b']=cast['c']=cast['d']=cast['s']=cast['t']=cast['l']=3;
    cast['(']=-10000;
    ui->setupUi(this);
    this->setMaximumSize(344,399);
    this->setMinimumSize(344,399);
    this->setWindowTitle("计算器");
    QFont f("仿宋",13);
    ui->LE->setFont(f);
    this->lable="";
    QShortcut *shortcut = new QShortcut(QKeySequence("="),this);
    connect(shortcut,&QShortcut::activated,this,[this](){
        MainWindow::on_Bu12_clicked();
    });

    QShortcut *shortcut_1 = new QShortcut(QKeySequence(Qt::Key_Return),this);
    connect(shortcut_1,&QShortcut::activated,this,[this](){
        MainWindow::on_Bu12_clicked();
    });

    QShortcut *shortcut_BS = new QShortcut(QKeySequence(Qt::Key_Backspace),this);
    connect(shortcut_BS,&QShortcut::activated,this,&MainWindow::on_pushButton_clicked);

    QShortcut *shortcut_11 = new QShortcut(QKeySequence("1"),this);
    connect(shortcut_11,&QShortcut::activated,this,&MainWindow::on_Bu1_clicked);

    QShortcut *shortcut_2 = new QShortcut(QKeySequence("2"),this);
    connect(shortcut_2,&QShortcut::activated,this,&MainWindow::on_Bu2_clicked);

    QShortcut *shortcut_3 = new QShortcut(QKeySequence("3"),this);
    connect(shortcut_3,&QShortcut::activated,this,&MainWindow::on_Bu3_clicked);

    QShortcut *shortcut_4 = new QShortcut(QKeySequence("4"),this);
    connect(shortcut_4,&QShortcut::activated,this,&MainWindow::on_Bu4_clicked);

    QShortcut *shortcut_5 = new QShortcut(QKeySequence("5"),this);
    connect(shortcut_5,&QShortcut::activated,this,&MainWindow::on_Bu5_clicked);

    QShortcut *shortcut_6 = new QShortcut(QKeySequence("6"),this);
    connect(shortcut_6,&QShortcut::activated,this,&MainWindow::on_Bu6_clicked);

    QShortcut *shortcut_7 = new QShortcut(QKeySequence("7"),this);
    connect(shortcut_7,&QShortcut::activated,this,&MainWindow::on_Bu7_clicked);

    QShortcut *shortcut_8 = new QShortcut(QKeySequence("8"),this);
    connect(shortcut_8,&QShortcut::activated,this,&MainWindow::on_Bu8_clicked);

    QShortcut *shortcut_9 = new QShortcut(QKeySequence("9"),this);
    connect(shortcut_9,&QShortcut::activated,this,&MainWindow::on_Bu9_clicked);

    QShortcut *shortcut_0 = new QShortcut(QKeySequence("0"),this);
    connect(shortcut_0,&QShortcut::activated,this,&MainWindow::on_Bu0_clicked);

    QShortcut *shortcut_add = new QShortcut(QKeySequence("+"),this);
    connect(shortcut_add,&QShortcut::activated,this,&MainWindow::on_Bu13_clicked);

    QShortcut *shortcut_mius = new QShortcut(QKeySequence("-"),this);
    connect(shortcut_mius,&QShortcut::activated,this,&MainWindow::on_Bu15_clicked);

    QShortcut *shortcut_muti = new QShortcut(QKeySequence("*"),this);
    connect(shortcut_muti,&QShortcut::activated,this,&MainWindow::on_Bu14_clicked);

    QShortcut *shortcut_divide = new QShortcut(QKeySequence("/"),this);
    connect(shortcut_divide,&QShortcut::activated,this,&MainWindow::on_Bu16_clicked);

    QShortcut *shortcut_p = new QShortcut(QKeySequence("."),this);
    connect(shortcut_p,&QShortcut::activated,this,&MainWindow::on_Bu10_clicked);

    QShortcut *shortcut_left = new QShortcut(QKeySequence("("),this);
    connect(shortcut_left,&QShortcut::activated,this,&MainWindow::on_left_button_clicked);

    QShortcut *shortcut_right = new QShortcut(QKeySequence(")"),this);
    connect(shortcut_right,&QShortcut::activated,this,&MainWindow::on_right_button_clicked);

    QShortcut *shortcut_clear = new QShortcut(QKeySequence(Qt::Key_Escape),this);
    connect(shortcut_clear,&QShortcut::activated,this,&MainWindow::on_Esc_clicked);

    QShortcut *shortcut_pow = new QShortcut(QKeySequence("^"),this);
    connect(shortcut_pow,&QShortcut::activated,this,&MainWindow::on_pushButton_2_clicked);

    QShortcut *shortcut_e = new QShortcut(QKeySequence("e"),this);
    connect(shortcut_e,&QShortcut::activated,this,&MainWindow::on_e_button_clicked);

    QShortcut *shortcut_Pi = new QShortcut(QKeySequence("p"),this);
    connect(shortcut_Pi,&QShortcut::activated,this,&MainWindow::on_pi_button_clicked);

    QShortcut *shortcut_sin = new QShortcut(QKeySequence("s"),this);
    connect(shortcut_sin,&QShortcut::activated,this,&MainWindow::on_sin_button_clicked);

    QShortcut *shortcut_cos = new QShortcut(QKeySequence("c"),this);
    connect(shortcut_cos,&QShortcut::activated,this,&MainWindow::on_cos_button_clicked);

    QShortcut *shortcut_tan = new QShortcut(QKeySequence("t"),this);
    connect(shortcut_tan,&QShortcut::activated,this,&MainWindow::on_tan_button_clicked);

    QShortcut *shortcut_ln = new QShortcut(QKeySequence("l"),this);
    connect(shortcut_ln,&QShortcut::activated,this,&MainWindow::on_ln_button_clicked);

    QShortcut *shortcut_x = new QShortcut(QKeySequence("x"),this);
    connect(shortcut_x,&QShortcut::activated,this,&MainWindow::on_x_button_clicked);

    QShortcut *shortcut_s1 = new QShortcut(QKeySequence("ctrl+1"),this);
    connect(shortcut_s1,&QShortcut::activated,this,&MainWindow::on_Save_1_clicked);

    QShortcut *shortcut_s2 = new QShortcut(QKeySequence("ctrl+2"),this);
    connect(shortcut_s2,&QShortcut::activated,this,&MainWindow::on_Save_2_clicked);

    QShortcut *shortcut_s3 = new QShortcut(QKeySequence("ctrl+3"),this);
    connect(shortcut_s3,&QShortcut::activated,this,&MainWindow::on_Save_3_clicked);

    QShortcut *shortcut_s4 = new QShortcut(QKeySequence("ctrl+4"),this);
    connect(shortcut_s4,&QShortcut::activated,this,&MainWindow::on_Save_4_clicked);

    QShortcut *shortcut_mod = new QShortcut(QKeySequence("m"),this);
    connect(shortcut_mod,&QShortcut::activated,this,&MainWindow::on_mod_Button_clicked);
}
MainWindow::~MainWindow()
{
        delete ui;
}

void MyButton::Set_Clicked(bool a){
    Clicked=a;
}

bool MyButton::Get_Clicked(){
    return Clicked;
}

double P(int op)
{
    double u=1;
    while(op--)
        u/=10;
    return u;
}

void Move(std::stack<double> &a,std::stack<char> &b,char C){
    double x,y;
    bool check=0;
    int m=cast[C];
    while(!b.empty()&&cast[b.top()]>=m&&m!=2){
        x=a.top();
        a.pop();
        char T=b.top();
        if(T!='s'&&T!='c'&&T!='t'&&T!='a'&&T!='b'&&T!='d'&&T!='l'){
            y=a.top();
            a.pop();
        }
        switch(T){
        case '+':a.push(x+y);break;
        case '-':a.push(y-x);break;
        case '*':a.push(x*y);break;
        case '/':a.push(y/x);break;
        case '^':a.push(pow(y,x));break;
        case 's':a.push(sin(x));break;
        case 'c':a.push(cos(x));break;
        case 't':a.push(tan(x));break;
        case 'a':a.push(asin(x));break;
        case 'b':a.push(acos(x));break;
        case 'd':a.push(atan(x));break;
        case 'l':a.push(log(x));break;
        case 'm':
            if(x-(long long)(x)<1e-5&&y-(long long)(y)<1e-5&&x>0)
                a.push(((long long)(y)%((long long)(x))+((long long)(x)))%((long long)(x)));
            else
                check=1;
            break;
        }
        b.pop();
        if(check){
            b.push('E');
            return;
        }
    }
    b.push(C);
}

void Move_2(std::stack<double>&a,std::stack<char>&b){
    double x,y;
    bool check=0;
    while(b.top()!='('){
        x=a.top();
        a.pop();
        char T=b.top();
        if(T!='s'&&T!='c'&&T!='t'&&T!='a'&&T!='b'&&T!='d'&&T!='l'){
            y=a.top();
            a.pop();
        }
        switch(T){
        case '+':a.push(x+y);break;
        case '-':a.push(y-x);break;
        case '*':a.push(x*y);break;
        case '/':a.push(y/x);break;
        case '^':a.push(pow(y,x));break;
        case 's':a.push(sin(x));break;
        case 'c':a.push(cos(x));break;
        case 't':a.push(tan(x));break;
        case 'a':a.push(asin(x));break;
        case 'b':a.push(acos(x));break;
        case 'd':a.push(atan(x));break;
        case 'l':a.push(log(x));break;
        case 'm':
            if(x-(long long)(x)<1e-5&&y-(long long)(y)<1e-5&&x>0){
                a.push(((long long)(y)%((long long)(x))+((long long)(x)))%((long long)(x)));
            }
            else
                check=1;
            break;
        }
        if(check){
            b.push('E');
            return;
        }
        b.pop();
    }
    b.pop();
}

double MainWindow::calculate(bool op) {
    QString lable_1=lable;
    if(op)lable_1=lable2;
    std::stack<double>S_Number;
    std::stack<char>S_Char;
    lable_1='('+lable_1+')';
    int Len=lable_1.size(),f=1,Point=0;
    double Now=0;
    bool R=0,Sign=true;
    for(int i=0;i<Len;i++){
        if(lable_1[i].toLatin1()>='0'&&lable_1[i].toLatin1()<='9'){
            R=false;
            Sign=false;
            if(Point)
                Now+=P(Point++)*(lable_1[i].digitValue());
            else
                Now=Now*10+lable_1[i].digitValue();
        }
        else if(lable_1[i]=='.')Point=1;
        else{
            Point=0;
            switch(lable_1[i].toLatin1()){
            case '-':
                if(Sign){
                    f=-1;
                    break;
                }
                else{
                    if(!R)S_Number.push(Now*f),f=1;
                    Move(S_Number,S_Char,lable_1[i].toLatin1());
                    Sign=true;
                    break;
                }
                break;

            case '(':S_Char.push(lable_1[i].toLatin1());
                Sign=true;
                break;

            case 's':
                if(i!=0&&lable_1[i-1].toLatin1()>='0'&&lable_1[i-1].toLatin1()<='9'){
                    S_Char.push('*');
                    S_Number.push(f*Now);
                    f=1;
                }
                if(i!=0&&lable_1[i-1]=='-'&&Sign){
                    S_Char.push('*');
                    S_Number.push(-1);
                    f=1;
                }
                S_Char.push('s');
                i+=2;
                Sign=true;
                break;

            case 'c':
                if(i!=0&&lable_1[i-1].toLatin1()>='0'&&lable_1[i-1].toLatin1()<='9'){
                    S_Char.push('*');
                    S_Number.push(f*Now);
                    f=1;
                }
                if(i!=0&&lable_1[i-1]=='-'&&Sign){
                    S_Char.push('*');
                    S_Number.push(-1);
                    f=1;
                }
                S_Char.push('c');
                i+=2;
                Sign=true;
                break;

            case 't':
                if(i!=0&&lable_1[i-1].toLatin1()>='0'&&lable_1[i-1].toLatin1()<='9'){
                    S_Char.push('*');
                    S_Number.push(f*Now);
                    f=1;
                }
                if(i!=0&&lable_1[i-1]=='-'&&Sign){
                    S_Char.push('*');
                    S_Number.push(-1);
                    f=1;
                }
                S_Char.push('t');
                i+=2;
                Sign=true;
                break;

            case 'a':
            {
                if(i!=0&&lable_1[i-1].toLatin1()>='0'&&lable_1[i-1].toLatin1()<='9'){
                    S_Char.push('*');
                    S_Number.push(f*Now);
                    f=1;
                }
                if(i!=0&&lable_1[i-1]=='-'&&Sign){
                    S_Char.push('*');
                    S_Number.push(-1);
                    f=1;
                }
                i+=3;
                switch(lable_1[i].toLatin1()){
                case 's':
                    S_Char.push('a');
                    break;
                case 'c':
                    S_Char.push('b');
                    break;
                case 't':
                    S_Char.push('d');
                    break;
                }
                Sign=true;
            }
            i+=2;
            break;

            case 'l':
                if(i!=0&&lable_1[i-1].toLatin1()>='0'&&lable_1[i-1].toLatin1()<='9'){
                    S_Char.push('*');
                    S_Number.push(f*Now);
                //    qDebug()<<f*Now<<"\n";
                    f=1;
                }
                if(i!=0&&lable_1[i-1]=='-'&&Sign){
                    S_Char.push('*');
                    S_Number.push(-1);
                    f=1;
                    //qDebug()<<"1\n";
                }
                S_Char.push('l');
                i+=1;
                Sign=true;
                break;

            case 'P':
                S_Number.push(f*pi*(Now==0?1:Now));
                i+=1;
                f=1;
                R=true;
                break;

            case 'e':
                S_Number.push(f*e*(Now==0?1:Now));
                R=true;
                f=1;
                break;

            case 'm':
                if(!R)S_Number.push(Now*f),f=1;
                Move(S_Number,S_Char,lable_1[i].toLatin1());
                Sign=true;
                i+=2;
                break;

            case ')':
                if(!R)S_Number.push(Now*f),f=1;
                Move_2(S_Number,S_Char);
                R=true;
                Sign=false;
                break;

            default :if(!R)S_Number.push(Now*f),f=1;
                Move(S_Number,S_Char,lable_1[i].toLatin1());
                Sign=true;
                break;
            }
            Now=0;
        }

    }
    if(!S_Char.empty()&&S_Char.top()=='E'){
        ui->lineEdit->setText("模的两端不都是整数");
        lable="input error";
        ui->LE->setText(lable);
        return 0;
    }
    if(op)
        return S_Number.top();
    this->lable=QString::number(S_Number.top());
    if(S_Number.size()!=1)lable="input error";
    ui->LE->setText(lable);
    return 0;
}

void MainWindow::on_Bu1_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='1';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='1';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu2_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='2';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='2';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu3_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='3';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='3';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu4_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='4';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='4';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu5_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='5';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='5';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu6_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='6';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='6';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu7_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='7';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='7';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu8_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='8';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='8';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu9_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='9';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='9';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu0_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='0';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='0';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu10_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='.';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='.';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu12_clicked()
{

    if(ui->radioButton->isChecked())
        on_drawbutton_clicked();
    else
        calculate(0);
}


void MainWindow::on_Bu13_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='+';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='+';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu15_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='-';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='-';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu14_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='*';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='*';
    ui->LE->setText(lable);
}


void MainWindow::on_Bu16_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='/';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='/';
    ui->LE->setText(lable);
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2.chop(1);
        ui->LE2->setText(lable2);
    }
    lable.chop(1);
    ui->LE->setText(lable);
}


void MainWindow::on_Esc_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2.clear();
        ui->LE2->setText(lable2);
    }
    lable.clear();
    ui->LE->setText(lable);
}

void MainWindow::on_left_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='(';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='(';
    ui->LE->setText(lable);
}


void MainWindow::on_right_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+=')';
        ui->LE2->setText(lable2);
        return;
    }
    lable+=')';
    ui->LE->setText(lable);
}


void MainWindow::on_pushButton_2_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='^';
        ui->LE2->setText(lable2);
        return;
    }
    lable+='^';
    ui->LE->setText(lable);
}


void MainWindow::on_Save_1_clicked()
{
    if(ui->Save_1->Get_Clicked()){
        if(ui->radioButton->isChecked()){
            lable2+=ui->Save_1->text();
            ui->LE2->setText(lable2);
        }
        lable+=ui->Save_1->text();
        ui->LE->setText(lable);
        return;
    }
    int Len=this->lable.size();
    for(int i=0;i<Len;i++)
    {
        if((lable[i]<'0'||lable[i]>'9')&&lable[i]!='.'&&lable[i]!='-')
        {
            ui->lineEdit->setText("保存的不是一个数");
            return;
        }
    }
    ui->Save_1->setText(lable);
    ui->Save_1->Set_Clicked(1);
}

void MainWindow::on_Save_2_clicked()
{
    if(ui->Save_2->Get_Clicked()){
        if(ui->radioButton->isChecked()){
            lable2+=ui->Save_2->text();
            ui->LE2->setText(lable2);
        }
        lable+=ui->Save_2->text();
        ui->LE->setText(lable);
        return;
    }
    int Len=this->lable.size();
    for(int i=0;i<Len;i++)
    {
        if((lable[i]<'0'||lable[i]>'9')&&lable[i]!='.'&&lable[i]!='-')
        {
            ui->lineEdit->setText("保存的不是一个数");
            return;
        }
    }
    ui->Save_2->setText(lable);
    ui->Save_2->Set_Clicked(1);
}

void MainWindow::on_Save_3_clicked()
{
    if(ui->Save_3->Get_Clicked()){
        if(ui->radioButton->isChecked()){
            lable2+=ui->Save_3->text();
            ui->LE2->setText(lable2);
        }
        lable+=ui->Save_3->text();
        ui->LE->setText(lable);
        return;
    }
    int Len=this->lable.size();
    for(int i=0;i<Len;i++)
    {
        if((lable[i]<'0'||lable[i]>'9')&&lable[i]!='.'&&lable[i]!='-')
        {
            ui->lineEdit->setText("保存的不是一个数");
            return;
        }
    }
    ui->Save_3->setText(lable);
    ui->Save_3->Set_Clicked(1);
}

void MainWindow::on_Save_4_clicked()
{
    if(ui->Save_4->Get_Clicked()){
        if(ui->radioButton->isChecked()){
            lable2+=ui->Save_4->text();
            ui->LE2->setText(lable2);
        }
        lable+=ui->Save_4->text();
        ui->LE->setText(lable);
        return;
    }
    int Len=this->lable.size();
    for(int i=0;i<Len;i++)
    {
        if((lable[i]<'0'||lable[i]>'9')&&lable[i]!='.'&&lable[i]!='-')
        {
            ui->lineEdit->setText("保存的不是一个数");
            return;
        }
    }
    ui->Save_4->setText(lable);
    ui->Save_4->Set_Clicked(1);
}


void MainWindow::on_sin_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+="sin";
        ui->LE2->setText(lable2);
        return;
    }
    lable+="sin";
    ui->LE->setText(lable);
}


void MainWindow::on_cos_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+="cos";
        ui->LE2->setText(lable2);
        return;
    }
    lable+="cos";
    ui->LE->setText(lable);
}


void MainWindow::on_tan_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+="tan";
        ui->LE2->setText(lable2);
        return;
    }
    lable+="tan";
    ui->LE->setText(lable);
}


void MainWindow::on_arcsin_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+="arcsin";
        ui->LE2->setText(lable2);
        return;
    }
    lable+="arcsin";
    ui->LE->setText(lable);
}


void MainWindow::on_arccos_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+="arccos";
        ui->LE2->setText(lable2);
        return;
    }
    lable+="arccos";
    ui->LE->setText(lable);
}


void MainWindow::on_arctan_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+="arctan";
        ui->LE2->setText(lable2);
        return;
    }
    lable+="arctan";
    ui->LE->setText(lable);
}


void MainWindow::on_ln_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+="ln";
        ui->LE2->setText(lable2);
        return;
    }
    lable+="ln";
    ui->LE->setText(lable);
}


void MainWindow::on_pi_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+="Pi";
        ui->LE2->setText(lable2);
        return;
    }
    lable+="Pi";
    ui->LE->setText(lable);
}


void MainWindow::on_e_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='e';
        ui->LE2->setText(lable2);
        return;
    }
    lable+="e";
    ui->LE->setText(lable);
}


void MainWindow::on_pushButton_3_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+="^(-1)";
        ui->LE2->setText(lable2);
        return;
    }
    lable+="^(-1)";
    ui->LE->setText(lable);
}

void MainWindow::on_drawbutton_clicked()
{

    painter *a = new painter();
    a->setAttribute(Qt::WA_DeleteOnClose);
    a->show();
    a->raise();
    a->activateWindow();
}


void MainWindow::on_x_button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+='x';
        ui->LE2->setText(lable2);
    }
    return;
}

double painter::calculate(double a){
    QString S=MainWindow::lable2,SS=S;
    S="("+S+")";
    int size=S.size();
    for(int i=0;i<size;i++,size=S.size()){
        if(S[i]=='x'&&i!=0){
            if(S[i-1].toLatin1()>='0'&&S[i-1].toLatin1()<='9')
                S=S.left(i)+"*"+QString::number(a)+S.right(size-i-1);
            else
                S=S.left(i)+QString::number(a)+S.right(size-i-1);
        }
        else if(S[i]=='x')
            S=S.left(i)+"*"+QString::number(a)+S.right(size-i-1);
    }
    MainWindow::lable2=S;
    double ans=windo->calculate(1);
    MainWindow::lable2=SS;
    return ans;
}


void MainWindow::on_mod_Button_clicked()
{
    if(ui->radioButton->isChecked()){
        lable2+="mod";
        ui->LE2->setText(lable2);
        return;
    }
    lable+="mod";
    ui->LE->setText(lable);
}


#include "coursetabelwidget.h"

coursetabelwidget::coursetabelwidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(QSize(1600,1400));//设置大小
    //new语句
    newcourses();
    initcourseslocation();

}

void coursetabelwidget::newcourses(){
    // 星期一
    coursemonday1 = new coursecard(this);
    coursecards[1] = coursemonday1;
    coursemonday2 = new coursecard(this);
    coursecards[2] = coursemonday2;
    coursemonday3 = new coursecard(this);
    coursecards[3] = coursemonday3;
    coursemonday4 = new coursecard(this);
    coursecards[4] = coursemonday4;
    coursemonday5 = new coursecard(this);
    coursecards[5] = coursemonday5;
    coursemonday6 = new coursecard(this);
    coursecards[6] = coursemonday6;
    coursemonday7 = new coursecard(this);
    coursecards[7] = coursemonday7;
    coursemonday8 = new coursecard(this);
    coursecards[8] = coursemonday8;
    coursemonday9 = new coursecard(this);
    coursecards[9] = coursemonday9;
    coursemonday10 = new coursecard(this);
    coursecards[10] = coursemonday10;
    coursemonday11 = new coursecard(this);
    coursecards[11] = coursemonday11;
    coursemonday12 = new coursecard(this);
    coursecards[12] = coursemonday12;
    coursemonday13 = new coursecard(this);
    coursecards[13] = coursemonday13;

    // 星期二
    coursetuesday1 = new coursecard(this);
    coursecards[14] = coursetuesday1;
    coursetuesday2 = new coursecard(this);
    coursecards[15] = coursetuesday2;
    coursetuesday3 = new coursecard(this);
    coursecards[16] = coursetuesday3;
    coursetuesday4 = new coursecard(this);
    coursecards[17] = coursetuesday4;
    coursetuesday5 = new coursecard(this);
    coursecards[18] = coursetuesday5;
    coursetuesday6 = new coursecard(this);
    coursecards[19] = coursetuesday6;
    coursetuesday7 = new coursecard(this);
    coursecards[20] = coursetuesday7;
    coursetuesday8 = new coursecard(this);
    coursecards[21] = coursetuesday8;
    coursetuesday9 = new coursecard(this);
    coursecards[22] = coursetuesday9;
    coursetuesday10 = new coursecard(this);
    coursecards[23] = coursetuesday10;
    coursetuesday11 = new coursecard(this);
    coursecards[24] = coursetuesday11;
    coursetuesday12 = new coursecard(this);
    coursecards[25] = coursetuesday12;
    coursetuesday13 = new coursecard(this);
    coursecards[26] = coursetuesday13;

    // 星期三
    coursewednesday1 = new coursecard(this);
    coursecards[27] = coursewednesday1;
    coursewednesday2 = new coursecard(this);
    coursecards[28] = coursewednesday2;
    coursewednesday3 = new coursecard(this);
    coursecards[29] = coursewednesday3;
    coursewednesday4 = new coursecard(this);
    coursecards[30] = coursewednesday4;
    coursewednesday5 = new coursecard(this);
    coursecards[31] = coursewednesday5;
    coursewednesday6 = new coursecard(this);
    coursecards[32] = coursewednesday6;
    coursewednesday7 = new coursecard(this);
    coursecards[33] = coursewednesday7;
    coursewednesday8 = new coursecard(this);
    coursecards[34] = coursewednesday8;
    coursewednesday9 = new coursecard(this);
    coursecards[35] = coursewednesday9;
    coursewednesday10 = new coursecard(this);
    coursecards[36] = coursewednesday10;
    coursewednesday11 = new coursecard(this);
    coursecards[37] = coursewednesday11;
    coursewednesday12 = new coursecard(this);
    coursecards[38] = coursewednesday12;
    coursewednesday13 = new coursecard(this);
    coursecards[39] = coursewednesday13;

    // 星期四
    coursethursday1 = new coursecard(this);
    coursecards[40] = coursethursday1;
    coursethursday2 = new coursecard(this);
    coursecards[41] = coursethursday2;
    coursethursday3 = new coursecard(this);
    coursecards[42] = coursethursday3;
    coursethursday4 = new coursecard(this);
    coursecards[43] = coursethursday4;
    coursethursday5 = new coursecard(this);
    coursecards[44] = coursethursday5;
    coursethursday6 = new coursecard(this);
    coursecards[45] = coursethursday6;
    coursethursday7 = new coursecard(this);
    coursecards[46] = coursethursday7;
    coursethursday8 = new coursecard(this);
    coursecards[47] = coursethursday8;
    coursethursday9 = new coursecard(this);
    coursecards[48] = coursethursday9;
    coursethursday10 = new coursecard(this);
    coursecards[49] = coursethursday10;
    coursethursday11 = new coursecard(this);
    coursecards[50] = coursethursday11;
    coursethursday12 = new coursecard(this);
    coursecards[51] = coursethursday12;
    coursethursday13 = new coursecard(this);
    coursecards[52] = coursethursday13;

    // 星期五
    coursefriday1 = new coursecard(this);
    coursecards[53] = coursefriday1;
    coursefriday2 = new coursecard(this);
    coursecards[54] = coursefriday2;
    coursefriday3 = new coursecard(this);
    coursecards[55] = coursefriday3;
    coursefriday4 = new coursecard(this);
    coursecards[56] = coursefriday4;
    coursefriday5 = new coursecard(this);
    coursecards[57] = coursefriday5;
    coursefriday6 = new coursecard(this);
    coursecards[58] = coursefriday6;
    coursefriday7 = new coursecard(this);
    coursecards[59] = coursefriday7;
    coursefriday8 = new coursecard(this);
    coursecards[60] = coursefriday8;
    coursefriday9 = new coursecard(this);
    coursecards[61] = coursefriday9;
    coursefriday10 = new coursecard(this);
    coursecards[62] = coursefriday10;
    coursefriday11 = new coursecard(this);
    coursecards[63] = coursefriday11;
    coursefriday12 = new coursecard(this);
    coursecards[64] = coursefriday12;
    coursefriday13 = new coursecard(this);
    coursecards[65] = coursefriday13;

    // 星期六
    coursesaturday1 = new coursecard(this);
    coursecards[66] = coursesaturday1;
    coursesaturday2 = new coursecard(this);
    coursecards[67] = coursesaturday2;
    coursesaturday3 = new coursecard(this);
    coursecards[68] = coursesaturday3;
    coursesaturday4 = new coursecard(this);
    coursecards[69] = coursesaturday4;
    coursesaturday5 = new coursecard(this);
    coursecards[70] = coursesaturday5;
    coursesaturday6 = new coursecard(this);
    coursecards[71] = coursesaturday6;
    coursesaturday7 = new coursecard(this);
    coursecards[72] = coursesaturday7;
    coursesaturday8 = new coursecard(this);
    coursecards[73] = coursesaturday8;
    coursesaturday9 = new coursecard(this);
    coursecards[74] = coursesaturday9;
    coursesaturday10 = new coursecard(this);
    coursecards[75] = coursesaturday10;
    coursesaturday11 = new coursecard(this);
    coursecards[76] = coursesaturday11;
    coursesaturday12 = new coursecard(this);
    coursecards[77] = coursesaturday12;
    coursesaturday13 = new coursecard(this);
    coursecards[78] = coursesaturday13;

    // 星期天
    coursesunday1 = new coursecard(this);
    coursecards[79] = coursesunday1;
    coursesunday2 = new coursecard(this);
    coursecards[80] = coursesunday2;
    coursesunday3 = new coursecard(this);
    coursecards[81] = coursesunday3;
    coursesunday4 = new coursecard(this);
    coursecards[82] = coursesunday4;
    coursesunday5 = new coursecard(this);
    coursecards[83] = coursesunday5;
    coursesunday6 = new coursecard(this);
    coursecards[84] = coursesunday6;
    coursesunday7 = new coursecard(this);
    coursecards[85] = coursesunday7;
    coursesunday8 = new coursecard(this);
    coursecards[86] = coursesunday8;
    coursesunday9 = new coursecard(this);
    coursecards[87] = coursesunday9;
    coursesunday10 = new coursecard(this);
    coursecards[88] = coursesunday10;
    coursesunday11 = new coursecard(this);
    coursecards[89] = coursesunday11;
    coursesunday12 = new coursecard(this);
    coursecards[90] = coursesunday12;
    coursesunday13 = new coursecard(this);
    coursecards[91] = coursesunday13;

}

void coursetabelwidget::initcourseslocation(){
    // 星期一
    coursemonday1->move(hinterval*0, vinterval*0);
    coursemonday2->move(hinterval*0, vinterval*1);
    coursemonday3->move(hinterval*0, vinterval*2);
    coursemonday4->move(hinterval*0, vinterval*3);
    coursemonday5->move(hinterval*0, vinterval*4);
    coursemonday6->move(hinterval*0, vinterval*5);
    coursemonday7->move(hinterval*0, vinterval*6);
    coursemonday8->move(hinterval*0, vinterval*7);
    coursemonday9->move(hinterval*0, vinterval*8);
    coursemonday10->move(hinterval*0, vinterval*9);
    coursemonday11->move(hinterval*0, vinterval*10);
    coursemonday12->move(hinterval*0, vinterval*11);
    coursemonday13->move(hinterval*0, vinterval*12);

    // 星期二
    coursetuesday1->move(hinterval*1, vinterval*0);
    coursetuesday2->move(hinterval*1, vinterval*1);
    coursetuesday3->move(hinterval*1, vinterval*2);
    coursetuesday4->move(hinterval*1, vinterval*3);
    coursetuesday5->move(hinterval*1, vinterval*4);
    coursetuesday6->move(hinterval*1, vinterval*5);
    coursetuesday7->move(hinterval*1, vinterval*6);
    coursetuesday8->move(hinterval*1, vinterval*7);
    coursetuesday9->move(hinterval*1, vinterval*8);
    coursetuesday10->move(hinterval*1, vinterval*9);
    coursetuesday11->move(hinterval*1, vinterval*10);
    coursetuesday12->move(hinterval*1, vinterval*11);
    coursetuesday13->move(hinterval*1, vinterval*12);

    // 星期三
    coursewednesday1->move(hinterval*2, vinterval*0);
    coursewednesday2->move(hinterval*2, vinterval*1);
    coursewednesday3->move(hinterval*2, vinterval*2);
    coursewednesday4->move(hinterval*2, vinterval*3);
    coursewednesday5->move(hinterval*2, vinterval*4);
    coursewednesday6->move(hinterval*2, vinterval*5);
    coursewednesday7->move(hinterval*2, vinterval*6);
    coursewednesday8->move(hinterval*2, vinterval*7);
    coursewednesday9->move(hinterval*2, vinterval*8);
    coursewednesday10->move(hinterval*2, vinterval*9);
    coursewednesday11->move(hinterval*2, vinterval*10);
    coursewednesday12->move(hinterval*2, vinterval*11);
    coursewednesday13->move(hinterval*2, vinterval*12);

    // 星期四
    coursethursday1->move(hinterval*3, vinterval*0);
    coursethursday2->move(hinterval*3, vinterval*1);
    coursethursday3->move(hinterval*3, vinterval*2);
    coursethursday4->move(hinterval*3, vinterval*3);
    coursethursday5->move(hinterval*3, vinterval*4);
    coursethursday6->move(hinterval*3, vinterval*5);
    coursethursday7->move(hinterval*3, vinterval*6);
    coursethursday8->move(hinterval*3, vinterval*7);
    coursethursday9->move(hinterval*3, vinterval*8);
    coursethursday10->move(hinterval*3, vinterval*9);
    coursethursday11->move(hinterval*3, vinterval*10);
    coursethursday12->move(hinterval*3, vinterval*11);
    coursethursday13->move(hinterval*3, vinterval*12);

    // 星期五
    coursefriday1->move(hinterval*4, vinterval*0);
    coursefriday2->move(hinterval*4, vinterval*1);
    coursefriday3->move(hinterval*4, vinterval*2);
    coursefriday4->move(hinterval*4, vinterval*3);
    coursefriday5->move(hinterval*4, vinterval*4);
    coursefriday6->move(hinterval*4, vinterval*5);
    coursefriday7->move(hinterval*4, vinterval*6);
    coursefriday8->move(hinterval*4, vinterval*7);
    coursefriday9->move(hinterval*4, vinterval*8);
    coursefriday10->move(hinterval*4, vinterval*9);
    coursefriday11->move(hinterval*4, vinterval*10);
    coursefriday12->move(hinterval*4, vinterval*11);
    coursefriday13->move(hinterval*4, vinterval*12);

    // 星期六
    coursesaturday1->move(hinterval*5, vinterval*0);
    coursesaturday2->move(hinterval*5, vinterval*1);
    coursesaturday3->move(hinterval*5, vinterval*2);
    coursesaturday4->move(hinterval*5, vinterval*3);
    coursesaturday5->move(hinterval*5, vinterval*4);
    coursesaturday6->move(hinterval*5, vinterval*5);
    coursesaturday7->move(hinterval*5, vinterval*6);
    coursesaturday8->move(hinterval*5, vinterval*7);
    coursesaturday9->move(hinterval*5, vinterval*8);
    coursesaturday10->move(hinterval*5, vinterval*9);
    coursesaturday11->move(hinterval*5, vinterval*10);
    coursesaturday12->move(hinterval*5, vinterval*11);
    coursesaturday13->move(hinterval*5, vinterval*12);

    // 星期天
    coursesunday1->move(hinterval*6, vinterval*0);
    coursesunday2->move(hinterval*6, vinterval*1);
    coursesunday3->move(hinterval*6, vinterval*2);
    coursesunday4->move(hinterval*6, vinterval*3);
    coursesunday5->move(hinterval*6, vinterval*4);
    coursesunday6->move(hinterval*6, vinterval*5);
    coursesunday7->move(hinterval*6, vinterval*6);
    coursesunday8->move(hinterval*6, vinterval*7);
    coursesunday9->move(hinterval*6, vinterval*8);
    coursesunday10->move(hinterval*6, vinterval*9);
    coursesunday11->move(hinterval*6, vinterval*10);
    coursesunday12->move(hinterval*6, vinterval*11);
    coursesunday13->move(hinterval*6, vinterval*12);



}

void coursetabelwidget::setcoursecard(int number,int id,int week,QString firstlabel,QString secondlabel){
    coursecards[number]->setcourseid(id);
    coursecards[number]->setcourseweekid(week);
    coursecards[number]->setfirstlabel(firstlabel);
    coursecards[number]->setsecondlabel(secondlabel);
}

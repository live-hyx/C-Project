//万年历
//bool函数，switch，case使用，类的使用，格式控制，文件打开与关闭
#include<iostream>//通用输入输出
#include<fstream>//文件输入输出
#include<iomanip>//setw，setiosflags函数(起控制格式的作用）头文件
using namespace std;
int everyMonth[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
class WNL//类声明
{
public:
    void Input();//进行操作选择
    void SetDays();//如果输入某年某月某日，进行'3'操作处理
    void SetMonth();//如果选输入某年某月，进行'2'操作处理
    void SetYear();//如果输入某年，进行'1'操作处理
    bool IsLeap(int year);//判断是否是闰年
    bool IsRight(int year,int month,int day);//判断输入是否合法
    int GetDays(int year,int month,int day);//得到此日期前的天数
    void Print(int year,int month);//输出到界面上
    void Output(int year); //打印到文档out，一年的
};
void WNL::Input()//用户输入
{
    char choose;
    bool flag=true;
    while(flag)
    {
        cout<<"欢迎使用万年历！"<<endl<<"请选择: (1/2/3/4)"<<endl;
        cout<<"1:输入某年（显示该年的年历，并显示生肖）"<<endl;
        cout<<"2:输入某年某月（显示该月的万年历,并显示季度和季节）"<<endl;
        cout<<"3:输入某年某月某日（显示该日是星期几,并显示节日）"<<endl;
        cout<<"4:退出"<<endl;
        cout<<"输入您的选择： ";
        cin>>choose;
        switch(choose)
        {
            case '1':SetYear();break;
            case '2':SetMonth();break;
            case '3':SetDays();break;
            case '4':flag=false;break;
            default:cout<<"输入错误，请重新输入";
        }
    }
}
bool WNL::IsRight(int year,int month,int day) //判断日期输入是否正确
{//bool函数返回true或者false，多用于循环判断条件
    if(year<1 || year>9999 || month<1 || month>12)//年月是否正确
        return false;
    //日期是否正确
    if(day<0)
        return false;
    else if( day==29)
        return((month==2 && IsLeap(year))|| month!=2);
    else if(day==31)return(month==1 ||month==3 ||month==5 ||month==7 ||month==8 || month==10 || month==12);
    else if(day>31)
        return false;
    else
        return true;
}
void WNL::SetDays()//输入某年某月某日
{
    int weekDay;
    int year,month,day;
    cout<<"请输入年_月_日：";
    cin>>year>>month>>day;
    while(!IsRight(year,month,day))
    {
        cout<<"输入错误，请重新输入年_月_日：";
        cin>>year>>month>>day;
    }
    weekDay=GetDays(year, month,day)%7;
    switch(weekDay)
    {
        case 0: cout<<year<<"年"<<month<<"月"<<day<<"日  星期日(SUN)  ";
            break;
        case 1: cout<<year<<"年"<<month<<"月"<<day<<"日  星期一(MON)  ";
            break;
        case 2: cout<<year<<"年"<<month<<"月"<<day<<"日  星期二(TUE)  ";
            break;
        case 3: cout<<year<<"年"<<month<<"月"<<day<<"日  星期三(WES)  ";
            break;
        case 4: cout<<year<<"年"<<month<<"月"<<day<<"日  星期四(THU)  ";
            break;
        case 5: cout<<year<<"年"<<month<<"月"<<day<<"日  星期五(FRI)  ";
            break;
        case 6: cout<<year<<"年"<<month<<"月"<<day<<"日  星期六(SAT)  ";
            break;
    }
    switch(month)
    {
        case 1:
        {
            if(day == 1)
                cout<<"元旦节"<<endl;
            else
                cout<<"非节日"<<endl;
        };break;
        case 2:
        {
            if(14 == day)
                cout<<"情人节"<<endl;
            else
                cout<<"非节日"<<endl;
        };break;
        case 3:
        {
            if(8 == day)
                cout<<"妇女节"<<endl;
            else if(12 == day)
                cout<<"植树节"<<endl;
            else
                cout<<"非节日"<<endl;
        };break;
        case 4:
        {
            if(1 == day)
                cout<<"愚人节"<<endl;
            else if(5==day)
                cout<<"清明节"<<endl;
            else
                cout<<"非节日"<<endl;
        };break;
        case 5:
        {
            if(1 == day)
                cout<<"劳动节"<<endl;
            else if(4==day)
                cout<<"青年节"<<endl;
            else if(14 == day)
                cout<<"母亲节"<<endl;
            else
                cout<<"非节日"<<endl;
        };break;
        case 6:
        {
            if(1 == day)
                cout<<"儿童节"<<endl;
            else if(19 == day)
                cout<<"父亲节"<<endl;
            else
                cout<<"非节日"<<endl;
        };break;
        case 7:
        {
            if(1 == day)
                cout<<"建党节"<<endl;
            else
                cout<<"非节日"<<endl;
        };break;
        case 8:
        {
            if(1 == day)
                cout<<"建军节"<<endl;
            else
                cout<<"非节日"<<endl;
        };break;
        case  9:
        {
            if(10 == day)
                cout<<"教师节"<<endl;
            else if(28 == day)
                cout<<"孔子诞辰"<<endl;
            else
                cout<<"非节日"<<endl;
        };break;
        case 10:
        {
            if(1 == day)
                cout<<"国庆节"<<endl;
            else
                cout<<"非节日"<<endl;
        };break;
        case 11:
        {
            cout<<"非节日"<<endl;
        };break;
        case 12:
        {
            if(24 == day)
                cout<<"平安夜"<<endl;
            else if(25 == day)
                cout<<"圣诞节"<<endl;
            else
                cout<<"非节日"<<endl;
        };break;
        default:
            break;
    }
}
bool WNL::IsLeap(int year)//判断是否是闰年
{
    return ((year%4==0 && year%100!=0)||(year%400==0));
}
int WNL::GetDays(int year,int month,int day)//得到此日前已经过的日子
{
    int yearDays,sum,monthDays=0;
    int accumulate=0;
    for(int i=1;i<year;i++)
        if(IsLeap(i))
            accumulate++;//闰年每年366天，把闰年多的一天加起来
    yearDays=accumulate+365*(year-1);
    if((year%4==0 && year%100!=0)||(year%400==0))
        everyMonth[2]=29;//如果是闰年，则2月为29天
    for(int j=1;j<month;j++)
        monthDays+=everyMonth[j];//未满一年的已过的天数
    sum=yearDays+monthDays+day;//所有已经过的日子之和
    return sum;
}
void WNL::SetMonth()//输入的是年月
{
    int weekDay;
    int year,month,day;
    cout<<"请输入年_月：";
    cin>>year>>month;
    day=1;//任意设置day=1
    while(!IsRight(year,month,day))//判断输入是否正确
    {
        cout<<"输入错误，请重新输入年_月：";
        cin>>year>>month;
    }
    switch(month)
    {
        case 1:
        {
            cout<<"     第一季度"<<"  "<<"冬季"<<endl;
        };break;
        case 2:
        {
            cout<<"     第一季度"<<"  "<<"冬季"<<endl;
        };break;
        case 3:
        {
            cout<<"     第一季度"<<"  "<<"春季"<<endl;
        };break;
        case 4:
        {
            cout<<"     第二季度"<<"  "<<"春季"<<endl;
        };break;
        case 5:
        {
            cout<<"     第二季度"<<"  "<<"春季"<<endl;
        };break;
        case 6:
        {
            cout<<"     第二季度"<<"  "<<"夏季"<<endl;
        };break;
        case 7:
        {
            cout<<"     第三季度"<<"  "<<"夏季"<<endl;
        };break;
        case 8:
        {
            cout<<"     第三季度"<<"  "<<"夏季"<<endl;
        };break;
        case 9:
        {
            cout<<"     第三季度"<<"  "<<"秋季"<<endl;
        };break;
        case 10:
        {
            cout<<"     第四季度"<<"  "<<"秋季"<<endl;
        };break;
        case 11:
        {
            cout<<"     第四季度"<<"  "<<"秋季"<<endl;
        };break;
        case 12:
        {
            cout<<"     第四季度"<<"  "<<"冬季"<<endl;
        };break;
        default:
            break;
    }
    weekDay=GetDays(year, month,day)%7;
    Print(year,month);
}
void WNL::SetYear()//输入年
{
    int year,month,day;
    cout<<"请输入年：";
    cin>>year;
    month=1;day=1;//设置day=1，month=1
    while(!IsRight(year,month,day))//判断是否输入正确
    {
        cout<<"输入错误，请重新输入年：";
        cin>>year;
    }
    char const *animal[12] = {"子鼠", "丑牛", "寅虎", "卯兔", "辰龙", "巳蛇", "午马", "未羊", "申猴", "酉鸡", "戌狗","亥猪"};
    int baseYear = 2008; //08年是鼠年，以此为基准进行判断
    int count = 0;
    int result = 0;
    count = abs(baseYear - year); //判断是基准年之前还是之后
    if ((baseYear - year) > 0)
    { //基准年之前，差值取余再取补数即可得到生肖的位置，
        result = 12 - count % 12;
    }
    else
    { //差值取余即可得到生肖的位置，
        result = count % 12;
    }
    cout<<"万年历打印在out文档中，请查看。"<<endl<<endl;
    cout<<"         "<<year<<"年的生肖是:"<<animal[result]<<endl;
    Output(year);
    for(int k=1;k<=12;k++)//将12个月的万年历在界面上输出
        Print(year,k);
}
void WNL:: Print(int year,int month)//打印到界面上
{
    int weekday,day=1;
    cout<<"                公元"<<year<<"年"<<month<<"月"<<endl;
    cout<<"     SUN   MON   TUE   WES   THU   FRI   SAT"<<endl;
    weekday=GetDays(year, month,day)%7;//所有的日期之和取余
    switch(weekday)//输出处理
    {
        case 0: cout<<"     "<<setw(6)<<setiosflags(ios::left)<<"1"; break;//setw(6)表示用5个空格来分隔
        case 1: cout<<"           "<<setw(6)<<setiosflags(ios::left)<<"1";
            break;//setiosflags(ios::left)表示在指定区域向右对齐
        case 2: cout<<"                 "<<setw(6)<<setiosflags(ios::left)<<"1";
            break;
        case 3: cout<<"                       "<<setw(6)<<setiosflags(ios::left)<<"1";
            break;
        case 4: cout<<"                             "<<setw(6)<<setiosflags(ios::left)<<"1";
            break;
        case 5: cout<<"                                   "<<setw(6)<<setiosflags(ios::left)<<"1";
            break;
        case 6: cout<<"                                         "<<setw(6)<<setiosflags(ios::left)<<"1";
            break;
    }
    for(int i=2;i<=everyMonth[month];i++)
    {
        weekday=(++weekday)%7;
        if(!weekday)
        {cout<<endl; cout<<"     "<<setw(6)<<setiosflags(ios::left)<<i;}
        else
            cout<<setw(6)<<setiosflags(ios::left)<<i;
    }
    cout<<endl;
}
void WNL::Output(int year)//打印到out文本框内
{
    int weekday,day=1;
    int i,j;
    ofstream outfile;
    outfile.open("out.txt",ios::out);//以输出方式打开文件
    for(i=1;i<=12;i++)
    {
        outfile<<"             公元"<<year<<"年"<<i<<"月"<<endl;
        outfile<<"     SUN   MON   TUE   WES   THU   FRI   SAT"<<endl;
        weekday=GetDays(year, i,day)%7;
        switch(weekday)
        {
            case 0: outfile<<"     "<<setw(6)<<setiosflags(ios::left)<<"1"; break;
            case 1: outfile<<"           "<<setw(6)<<setiosflags(ios::left)<<"1";break;
            case 2: outfile<<"                 "<<setw(6)<<setiosflags(ios::left)<<"1";break;
            case 3: outfile<<"                       "<<setw(6)<<setiosflags(ios::left)<<"1";break;
            case 4: outfile<<"                             "<<setw(6)<<setiosflags(ios::left)<<"1";break;
            case 5: outfile<<"                                   "<<setw(6)<<setiosflags(ios::left)<<"1";break;
            case 6: outfile<<"                                         "<<setw(6)<<setiosflags(ios::left)<<"1";break;
        }
        for( j=2;j<=everyMonth[i];j++)
        {
            weekday=(++weekday)%7;
            if(!weekday)
            {outfile<<endl; outfile<<"     "<<setw(6)<<setiosflags(ios::left)<<j;}
            else
                outfile<<setw(6)<<setiosflags(ios::left)<<j;
        }
        outfile<<endl;
        outfile<<endl;
    }
    cout<<endl;
    outfile.close();//关闭文件流对象outfile
}
int main()//主函数
{
    WNL WNL;
    WNL.Input();
}


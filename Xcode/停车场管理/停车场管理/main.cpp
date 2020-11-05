//停车场管理
#include <iostream>
using namespace std;

enum StatusCode{ SUCCESS, FAIL, UNDER_FLOW, UNFER_FLOW, NOT_PRESENT, ENTRY_FOUND, RANGE_ERROR,OVER_FLOW };

struct VehicleType
{// 车辆类型
    unsigned int num;// 车辆编号
    unsigned int time;
};

void Write(const struct VehicleType &e)
{
    cout<<"("<<e.num<<","<<e.time<<")";
}

template<class ElemType>
struct Node{
    ElemType data;//定义一个结点元素
    Node<ElemType> *next;//定义一个结点指针
    Node();//无参构造函数
    Node(ElemType item, Node<ElemType> *link = NULL);//含参构造函数
};

template<class ElemType>
Node<ElemType>::Node(){
    //构造函数
    next = NULL;
}

template<class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType> *link){
    //含参构造函数
    data = item;
    next = link;
}
 
template<class ElemType>
class LinkStack{
protected:
    Node<ElemType> *top;//定义一个指针
    void Init();
public:
    LinkStack();//无参构造函数
    virtual ~LinkStack();//析构函数
    bool Empty() const;//判断堆栈是否为空
    void Clear();//清空堆栈的所有元素
    int Length() const;
    void Traverse(void(*visit)(const ElemType &))const;
    StatusCode Push(const ElemType &e);//往堆栈中传入元素
    StatusCode Pop(ElemType &e);//删除堆栈的栈顶元素
    StatusCode Top(ElemType &e) const;//返回栈顶元素
    LinkStack(const LinkStack<ElemType> &copy);
    LinkStack<ElemType> &operator = (const LinkStack<ElemType> &copy);//操作符重载

};
 
template<class ElemType>
void LinkStack<ElemType>::Init(){
    //堆栈的构造函数
    top = NULL;
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(){
    //堆栈的构造函数
    Init();
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack(){
    //析构函数
    Clear();
}

template<class ElemType>
bool LinkStack<ElemType>::Empty() const{
    //判断堆栈是否为空
    return top == NULL;
}

template<class ElemType>
void LinkStack<ElemType>::Clear(){
    //清空堆栈的所有元素
    ElemType tmpElem;
    while (!Empty())
        Pop(tmpElem);
}

template<class ElemType>
int LinkStack<ElemType>::Length() const
{
    int count=0;
    for(Node<ElemType> *tmpPtr=top;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
    {
        count++;
    }
    return count;
}

template<class ElemType>
void LinkStack<ElemType>::Traverse(void (*visit)(const ElemType &))const
{
    Node<ElemType> *tmpPtr;
    LinkStack<ElemType> tmpS;
    for(tmpPtr=top;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
    {
        tmpS.Push(tmpPtr->data);
    }
    for(tmpPtr=tmpS.top;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
    {
        (*visit)(tmpPtr->data);
    }
}

template<class ElemType>
StatusCode LinkStack<ElemType>::Push(const ElemType &e){
    //向堆栈中添加元素
    Node<ElemType>*new_top = new Node<ElemType>(e, top);
    if (new_top == NULL)
    {
        return OVER_FLOW;
    }
        
    else
    {
        top = new_top;
        return SUCCESS;
    }
}

template<class ElemType>
StatusCode LinkStack<ElemType>::Top(ElemType &e) const{
    //得到堆栈的栈顶元素
    if (Empty())
        return UNDER_FLOW;
    else{
        e = top->data;
        return SUCCESS;
    }
}

template<class ElemType>
StatusCode LinkStack<ElemType>::Pop(ElemType &e){
    //删除堆栈中的栈顶元素
    if (Empty()){
        //栈空
        return UNDER_FLOW;
    }
    else{
        //操作成功
        Node<ElemType>*old_top = top;
        if (top == NULL)
            return UNDER_FLOW;
        e = old_top->data;
        top = old_top->next;
        delete old_top;
        return SUCCESS;
    }
}

/*template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &copy)
{
    if(copy.Empt())
    {
        Init();
    }
    else
    {
        top=new Node<ElemType>(copy.top->data);
        Node<ElemType> *buttomPtr=top;
        for(Node<ElemType> *tmpPtr=copy.top->next;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
        {
            buttomPtr->next=new Node<ElemType>(tmpPtr->data);
            buttomPtr=buttomPtr->next;
        }
    }
}

template<class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator =(const LinkStack<ElemType> &copy)
{
    if(&copy!=this)
    {
        if(copy.Empty())
        {
            Init();
        }
        else{
            Clear();
            top=new Node<ElemType>(copy.top->data);
            Node<ElemType> *buttomPtr=top;
            for(Node<ElemType> *tmpPtr=copy.top->next;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
            {
                buttomPtr->next=new Node<ElemType>(tmpPtr->data);
                buttomPtr=buttomPtr->next;
            }
        }
    }
    return *this;
}*/

template<class ElemType>
class LinkList
{
protected:
    Node<ElemType> *head;
    mutable int curPosition;
    mutable Node<ElemType> *curPtr;
    int count;
    Node<ElemType> *GetElemPtr(int position) const;
    void Init();
public:
    LinkList();
    virtual ~LinkList();
    int Length() const;
    bool Empty() const;
    void Clear();
    void Traverse(void(*visit)(const ElemType &)) const;
    int GetCurPosition() const;
    StatusCode GetElem(int position,ElemType &e) const;
    StatusCode SetElem(int position,const ElemType &e);
    StatusCode Delete(int position,ElemType &e);
    StatusCode Insert(int position,const ElemType &e);
    LinkList(const LinkList<ElemType> &copy);
    LinkList<ElemType> &operator =(const LinkList<ElemType> &copy);
};

template<class ElemType>
Node<ElemType> *LinkList<ElemType>::GetElemPtr(int position) const
{
    if(curPosition>position)
    {
        curPosition=0;
        curPtr=head;
    }
    for(;curPosition<position;curPosition++)
        curPtr=curPtr->next;
    return curPtr;
}

template<class ElemType>
void LinkList<ElemType>::Init()
{
    head=new Node<ElemType>;
    curPtr=head;
    curPosition=0;
    count=0;
}

template<class ElemType>
LinkList<ElemType>::LinkList()
{
    Init();
}

template<class ElemType>
LinkList<ElemType>::~LinkList()
{
    Clear();
    delete head;
}

template<class ElemType>
int LinkList<ElemType>::Length() const
{
    return count;
}

template<class ElemType>
bool LinkList<ElemType>::Empty() const
{
    return head->next == NULL;
}

template<class ElemType>
void LinkList<ElemType>::Clear()
{
    ElemType tmpElem;
    while(Length()>0)
    {
        Delete(1, tmpElem);
    }
}

template<class ElemType>
void LinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
{
    for(Node<ElemType> *tmpPtr=head->next;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
    {
        (*visit)(tmpPtr->data);
    }
}

template<class ElemType>
int LinkList<ElemType>::GetCurPosition() const
{
    return curPosition;
}

template<class ElemType>
StatusCode LinkList<ElemType>::GetElem(int position, ElemType &e) const
{
    if(position<1||position>Length())
    {
        return NOT_PRESENT;
    }
    else
    {
        Node<ElemType> *tmpPtr;
        tmpPtr=GetElemPtr(position);
        e=tmpPtr->data;
        return ENTRY_FOUND;
    }
}

template<class ElemType>
StatusCode LinkList<ElemType>::SetElem(int position, const ElemType &e)
{
    if(position<1||position>Length())
    {
        return RANGE_ERROR;
    }
    else
    {
        Node<ElemType> *tmpPtr;
        tmpPtr=GetElemPtr(position);
        tmpPtr->data=e;
        return SUCCESS;
    }
}

template<class ElemType>
StatusCode LinkList<ElemType>::Delete(int position, ElemType &e)
{
    if(position<1||position>Length())
    {
        return RANGE_ERROR;
    }
    else
    {
        Node<ElemType> *tmpPtr;
        tmpPtr=GetElemPtr(position-1);
        Node<ElemType> *nextPtr=tmpPtr->next;
        tmpPtr->next=nextPtr->next;
        e=nextPtr->data;
        if(position==Length())
        {
            curPosition=0;
            curPtr=head;
        }
        else
        {
            curPosition=position;
            curPtr=tmpPtr->next;
        }
        count--;
        delete nextPtr;
        return SUCCESS;
    }
}

template<class ElemType>
StatusCode LinkList<ElemType>::Insert(int position, const ElemType &e)
{
    if(position<1||position>Length()+1)
    {
        return RANGE_ERROR;
    }
    else
    {
        Node<ElemType> *tmpPtr;
        tmpPtr=GetElemPtr(position-1);
        Node<ElemType> *newPtr;
        newPtr=new Node<ElemType>(e,tmpPtr->next);
        tmpPtr->next=newPtr;
        curPosition=position;
        curPtr=newPtr;
        count++;
        return SUCCESS;
    }
}

/*template<class ElemType>
LinkList<ElemType>::LinkList(const LinkList<ElemType> &copy)
{
    int copyLength=copy.Length();
    ElemType e;
    Init();
    for(int curPosition=1;curPosition<=copyLength;curPosition++)
    {
        copy.GetElem(curPosition, e);
        Insert(Length()+1, e);
    }
}

template<class ElemType>
LinkList<ElemType> &LinkList<ElemType>::operator =(const LinkList<ElemType> &copy)
{
    if(&copy!=this)
    {
        int copyLength=copy.Length();
        ElemType e;
        for(int curPosition=1;curPosition<=copyLength;curPosition++)
        {
            copy.GetElem(curPosition, e);
            Insert(Length()+1, e);
        }
    }
    return *this;
}

ostream &operator <<(ostream &outStream, const VehicleType &vehicle); // 重载输出运算符<<*/
class StoppingPlace
{
private:
// 停车场类地数据成员:
LinkStack<VehicleType> *pStopPath;// 停车场地停车道
LinkList<VehicleType> *pShortcutPath;// 便道
int maxNumOfStopVehicle;// 停车场地停车道停放车辆地最大数
int rate;// 停单位时间地收费值
bool ExistVehicleInStopPath(const VehicleType &vehicle) const;
int LocateInpShortcutPath(const VehicleType &vehicle) const;
public:
//  方法声明及重载编译系统默认方法声明:
StoppingPlace(int n, int r);// 构造函数
virtual ~StoppingPlace();// 析构函数
void DisplayStatus() const;// 显示停车道与便道中车辆状态
void Arrive(const VehicleType &vehicle);//处理车辆到达地情形
void Leave(const VehicleType &vehicle);//处理车辆离开地情形
};
//停车场类及相关函数地实现部分

 /*ostream &operator <<(ostream &outStream, const VehicleType &vehicle)
//操作结果:重载输出运算符＜＜
{

    cout <<"("<<vehicle.num<<"," << vehicle.time <<")";
//输出车辆编号与到达时间
    return outStream;
}*/

bool StoppingPlace::ExistVehicleInStopPath(const VehicleType &vehicle)const
{
    VehicleType ve;
    LinkStack<VehicleType> tmpS;
    bool found = false;
    while(!pStopPath->Empty()&&!found)
    {
        pStopPath->Pop(ve);
        tmpS.Push(ve);
        if(vehicle.num == ve.num)
        {
            found = true;
        }
    }
    while(!tmpS.Empty())
    {
        tmpS.Pop(ve);
        pStopPath->Push(ve);

    }
return found;
}

int StoppingPlace::LocateInpShortcutPath(const VehicleType &vehicle)const
{
VehicleType ve;
for(int pos=1;pos<=pShortcutPath->GetElem(pos,ve);pos++)
{
    if(vehicle.num==ve.num)
    {
        return pos;
    }
}
return 0;
}

StoppingPlace::StoppingPlace(int n,int r)
{
pStopPath=new LinkStack<VehicleType>;
pShortcutPath=new LinkList<VehicleType>;
maxNumOfStopVehicle=n;
rate=r;
}

StoppingPlace::~StoppingPlace()
{
delete pStopPath;
delete pShortcutPath;
}

void StoppingPlace::DisplayStatus() const
{
cout<<"停车到中的车辆：";
pStopPath->Traverse(Write);
cout<<endl;
cout<<"便道中的车辆：";
pShortcutPath->Traverse(Write);
cout<<endl<<endl;
}

void StoppingPlace::Arrive(const VehicleType &vehicle)
{
    if(!ExistVehicleInStopPath(vehicle))
    {
        if(pStopPath->Length()<maxNumOfStopVehicle)
        {
            pStopPath->Push(vehicle);
        }
        else
        {
            pShortcutPath->Insert(pShortcutPath->Length()+1,vehicle);
        }
    }
    else{
        cout<<"已存在该编号的车辆，请重新输入！"<<endl;
    }
}

void StoppingPlace::Leave(const VehicleType &vehicle)
{
LinkStack<VehicleType> tmpS;
VehicleType ve;
if(ExistVehicleInStopPath(vehicle))
{
    for(pStopPath->Pop(ve);vehicle.num!=ve.num;pStopPath->Pop(ve))
    {
        tmpS.Push(ve);
    }
    cout<<"在停车道中存在编号为"<<vehicle.num<<"的车辆"<<endl;
    cout<<"此车将离开，应收停车费"<<(vehicle.time-ve.time)*rate<<"元"<<endl;
    while(!tmpS.Empty())
    {
        tmpS.Pop(ve);
        pStopPath->Push(ve);
    }
    if(!pShortcutPath->Empty())
    {
        pShortcutPath->Delete(1,ve);
        pStopPath->Push(ve);
    }
}
else if(LocateInpShortcutPath(vehicle)!=0)
{
int pos=LocateInpShortcutPath(vehicle);
cout<<"在便道中存在编号为"<<vehicle.num<<"的车辆"<<endl;
cout<<"此车将离开，不收取停车费"<<endl;
pShortcutPath->Delete(pos,ve);
}
else
{
cout<<"在停车道与便道中不存在编号为"<<vehicle.num<<"的车辆"<<endl;
}
}

int main()
{
    cout<<"输入停车道停车辆的最大数与停单位时间的收费：";
    int maxNumOfStop,cost;
    char ch;
    cin>>maxNumOfStop>>cost;
    StoppingPlace PtrStopping(maxNumOfStop,cost);
    /*cout<<"1.车辆到达"<<endl<<"2.车辆离开"<<endl<<"3.显示状态"<<endl<<"4.结束"<<endl<<"选择功能："<<endl;
while(1)
{
    int i;
    cin>>i;
    switch(i)
    {
        case 1:
            cout<<"输入车辆编号与到达时间：";
            VehicleType new_ve;
            cin>>new_ve.num>>new_ve.time;
            PtrStopping.Arrive(new_ve);
            cout<<"1.车辆到达"<<endl<<"2.车辆离开"<<endl<<"3.显示状态"<<endl<<"4.结束"<<endl<<"选择功能："<<endl;
            break;
        case 2:
            cout<<"输入车辆编号与离开时间：";
            VehicleType new_ve2;
            cin>>new_ve2.num>>new_ve2.time;
            PtrStopping.Leave(new_ve2);
            cout<<"1.车辆到达"<<endl<<"2.车辆离开"<<endl<<"3.显示状态"<<endl<<"4.结束"<<endl<<"选择功能："<<endl;
            break;
        case 3:
            PtrStopping.DisplayStatus();
            cout<<"1.车辆到达"<<endl<<"2.车辆离开"<<endl<<"3.显示状态"<<endl<<"4.结束"<<endl<<"选择功能："<<endl;
            break;
        case 4:
            exit(0);
    }
}
return 0;*/
    while(1)
    {
        cout<<"1.车辆到达"<<endl<<"2.车辆离开"<<endl<<"3.显示状态"<<endl<<"4.结束"<<endl<<"请选择功能（1-4）："<<endl;
        cin>>ch;
            switch(ch)
                    {
                        case '1':
                            cout<<"输入车辆编号与到达时间：";
                            VehicleType new_ve;
                            cin>>new_ve.num>>new_ve.time;
                            PtrStopping.Arrive(new_ve);
                            break;
                        case '2':
                            cout<<"输入车辆编号与离开时间：";
                            VehicleType new_ve2;
                            cin>>new_ve2.num>>new_ve2.time;
                            PtrStopping.Leave(new_ve2);
                            break;
                        case '3':
                            PtrStopping.DisplayStatus();
                            break;
                        case '4':
                            exit(0);
                    }
        
    }
     return 0;
}
        


//  电话客户服务模拟
#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

struct CustomerType
{
    unsigned int arrivalTime;//客户到达时间
    unsigned int duration;//客户接受服务所需的时间
    unsigned int curServiceTime;//当前接受服务的时间
};

enum StatusCode{ SUCCESS, fail, UNDER_FLOW, UNFER_FLOW };

void SetRandSeed()
{
    srand((unsigned)time(NULL));
}

int GetPoissionRand(double value)
{
    double x=rand()/(double)(RAND_MAX+1.0);//x均匀分布于【0，1）
    int k=0;
    double p=exp(-value);
    double s=0;
    while(s<=x)
    {
        s+=p;
        k++;
        p=p*value/k;
    }
    return k-1;//k-1服从期望为value的泊松分布
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

/*template<class ElemType>
class LinkQueue
{
protected:
    Node<ElemType> *front,*rear;
    void Init();
public:
    LinkQueue();
    virtual ~LinkQueue();
    int Length() const;
    bool Empty() const;
    void Clear();
    StatusCode OutQueue(ElemType &e);
    StatusCode GetHead(ElemType &e) const;
    StatusCode InQueue(const ElemType &e);
};

template<class ElemType>
void LinkQueue<ElemType>::Init()
{
    rear=front=new Node<ElemType>;
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue()
{
    Init();
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue()
{
    Clear();
}

template<class ElemType>
int LinkQueue<ElemType>::Length() const
{
    int count=0;
    for(Node<ElemType> *tmpPtr=front->next;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
    {
        count++;
    }
    return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::Empty() const
{
    return rear==front;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear()
{
    ElemType tmpElem;
    while(Length()>0)
    {
        OutQueue(tmpElem);
    }
}

template<class ElemType>
StatusCode LinkQueue<ElemType>::OutQueue(ElemType &e)
{
    if(!Empty())
    {
        Node<ElemType> *tmpPtr=front->next;
        e=tmpPtr->data;
        front->next=tmpPtr->next;
        if(rear==tmpPtr)
        {
            rear=front;
        }
        delete tmpPtr;
        return SUCCESS;
    }
    else
    {
        return UNDER_FLOW;
    }
}

template<class ElemType>
StatusCode LinkQueue<ElemType>::GetHead(ElemType &e) const
{
    if(!Empty())
    {
        Node<ElemType> *tmpPtr=front->next;
        e=tmpPtr->data;
        return SUCCESS;
    }
    else
    {
        return UNDER_FLOW;
    }
}

template<class ElemType>
StatusCode LinkQueue<ElemType>::InQueue(const ElemType &e)
{
    Node<ElemType> *tmpPtr=new Node<ElemType>(e);
    rear->next=tmpPtr;
    rear=tmpPtr;
    return SUCCESS;
}*/

template<class ElemType>
class LinkQueue
{
protected:
    Node<ElemType> *front,*rear;
    int count;
public:
    LinkQueue();
    virtual ~LinkQueue();
    int Length()const;
    bool Empty()const;
    void Clear();
    bool InQueue(const ElemType &e);
    bool OutQueue(ElemType &e);
    bool GetHead(ElemType &e) const;
    void Traverse(void(*visit)(const ElemType &))const;
    LinkQueue(const LinkQueue<ElemType> &copy);
    LinkQueue<ElemType> &operator=(const LinkQueue<ElemType> &copy);
};
template<typename ElemType>
//构造一个空队列；
LinkQueue<ElemType>::LinkQueue()
{
    front=rear=new Node<ElemType>;
    count=0;
}
template<typename ElemType>
//虚虚构函数
LinkQueue<ElemType>::~LinkQueue()
{
    Clear();
}
template<typename ElemType>
//返回队列长度
int LinkQueue<ElemType>::Length()const
{
    return count;
}
template<typename ElemType>
//判断队列为空
bool LinkQueue<ElemType>::Empty()const
{
    return count==0;
}
template<typename ElemType>
//清除队列
void LinkQueue<ElemType>::Clear()
{
    ElemType tmpElem;
    while(!Empty())
        OutQueue(tmpElem);
}
template<typename ElemType>
//队尾进队
bool LinkQueue<ElemType>::InQueue(const ElemType &e)
{
    Node<ElemType> *tmpPtr=new Node<ElemType>(e);
    rear->next=tmpPtr;
    rear=tmpPtr;
    count++;
    return true;

}
template<typename ElemType>
//队头出队
bool LinkQueue<ElemType>::OutQueue(ElemType &e)
{
    if(!Empty())
    {
        Node<ElemType> *tmpPtr=front->next;
        e=tmpPtr->data;
        front->next=tmpPtr->next;
        if(rear==tmpPtr)
            rear=front;
        delete tmpPtr;
        count--;
        return true;
    }
    else
        return false;
}
template<typename ElemType>
//返回队头元素
bool LinkQueue<ElemType>::GetHead(ElemType &e) const
{
    if(!Empty())
    {
        e=front->next->data;
        return true;
    }
    else
        return false;

}
template<typename ElemType>
//visit
void LinkQueue<ElemType>::Traverse(void(*visit)(const ElemType &))const
{
    for(Node<ElemType> *tmpPtr=front->next;tmpPtr;tmpPtr=tmpPtr->next)
        (*visit)(tmpPtr->data);
}
template<typename ElemType>
//复制构造
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy)
{
    rear=front=new Node<ElemType>;
    count=0;
    for(Node<ElemType> *tmpPtr=copy.front->next;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
        Inqueue(tmpPtr->data);
}
template<typename ElemType>
//重载=operator
LinkQueue<ElemType> &LinkQueue<ElemType>::operator=(const LinkQueue<ElemType> &copy)
{
    if(&copy!=this)
    {
        Clear();
        for(Node<ElemType> *tmpPtr=copy.front->next;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
            Inqueue(tmpPtr->data);
        return *this;
    }
}

class CallSimulation
{
private:
    LinkQueue<CustomerType> *callsWaitingQueue;//客服电话等待队列
    CustomerType *customerServed;//客户服务人员正在服务的客户
    unsigned int curTime;//当前时间
    unsigned int totalWaitingTime;//总客户等待时间
    unsigned int numOfCalls;//处理的电话数
    unsigned int numOfCustomerServiceStaffs;//客户服务人员的人数
    unsigned int limitTime;//时间限制（不再接受更多电话）
    double arrivalRate;//客户到达率
    double averageServiceTime;//平均服务时间
    //辅助函数
    void Service();//服务当前电话（如果有电话）
    void CheckForNewCall();//检查是否有新电话，如果有，则将电话添加到电话队列
    void Display();//显示模拟结果
    int GetNumOfWaitingCall();//得到电话队列中等待的电话数
    int MinLengthCallWaitingQueue();//最短客户服务电话等待队列
    //电话客户服务模拟类方法声明
public:
    CallSimulation();//无参数构造函数
    virtual ~CallSimulation();//析构函数
    void Run();//模拟电话客户服务
};

CallSimulation::CallSimulation()
{
    curTime=0;
    totalWaitingTime=0;
    numOfCalls=0;
    cout<<"输入客服人员人数：";
    cin>>numOfCustomerServiceStaffs;
    cout<<"输入时间限制：";
    cin>>limitTime;
    int callsPerHour;//每小时电话数
    cout<<"输入每小时电话数：";
    cin>>callsPerHour;
    arrivalRate=callsPerHour/60.0;
    cout<<"输入平均服务时间：";
    cin>>averageServiceTime;
    callsWaitingQueue=new LinkQueue<CustomerType>[numOfCustomerServiceStaffs];
    customerServed=new CustomerType[numOfCustomerServiceStaffs];
    for(int i=0;i<numOfCustomerServiceStaffs;i++)
    {
        customerServed[i].curServiceTime=customerServed[i].duration=0;
    }
    SetRandSeed();
}

CallSimulation::~CallSimulation()
{
    delete callsWaitingQueue;
    delete customerServed;
}

void CallSimulation::Service()
{
    for(int i=0;i<numOfCustomerServiceStaffs;i++)
    {
        if(customerServed[i].curServiceTime<customerServed[i].duration)
        {
            customerServed[i].curServiceTime++;
        }
        else
        {
            if(!callsWaitingQueue[i].Empty())
            {
                callsWaitingQueue[i].OutQueue(customerServed[i]);
                totalWaitingTime+=curTime-customerServed[i].arrivalTime;
            }
        }
    } 
}

void CallSimulation::CheckForNewCall()
{
    int calls=GetPoissionRand(arrivalRate);
    for(int i=1;i<=calls;i++)
    {
        CustomerType customer;
        customer.arrivalTime=curTime;
        customer.duration=GetPoissionRand(averageServiceTime);
        customer.curServiceTime=0;
        int pos=MinLengthCallWaitingQueue();
        callsWaitingQueue[pos].InQueue(customer);
        numOfCalls++;
    }
}

void CallSimulation::Display()
{
    cout<<"处理的电话总数："<<numOfCalls<<endl;
    cout<<"平均等待时间："<<(double)totalWaitingTime/numOfCalls<<endl<<endl;
}

int CallSimulation::MinLengthCallWaitingQueue()
{
    int min=callsWaitingQueue[0].Length();
    for(int i=0;i<numOfCustomerServiceStaffs;i++)
    {
        if(callsWaitingQueue[i].Length()>min)
        {
            min=callsWaitingQueue[i].Length();
        }
    }
    return min;
}

void CallSimulation::Run()
{
    while(curTime<limitTime)
    {
        CheckForNewCall();
        Service();
        curTime++;
    }
    while(MinLengthCallWaitingQueue()>0)
    {
        Service();
        curTime++;
        
    }
    Display();
}

int main() {
    char ch='y';
    CallSimulation call;
    while(ch=='y')
    {
        call.Run();
        cout<<"是否继续(y/n)?";
        cin>>ch;
    }
    return 0;
}

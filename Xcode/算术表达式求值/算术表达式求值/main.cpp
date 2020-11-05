//中缀表达式求值
#include <iostream>
#include<math.h>
using namespace std;

enum StatusCode{ SUCCESS, fail, UNDER_FLOW, UNFER_FLOW };
class Error :public std::logic_error{
public:
    Error(const std::string &s) :std::logic_error(s){}
    virtual ~Error() throw(){}
};

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
    StatusCode push(const ElemType &e);//往堆栈中传入元素
    StatusCode pop(ElemType &e);//删除堆栈的栈顶元素
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
        pop(tmpElem);
}

template<class ElemType>
StatusCode LinkStack<ElemType>::push(const ElemType &e){
    //向堆栈中添加元素
    Node<ElemType>*new_top = new Node<ElemType>(e, top);
    if (new_top == NULL)
    {
        return UNFER_FLOW;
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
StatusCode LinkStack<ElemType>::pop(ElemType &e){
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

template<class ElemType>
class Calculator{
private:
    //计算器的数据成员
    LinkStack<ElemType> opnd;//操作数栈
    LinkStack<char> optr;//操作符栈
    //辅助函数模板
    int OperPrior(char op);//操作符优先级
    void Get2Operands(ElemType &left, ElemType &right);//从栈opnd中退出两个操作数
    ElemType Operate(ElemType left, char op, ElemType right);//执行运算left op right
    bool IsOperator(char ch);//判断ch是否为操作符
 
public:
    //计算器类方法声明
    Calculator(){};//无参数的构造函数
    virtual ~Calculator(){};//析构函数
    char GetChar();//读取字符
    void Run();//运算表达式
};

template<class ElemType>
int Calculator<ElemType>::OperPrior(char op)
{
    switch(op)
    {
        case'=':
            return 1;
            break;
        case')':
        case'(':
            return 2;
            break;
        case'+':
        case'-':
            return 3;
            break;
        case'*':
        case'/':
        case'%':
            return 4;
            break;
        case'^':
            return 5;
            break;
        default:
            return -1;
            break;
    }
}

template<class ElemType>
void Calculator<ElemType>::Get2Operands(ElemType &left, ElemType &right)
{
    if (opnd.pop(right) == UNDER_FLOW) throw Error("表达式有错！");//抛出异常
    if (opnd.pop(left) == UNDER_FLOW) throw Error("表达式有错！");//抛出异常

}

template<class ElemType>
ElemType Calculator<ElemType>::Operate(ElemType left, char op, ElemType right){
    //执行left op right
    if(op=='+')
    {
        return left + right;
    }
    if(op=='-')
    {
        return left - right;
    }
    if(op=='*')
    {
        return left * right;
    }
    if(op=='/')
    {
        if (right == 0)
        {
            cout << "Error!除数为0！"<<endl;
        }
        return left / right;
    }
    if(op=='%')
    {
        return int(left) % int(right);
    }
    if(op=='^')
    {
        return pow(left, right);
    }
    else
        return -1;
}

template<class ElemType>
bool Calculator<ElemType>::IsOperator(char ch){
    //判断是否为操作符
    return (ch == '=' || ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^');
}

template <class ElemType>
char Calculator<ElemType>::GetChar(){
    char ch;
    cin >> ch;
    while (ch == ' ' || ch == '\n' || ch == '\t')
        cin >> ch;
    return ch;
}

template <class ElemType>
void Calculator<ElemType>::Run(){
    //操作结果：运算表达式
    optr.Clear();
    opnd.Clear();//清空optr和opnd栈
    optr.push('=');//在optr栈中加入一个‘=’
    char ch;//临时字符
    char priorChar;//当前输入的前一个字符，如不为操作符,设其值为‘0’
    char optrTop;//临时optr栈的栈顶字符
    ElemType operand;//操作数
    char op;//操作符
 
    priorChar = '=';//前一个字符
    ch = GetChar();//读入一个字符
    if (optr.Top(optrTop) == UNDER_FLOW) throw Error("表达式有错!");//抛出异常
    //取出optr的栈顶
    while (optrTop != '=' || ch != '='){
        //当前表达式还未运算结束，继续运算
        if (isdigit(ch) || ch == '.'){
            //ch为一个操作数的第一个字符
            cin.putback(ch);//将字符ch放回输入流
            cin >> operand;//读入操作数
            opnd.push(operand);//操作数入opnd栈
            priorChar = '0';
            ch = GetChar();
        }
        else if (!IsOperator(ch)){
            //既不是操作符，也不属于操作数
            throw Error("表达式有错!");//抛出异常
        }
        else{
            //ch为操作符
            if ((priorChar == '=' || priorChar == '(') && (ch == '+' || ch == '-')){
                opnd.push(0);//ch为单目运算符+、-，在其前面加上操作数0
                priorChar = '0';//前一个字符不是操作数，规定前一字符为0
            }
            if ((optrTop == ')'&&ch == '(') || (optrTop == '('&&ch == '=') || (optrTop == '='&&ch == ')'))
                throw Error("表达式有错！");
            else if (optrTop == '('&&ch == ')'){
                //去括号
                if (optr.pop(optrTop) == UNDER_FLOW)
                    throw Error("表达式有错!");
                ch = GetChar();//读入新字符
                priorChar = ')';//新的前一字符为）
            }
            else if (ch == '(' || OperPrior(optrTop) < OperPrior(ch)){
                //optrTop为(,或optrTop比ch的优先级还低
                optr.push(ch);//ch入optr栈
                priorChar = ch;//新的前一字符为ch
                ch = GetChar();//读入新字符
            }
            else{
                //optrTop的大于或等于ch的优先级
                if (optr.pop(op) == UNDER_FLOW)
                    throw Error("表达式有错！");
                ElemType left, right;//操作数
                Get2Operands(left, right);//从opnd栈中取操作数
                opnd.push(Operate(left, op, right));//运算结果入opnd栈
                //Operate(left, op, right);
            }
        }
        if (optr.Top(optrTop) == UNDER_FLOW)
            throw Error("表达式有错！");
    }
    if (opnd.Top(operand) == UNFER_FLOW)
        throw Error("表达式有错!");
    cout << operand << endl;//显示表达式的值
}

int main()
{
    Calculator<double> cal;
    char c = 'y' ;
    while (c == 'Y'||c == 'y'){
        cout<<"注意输入等号要把左右两个输完整！"<<endl;
        cout << "输入表达式(注意以等号结束):" << endl;
        cal.Run();
        cout << "是否继续(Y/N):" << endl;
        cin >> c;
        //iscontinue = toupper(iscontinue);
    }
    return 0;
}

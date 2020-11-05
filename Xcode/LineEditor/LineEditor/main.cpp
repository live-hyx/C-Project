// 简单文本编辑器
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
enum StatusCode{ SUCCESS, fail, UNDER_FLOW, UNFER_FLOW ,RANGE_ERROR , ENTRY_FOUND};
template<class ElemType>
struct DblNode
{
    ElemType data;
    DblNode<ElemType> *back; DblNode<ElemType> *next;
    DblNode();
    DblNode(ElemType,DblNode<ElemType>*linkBack=NULL,DblNode<ElemType> *linkNext=NULL);
    
};

template<class ElemType>
DblNode<ElemType>::DblNode()
{
    next=NULL;
    
}
template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item,DblNode<ElemType> *linkBack,DblNode<ElemType> *linkNext)
{
    data=item;
    back=linkBack;
    next=linkNext;
}
template<class ElemType>
class DblLinkList
{
protected:
    DblNode<ElemType> *head;
    mutable int curPosition;
    mutable DblNode<ElemType> *curPtr; int count;
    DblNode<ElemType> *GetElemPtr(int position) const;
    void Init(); public:
    DblLinkList();
    virtual ~DblLinkList();
    int Length() const;
    bool Empty() const;
    void Clear();
    void Traverse(void (*visit)(const ElemType &)) const;
    StatusCode GetElem(int position,ElemType &e) const;
    StatusCode SetElem(int position,const ElemType &e);
    StatusCode Delete(int position,ElemType &e);
    StatusCode Insert(int position,const ElemType &e);
};
template<class ElemType>
DblNode<ElemType> *DblLinkList<ElemType>::GetElemPtr(int position) const
{
    if(curPosition<position)
    {
        for(;curPosition<position;curPosition++)
        {
            curPtr=curPtr->next;
            
        }
    }
    else if(curPosition>position)
    {
        for(;curPosition>position;curPosition--)
        {
            curPtr=curPtr->back;
            
        }
    }
    return curPtr;
    
}
template<class ElemType>
void DblLinkList<ElemType>::Init()
{
    head=new DblNode<ElemType>;
    head->next=head;
    curPtr=head;
    curPosition=0;
    count=0;
}
template<class ElemType> DblLinkList<ElemType>::DblLinkList()
{
    Init();
    
}
template<class ElemType> DblLinkList<ElemType>::~DblLinkList()
{
    Clear();
    delete head;
    
}
template<class ElemType>
int DblLinkList<ElemType>::Length() const
{
    return count;
    
}
template<class ElemType>
bool DblLinkList<ElemType>::Empty() const
{
    return head->next==head;
    
}
template<class ElemType>
void DblLinkList<ElemType>::Clear()
{
    ElemType tmpElem;
    while(Length()>0)
    {
        Delete(1, tmpElem);
        
    }
}
template<class ElemType>
void DblLinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
{
    for(DblNode<ElemType> *tmpPtr=head->next;tmpPtr!=head;tmpPtr=tmpPtr->next)
    {
        
        (*visit)(tmpPtr->data);
        
    }
}
template<class ElemType>
StatusCode DblLinkList<ElemType>::GetElem(int position, ElemType &e) const
{
    if(position<1||position>Length())
    {
        return RANGE_ERROR;
        
    }
    else
    {
        DblNode<ElemType> *tmpPtr;
        tmpPtr=GetElemPtr(position);
        e=tmpPtr->data;
        return ENTRY_FOUND;
    }
}
template<class ElemType>
StatusCode DblLinkList<ElemType>::SetElem(int position, const ElemType &e)
{
    if(position<1||position>Length())
    {
        return RANGE_ERROR;
        
    }
    else
    {
        DblNode<ElemType> *tmpPtr;
        tmpPtr=GetElemPtr(position);
        tmpPtr->data=e;
        return SUCCESS;
    }
    
}
template<class ElemType>
StatusCode DblLinkList<ElemType>::Insert(int position, const ElemType &e)
{
    if(position<1||position>Length()+1)
    {
        return RANGE_ERROR;
        
    }
    
    else
    {
        DblNode<ElemType> *tmpPtr,*nextPtr,*newPtr;
        tmpPtr=GetElemPtr(position-1);
        nextPtr=tmpPtr->next;
        newPtr=new DblNode<ElemType> (e,tmpPtr,nextPtr);
        tmpPtr->next=newPtr;
        nextPtr->back=newPtr;
        curPosition=position;
        curPtr=newPtr;
        count++;
        return SUCCESS;
        
    }
}
template<class ElemType>
StatusCode DblLinkList<ElemType>::Delete(int position, ElemType &e)
{
    if(position<1||position>Length())
    {
        return RANGE_ERROR;
        
    }
    else
    {
        DblNode<ElemType> *tmpPtr;
        tmpPtr=GetElemPtr(position);
        tmpPtr->back->next=tmpPtr->next;
        tmpPtr->next->back=tmpPtr->back;
        e=tmpPtr->data;
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
        delete tmpPtr; return SUCCESS;
    }
}

class String
{
protected:
    mutable char *strVal;
    int length; public:
    String();
    virtual ~String();
    String(const String &copy);
    String(const char *copy);
    String(DblLinkList<char> &copy);
    int Length() const;
    bool Empty() const;
    String &operator= (const String &copy);
    const char *CStr() const;
    char &operator [](int pos) const;
};
String::String()
{
    length=0;
    strVal=NULL;
    
}
String::~String()
{
    delete []strVal;
    
}
String::String(const String &copy)
{
    length=(int)strlen(copy.CStr());
    strVal=new char[length+1];
    strcpy(strVal,copy.CStr());
}
String::String(const char *copy)
{
    length=int(strlen(copy));
    strVal=new char[length+1];
    strcpy(strVal,copy);
    
}
String::String(DblLinkList<char> &copy)
{
    length=copy.Length();
    strVal=new char[length+1];
    for(int i=0;i<length;i++)
    {
        copy.GetElem(i+1, strVal[i]);
        
    }
    strVal[length]='\0';
    
}
int String::Length() const
{
    return length;
    
}
bool String::Empty() const
{
    return length==0;
    
}
String &String::operator=(const String &copy)
{
    if(&copy!=this)
    {
        delete []strVal;
        length=(int)strlen(copy.CStr());
        strVal=new char[length+1];
        strcpy(strVal,copy.CStr());
    }
    return *this;
    
}
const char *String::CStr() const
{
    return (const char *)strVal;
    
}
char &String::operator [](int pos) const
{
    return strVal[pos];
}
void Concat(String &addTo,const String &addOn)
{
    const char *cFirst=addTo.CStr();
    const char *cSecond=addOn.CStr();
    char *copy=new char[strlen(cFirst)+strlen(cSecond)+1];
    strcpy(copy,cFirst);
    strcat(copy,cSecond);
    addTo=copy;
    delete []copy;
}
String Read(istream &input)
{
    DblLinkList<char> temp;
    int size=0;
    char c;
    while((c=input.peek())!=EOF&&(c=input.get())!='\n')
    {
        temp.Insert(++size, c);
        
    }
    String answer(temp);
    return answer;
    
}
String Read(istream &input,char &terminalChar)
{
    DblLinkList<char> temp;
    int size=0;
    char c;
    while((c=input.peek())!=EOF&&(c=input.get())!='\n')
    {
        temp.Insert(++size, c);
        
    }
    terminalChar=c;
    String answer(temp);
    return answer;
}
void Write(const String &s)
{
    cout<<s.CStr()<<endl;
}
void Copy(String &copy,const String &original)
{
    const char *cOriginal=original.CStr();
    char *cCopy=new char[strlen(cOriginal)+1];
    strcpy(cCopy,cOriginal);
    copy=cCopy;
    delete []cCopy;
}
void Copy(String &copy,const String &original,int n)
{
    const char *cOriginal=original.CStr();
    int len=(int)strlen(cOriginal)<n?(int)strlen(cOriginal):n;
    char *cCopy=new char[len+1];
    strncpy(cCopy,cOriginal,n);
    copy=cCopy;
    delete []cCopy;
}
int Index(const String &target,const String &pattern,int pos=0)
{
    const char *cTarget=target.CStr();
    const char *cPattern=pattern.CStr();
    const char *ptr=strstr(cTarget+pos,cPattern);
    if(ptr==NULL)
    {
        return -1;
        
    }
    else
    {
        return int(ptr-cTarget);
        
    }
}
String SubString(const String &s,int pos,int len)
{
    if(pos>=0&&pos<s.Length()&&len>=0)
    {
        len=(len<s.Length()-pos)?len:(s.Length()-pos);
        char *sub=new char[len+1];
        const char *str=s.CStr();
        strncpy(sub,str+pos,len); sub[len]='\0';
        String tem(sub);
        return tem;
    }
    else
    {
        String tem("");
        return tem;
        
    }
}
bool operator ==(const String &first,const String &second) {
    return strcmp(first.CStr(),second.CStr())==0; }
bool operator <(const String &first,const String &second) {
    return strcmp(first.CStr(),second.CStr())<0; }
bool operator >(const String &first,const String &second) {
    return strcmp(first.CStr(),second.CStr())>0; }
bool operator <=(const String &first,const String &second) {
    return strcmp(first.CStr(),second.CStr())<=0; }
bool operator >=(const String &first,const String &second) {
    return strcmp(first.CStr(),second.CStr())>=0; }
bool operator !=(const String &first,const String &second) {
    return strcmp(first.CStr(),second.CStr())!=0; }
char GetChar() // 从输入流in中跳过空格及制表符获取一字符
{
    istream &in=cin;
    char ch; // 临时变量
    while ((ch = in.peek()) != EOF&& ((ch = in.get()) == ' '|| ch == '\t' ));
    return ch;
}
class LineEditor {
private:
    DblLinkList<String> textBuffer;//文本缓存
    int curLineNo;//当前行号
    DblLinkList<String> textUndoBuffer;//用于恢复的文本缓存
    int curUndoLineNo;//用于恢复的当前行号
    ifstream inFile;//输入文件
    ofstream outFile;//输出文件
    string outFileStr;
    string inFileStr;
    StatusCode NextLine();//转到下一行
    StatusCode PreviousLine();//转到上一行
    StatusCode GotoLine();//转到指定行
    StatusCode InsertLine();//插入一行
    void ChangeLine();//替换当前行或所有行的指定文本串
    void ReadFile();//读入文本文件
    void WriteFile();//写文本文件
    void FindString();//查找串
public:
    LineEditor(string infName,string outfName);//构造函数
    void Run();//运行
};
LineEditor::LineEditor(string infName, string outfName)//构造函数，读入文件赋给文本缓存
{
    curUndoLineNo=curLineNo = 1;
    outFileStr=outfName;
    inFile.open(infName.c_str());
    assert(inFile.is_open());
    String s;
    String Read(s);
    inFile.close();
}

StatusCode LineEditor::NextLine()
{
    if(curLineNo+1<=textBuffer.Length())
    {
        curLineNo++;
        return SUCCESS;
        
    }
    else
    {
        return fail;
        
    }
}
StatusCode LineEditor::PreviousLine()
{
    if(curLineNo>1)
    {
        curLineNo--;
        return SUCCESS;
        
    }
    else
    {
        return fail;
        
    }
}
StatusCode LineEditor::GotoLine()
{
    int enLine;
    cout << "输入行号:";
    cin >> enLine;
    if(enLine<=textBuffer.Length())
    {
        curLineNo = enLine;
        return SUCCESS;
        
    }
    else
    {
        return fail;
        
    }
}

StatusCode LineEditor::InsertLine()
{
    int enLine;
    String c;
    cout << "输入行号:";
    cin >> enLine;
    cout << "插入:";
    String Read(c);
    if(enLine<=textBuffer.Length())
    {
        textBuffer.Insert(enLine, c);
        return SUCCESS;
        
    }
    else
    {
        return fail;
        
    }
}
void LineEditor::ReadFile()//读入一个新的文本文件到文本缓存内
{
    string infStr = "";
    do
    {
        cout << "请输入要读取的文本文件名:";
        getline(std::cin, infStr);
    } while (infStr == "");
    outFileStr=inFileStr=infStr;
    ifstream inFile(infStr.c_str(), ios::in);
    assert(inFile.is_open());
    String s;
    String Read(s);
    inFile.close();
}
void LineEditor::WriteFile()//将文本缓存写入文件内
{
    int function = 0;
    do
    {
        std::cout << "\n想在文件尾添加新内容还是重写文件?--1:添加--2:重写--:";
        std::cin >> function;
    } while (function != 1 && function != 2);
    if (function == 1)
        outFile.open(outFileStr.c_str(), ios::app);
    else
        outFile.open(outFileStr.c_str(), ios::out);
    assert(outFile.is_open()); String c;
    string tmpString;
    int i=1;
    while(i<=textBuffer.Length())
    {
        textBuffer.GetElem(i,c);
        tmpString=c.CStr();
        if(i!=textBuffer.Length())
            outFile<<tmpString<<"\n";
        else
            outFile<<tmpString; i++;
    }
    outFile.close();
    
}
void LineEditor::ChangeLine() {
    char answer;
    bool initialResponse=true;
    do
    {
        if(initialResponse)
        {
            cout<<"替换当前行c(urrent)或替换所有行a(ll):";
            
        }
        else
        {
            cout<<"用c或a回答";
            
        }
        answer=GetChar();
        while(cin.get()!='\n');
        answer=tolower(answer);
        initialResponse=false;
    }while(answer!='c'&&answer!='a');
    cout<<"输入要被替换的指定文本串:";
    String strOld=Read(cin);
    cout<<"输入新文本串:";
    String strNew=Read(cin);
    for(int row=1;row<=textBuffer.Length();row++)
    {
        
        if(answer=='c'&&row!=curLineNo)
        {
            continue;
            
        }
        String strRow;
        textBuffer.GetElem(row, strRow);
        int index=Index(strRow, strOld);
        if(index!=-1)
        {
            String newLine;
            Copy(newLine, strRow, index);
            Concat(newLine, strNew);
            const char *oldLine=strRow.CStr();
            Concat(newLine, (String)(oldLine+index+strlen(strOld.CStr())));
            textBuffer.SetElem(row, newLine);
        }
        
    }
}
void LineEditor::FindString()
{
    char answer;
    bool initialResponse=true;
    do
    {
        if(initialResponse)
        {
            cout<<"从第1行开始f(irst)或从当前行开始c(urrent):";
            
        }
        else
        {
            cout<<"用f或c回答:";
            
        }
        answer=GetChar();
        while(cin.get()!='\n');
        answer=tolower(answer);
        initialResponse=false;
    }
    while(answer!='f'&&answer!='c'); if(answer=='f')
    {
        curLineNo=1;
        
    }
    int index;
    cout<<"输入被查找的文本串:";
    String searchString=Read(cin);
    String curLine;
    textBuffer.GetElem(curLineNo, curLine);
    while((index=Index(curLine, searchString))==-1)
    {
        if(curLineNo<textBuffer.Length())
        {
            curLineNo++;
            textBuffer.GetElem(curLineNo, curLine);
            
        }
        else
        {
            break;
            
        }
    }
    if(index==-1)
    {
        cout<<"查找串失败。";
        
    }
    else
    {
        cout<<curLine.CStr()<<endl;
        for(int i=0;i<index;i++)
        {
            cout<<" ";
            
        }
        for(int j=0;j<(int)strlen(searchString.CStr());j++)
        {
            cout<<"^";
            
        }
    }
    cout<<endl;
    
}
template<class ElemType>
void Swap(ElemType a,ElemType b)
{
    ElemType c; c=a;
    a=b;
    b=c;
}

void LineEditor::Run()
{
    char userCommand;
    do
    {
        String tempString;
        String curLine;
        if(curLineNo!=0)
        {
            textBuffer.GetElem(curLineNo, curLine);
            cout<<curLineNo<<":"<<curLine.CStr()<<endl<<"?";
        }
        else
        {
            cout<<"文件缓存空"<<endl<<"?";
        }
        userCommand=GetChar();
        userCommand=tolower(userCommand);
        while(cin.get()!='\n');
        if(userCommand!='u'&&userCommand!='h'&&userCommand!='?'&&userCommand!='v')
        {
            textUndoBuffer=textBuffer;
            curUndoLineNo=curLineNo;
        }
        switch(userCommand)
        {
            case 'b'://转到第一行
                if(textBuffer.Empty())
                {
                    cout<<"警告:文本缓存空"<<endl;
                    
                }
                else
                {
                    curLineNo=1;
                    
                }
                break;
            case 'c'://替换当前行或所有行
                if(textBuffer.Empty())
                {
                    cout<<"警告:文本缓存空"<<endl;
                    
                }
                
                else
                {
                    ChangeLine();
                    
                }
                break;
            case 'd'://删除当前行
                if(textBuffer.Delete(curLineNo, tempString)!=SUCCESS)
                {
                    cout<<"错误:删除失败"<<endl;
                    
                }
                break;
            case 'e'://转到最后一行
                if(textBuffer.Empty())
                {
                    cout<<"警告:文本缓存空"<<endl;
                    
                }
                else
                {
                    curLineNo=textBuffer.Length();
                    
                }
                break;
            case 'f'://从当前行或第一行开始查找指定文本
                if(textBuffer.Empty())
                {
                    cout<<"警告:文本缓存空"<<endl;
                    
                }
                else
                {
                    FindString();
                    
                }
                break;
            case 'g'://转到指定行
                if(GotoLine()!=SUCCESS)
                {
                    cout<<"警告:没有那样的行"<<endl;
                    
                }
                break;
            case '?':
            case 'h'://获得帮助
                cout<<"有效命令:b(egin) c(hange) d(el) e(nd)"<<endl<<"f(ind) g(o) h(elp) i(nsert) n(ext) p(rior)"<<endl<<"q(uit) r(ead) u(ndo) v(iew) w(rite)"<<endl;
                break;
            case 'i'://插入一行
                if(InsertLine()!=SUCCESS)
                {
                    cout<<"错误:插入行错误"<<endl;
                    
                }
                break;
            case 'n'://转到下一行
                if(NextLine()!=SUCCESS)
                {
                    cout<<"警告:当前行已是最后一行"<<endl;
                    
                }
                break;
            case 'p'://转到上一行
                if(PreviousLine()!=SUCCESS)
                {
                    cout<<"警告:当前行已是最后一行"<<endl;
                    
                }
                break;
            case 'q'://退出
                break;
            case 'r'://读入文件
                ReadFile();
                break;
            case 'u'://撤销上次操作
                Swap(textUndoBuffer,textBuffer);
                Swap(curUndoLineNo,curLineNo);
                break;
            case 'v'://显示文本
                textBuffer.Traverse(Write);
                break;
            case 'w'://写文本缓存到输出文件中
                if(textBuffer.Empty())
                {
                    cout<<"警告:文本缓存空"<<endl;
                    
                }
            else
            {
                WriteFile();
                
            }
            break;
            default:
                cout<<"输入h或?获得帮助或输入有效命令字符:\n"; }
    }
    while(userCommand!='q');
    
}

int main()
{
    string fi,fo;
    cout<<"请输入文件名(默认:file_in.txt):";
    getline(cin,fi);
    cout<<"请输出文件名(默认:file_out.txt):";
    getline(cin,fo);
    if(fi==""||fo=="")
    {
        fi="file_in.txt";
        fo="file_out.txt";
        
    }
    LineEditor *lineeditor= new LineEditor(fi, fo);
    lineeditor->Run();
    delete lineeditor;
    return 0;
}


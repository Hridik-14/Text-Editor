#include <bits/stdc++.h>
using namespace std;
class Textfile
{
    private:
        string file_name;
        stack<string> Undo;
        stack<string> Redo;
        stack<int> redo_input;
        stack<string> Temp;
        vector<int> lines;
        int words=0;
        public:
        char last_el='.';
        int icall=0;
    public:
        Textfile(string s);
        stack<int> input;
        stack<int> ind;
        stack<int> ind_redo;
        stack<int> num_char;
        stack<int> num_char_redo;
        void undo();
        void redo();
        void write(string s);
        void read();
        int  find(string s);
        void insert(string s,int p);
        string getname();
        string gram_check(string s);
};
Textfile::Textfile(string s)
{
    file_name=s;
}
void Textfile::read()
{
    while (!Undo.empty()) 
    {
        Temp.push(Undo.top());
        Undo.pop();
    }
    while (!Temp.empty()) 
    {
        cout << Temp.top();
        Undo.push(Temp.top());
        Temp.pop();
    }
}
void Textfile::undo()
{
    if(input.top() == 1){
        redo_input.push(input.top());
        input.pop();
        Redo.push(Undo.top());
        Undo.pop();
    }
    else{
        num_char_redo.push(num_char.top());
        redo_input.push(input.top());
        input.pop();
        if(ind.top() == 1)
        {
            string ch;
            string temp;
            char t=last_el;
            while (Undo.size()>1) 
            {
                Temp.push(Undo.top());
                Undo.pop();
            }
            ch=Undo.top();
            Undo.pop();
            temp = ch.substr(0,num_char.top());
            Redo.push(temp);
            ch.erase(0,num_char.top());
            last_el='.';
            icall=1;
            write(ch);
            icall=0;
            while (!Temp.empty()) 
            {
                Undo.push(Temp.top());
                Temp.pop();
            }
            last_el=t;
            lines.insert(lines.begin(),0);
        }
        else
        {
            int si=lines.at(ind.top() - 2);
            int i=0;
            string temp;
            for(i=0;i<lines.size();i++)
            {
                if(lines[i]==si)
                break;
            }
            int num=ind.top()-i-1;
            while(Undo.size()!=(si+1))
            {
                Temp.push(Undo.top());
                Undo.pop();
            }
            string ch=Undo.top();
            Undo.pop();
            int index=0;
            int cnt=0;
            while(num!=cnt)
            {
                if(ch[index]=='.')
                cnt++;
                index++;
            }
            char t=last_el;
            last_el='.';
            temp = ch.substr(index, num_char.top());
            Redo.push(temp);
            ch.erase(index, num_char.top());
            last_el=t;
            Undo.push(ch);
            while (!Temp.empty()) 
            {
            Undo.push(Temp.top());
            Temp.pop();
            }
            lines.insert(lines.begin()+(ind.top()-2),si);
        }
        num_char.pop();
        ind_redo.push(ind.top());
        ind.pop();
    }
}
void Textfile::redo()
{       
    if(redo_input.top() == 1){
        string temp00=Redo.top();
        icall=1;
        write(temp00);
        icall=0;
        Redo.pop();
        input.push(redo_input.top());
        redo_input.pop();
    }
    else if(redo_input.top() == 6){
        icall=1;
        insert(Redo.top(), ind_redo.top());
        ind.push(ind_redo.top());
        ind_redo.pop();
        icall=0;
        Redo.pop();
        input.push(redo_input.top());
        redo_input.pop();
        num_char_redo.pop();
    }
    
}
string Textfile::gram_check(string s)
{
    char t=last_el;
    for(int i=0;i<s.length();i++)
    {
        if((last_el=='.' || last_el==(char)10) && (s[i]>96 && s[i]<123))
        s[i]-=32;
        if(s[i]=='i' && last_el==' ' && s[i+1]==' ')
        s[i]-=32;
        if(s[i]==' ' && (last_el==' '))
        s.erase(s.begin() + i--);
        if(last_el==',' && s[i]!=' ')
        s.insert(s.begin() + i,' ');
        if(s[i]==92)
        {
            if(((i+1)<s.length()) && s[i+1]=='n')
            {
            s.erase(s.begin()+i);
            s.erase(s.begin()+i);
            s.insert(s.begin()+i,(char)10);
            }
        }
        last_el=s[i];
    }
    last_el=t;
    return s;
}
void Textfile::write(string s)
{
    s=gram_check(s);
    string check=s;
    while(!Redo.empty() && icall==0){
        Redo.pop();
    }
    while(!redo_input.empty()&& icall==0){
        redo_input.pop();
    }
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='.')
        lines.push_back(Undo.size());
        last_el=s[i];
    }
    Undo.push(s);
    
    words+=s.length();
}
void Textfile::insert(string s,int p)
{
    num_char.push(s.length());
    while(!Redo.empty()&& icall==0){
        Redo.pop();
    }
    while(!redo_input.empty()&& icall==0){
        redo_input.pop();
    }
    if(p==1)
    {
        string ch;
        char t=last_el;
        while (Undo.size()>1) 
        {
            Temp.push(Undo.top());
            Undo.pop();
        }
        ch=Undo.top();
        Undo.pop();
        s=gram_check(s);
        ch.insert(0,s);
        last_el='.';
        icall=1;
        write(ch);
        icall=0;
        while (!Temp.empty()) 
        {
            Undo.push(Temp.top());
            Temp.pop();
        }
        last_el=t;
        lines.insert(lines.begin(),0);
    }
    else
    {
        int si=lines.at(p-2);
        int i=0;
        for(i=0;i<lines.size();i++)
        {
            if(lines[i]==si)
            break;
        }
        int num=p-i-1;
        while(Undo.size()!=(si+1))
        {
            Temp.push(Undo.top());
            Undo.pop();
        }
        string ch=Undo.top();
        Undo.pop();
        int index=0;
        int cnt=0;
        while(num!=cnt)
        {
            if(ch[index]=='.')
            cnt++;
            index++;
        }
        char t=last_el;
        last_el='.';
        s=gram_check(s);
        ch.insert(index,s);
        last_el=t;
        Undo.push(ch);
        while (!Temp.empty()) 
        {
        Undo.push(Temp.top());
        Temp.pop();
        }
        lines.insert(lines.begin()+(p-2),si);
    }
}
int Textfile::find(string s)
{
   int j = 0, k = 0, nP = 0, count = 0;
    string S;
    vector<int> P;
    
    while(!Undo.empty()){
        Temp.push(Undo.top());
        Undo.pop();
    }
    
    while(!Temp.empty()){
        S.append(Temp.top());
        Undo.push(Temp.top());
        Temp.pop();
    }
    
    while(j < S.length()){
        
        if(s[k] == S[j] || s[k] == S[j]-32 || s[k] == S[j]+32){
            if(k == s.length()-1){
                P.push_back(j-k);
                nP++;
                k -= count;
                j -= count;
                count = 0;
            }
            else{
                k++;
                count++;
            }
        }
        
        else{
            k -= count;
            j -= count;
            count = 0;
        }
        
        j++;
    }
    
    if(nP > 0){
        cout << "The positions are as follows: " << endl;
        for(int l = 0; l < P.size();  l++){
            cout << P[l];
            if(l != P.size()-1)
                cout << ", ";
            else
                cout << ".";
        }
        cout << endl;
    }
    
    return nP;
}
string Textfile::getname()
{
    return file_name;
}
int main()
{
    vector<Textfile*> storage;
    int task=1;
    while(task!=0)
    {
        cout<<"Enter 1 to create a new file\n";
        cout<<"Enter 2 to open a file using name of the file\n";
        cout<<"Enter 3 to show all files in the storage\n";
        cout<<"Enter 0 to Exit\n";
        cin>>task;
        if(task==1)
        {
            cout<<"Enter the name of the file:\n";
            string s;
            cin>>s;
            Textfile* n = new Textfile(s);
            storage.push_back(n);
            cout<<"\n<------------New file named "<<s<<" created in storage------------>\n\n";
        }
        if(task==2)
        {
            cout<<"Enter the name of the file you want to open:\n";
            string s;
            cin>>s;
            int found=-1;
            int cnt=0;
            vector<Textfile *>::iterator it;
            for (int j = 0; j < storage.size(); j++)
            {
                if(storage[j]->getname()==s)
                found=cnt;
                cnt++;
            }
            if(found==-1)
            cout<<"\n<------------There is No file named "<<s<<" in storage------------>\n\n";
            else
            {
                cout<<"\n<------------file named "<<storage.at(found)->getname()<<" opened------------>\n\n"; 
                int t2=1;
                Textfile* file=storage.at(found);
                while(t2!=0)
                {
                    Textfile* file=storage.at(found);
                    cout<<"Enter 1 to write into the file\n";
                    cout<<"Enter 2 to read the file\n";
                    cout<<"Enter 3 to undo\n";
                    cout<<"Enter 4 to redo\n";
                    cout<<"Enter 5 to find a text\n";
                    cout<<"Enter 6 to insert a sentence after ith sentence\n";
                    cout<<"Enter 0 to close the file\n";
                    cin>>t2;
                    if(t2 != 2 && t2 != 3 && t2 != 4 && t2 != 5){
                        file->input.push(t2);
                    }
                    if(t2==1)
                    {
                        cout<<"*****If you want to enter a new line please enter '\\n'*****\n";
                        cout<<"Enter the text you want to write into the file:\n";
                        string text;
                        getline(cin, text);     // this takes the \n entered in the above scan
                        getline(cin, text);
                        file->write(text);
                        cout<<"\n<------------Written successfully------------>\n";
                    }
                    if(t2==2)
                    {
                        cout<<"\n<------------The file contains the following content------------>\n\n";
                        file->read();
                        cout<<"\n<------------                                       ------------>\n\n";
                    }
                    if(t2==3)
                    {
                        file->undo();
                        cout<<"\n<------------Undo completed successfully------------>\n\n";
                    }
                    if(t2==4)
                    {
                        file->redo();
                        cout<<"\n<------------Redo completed successfully------------>\n\n";
                    }
                    if(t2==5)
                    {
                        cout<<"Enter the text you want to find in the file:\n";
                        string text;
                        getline(cin, text);     // this takes the \n entered in the above scan
                        getline(cin, text);
                        int ans=0; 
                        ans=file->find(text);
                        cout<<"\n<------------The text was found "<<ans<<" times in the file------------>\n\n";
                    }
                    if(t2==6)
                    {
                        cout<<"Enter the position and the sentence you want to insert:\n";
                        int idx;
                        cin>>idx;
                        file->ind.push(idx);
                        string text;
                        getline(cin, text);     // this takes the \n entered in the above scan
                        getline(cin, text);
                        file->insert(text,idx);
                        cout<<"\n<------------successfully inserted------------>\n\n";
                    }
                    
                }
            }
        }
        if(task==3)
        {
            cout<<"\nFiles in the storage are:\n";
            vector<Textfile *>::iterator it;
            for (int j=0;j<storage.size();j++)
            {
                cout << ">> " << storage[j]->getname() << endl;
            }
            cout<<"\n";
        }
    }

    return 0;
}

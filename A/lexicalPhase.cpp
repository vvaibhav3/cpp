#include <iostream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
#define BUFFER_SIZE 1024

struct T_Format
{
    int id;
    string value, type;
};

// struct I_L_Format
// {
//     int id;
//     string value;
// };

class lexicalPhase
{
private:
    /* data */
    T_Format *bdata;
    T_Format *kdata;
    T_Format *odata;
    vector<struct T_Format *> b_table;
    vector<struct T_Format *> k_table;
    vector<struct T_Format *> o_table;
    vector<string> l_table;
    vector<string> i_table;
    vector<struct T_Format *> t_table;

public:
    lexicalPhase();
    ~lexicalPhase();

    //validators
    int check_pattern(string);
    int checkBreackChar(char);
    int checkKeyword(string);
    int checkOperator(char);

    //getter and setters
    int putIdentifier(string);
    int putLiteal(string);
    void showTables();

    int checkTerminal(char[]);
};

lexicalPhase::lexicalPhase()
{
    bdata = new T_Format[5];

    bdata[0].id = 1, bdata[0].value = "{", bdata[0].type = "BC";
    bdata[1].id = 2, bdata[1].value = "}", bdata[1].type = "BC";
    bdata[2].id = 3, bdata[2].value = "(", bdata[2].type = "BC";
    bdata[3].id = 4, bdata[3].value = ")", bdata[3].type = "BC";
    bdata[4].id = 5, bdata[4].value = ";", bdata[4].type = "BC";

    odata = new T_Format[10];

    odata[0].id = 1, odata[0].value = "+", odata[0].type = "OP";
    odata[1].id = 2, odata[1].value = "-", odata[1].type = "OP";
    odata[2].id = 3, odata[2].value = ">", odata[2].type = "OP";
    odata[3].id = 4, odata[3].value = "<", odata[3].type = "OP";
    odata[4].id = 5, odata[4].value = "%", odata[4].type = "OP";
    odata[5].id = 6, odata[5].value = "/", odata[5].type = "OP";
    odata[6].id = 7, odata[6].value = ",", odata[6].type = "OP";
    odata[7].id = 8, odata[7].value = "=", odata[7].type = "OP";
    odata[8].id = 9, odata[8].value = "*", odata[8].type = "OP";
    odata[9].id = 10, odata[9].value = '"', odata[9].type = "OP";

    kdata = new T_Format[10];

    kdata[0].id = 1, kdata[0].value = "int", kdata[0].type = "KEY";
    kdata[1].id = 2, kdata[1].value = "float", kdata[1].type = "KEY";
    kdata[2].id = 3, kdata[2].value = "if", kdata[2].type = "KEY";
    kdata[3].id = 4, kdata[3].value = "else", kdata[3].type = "KEY";
    kdata[4].id = 5, kdata[4].value = "char", kdata[4].type = "KEY";
    kdata[5].id = 6, kdata[5].value = "printf", kdata[5].type = "KEY";
    kdata[6].id = 7, kdata[6].value = "printf", kdata[6].type = "KEY";
    kdata[7].id = 8, kdata[7].value = "scanf", kdata[7].type = "KEY";
    kdata[8].id = 9, kdata[8].value = "return", kdata[8].type = "KEY";
    kdata[9].id = 10, kdata[9].value = "void", kdata[9].type = "KEY";

    for (int i = 0; i < 10; i++)
    {
        if (i < 5)
        {
            b_table.push_back(&bdata[i]);
        }
        k_table.push_back(&kdata[i]);
        o_table.push_back(&odata[i]);
    }
}

lexicalPhase::~lexicalPhase()
{
    delete[] odata;
    delete[] bdata;
    delete[] kdata;
}

int lexicalPhase::checkKeyword(string lexems)
{
    T_Format *temp = NULL;
    for (vector<T_Format *>::iterator i = k_table.begin(); i != k_table.end(); i++)
    {
        temp = *i;
        if (temp->value == lexems)
        {
            t_table.push_back(temp);
            return 1;
        }
    }
    return 0;
}

int lexicalPhase::checkBreackChar(char lexems)
{
    T_Format *temp = NULL;
    for (vector<T_Format *>::iterator i = b_table.begin(); i != b_table.end(); i++)
    {
        temp = *i;
        if (temp->value[0] == lexems)
        {
            t_table.push_back(temp);
            return 1;
        }
    }

    return 0;
}

int lexicalPhase::checkOperator(char lexems)
{
    T_Format *temp = NULL;
    for (vector<T_Format *>::iterator i = o_table.begin(); i != o_table.end(); i++)
    {
        temp = *i;
        if (temp->value[0] == lexems)
        {
            t_table.push_back(temp);
            return 1;
        }
    }

    return 0;
}

int lexicalPhase::check_pattern(string lexems)
{
    if (lexems[0] >= 97 && lexems[0] <= 122)
    {
        return checkKeyword(lexems);
    }
    else
    {
        if (checkOperator(lexems[0]))
        {
            return 2;
        }
    }
    return 0;
}

int lexicalPhase::putIdentifier(string value){

    for (vector<string>::iterator i = i_table.begin(); i != i_table.end(); i++)
    {
        if(*i==value){
            return 0;
        }
    }
    i_table.push_back(value);
    return 1;
}

int lexicalPhase::putLiteal(string value){

    l_table.push_back(value);
    return 1;
}

void lexicalPhase::showTables(){

    int idx=1;
    
    cout<<"\n";
    cout<<"---------- Terminals -------------\n";
    for (vector<struct T_Format *>::iterator i = t_table.begin(); i != t_table.end(); i++,idx++)
    {
        cout<<idx<<" --> "<<(*i)->id<<" "<<(*i)->type<<" "<<(*i)->value<<"\n";
    }

    idx=1;

    cout<<"\n";
    cout<<"---------- Identifiers -------------\n";
    for (vector<string>::iterator i = i_table.begin(); i != i_table.end(); i++,idx++)
    {
        cout<<idx<<" --> "<<*i<<"\n";
    }

    cout<<"\n";
    cout<<"---------- Literal -------------\n";
    for (vector<string>::iterator i = l_table.begin(); i != l_table.end(); i++,idx++)
    {
        cout<<idx<<" --> "<<*i<<"\n";
    }

}

int lexicalPhase::checkTerminal(char buff[]){

    int i=check_pattern(buff);
    if(i==2){
        cout<<"Operator : "<<buff<<"\n";
    }
    else if(i==1){
        cout<<"Keyword : "<<buff<<"\n";
    }
    else{
        //identifier
        if(isdigit(buff[0])){
            putLiteal(buff);
        }
        else{
            putIdentifier(buff);
            // cout << "buffer before ('\\n' | '\\t' | ' ') : " << buff << "\n";
        }
    }
    return i;
}

int main(int argc, char const *argv[])
{

    ifstream ifs("test1.c");

    // file check
    if (!ifs)
    {
        cout << "Failed to open file...........\n";
        return 0;
    }

    char buff[BUFFER_SIZE], ch;
    int i = 0;
    lexicalPhase p1;
    while (ifs.get(ch))
    {
        if (ch == ' ' || ch == '\n' || ch == '\t')
        {
            buff[i] = '\0';

            //to make shure there is no first and last char as '\n' '\t' ' '
            if (i > 0)
            {
                p1.checkTerminal(buff);
            }
            i = 0;
        }
        else
        {
            //check for break char
            if (p1.checkBreackChar(ch))
            {
                if (i > 0)
                {
                    p1.checkTerminal(buff);
                    i = 0;
                    buff[i] = '\0';
                }
                cout << "Break char : " << ch << "\n";
            }
            else
            {
                //put operator and next check if literal or identifier
                if(p1.checkOperator(ch)){
                    cout<<"Operator : "<<ch<<"\n";
                    if(i>0){
                        p1.checkTerminal(buff);
                        cout<<"Buffer before operator : "<<buff<<"\n";
                    }
                    if(ch=='"'){
                        ifs.get(ch);
                        i=0;
                        while(ch!='"'){
                            buff[i]=ch;
                            i++;
                            ifs.get(ch);
                        }
                        buff[i]='\0';
                        p1.putLiteal(buff);
                        cout<<"String litral : "<<buff<<"\n";
                    }
                    i=0;
                }
                else{
                    buff[i] = ch;
                    i++;
                    buff[i] = '\0';
                }
            }
        }
    }

    p1.showTables();
    return 0;
}

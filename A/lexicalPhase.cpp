#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
#define BUFFER_SIZE 1024

//for terminals
struct T_Format
{
    int id;
    string value, type, token;
};

class lexicalPhase
{
private:
    /* data */
    T_Format *bdata;
    T_Format *kdata;
    T_Format *odata;
    
    unordered_map<string, struct T_Format *> b_table;
    unordered_map<string, struct T_Format *> k_table;
    unordered_map<string, struct T_Format *> o_table;

    vector<struct T_Format *> l_table;
    vector<struct T_Format *> i_table;
    vector<struct T_Format *> t_table;
    int id_count, lt_count;

public:
    lexicalPhase();
    ~lexicalPhase();

    //validators
    int check_pattern(string);
    int checkBreackChar(char);
    int checkKeyword(string);
    int checkOperator(char);
    int checkTerminal(char[]);

    //getter and setters
    int putIdentifier(string);
    int putLiteral(string);
    void showTables();
};

lexicalPhase::lexicalPhase()
{
    //intial count of litral and identifiers
    id_count = lt_count = 1;

    //building fixed table data

    //break characters
    bdata = new T_Format[5];

    bdata[0].id = 1, bdata[0].value = "{", bdata[0].type = "BC", bdata[0].token = "{";
    bdata[1].id = 2, bdata[1].value = "}", bdata[1].type = "BC", bdata[1].token = "}";
    bdata[2].id = 3, bdata[2].value = "(", bdata[2].type = "BC", bdata[2].token = "(";
    bdata[3].id = 4, bdata[3].value = ")", bdata[3].type = "BC", bdata[3].token = ")";
    bdata[4].id = 5, bdata[4].value = ";", bdata[4].type = "BC", bdata[4].token = ";";

    //operators
    odata = new T_Format[10];

    odata[0].id = 1, odata[0].value = "+", odata[0].type = "OP", odata[0].token = "+";
    odata[1].id = 2, odata[1].value = "-", odata[1].type = "OP", odata[1].token = "-";
    odata[2].id = 3, odata[2].value = ">", odata[2].type = "OP", odata[2].token = ">";
    odata[3].id = 4, odata[3].value = "<", odata[3].type = "OP", odata[3].token = "<";
    odata[4].id = 5, odata[4].value = "%", odata[4].type = "OP", odata[4].token = "%";
    odata[5].id = 6, odata[5].value = "/", odata[5].type = "OP", odata[5].token = "/";
    odata[6].id = 7, odata[6].value = ",", odata[6].type = "OP", odata[6].token = ",";
    odata[7].id = 8, odata[7].value = "=", odata[7].type = "OP", odata[7].token = "=";
    odata[8].id = 9, odata[8].value = "*", odata[8].type = "OP", odata[8].token = "*";
    odata[9].id = 10, odata[9].value = '"', odata[9].type = "OP", odata[9].token = '"';

    //keywords
    kdata = new T_Format[10];

    kdata[0].id = 1, kdata[0].value = "int", kdata[0].type = "KEY", kdata[0].token = "INT";
    kdata[1].id = 2, kdata[1].value = "float", kdata[1].type = "KEY", kdata[1].token = "FLOAT";
    kdata[2].id = 3, kdata[2].value = "if", kdata[2].type = "KEY", kdata[2].token = "IF";
    kdata[3].id = 4, kdata[3].value = "else", kdata[3].type = "KEY", kdata[3].token = "ELSE";
    kdata[4].id = 5, kdata[4].value = "char", kdata[4].type = "KEY", kdata[4].token = "CHAR";
    kdata[5].id = 6, kdata[5].value = "printf", kdata[5].type = "KEY", kdata[5].token = "PRINTF";
    kdata[6].id = 7, kdata[6].value = "scanf", kdata[6].type = "KEY", kdata[6].token = "SCANF";
    kdata[7].id = 8, kdata[7].value = "return", kdata[7].type = "KEY", kdata[7].token = "RETURN";
    kdata[8].id = 9, kdata[8].value = "void", kdata[8].type = "KEY", kdata[8].token = "VOID";

    //adding data into tables
    for (int i = 0; i < 10; i++)
    {
        if (i < 5)
            b_table.insert({bdata[i].value, &bdata[i]});

        if (i < 9)
            k_table.insert({kdata[i].value, &kdata[i]});

        o_table.insert({odata[i].value, &odata[i]});
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
    auto itr = k_table.find(lexems);
    if (itr == k_table.end())
        return 0;

    t_table.push_back(itr->second);
    return 1;
}

int lexicalPhase::checkBreackChar(char lexems)
{
    string str;
    str = lexems;
    auto itr = b_table.find(str);
    if (itr == b_table.end())
        return 0;

    t_table.push_back(itr->second);
    return 1;
}

int lexicalPhase::checkOperator(char lexems)
{

    string str;
    str = lexems;
    auto itr = o_table.find(str);

    if (itr == o_table.end())
        return 0;

    t_table.push_back(itr->second);
    return 1;
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

int lexicalPhase::putIdentifier(string value)
{

    //check if identifier is already present
    for (auto i = i_table.begin(); i != i_table.end(); i++)
    {
        if ((*i)->value == value)
        {
            return 0;
        }
    }

    T_Format *temp = new T_Format;
    temp->id = id_count, temp->value = value, temp->type = "Symbol", temp->token = "ID" + to_string(id_count);

    //adding into universal symbol table
    t_table.push_back(temp);
    //adding into symbol table
    i_table.push_back(temp);

    id_count += 1;
    return 1;
}

int lexicalPhase::putLiteral(string value)
{

    T_Format *temp = new T_Format;
    temp->id = lt_count, temp->value = value, temp->type = "Literal", temp->token = "L" + to_string(lt_count);

    //adding into universal symbol table
    t_table.push_back(temp);
    //adding into litral table
    l_table.push_back(temp);
    lt_count += 1;
    return 1;
}

void lexicalPhase::showTables()
{

    int idx = 1;

    cout << "\n";

    cout << "------------------------------ Universal symbol table ---------------------------------\n\n";
    cout << setw(5) << "idx" << setw(20) << "table idx" << setw(20) << "value" << setw(20) << "type" << setw(20) << "token"
         << "\n\n";

    for (auto i = t_table.begin(); i != t_table.end(); i++, idx++)
        cout << setw(5) << idx << setw(20) << (*i)->id << setw(20) << (*i)->value << setw(20) << (*i)->type << setw(20) << (*i)->token << "\n";

    idx = 1;
    cout << "\n\n";

    cout << "------------------------------------- Symbol table ------------------------------------\n\n";
    cout << setw(5) << "idx" << setw(20) << "value" << setw(20) << "type" << setw(20) << "token" << setw(20)
         << "\n\n";

    for (auto i = i_table.begin(); i != i_table.end(); i++, idx++)
        cout << setw(5) << idx << setw(20) << (*i)->value << setw(20) << (*i)->type << setw(20) << (*i)->token << "\n";

    idx = 1;
    cout << "\n\n";

    cout << "------------------------------------- Literal table -------------------------------------\n\n";
    cout << setw(5) << "idx" << setw(20) << "value" << setw(20) << "type" << setw(20) << "token" << setw(20)
         << "\n\n";

    for (auto i = l_table.begin(); i != l_table.end(); i++, idx++)
        cout << setw(5) << idx << setw(20) << (*i)->value << setw(20) << (*i)->type << setw(20) << (*i)->token << "\n";
}

int lexicalPhase::checkTerminal(char buff[])
{

    int i = check_pattern(buff);
    if (i == 2)
    {
        cout << "Operator : " << buff << "\n";
    }
    else if (i == 1)
    {
        cout << "Keyword : " << buff << "\n";
    }
    else
    {
        //identifier or literal check
        if (isdigit(buff[0]))
        {
            putLiteral(buff);
        }
        else
        {
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
                if (p1.checkOperator(ch))
                {
                    cout << "Operator : " << ch << "\n";
                    if (i > 0)
                    {
                        p1.checkTerminal(buff);
                        cout << "Buffer before operator : " << buff << "\n";
                    }
                    if (ch == '"')
                    {
                        ifs.get(ch);
                        i = 0;
                        while (ch != '"')
                        {
                            buff[i] = ch;
                            i++;
                            ifs.get(ch);
                        }
                        buff[i] = '\0';
                        p1.putLiteral(buff);
                        cout << "String litral : " << buff << "\n";
                    }
                    i = 0;
                }
                else
                {
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

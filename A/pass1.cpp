//pass1 of assembler for hypothetical instruction

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <iomanip>
#define SIZE 1024
using namespace std;

#define ARROW "---------"
#define BR "\n--------------------------------\n"

#define BLACK "\033[1;30m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define PINK "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[4;37m" //with underline
#define RESET "\033[0m"

//for reading records from file
struct data
{
    char lable[SIZE], mnemonic[SIZE], op1[SIZE], op2[SIZE];
};

//for mnemonic table(mot)
struct mtable
{
    string mname, mclass;
    int mcode, midx, mlink, mlen;
};

//for literal and symbol table
struct LStable
{
    string name;
    int lsidx, addr;
};

//for pseudo op table (pot)
struct ptable
{
    string pname, pclass;
    int pidx, pcode, plink;
};

//for register table
struct rtable
{
    string rname;
    int ridx;
};

//for intermediate code format
struct ICformat
{
    char type1[SIZE], type2[SIZE], regNo;
    int lc, code1, code2;
};

struct TCformat
{
    int lc, code1, regNo, addr;
};

class PASS1
{
    mtable *mdata;
    ptable *pdata;
    rtable *rdata;
    map<int, struct mtable *> mot;
    map<int, struct ptable *> pot;
    map<int, struct rtable *> rt;
    vector<struct LStable> symtb;
    vector<struct LStable> litrtb;
    vector<int> pooltb;
    vector<ICformat> buf;

public:
    PASS1();
    void showPrgm(string);
    mtable *findMdata(char, string);
    ptable *findPdata(char, string);
    rtable *findRdata(char, string);
    LStable *findSymbol(string);
    LStable *findLitral(string);
    void insertSymbol(int, string, int);
    void insertLitral(int, string, int);
    void insertAtPool(int, int &);
    void showTables();
    void buffer(int, string, int, int, string, int);
    void showBuffer();

    int getSymbolAddr(int);
    int getLitralAddr(int);

    void UndefineError()
    {
        for (vector<LStable>::iterator j = symtb.begin(); j != symtb.end(); j++)
        {
            if (j->addr == -1)
                cout << RED << "ERROR : { Symbol \"" << j->name << "\" not defined.. }" << RESET << endl;
        }
    }
    void showSymTab()
    {
        for (vector<LStable>::iterator j = symtb.begin(); j != symtb.end(); j++)
        {
            cout << setw(5) << j->lsidx << " " << setw(5) << j->name << " " << setw(5) << j->addr << endl;
        }
    }

    void showLitrTab()
    {

        for (vector<LStable>::iterator j = litrtb.begin(); j != litrtb.end(); j++)
        {
            cout << setw(5) << j->lsidx << " " << setw(5) << j->name << " " << setw(5) << j->addr << endl;
        }
    }

    void showPoolTab()
    {
        int i = 0;
        for (vector<int>::iterator j = pooltb.begin(); j != pooltb.end() - 1; j++)
        {
            i++;
            cout << setw(5) << i << setw(5) << " #" << *j << endl;
        }
    }
};

class PASS2 : public PASS1
{
    vector<TCformat> tc;
public:
    void genTargetCode();
    void showTargetCode();
};

PASS1::PASS1()
{

    mdata = new mtable[26];
    pdata = new ptable[10];
    rdata = new rtable[4];
    pooltb.push_back(1);
    //data for MOT
    mdata[0].mname = "MOVER", mdata[0].mcode = 01, mdata[0].mclass = "IS", mdata[0].mlen = 2, mdata[0].mlink = 1;
    mdata[1].mname = "MOVEM", mdata[1].mcode = 02, mdata[1].mclass = "IS", mdata[1].mlen = 2, mdata[1].mlink = -1;
    mdata[2].mname = "PRINT", mdata[2].mcode = 9, mdata[2].mclass = "IS", mdata[2].mlen = 2, mdata[2].mlink = -1;
    mdata[4].mname = "READ", mdata[4].mcode = 10, mdata[4].mclass = "IS", mdata[4].mlen = 2, mdata[4].mlink = -1;
    mdata[5].mname = "STOP", mdata[5].mcode = 00, mdata[5].mclass = "IS", mdata[5].mlen = 1, mdata[5].mlink = 6;
    mdata[6].mname = "SUB", mdata[6].mcode = 04, mdata[6].mclass = "IS", mdata[6].mlen = 2, mdata[6].mlink = -1;
    mdata[13].mname = "ADD", mdata[13].mcode = 03, mdata[13].mclass = "IS", mdata[13].mlen = 2, mdata[13].mlink = -1;
    mdata[14].mname = "BC", mdata[14].mcode = 07, mdata[14].mclass = "IS", mdata[14].mlen = 2, mdata[14].mlink = -1;
    mdata[15].mname = "COMP", mdata[15].mcode = 8, mdata[15].mclass = "IS", mdata[15].mlen = 2, mdata[15].mlink = -1;
    mdata[16].mname = "DIV", mdata[16].mcode = 6, mdata[16].mclass = "IS", mdata[16].mlen = 2, mdata[16].mlink = 17;
    mdata[17].mname = "DC", mdata[17].mcode = 02, mdata[17].mclass = "DL", mdata[17].mlen = 1, mdata[17].mlink = 18;
    mdata[18].mname = "DS", mdata[18].mcode = 01, mdata[18].mclass = "DL", mdata[18].mlen = 2, mdata[18].mlink = -1;
    mdata[25].mname = "MULT", mdata[25].mcode = 05, mdata[25].mclass = "IS", mdata[25].mlen = 2, mdata[25].mlink = 0;

    //data for POT
    pdata[0].pname = "EQU", pdata[0].pcode = 03, pdata[0].pclass = "AD", pdata[0].plink = 1;
    pdata[1].pname = "ORIGIN", pdata[1].pcode = 04, pdata[1].pclass = "AD", pdata[1].plink = -1;
    pdata[3].pname = "START", pdata[3].pcode = 01, pdata[3].pclass = "AD", pdata[3].plink = -1;
    pdata[6].pname = "LTORG", pdata[6].pcode = 05, pdata[6].pclass = "AD", pdata[6].plink = -1;
    pdata[9].pname = "END", pdata[9].pcode = 02, pdata[9].pclass = "AD", pdata[9].plink = 0;

    //for register table
    rdata[0].rname = "AREG", rdata[0].ridx = 01;
    rdata[1].rname = "BREG", rdata[1].ridx = 02;
    rdata[2].rname = "CREG", rdata[2].ridx = 03;
    rdata[3].rname = "DREG", rdata[3].ridx = 04;

    for (int i = 0; i < 26; i++)
    {
        //for RT
        if (i < 4)
        {
            rt.insert(pair<int, struct rtable *>(i, &rdata[i]));
        }
        //for POT
        if (i < 10)
        {
            if (pdata[i].pname.size() <= 0)
                pdata[i].pidx = i, pdata[i].plink = -1;
            pot.insert(pair<int, struct ptable *>(i, &pdata[i]));
        }

        //for MOT
        if (mdata[i].mname.size() <= 0)
            mdata[i].midx = i, mdata[i].mlink = -1;

        mot.insert(pair<int, struct mtable *>(i, &mdata[i]));
    }
}
void PASS1::showPrgm(string fileName)
{
    struct data s;
    ifstream ifs;
    ifs.open(fileName.c_str(), ios::in | ios::binary);
    while (1)
    {
        ifs.read((char *)&s, sizeof(struct data));

        if (ifs)
            cout << s.lable << " " << s.mnemonic << " " << s.op1 << " " << s.op2 << "\n";
        else
            break;
    }
    cout << endl;
}

mtable *PASS1::findMdata(char ch, string s)
{

    int key = (ch % 26);
    map<int, struct mtable *>::iterator res;

    res = mot.find(key);
    mtable *temp = NULL;

    while (res != mot.end())
    {
        temp = res->second;
        if (temp->mname == s)
            return res->second;
        else
            res = mot.find(temp->mlink);

        // cout << temp->mname << endl;
    }
    return NULL;
}

ptable *PASS1::findPdata(char ch, string s)
{

    int key = (ch % 10);
    map<int, struct ptable *>::iterator res;

    res = pot.find(key);
    ptable *temp = NULL;

    while (res != pot.end())
    {
        temp = res->second;
        if (temp->pname == s)
            return res->second;
        else
            res = pot.find(temp->plink);
    }
    return NULL;
}

rtable *PASS1::findRdata(char ch, string regName)
{
    int key = (ch % 65);
    map<int, struct rtable *>::iterator res;
    res = rt.find(key);
    if (res != rt.end() && res->second->rname == regName)
        return res->second;

    return NULL;
}

LStable *PASS1::findLitral(string data)
{

    for (vector<LStable>::iterator j = litrtb.begin(); j != litrtb.end(); j++)
    {
        if (j->name == data)
            return &(*j);
    }
    return NULL;
}

LStable *PASS1::findSymbol(string data)
{
    for (vector<LStable>::iterator j = symtb.begin(); j != symtb.end(); j++)
    {

        if (j->name == data)
            return &(*j);
    }
    return NULL;
}

void PASS1::insertSymbol(int idx, string lable, int addr)
{
    LStable temp;
    temp.lsidx = idx, temp.name = lable, temp.addr = addr;
    symtb.push_back(temp);
}

void PASS1::insertLitral(int idx, string lable, int addr)
{
    LStable temp;
    temp.lsidx = idx, temp.name = lable, temp.addr = addr;
    litrtb.push_back(temp);
}

void PASS1::insertAtPool(int idx, int &lc)
{
    // cout << "idx : " << idx << endl;
    int temp = pooltb[idx - 1];
    int end = (litrtb.end() - 1)->lsidx;
    // cout << "start : " << temp << " end : " << end << endl;
    if (litrtb[temp - 1].addr != -1)
        return;
    while (temp <= end)
    {
        litrtb[temp - 1].addr = lc;
        lc += 1;
        temp++;
    }
    pooltb.push_back(litrtb[end - 1].lsidx + 1);
}

void PASS1::showTables()
{
    cout << RED << ARROW << " Symbol Table " << ARROW
         << RESET << endl;
    showSymTab();

    cout << RED << BR << RESET << endl;
    cout << RED << ARROW << " Litral Table " << ARROW
         << RESET << endl;
    showLitrTab();

    cout << RED << BR << RESET << endl;

    cout << RED << ARROW << " Pool Table " << ARROW
         << RESET << endl;

    showPoolTab();
    cout << RED << BR << RESET << endl;
    
}

void PASS1::buffer(int lc, string cls, int code, int regNo, string type, int cnst)
{
    struct ICformat ictemp;
    ictemp.lc = lc, strcpy(ictemp.type1, cls.c_str()), ictemp.code1 = code, ictemp.regNo = regNo, strcpy(ictemp.type2, type.c_str()), ictemp.code2 = cnst;
    buf.push_back(ictemp);
}

void PASS1::showBuffer()
{
    ofstream ofs;
    ofs.open("output.dat", ios::binary);
    for (vector<ICformat>::iterator j = buf.begin(); j != buf.end(); j++)
    {
        if (j->code2 == 45)
        {
            cout << GREEN << "\n"
                 << setw(5) << j->lc << " " << setw(5) << j->type1 << " " << setw(5) << j->code1 << " " << setw(5) << j->regNo << " " << setw(5) << j->type2 << " " << setw(5) << (char)j->code2
                 << RESET;
        }
        else
        {
            cout << GREEN << "\n"
                 << setw(5) << j->lc << " " << setw(5) << j->type1 << " " << setw(5) << j->code1 << " " << setw(5) << j->regNo << " " << setw(5) << j->type2 << " " << setw(5) << j->code2
                 << RESET;
        }
        ofs.write((char *)&(*j), sizeof(ICformat));
    }

    cout<<endl;
}

int PASS1::getSymbolAddr(int sidx)
{
    for (vector<LStable>::iterator j = symtb.begin(); j != symtb.end(); j++)
    {
        //cout << j->lsidx << endl;
        if (j->lsidx == sidx)
            return j->addr;
    }
    return -1;
}

int PASS1::getLitralAddr(int lidx)
{
    for (vector<LStable>::iterator j = litrtb.begin(); j != litrtb.end(); j++)
    {
        //cout << j->lsidx << endl;
        if (j->lsidx == lidx)
            return j->addr;
    }
    return -1;
}

void PASS2::genTargetCode()
{
    ifstream ifs; // stream for reading target code
    ifs.open("output.dat", ios::in | ios::binary);
    ICformat ic;
    TCformat temp;
    for (ifs.read((char *)&ic, sizeof(ICformat)); !ifs.eof(); ifs.read((char *)&ic, sizeof(ICformat)))
    {
        //cout<<ic.lc<<" "<<ic.type1<<" "<<ic.code1<<" "<<ic.regNo<<" "<<ic.type2<<" "<<ic.code2<<endl;
        if (!strcmp(ic.type1, "AD"))
        {
            continue;
            // temp.lc = ic.lc, temp.code1 = '-', temp.regNo = '-', temp.addr = '-';
            // tc.push_back(temp);
        }
        else
        {
            int addr = -1;
            if (!strcmp(ic.type2, "S"))
            {
                addr = getSymbolAddr(ic.code2);
                if (addr == -1)
                {
                    cout << RED << "ERROR : { Symbol at loation : \"" << ic.lc << "\" not defined.. }" << RESET << endl;
                    break;
                }
                temp.lc = ic.lc, temp.code1 = ic.code1, temp.regNo = ic.regNo, temp.addr = addr;
            }

            if (!strcmp(ic.type2, "L"))
            {
                addr = getLitralAddr(ic.code2);
                temp.lc = ic.lc, temp.code1 = ic.code1, temp.regNo = ic.regNo, temp.addr = addr;
            }

            if (!strcmp(ic.type2, "C"))
            {
                // temp.lc = ic.lc, temp.code1 = '-', temp.regNo = '-', temp.addr = ic.code2;
                continue;
            }

            tc.push_back(temp);
        }
    }
}

void PASS2::showTargetCode(){


    cout << RED << ARROW << " Target code " << ARROW
         << RESET << endl;

    for (vector<TCformat>::iterator j = tc.begin(); j != tc.end(); j++)
    {
        if (j->code1 == 45)
        {
            cout << GREEN << "\n"
                 << setw(5) << j->lc << " " << setw(5) << (char)j->code1 << " " << setw(5) <<(char)j->regNo << " ";
                 
                if(j->addr==45)
                    cout << setw(5) <<(char) j->addr;
                else
                    cout << setw(5) << j->addr;
                 cout<< RESET;
        }
        else
        {
            cout << GREEN << "\n"
                 << setw(5) << j->lc << " " << setw(5) << j->code1 << " " << setw(5) << (char)j->regNo << " " << setw(5) << j->addr
                 << RESET;
        }
    }
    cout<<endl;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "\033[1;31mPLEASE ENTER FILE NAME \033[0m\n";
        return 0;
    }
    PASS2 p;

    string fileName = argv[1]; //getting prgm name from cmd line
    //p.showPrgm(fileName);      //displying prgm

    struct data s; //for getting record from file

    ifstream ifs; // stream for reading prgm
    ifs.open(fileName.c_str(), ios::in | ios::binary);

    int lc = 0, stab = 1, ltab = 1, ptab = 1; // pointers for diff tables

    vector<ICformat> ic; // buffer for storing intermediate code

    //temprary holders for every statement
    struct ICformat ictemp;
    struct ptable *ptemp;
    struct mtable *mtemp;
    struct rtable *rtemp;
    struct LStable *stemp;
    struct LStable *ltemp;

    // file check
    if (!ifs)
    {
        cout << RED << "Failed to open file...........\n"
             << RESET;
        return 0;
    }

    //getting start of prgm and intializing LC (location counter)
    // ifs.read((char *)&s, sizeof(struct data));

    // if (!strcmp(s.mnemonic, "START"))
    // {
    //     // sscanf(s.op2, "%d", &lc);
    //     lc = stoi(s.op2);
    //     cout << CYAN << "LC : " << lc << RESET << endl;
    //     ptemp = p.findPdata(s.mnemonic[0], s.mnemonic);
    //     ictemp.type1 = ptemp->pclass, ictemp.code1 = ptemp->pcode, ictemp.type2 = 'c', ictemp.code2 = lc, ictemp.regNo = '-';
    //     ic.push_back(ictemp);
    // }
    // else
    // {
    //     cout << RED << "START NOT FOUND...........\n"
    //          << RESET;
    //     return 0;
    // }

    for (ifs.read((char *)&s, sizeof(struct data)); strcmp(s.mnemonic, "END"); ifs.read((char *)&s, sizeof(struct data)))
    {

        if (!ifs)
            break;

        // cout << s.lable << " " << s.mnemonic << " " << s.op1 << " " << s.op2 << endl;
        if (s.lable[0] != '-')
        {
            stemp = p.findSymbol(s.lable);
            if (stemp == NULL)
            {
                p.insertSymbol(stab, s.lable, lc);
                stab += 1;
            }
            else
            {

                if ((stemp->addr != -1 && !strcmp(s.mnemonic, "DS")) || (stemp->addr != -1 && !strcmp(s.mnemonic, "DC")))
                {
                    cout << RED << "ERROR :  { \"" << s.lable << "\"  already defined... }\n"
                         << RESET;
                    return 0;
                }

                stemp->addr = lc;
            }
        }

        mtemp = p.findMdata(s.mnemonic[0], s.mnemonic);
        if (mtemp != NULL)
        {

            // cout << "mtable" << endl;
            if (!strcmp(s.mnemonic, "DC"))
            {
                stemp = p.findSymbol(s.lable);
                p.buffer(lc, mtemp->mclass, mtemp->mcode, '-', "C", stoi(s.op2));
            }
            else if (!strcmp(s.mnemonic, "DS"))
            {
                stemp = p.findSymbol(s.lable);
                p.buffer(lc, mtemp->mclass, mtemp->mcode, '-', "C", stoi(s.op2));
                lc += stoi(s.op2);
                lc -= 1;
            }
            else if (s.op2[0] == '=')
            {
                rtemp = p.findRdata(s.op1[0], s.op1);
                if (rtemp == NULL)
                {

                    cout << RED << "ERROR :  { Register \"" << s.op1 << "\" not found... }\n"
                         << RESET;
                    return 0;
                }
                p.buffer(lc, mtemp->mclass, mtemp->mcode, '0' + rtemp->ridx, "L", ltab);
                p.insertLitral(ltab, s.op2, -1);
                ltab += 1;
            }
            else
            {
                rtemp = p.findRdata(s.op1[0], s.op1);
                if (rtemp == NULL)
                {

                    cout << RED << "ERROR :  { Register \"" << s.op1 << "\" not found... }\n"
                         << RESET;
                    return 0;
                }
                stemp = p.findSymbol(s.op2);
                if (stemp == NULL)
                {
                    p.insertSymbol(stab, s.op2, -1);
                    p.buffer(lc, mtemp->mclass, mtemp->mcode, '0' + rtemp->ridx, "S", stab);
                    stab += 1;
                }
                else
                {
                    p.buffer(lc, mtemp->mclass, mtemp->mcode, '0' + rtemp->ridx, "S", stemp->lsidx);
                }
            }
            lc += 1;
        }

        ptemp = p.findPdata(s.mnemonic[0], s.mnemonic);
        if (ptemp != NULL)
        {

            // cout << "ptable" << endl;
            if (!strcmp(s.mnemonic, "LTORG"))
            {
                // cout << "ptab : " << ptab << endl;
                p.buffer(lc, ptemp->pclass, ptemp->pcode, '-', "-", '-');
                p.insertAtPool(ptab, lc);
                // p.showTables();
                ptab += 1;
            }
            else if (!strcmp(s.mnemonic, "START") || !strcmp(s.mnemonic, "ORIGIN"))
            {
                string label = s.op2;
                string value, opr;
                int x = -1;
                if (label.find("+", 0) != -1)
                {
                    x = label.find("+", 0);
                }
                else if (label.find("-", 0) != -1)
                {
                    x = label.find("-", 0);
                }
                // cout << " x : " << x << " size : " << label.size() << endl;
                if (x != -1)
                {
                    value.assign(label, x + 1, label.size() - x);
                    opr.assign(label, x, 1);
                    label.assign(label, 0, x);

                    stemp = p.findSymbol(s.op2);
                    if (stemp != NULL)
                    {
                        lc = stemp->addr;
                        if (value != "")
                            lc += stoi(value);
                    }
                    else
                    {
                        cout << RED << "ERROR :  { symbol not found.. }\n"
                             << RESET;
                    }
                }
                else
                {
                    lc = stoi(s.op2);
                }

                p.buffer(0, ptemp->pclass, ptemp->pcode, '-', "C", lc);

                // cout << " lc : " << lc << " " << label << " " << opr << " " << value << endl;
            }
            else if (!strcmp(s.mnemonic, "EQU"))
            {
                LStable *stemp2 = p.findSymbol(s.lable);
                if (stemp2 == NULL)
                {
                    stemp = p.findSymbol(s.op2);

                    //if not in symtab
                    if (stemp == NULL)
                    {
                        p.insertSymbol(stab, s.lable, stoi(s.op2));

                        p.buffer(lc, ptemp->pclass, ptemp->pcode, '-', "C", stoi(s.op2));
                        stab += 1;
                    }
                    else
                    {
                        p.insertSymbol(stab, s.lable, stemp->addr);

                        p.buffer(lc, ptemp->pclass, ptemp->pcode, '-', "S", stemp->lsidx);
                        stab += 1;
                    }
                }
                else
                {
                    stemp = p.findSymbol(s.op2);

                    //if not in symtab
                    if (stemp == NULL)
                    {
                        stemp2->addr = stoi(s.op2);
                        p.buffer(lc, ptemp->pclass, ptemp->pcode, '-', "C", stoi(s.op2));
                        stab += 1;
                    }
                    else
                    {
                        stemp2->addr = stemp->addr;
                        p.buffer(lc, ptemp->pclass, ptemp->pcode, '-', "S", stemp->lsidx);
                        stab += 1;
                    }
                }
            }
        }
        if (mtemp == NULL && ptemp == NULL)
        {
            cout << RED << "ERROR :  { Mnemonic \"" << s.mnemonic << "\" not found... }\n"
                 << RESET;
            return 0;
        }
    }

    //processing end statement
    if (strcmp(s.mnemonic, "END") != 0)
    {
        cout << RED << "ERROR :  { Mnemonic \"" << s.mnemonic << "\" not found... }\n"
             << RESET;
        return 0;
    }
    ptemp = p.findPdata(s.mnemonic[0], s.mnemonic);
    p.buffer(0, ptemp->pclass, ptemp->pcode, '-', "-", '-');

    p.insertAtPool(ptab, lc);
    p.showTables();
    //p.UndefineError();

    //displying intermediate code
    p.showBuffer();
    cout << endl;

    // PASS2 p2;
    p.genTargetCode();
    p.showTargetCode();
    //***********tests***********
    // cout<<argc<<endl;
    // cout<<argv[1];
    // mtable *temp=p.findMnemonic('M',"MOVEM");
    // cout<<temp->mcode<<endl;
    // p.showPrgm(argv[1]);
    return 0;
}

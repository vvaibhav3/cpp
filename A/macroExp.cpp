#include <iostream>
using namespace std;
#include <vector>
#include <fstream>
#include <string.h>
#include <iomanip>
#define SIZE 1024

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

struct MdtFormat
{
    int midx;
    struct data offset;
};

struct MntFormat
{
    string mname;
    int mdt_ptr;
    int ala_ptr;
};

struct ALAFormat
{
    string pname, avalue;
    int pidx;
};

class MacroPP
{
    vector<struct ALAFormat> ala;
    vector<struct MntFormat> mnt;
    vector<struct MdtFormat> mdt;
    vector<struct data> expcode;

public:
    void insertMdt(struct MdtFormat);
    void insertMnt(struct MntFormat);
    void insertExpcode(struct data);
    int checkMacro(string);
    void proccessMdt();
    void showExpandedForm();
    void showMdt()
    {
        cout << RED << ARROW << " MDT Table " << ARROW
             << RESET << endl;
        for (vector<MdtFormat>::iterator j = mdt.begin(); j != mdt.end(); j++)
        {
            cout << setw(5) << j->midx << " " << setw(5) << j->offset.lable << " " << setw(5) << j->offset.mnemonic << " " << setw(5) << j->offset.op1 << " " << setw(5) << j->offset.op2 << endl;
        }
    }
    void showMnt()
    {
        cout << RED << ARROW << " MNT Table " << ARROW
             << RESET << endl;
        int i = 1;
        for (vector<MntFormat>::iterator j = mnt.begin(); j != mnt.end(); j++, i++)
        {
            cout << setw(5) << i << " " << setw(5) << j->mname << " " << setw(5) << j->mdt_ptr << endl;
        }
    }
};

void MacroPP::insertMdt(MdtFormat mtemp)
{
    mdt.push_back(mtemp);
}

void MacroPP::insertMnt(MntFormat mtemp)
{
    mnt.push_back(mtemp);
}

void MacroPP::insertExpcode(data temp)
{
    expcode.push_back(temp);
}

void MacroPP::proccessMdt()
{
    vector<struct MdtFormat>::iterator s = mdt.begin();
    s++;
    while (s != mdt.end()-1)
    {
        expcode.push_back(s->offset);

        s++;
    }
}

int MacroPP::checkMacro(string mname)
{
    vector<struct MntFormat>::iterator s = mnt.begin();

    while (s != mnt.end())
    {
        if (s->mname == mname)
            return s->mdt_ptr;

        s++;
    }

    return 0;
}

void MacroPP::showExpandedForm()
{
    showMdt();
    showMnt();
    vector<struct data>::iterator s = expcode.begin();
    while (s != expcode.end())
    {
        cout << GREEN << "\n"
             << setw(5) << s->lable << " " << setw(5) << s->mnemonic << " " << setw(5) << s->op1 << " " << setw(5) << s->op2 << RESET;
        s++;
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "\033[1;31mPLEASE ENTER FILE NAME \033[0m\n";
        return 0;
    }
    MacroPP m;

    string fileName = argv[1]; //getting prgm name from cmd line
    struct data s;
    ifstream ifs; // stream for reading prgm
    ifs.open(fileName.c_str(), ios::in | ios::binary);

    MntFormat mntemp;
    MdtFormat mdtemp;
    ALAFormat altemp;

    int mdtptr = 1;

    for (ifs.read((char *)&s, sizeof(struct data)); strcmp(s.mnemonic, "END"); ifs.read((char *)&s, sizeof(struct data)))
    {

        if (!ifs)
            break;

        if (!strcmp("MACRO", s.mnemonic))
        {
            ifs.read((char *)&s, sizeof(struct data));

            if (s.lable[0] == '-')
            {
                strcpy(mdtemp.offset.lable, s.lable), strcpy(mdtemp.offset.mnemonic, s.mnemonic), strcpy(mdtemp.offset.op1, s.op1), strcpy(mdtemp.offset.op2, s.op2);
                mdtemp.midx = mdtptr;
                mdtptr += 1;
                mntemp.mname = s.mnemonic, mntemp.mdt_ptr = mdtptr, mntemp.ala_ptr = 0;
                m.insertMdt(mdtemp);
                m.insertMnt(mntemp);
            }

            for (ifs.read((char *)&s, sizeof(struct data)); strcmp(s.mnemonic, "MEND"); ifs.read((char *)&s, sizeof(struct data)))
            {
                strcpy(mdtemp.offset.lable, s.lable), strcpy(mdtemp.offset.mnemonic, s.mnemonic), strcpy(mdtemp.offset.op1, s.op1), strcpy(mdtemp.offset.op2, s.op2);
                mdtemp.midx = mdtptr;
                mdtptr += 1;
                m.insertMdt(mdtemp);
            }
            strcpy(mdtemp.offset.lable, s.lable), strcpy(mdtemp.offset.mnemonic, s.mnemonic), strcpy(mdtemp.offset.op1, s.op1), strcpy(mdtemp.offset.op2, s.op2);
            mdtemp.midx = mdtptr;
            mdtptr += 1;
            m.insertMdt(mdtemp);
        }

        if (!strcmp("START", s.mnemonic))
        {
            m.insertExpcode(s);
            for (ifs.read((char *)&s, sizeof(struct data)); strcmp(s.mnemonic, "END"); ifs.read((char *)&s, sizeof(struct data)))
            {
                if (m.checkMacro(s.mnemonic))
                {
                    m.proccessMdt();
                }
                else
                {
                    m.insertExpcode(s);
                }
            }
        }
    }
    m.insertExpcode(s);
    m.showExpandedForm();
    return 0;
}

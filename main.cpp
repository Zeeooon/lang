#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::string> vmap;
std::unordered_map<std::string, double> nmap;
std::unordered_map<std::string, int> maploc;
std::unordered_map<std::string, std::string> funcmap;
std::vector<std::string> params;
int pramloc = 0;

void error(std::string error, int code)
{
    std::cout << "[" << code << "] " << error << "\n";
    exit(code);
}

void run(std::string line);

void var(std::string line);
void num(std::string line);
void inc(std::string line);
void out(std::string line);
void in(std::string line);
void add(std::string line);
void sub(std::string line);
void mul(std::string line);
void div(std::string line);
void loop(std::string line);
void iff(std::string line);
void not(std::string line);
void gre(std::string line);
void les(std::string line);
void func(std::string line);

int main(int argc, char* argv[])
{
    if (argv[1] == NULL)
        error("No File inputted", 1);
    std::string line;
    std::string file = argv[1];
    std::ifstream myfile(file);  
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            run(line);
        }
        myfile.close();
    }
    else
        error("Unable to open file" + file, 2);
}

void run(std::string line)
{
    if (line[0] == 'v')
        var(line.erase(0, 2));
    else if (line[0] == 'n')
        num(line.erase(0, 2));
    else if (line[0] == '#')
        inc(line.erase(0, 2));
    else if (line[0] == '<')
        out(line.erase(0, 2));
    else if (line[0] == '>')
        in(line.erase(0, 2));
    else if (line[0] == '=')
        iff(line.erase(0, 2));
    else if (line[0] == '!')
        not(line.erase(0, 2));
    else if (line[0] == '\\')
        gre(line.erase(0, 2));
    else if (line[0] == '/')
        les(line.erase(0, 2));
    else if (line[0] == '+')
        add(line.erase(0, 2));
    else if (line[0] == '-')
        sub(line.erase(0, 2));
    else if (line[0] == '*')
        mul(line.erase(0, 2));
    else if (line[0] == '/')
        div(line.erase(0, 2));
    else if (line[0] == 'e')
        loop(line.erase(0, 2));
    else if (line[0] == 'r')
        func(line.erase(0, 2));
    else
       error("command not found " + line, 3);
}

void var(std::string line)
{
    std::string name = line;
    line.erase(0, line.find_first_of(' ')+1);
    if (line.length() == 0)
        line = "!";
    name.erase(name.find_first_of(' '), name.length());
    vmap[name] = line;
    maploc[name] = 0;
}
void num(std::string line)
{
    std::string name = line;
    line.erase(0, line.find_first_of(' ')+1);
    if (line.length() == 0)
        line = "0";
    name.erase(name.find_first_of(' '), name.length());
    nmap[name] = std::stod(line);
    maploc[name] = 1;
}
void inc(std::string line)
{
    std::string name, loc;
    name = line.substr(0, line.find_first_of('|'));
    loc = line.substr(line.find_first_of('|')+1, line.length());
    funcmap[name] = loc;
}

void out(std::string line)
{
    if(line[0] == '"')
    {
        std::cout << line.erase(0,1) << "\n";
    }
    else
    {
        int map = maploc.find(line)->second;
        if(map == 0)
            std::cout << vmap.find(line)->second << "\n";
        else
            std::cout << nmap.find(line)->second << "\n";
    }
}
void in(std::string line)
{
    int map = maploc.find(line)->second;
    if(map == 0)
    {
        std::getline(std::cin, vmap[maploc.find(line)->first]);
    }
    else
    {
        std::cin >> nmap[maploc.find(line)->first];
    }
}
void iff(std::string line)
{
    std::string cmd = line.substr(line.find_first_of(' ') + 1, line.size());
    line.erase(line.find_first_of(' '), line.size());
    int map = maploc.find(line.substr(0, line.find_first_of('|')))->second;
    if (map == 0)
    {
        std::string op1, op2;
        op1 = vmap.find(line.substr(0, line.find_first_of('|')))->second;
        op2 = line.substr(line.find_first_of('|') + 1, line.size());
        if (op1 == op2)
            run(cmd);
    }
    else
    {
        double op1, op2;
        op1 = nmap.find(line.substr(0, line.find_first_of('|')))->second;
        op2 = std::stod(line.substr(line.find_first_of('|') + 1, line.size()));
        if (op1 == op2)
            run(cmd);
    }
}
void not(std::string line)
{
    std::string cmd = line.substr(line.find_first_of(' ') + 1, line.size());
    line.erase(line.find_first_of(' '), line.size());
    int map = maploc.find(line.substr(0, line.find_first_of('|')))->second;
    if (map == 0)
    {
        std::string op1, op2;
        op1 = vmap.find(line.substr(0, line.find_first_of('|')))->second;
        op2 = line.substr(line.find_first_of('|') + 1, line.size());
        if (op1 != op2)
            run(cmd);
    }
    else
    {
        double op1, op2;
        op1 = nmap.find(line.substr(0, line.find_first_of('|')))->second;
        op2 = std::stod(line.substr(line.find_first_of('|') + 1, line.size()));
        if (op1 != op2)
            run(cmd);
    }
}
void gre(std::string line)
{
    double op1, op2;
    std::string cmd = line.substr(line.find_first_of(' ') + 1, line.size());
    op1 = nmap.find(line.substr(0, line.find_first_of('|')))->second;
    op2 = std::stod(line.substr(line.find_first_of('|') + 1, line.size()));
    if (op1 > op2)
        run(cmd);
}
void les(std::string line)
{
    double op1, op2;
    std::string cmd = line.substr(line.find_first_of(' ') + 1, line.size());
    op1 = nmap.find(line.substr(0, line.find_first_of('|')))->second;
    op2 = std::stod(line.substr(line.find_first_of('|') + 1, line.size()));
    if (op1 < op2)
        run(cmd);
}
void add(std::string line)
{
    double num1, num2;
    std::string line2 = line.substr(line.find_first_of('|')+1, line.size());
    line.erase(line.find_first_of('|'), line.size());
    num1 = nmap.find(line)->second;
    num2 = nmap.find(line2)->second;
    nmap[line] = num1 + num2;
}
void sub(std::string line)
{
    double num1, num2;
    std::string line2 = line.substr(line.find_first_of('|')+1, line.size());
    line.erase(line.find_first_of('|'), line.size());
    num1 = nmap.find(line)->second;
    num2 = nmap.find(line2)->second;
    nmap[line] = num1 - num2;
}
void mul(std::string line)
{
    double num1, num2;
    std::string line2 = line.substr(line.find_first_of('|')+1, line.size());
    line.erase(line.find_first_of('|'), line.size());
    num1 = nmap.find(line)->second;
    num2 = nmap.find(line2)->second;
    nmap[line] = num1 * num2;
}
void div(std::string line)
{
    double num1, num2;
    std::string line2 = line.substr(line.find_first_of('|')+1, line.size());
    line.erase(line.find_first_of('|'), line.size());
    num1 = nmap.find(line)->second;
    num2 = nmap.find(line2)->second;
    nmap[line] = num1 / num2;
}
void loop(std::string line)
{
    
    if (line.substr(0, line.find_first_of(' ')) == "~")
        while (true)
            run(line.substr(line.find_first_of(' ') + 1, line.size()));
    else {
        int amount = std::stoi(line.substr(0, line.find_first_of(' ')));
        line.erase(0, line.find_first_of(' '));
        for (int i = 0; i < amount; i++)
        {
            run(line.substr(line.find_first_of(' ') + 1, line.size()));
        }
    }
}
void func(std::string line)
{
    std::string f, loc, cmd, paramss, temp;
    f = line.substr(0, line.find_first_of(' '));
    loc =  funcmap.find(f)->second;
    paramss = line.substr(line.find_first_of(' ') + 1, line.size());
    for (int i = 0; i < paramss.size(); i++)
    {
        temp += paramss[i];
        if (paramss[i] == ' ')
        {
            params.push_back(temp);
            temp = "";
        }
    }
    params.push_back(temp);
    for (int i = 0; i < params.size(); i++)
    {
        std::cout << params[i] <<  "\n";
    }
    std::ifstream funcf(loc);
    if (funcf.is_open())
    {
        while (getline(funcf, cmd))
        {
            run(cmd);
        }
        funcf.close();
    }
    else
        error("Unable to open file" + loc, 2);
}
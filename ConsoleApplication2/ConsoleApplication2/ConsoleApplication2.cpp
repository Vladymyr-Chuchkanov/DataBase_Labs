#include <iostream>
#include <string>
#include<fstream>
#include<vector>

using namespace std;

class Slave {
public:
    int id_;
    string PIB_;
    int age_;
    string rank_;
    string gender_;

    Slave(int id, int age, string PIB, string rank, string gender) {
        this->age_ = age;
        this->gender_ = gender;
        this->id_ = id;
        this->PIB_ = PIB;
        this->rank_ = rank;
    }

};
ostream& operator<<(ostream& out, Slave& X) {
    out << "  id: " << X.id_ << "  age: " << X.age_ << "  gender: " << X.gender_ << "  PIB: " << X.PIB_ << "  rank: " << X.rank_ << '\n';
    return out;
}
class table_Slave {
private:
    vector<Slave> table_;

public:

    void get_read()
    {
        ifstream read("Slave.txt");
        table_.clear();
        int id;
        string PIB;
        int age;
        string rank;
        string gender;
        while (read >> id >> age >> PIB >> rank >> gender)
        {

            table_.push_back(Slave(id, age, PIB, rank, gender));
        }
        read.close();
    }
    void save_slaves()
    {
        ofstream write;
        fstream clear_file("Slave.txt", ios::out);
        clear_file.close();
        write.open("Slave.txt");
        auto it = table_.begin();
        while (it != table_.end())
        {
            Slave X = *it;
            write << X.id_ << ' ' << X.age_ << ' ' << X.PIB_ << ' ' << X.rank_ << ' ' << X.gender_ << '\n';
            it++;
        }
        write.close();
    }
    void delete_row(int id) {
        auto it = table_.begin();
        if (table_.size() == 0)
        {
            cout << "nothing to delite";
        }
        while (it != table_.end())
        {
            Slave X = *it;
            if (X.id_ == id) {
                table_.erase(it);
                break;
            }
            it++;
        }
    }
    Slave add_row(string PIB, string rank, string gender, int age)
    {
        auto it = table_.end();
        int id = 0;
        if (it != table_.begin()) {
        
        it--;
        Slave Y = *it;
        id = Y.id_;
        }
        int* p = new int[0];
        Slave X = Slave(id + 1, age, PIB, rank, gender);
        table_.push_back(X);
        return X;
    }
    Slave get_row_by_id(int id)
    {
        auto it = table_.begin();
        while (it != table_.end())
        {
            Slave X = *it;
            if (X.id_ == id) {
                return X;
                break;
            }
            it++;
        }
        return Slave(0, 0, "", "", "");
    }
    void print_all()
    {
        auto it = table_.begin();
        while (it != table_.end())
        {
            Slave X = *it;
            cout << X;
            it++;
        }
    }
    vector<Slave> get_tbl()
    {
        return table_;
    }
    void update(int id, int age, string PIb, string rank, string gender)
    {
        auto it = table_.begin();
        int k = 0;
        while (it != table_.end())
        {
            Slave X = *it;
            if (X.id_ == id)
            {
                table_.erase(it);
                auto itt = table_.begin();
                for (int i = 0; i < k; i++)
                {
                    itt++;
                }
                table_.insert(itt, Slave(id, age, PIb, rank, gender));
                break;
            }
            it++;
            k++;
        }
    }
};

class Master {
public:
    int id_;
    string name_;
    string district_;
    string region_;
    int numder_of_slaves_;
    int* arr_;

    Master(int id, string name, string district, string region, int num, int* p)
    {
        id_ = id;
        name_ = name;
        district_ = district;
        region_ = region;
        numder_of_slaves_ = num;
        int* p_ = new int[num];
        p_ = p;
        arr_ = p_;

    }
    


};
ostream& operator<<(ostream& out, Master& X) {
    out << "id: " << X.id_ << "  name: " << X.name_ << "  district: " << X.district_ << "  region: " << X.region_ << '\n';
    return out;
}

class table_Master {
private:
    vector<Master> table_;
public:
    vector<Master> get_tbl() {
        return table_;
    }
    void get_read(table_Slave tbl_s)
    {
        table_.clear();
        ifstream read("Master.txt");
        int id, num;
        string name, district, region;

        while (read >> id >> name >> district >> region >> num)
        {
            int* ar = new int[num];
            for (int i = 0; i < num; i++)
            {
                int a;
                read >> a;
                Slave X = tbl_s.get_row_by_id(a);
                ar[i] = X.id_;
            }
            table_.push_back(Master(id, name, district, region, num, ar));

        }
        read.close();
    }
    void save_masters()
    {
        ofstream write;
        fstream clear_file("Master.txt", ios::out);
        clear_file.close();
        write.open("Master.txt");
        auto it = table_.begin();
        while (it != table_.end())
        {
            Master X = *it;
            write << X.id_ << ' ' << X.name_ << ' ' << X.district_ << ' ' << X.region_ << ' ' << X.numder_of_slaves_ << ' ';
            for (int i = 0; i < X.numder_of_slaves_; i++)
            {
                if (X.arr_[i] != 0)
                {
                    write << X.arr_[i] << ' ';
                }
            }
            write << '\n';
            it++;
        }
        write.close();
    }
    void del_master_by_id(table_Slave& tbl, int id)
    {
        auto it = table_.begin();
        while (it != table_.end())
        {
            Master X = *it;
            if (X.id_ == id) {
                int y = 0;
                for (int i = 0; i < X.numder_of_slaves_; X.numder_of_slaves_--)
                {
                    tbl.delete_row(X.arr_[y]);
                    y++;
                }
                tbl.save_slaves();
                table_.erase(it);
                break;
            }
            it++;
        }

    }
    void print_rel_slaves(Master& X, table_Slave& tbl)
    {
        cout << "related rows:" << '\n';
        for (int i = 0; i < X.numder_of_slaves_; i++)
        {
            Slave Z = tbl.get_row_by_id(X.arr_[i]);
            cout << Z << '\n';
        }

    }
    Master get_master_by_id(int id) {
        auto it = table_.begin();
        while (it != table_.end())
        {
            Master X = *it;
            if (X.id_ == id) {
                return X;
                break;
            }
            it++;
        }
        int* p=0;
        return Master(0, "", "", "", 0, p);
    }
    void print_all()
    {
        auto it = table_.begin();
        while (it != table_.end())
        {
            Master X = *it;
            cout << X;
            it++;
        }
    }
    void add_Master(string name, string district, string region)
    {
        int id = 0;
        auto it = table_.end();
        if (it != table_.begin()) {
            it--; Master Y = *it;
             id = Y.id_;
        }
        
        int* p = new int[0];
        table_.push_back(Master(id + 1, name, district,region, 0, p));
    }
    void add_slave(int id_m,int id_s)
    {
        auto it= table_.begin();
        int k = 0;
        while (it != table_.end())
        {
            
            Master X = *it;
            if (X.id_ == id_m)
            {
                int* p = new int[X.numder_of_slaves_ + 1];
                for (int i = 0; i < X.numder_of_slaves_; i++)
                {
                    p[i] = X.arr_[i];
                    
                }
                p[X.numder_of_slaves_] = id_s;
                X.numder_of_slaves_ += 1;
                X.arr_ = p;
                table_.erase(it);
                
                auto itt = table_.begin();
                for (int y = 0; y < k&&itt!=table_.end(); y++)
                {
                    itt++;
                }
                table_.insert(itt, X);
                break;
            }
            k++;
            it++;
        }
    }
    void update(int id, string name, string dis, string reg)
    {
        auto it = table_.begin();
        int k = 0;
        while (it != table_.end())
        {
            Master X = *it;
            if (X.id_ == id)
            {
                table_.erase(it);
                auto itt = table_.begin();
                for (int i = 0; i < k; i++)
                {
                    itt++;
                }
                table_.insert(itt, Master(id,name, dis, reg,X.numder_of_slaves_,X.arr_));
                break;
            }
            it++;
            k++;
        }
    }
};
int main()
{
    table_Slave tbl_s;
    table_Master tbl_m;
    while (true)
    {
        tbl_s.get_read();
        tbl_m.get_read(tbl_s);
        cin.clear();
        string inpt = "";
        cout << "enter command: ";
        cin >> inpt;
        if (inpt == "exit")
        {
            break;
        }
        if (inpt == "get-m")
        {
            cout << "enter id: ";
            int a;
            try {
                cin >> a;
            }
            catch (string) {}
            Master X = tbl_m.get_master_by_id(a);
            if (X.id_ == 0)
            {
                continue;
            }
            cout << X;
            tbl_m.print_rel_slaves(X, tbl_s);
            continue;
        }
        if (inpt == "get-s")
        {
            cout << "enter id: ";
            int a;
            try {
                cin >> a;
            }
            catch (string) {}
            Slave temp = tbl_s.get_row_by_id(a);
            if (temp.id_ == 0) {
                continue;
            }
            cout << temp;
            continue;
        }
        if (inpt == "del-m")
        {
            cout << "enter id to delete: ";
            int a;
            try {
                cin >> a;
            }
            catch (string) {}
            tbl_m.del_master_by_id(tbl_s, a);
            tbl_m.save_masters();
            cout << "done" << '\n';
            continue;
        }
        if (inpt == "del-s")
        {
            cout << "enter id to delete: ";
            int a;
            try {
                cin >> a;
            }
            catch (string) {}
            tbl_s.delete_row(a);
            tbl_s.save_slaves();
            cout << "done" << '\n';
            continue;
        }
        if (inpt == "update-m")
        {
            cout << "enter id to update: ";
            int a;
            try {
                cin >> a;
            }
            catch (string) {}
            Master X = tbl_m.get_master_by_id(a);
            cout << X << '\n';
            string name,dis,reg;            
            try {
                cout << "enter name: ";
                cin >> name;
                cout << "enter district: ";
                cin >> dis;
                cout << "enter region: ";
                cin >> reg;
            }
            catch (char) {}
            tbl_m.update(X.id_,name,dis,reg );
            tbl_m.save_masters();
            continue;
        }
        if (inpt == "update-s")
        {
            cout << "enter id to update: ";
            int a;
            try {
                cin >> a;
            }
            catch (string) {}
            Slave X = tbl_s.get_row_by_id(a);
            cout << X << '\n';
            string PIB, rank, gender;
            int age;
            try {
                cout << "enter age: ";
                cin >> age;
                cout << "enter PIB: ";
                cin >> PIB;
                cout << "enter rank: ";
                cin >> rank;
                cout << "enter gender: ";
                cin >> gender;
            }
            catch (char) {}
            tbl_s.update(X.id_, age, PIB, rank, gender);
            tbl_s.save_slaves();
            continue;
        }
        if (inpt == "insert-m")
        {
            string name="basic", dis="default", reg="none";
            try {
                cout << "enter name: ";
                cin >> name;
                cout << "enter district: ";
                cin >> dis;
                cout << "enter region: ";
                cin >> reg;
                
            }
            catch (char) {}
            tbl_m.add_Master(name, dis, reg);
            tbl_m.save_masters();
            continue;
        }
        if (inpt == "insert-s")
        {
            

            string PIB, rank, gender;
            int age;
            try {
                cout << "enter age: ";
                cin >> age;
                cout << "enter PIB: ";
                cin >> PIB;
                cout << "enter rank: ";
                cin >> rank;
                cout << "enter gender: ";
                cin >> gender;
            }
            catch (char) {}
            
            cout << "available masters: " << '\n';
            tbl_m.print_all();
            
            cout << "enter id of master: ";
            int b = 0;
            try {
                cin >> b;
            }
            catch(char){}
            if (b == 0) {
                tbl_m.save_masters();
                continue;
            }
            Master Check = tbl_m.get_master_by_id(b);
            if (Check.id_ == 0) {                
                continue;
            }
            Slave S = tbl_s.add_row(PIB, rank, gender, age);
            
            tbl_m.add_slave(b, S.id_);
            tbl_m.save_masters();
            tbl_s.save_slaves();
            continue;
        }
        if (inpt == "calc-m")
        {           
            cout<< "number of m rows: "<< tbl_m.get_tbl().size()<<'\n';
            continue;
        }
        if (inpt == "calc-s")
        {
            cout << "number of s rows: " << tbl_s.get_tbl().size()<<'\n';
            continue;
        }
        if (inpt == "ut-m")
        {
            tbl_m.print_all();
            continue;
        }
        if (inpt == "ut-s")
        {
            tbl_s.print_all();
            continue;
        }
        else {
            cout << "invalid command" << '\n';

            continue;
        }

    }
    return 0;
}
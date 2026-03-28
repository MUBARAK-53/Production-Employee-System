#include<iostream>
#include<fstream>
#include<cstring>
#include<stdlib.h>
#include<ctime>
#include<vector>
using namespace std;
/*
1.Admin(HR)
    all employee data 
    payroll slip
    confidential information
2.user
   Employee
   

*/
class Employee
{
    public:
    int id;
    string name,dept;
    string address;
    double annual_tax;
    int leaves=30;
    int present_days=0;
    double Salary;
    double hra()
    {
        return Salary*0.50;//50%
    }

    double pf()
    {
        return Salary*0.12;//12%
    }

    double tax()
    {
        double annual_Salary=Salary*12;
        double annual_tax=(annual_Salary>500000)?(annual_Salary*0.05):0;//5% PF
        return annual_tax/12;
    }

    double net_salary()
    {
        return (Salary+hra())-pf()-tax();
    }
};

// FUNCTION PROTOTYPE 
void add_employee();
void delete_employee();
void update_employee();
void display_unique();
void display_all();
void GeneratePayroll();
void TotalLeaves();
void attendance_tracking();
void Backup_Data();
void Show_Backup_Data();
string Backup_file;
void Restore_Data();


class Admin
{
    public:
    string user="ABC";
    string Upassword="Abc@123";
    string admin="MUBARAK";
    string Apassword="Admin@123";
   void Access() 
   {
    int id;
    string name, pass;
    
    cout << "1.ADMIN  2.USER\n";
    cin >> id;
    
    if(id == 1) {
        cout << "USERNAME:"; cin >> name;
        cout << "PASSWORD:"; cin >> pass;
        if(strcmp(name.c_str(), "MUBARAK") == 0 && strcmp(pass.c_str(), "Admin@123") == 0) {
            cout << "ADMIN LOGIN SUCCESSFUL!!\n";
            AdminMenu();
        }
        else{
            cout<<"ADMIN NOT FOUND!!"<<endl;
        }
    }
    else if(id == 2) {          
        cout << "USERNAME:"; cin >> name;
        cout << "PASSWORD:"; cin >> pass;
        if(strcmp(name.c_str(), "ABC") == 0 && strcmp(pass.c_str(), "Abc@123") == 0) {
            cout << "USER LOGIN SUCCESSFUL!!\n";
            userMenu();
        }
        else {
            cout << "USER NOT FOUND!!\n";
        }
    }
};

  void userMenu()
  {
     int choose;
    int choice;
    do
    {
           
            cout<<"1.ADD EMPLOYEE\n2.DELETE EMPLOYEE\n3.UPDATE EMPLOYEE\n4.SEARCH EMPLOYEE\n5.APPLY LEAVE\n6.EXIT";
            cin>>choose;
            switch(choose)
            {
                case 1: add_employee(); break;
                case 2: delete_employee(); break;
                case 3: update_employee(); break;
                case 4: display_unique(); break;
                case 5: TotalLeaves();break;
                case 6: return;break;
                default: cout<<"WRONG INPUT"<<endl;
            }
    }while(choose!=6);

  }


   void AdminMenu()
  {
       int choose;
    do
    {

 
            cout<<"1.PAYROLL\n2.ATTENDANCE\n3.EMPLOYEE DETAILS\n4.SEARCH EMPLOYEE\n5.BACKUP DATA\n6.SHOW BACKUP\n7.RESTORE\n8.EXIT\n";
            cin>>choose;
            switch(choose)
            {
                case 1: GeneratePayroll(); break;
                case 2: attendance_tracking(); break;
                case 3: display_all(); break;
                case 4: display_unique(); break;
                case 5: Backup_Data();break;
                case 6:Show_Backup_Data(); break;
                case 7: Restore_Data();break;
                case 8: return;break;
                default: cout<<"WRONG INPUT"<<endl;
            }
    }while(choose!=8);

  }


};


vector<Employee>employees;

int current_id=1000;

int id_no()
{
    
    return current_id++;
}


void add_employee()
{
    Employee e;
    
    cout<<"NAME:"<<endl;
    cin>>e.name;
    cout<<"DEPARTMENT:"<<endl;
    cin>>e.dept;
    cin.ignore();
    cout<<"ADDRESS:"<<endl;
    getline(cin,e.address);
    cout<<"ENTER SALARY:"<<endl;
    cin>>e.Salary;
    e.id=id_no();
    cout<<"YOUR ID:"<<e.id<<endl;

    ofstream file("Employees.txt",ios::app);
    if(file.is_open())
    {
        file << "ID:" << e.id << endl;
        file << "NAME:" << e.name << endl;
        file << "DEPT:" << e.dept << endl;
        file << "ADDRESS:" << e.address << endl;
        file << "SALARY:" << e.Salary << endl;
        file <<  "TAX:"<<e.tax()<<endl;
        file << "LEAVES:" << e.leaves << endl << "--------" << endl;
        file.close();
        employees.push_back(e);

        cout << "Employee saved!" << endl;
    }

}

void display_all()
{
    ifstream infile("Employees.txt");
    if(!infile.is_open())
    {
        cout<<"ERROR OPENING FILE!!"<<endl;
    }
    string line;

    while(getline(infile,line))
    {
        cout<<line<<endl;
    }
    infile.close();
}


void display_unique()
{
    int id_num;
    cout<<"ENTER SEARCH ID:"<<endl;
    cin>>id_num;
    bool found=false;
    ifstream infile("Employees.txt");
    string line;

   while(getline(infile, line))
    {
        if(line.find("ID:"+to_string(id_num)) == 0)
        {
            found = true;
            // Print ID line
            cout << line << endl;
            while(getline(infile, line) && line !="--------")
            {
                cout << line << endl;
            }
            cout << line << endl; 
            break;  // Stop after first match
        }
    }
}

void TotalLeaves()
{
    int id;
    int total; 

    char confirm;
    cout<<"ENTER ID:"<<endl;
    cin>>id;

    for(int i=0;i<employees.size();i++)
    {
        if(id==employees[i].id)
        {
            cout<<"YOUR TOTAL LEAVES REMAINING: "<<employees[i].leaves<<"DAYS"<<endl;
            cout<<"DO YOU WANT TO TAKE LEAVES:"<<endl;
            cin>>confirm;
            

            if(confirm=='y'||confirm=='Y')
            {
                cout<<"ENTER TOTAL DAYS LEAVE:"<<endl;
                cin>>total;
                employees[i].leaves-=total;

                cout<<"TOTAL REMAINING LEAVES:"<<employees[i].leaves<<" DAYS"<<endl;


            }
            
        }

    }
}


void GeneratePayroll()
{
    int id;
    string month;
    bool found=false;
   
    cout<<"ENTER YOUR ID:"<<endl;
    cin>>id;
    cout<<"Enter Month: "<<endl;
    cin>>month;

    string filename="PAYROLL-"+month+"-"+to_string(id)+".txt";


        for(int i=0;i<employees.size();i++)
    {
       if(employees[i].id == id)
{
    ofstream outfile (filename);
    string line ;
        
if(!outfile.is_open())
{
    cout<<"EMPLOYEE NOT FOUND";
    return;
}
   outfile<< "\n=== PAYROLL SLIP ===" << endl;
   outfile<<"EMPLOYEE     :  "<<employees[i].name<<endl;
   outfile << "ID         :  " << employees[i].id<< endl;
   outfile << "Dept       :  " << employees[i].dept << endl;
   outfile<<"BASIC PAY    :  "<<employees[i].Salary<<endl;
   outfile<<"HRA          :  "<<employees[i].hra()<<endl;
   outfile<<"PF DEDUCTION :  "<<employees[i].pf()<<endl;
   outfile<<"TAX          :  "<<employees[i].tax()<<endl;
   outfile<<"NET SALARY   :  "<<employees[i].net_salary()<<endl;
   outfile.close();

    ifstream infile(filename);
    if(infile.is_open())
    {
        string line;
        cout<<"----PAYROLL SLIP FOR "<<month<<"---"<<endl;
        while(getline(infile,line))
    {
        cout<<line<<endl;

    }
    infile.close();
    }
      
    else
    {
        cout<<"FAILED TO READ PAYROLL SLIP"<<endl;
    }  

    found=true;
    break;
    
}  
    if(!found)
    {
        cout<<"ERROR: CANNOT READ GENERATED SLIP!!!"<<endl;
    }
    }
    
}

void attendance_tracking()
{
    int id;
    cout<<"ENTER ID:"<<endl;
    cin>>id;
    bool found=false;
    
    for(int i=0; i<employees.size(); i++)
    {
        ofstream outfile("ATTENDANCE.txt", ios::app);
        if(id==employees[i].id)
        {
            // Mark & write
            employees[i].present_days++;
           
            outfile << "ID:" << id << " TOTAL DAYS:" << employees[i].present_days << endl;
            outfile.close();
            
            // Display ONLY for this employee
            ifstream infile("ATTENDANCE.txt");
            if(infile.is_open())
            {
                string line;
                while(getline(infile, line))
                {
                    if(line.find("ID:"+to_string(id))==0)
                    {
                        cout << line << endl;
                    }
                }
                infile.close();
            }
            found=true;
            return;  // Exit after success
        }
    }
    cout << "EMPLOYEE NOT FOUND" << endl;
}


void delete_employee()
{
    int id;
    bool found=false;
    cout<<"ENTER ID:";
    cin>>id;
    for(int i=0;i<employees.size();i++)
    {
        if(id==employees[i].id)
        {
            employees.erase(employees.begin()+i);
            cout<<"EMPLOYEE DELETED!!"<<endl;
            found=true;
            break;
        }
    }
    if(!found)
        {
            cout<<"EMPLOYEE NOT FOUND!!"<<endl;
        }
}

void update_employee()
{   
    int id,choice;
    cout<<"ENTER ID:";
    cin>>id;
    for(int i=0;i<employees.size();i++)
    {
        if(id==employees[i].id)
        {
            cout<<"1.NAME\n2.DEPARTMENT\n3.ADDRESS"<<endl;
            cin>>choice;
            
            if(choice==1)
            {
                cout<<"ENTER NEW NAME:"<<endl;
                cin>>employees[i].name;
            }
              
            else if(choice==2)
            {
                cout<<"ENTER NEW DEPARTMENT:"<<endl;
                cin>>employees[i].dept;
            }
              
           else if(choice==3)
            {
                cout<<"ENTER NEW ADDRESS:"<<endl;
                cin>>employees[i].address;
            }

        }
    }

}


void Backup_Data()
{
    string filename;
    cout<<"BACKUP DATA TO:"<<endl;
    cin>>Backup_file;

    ifstream src("Employees.txt");
    if(!src.is_open())
    {
        cout<<"NOT FOUND !";

    }
    ofstream dst(Backup_file);
    dst<<src.rdbuf();

    cout<<"DATA BACKUP SUCCESSFUL!!!"<<endl; 
}



void Show_Backup_Data()
{
    ifstream infile(Backup_file);
    string line;
    if(!infile.is_open())
    {
        cout<<"BACKUP NOT FOUND !";

    }
    cout<<"------BACKUP CONTENT-------\n";


        while(getline(infile,line))
        {
            cout<<line<<endl;
        }
   

    cout<<"  READING BACKUP FILE SUCCESSFUL !!!"<<endl; 
}


void Restore_Data()
{
    
    string filename;
    cout<<"RESTORE DATA FROM:"<<endl;
    cin>>filename;

    ifstream src(filename);
    if(!src.is_open())
    {
        cout<<"BACKUP NOT FOUND !";
    }

    ofstream dst("Employees.txt");
    dst<<src.rdbuf();
    cout<<"RESTORED FROM "<<filename<<" SUCCESSFUL!"<<endl;
    
}

int main()
{
    
    char login;
    Admin a;

        a.Access();
    
    return 0;
}
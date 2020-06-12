#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
using namespace std;
int i;
class customer
{char name[50],address[200];
int dd,mm,yyyy,cznno,age,accno;long  int pno;
float amount;
char typeofacc;
public: void newaccount();
		void viewlist();
		void edit();
		void transact();
		void see();
		int getaccno()
		{return accno;}
}c;
void customer::newaccount()
{cout<<"\nEnter account no";
cin>>accno;
cout<<"\nEnter name:";
cin>>name;
cout<<"\nEnter date of birth:";
cout<<"\nEnter date:dd";
cin>>dd;
cout<<"\nEnter month:mm";
cin>>mm;
cout<<"\nEnter year of birth:yyyy";
cin>>yyyy;
cout<<"\nEnter citizenship no:";
cin>>cznno;
cout<<"\nEnter age:";
cin>>age;
cout<<"\nEnter address:";
cin>>address;
cout<<"\nEnter phone no:";
cin>>pno;
cout<<"\nEnter amount to be deposited:";
cin>>amount;
cout<<"\nEnter type of deposit account";
cout<<"\nEnter 's' for savings account";
cout<<"\nEnter 'c' for current account";
cout<<"\nEnter 'f' for fixed for 1 year";
cout<<"\nEnter 'e' for fixed for 2 years";
cout<<"\nEnter 't' for fixed for 3 years";
cin>>typeofacc;
}
void customer::viewlist()
{cout<<"\tAccount Number:"<<accno;
cout<<"\tName:"<<name;
cout<<"\tAddress:"<<address;
cout<<"\tPhone Number:";
cout<<pno;
}
void customer::edit()
{int a;
cout<<"\n Enter 1 for changing address";
cout<<"\n Enter 2 for changing phone no";
cin>>a;
switch(a)
{ case 1: {char ad[200];
		   cout<<"\nEnter new address";
		   cin>>ad;
		   strcpy(address,ad);
		   break;
          }
  case 2: {long pn;
            cout<<"\nEnter new phone no";
            cin>>pn;
            for(i=0;i<10;++i)
            pno=pn;
	        break;
            }
     
}
}
void customer::transact() 
{int a;int date,month,year;
cout<<"\nEnter 1 for deposition:";
cout<<"\nEnter 2 for withdrawal:";
cin>>a;
switch(a)
	{ case 1: {float num;
			  cout<<"\nEnter amount to be deposited";
			  cin>>num;
			  amount=amount+num;
			  break;
	         }
	  case 2: {float num;
	  			cout<<"\nEnter amount to withdraw";
	  			cin>>num;
	  			if(num>amount)
	  			cout<<"\n Withdrawal not possible";
	  			else
	  			amount=amount-num;
				break;
	          }       
}
}
void customer::see()
{cout<<"\tAccount No:"<<accno;
cout<<"\tName:"<<name;
cout<<"\tDate of birth:"<<dd<<mm<<yyyy;
cout<<"\tAddress:"<<address;
cout<<"\tAmount deposited"<<amount<<"\n";
}
int main()
{system("color 09");
int ch,j=1;
do
{system("cls");
cout<<"\n                            			CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM      									";
cout<<"\n \n \n                                 ##### WELCOME TO THE MAIN MENU #####												";

cout<<"\n1.Create new account"
	<<"\n2.Display account banking information"
	<<"\n3.Update information of existing account"
	<<"\n4.For transactions"
	<<"\n5.Removing existing account"
	<<"\n6.View customer's list";
cout<<"\n\n\n Enter your choice:";
cin>>ch;
switch(ch)
   {
		case 1: {ofstream fout;
					fout.open("BankCustomer.dat",ios::app|ios::binary);
				c.newaccount();
				fout.write((char *)&c,sizeof(c));
				fout.close();
				break;
			    }
		case 2:{int ano;char found='n';
				ifstream fin("BankCustomer.dat",ios::in|ios::binary);
				cout<<"\n Enter account no to be searched for:";
				cin>>ano;
				while(!fin.eof())
				{fin.read((char*)&c,sizeof(c));
				 if(c.getaccno()==ano)
				 {c.viewlist();
				   found='y';
				   break;
				 }
				}
				if(found=='n')
				cout<<"\n Account not found";
				fin.close();
				break;
			   }
		case 3: {fstream fin("BankCustomer.dat",ios::in|ios::out|ios::binary);
				int ano;long pos;char found='f';
				cout<<"\n Enter account no whose record is to be modified";
				cin>>ano;
				while(!fin.eof())
				{ pos=fin.tellg();
				  fin.read((char*)&c,sizeof(c));
				  if(c.getaccno()==ano)
				  {c.edit();
				   fin.seekg(pos);
				   fin.write((char*)&c,sizeof(c));
				   found='t';
				   break;
				  }
				}
				if(found=='y')
				cout<<"\n Account not found"; 
				fin.seekg(0);
				fin.close();
				break;
			    }
		case 4: {fstream fin("BankCustomer.dat",ios::in|ios::out|ios::binary);
					int ano,pos;
					cout<<"\nEnter account no:";
					cin>>ano;
					while(!fin.eof())
						{pos=fin.tellg();
						   fin.read((char*)&c,sizeof(c));
						     if(c.getaccno()==ano)
						     {c.transact();
						      fin.seekg(pos);
						      fin.write((char*)&c,sizeof(c));
						      break;
							 }
						}
						fin.close();
						break;
				}
		case 5: {ifstream fin("BankCustomer.dat",ios::in|ios::binary);
				 ofstream fout("temp.dat",ios::out|ios::binary);
				 int ano;
				 char found='n';
				 cout<<"\nEnter account no to be deleted";
				 cin>>ano;
				 fin.seekg(0);
				 fin.read((char*)&c,sizeof(c));
				 while(!fin.eof())
				 {  
				 	if(c.getaccno()==ano)
				 	 found='t';
					else
					fout.write((char*)&c,sizeof(c));
					fin.read((char*)&c,sizeof(c));
			     }
					if(found=='n')
					cout<<"\nFile not found";
					else
					cout<<"\nRecord deleted";
					fin.close();
					fout.close();
					remove("BankCustomer.dat");
					rename("temp.dat","BankCustomer.dat");
				   break;
		        }
		case 6: {ifstream fin("BankCustomer.dat",ios::in|ios::binary);
					while(fin.read((char*)&c,sizeof(c)))
							{
							  c.see();}
							fin.close();
							break;
				}
		case 7:exit(0);
			
		default: cout<<"wrong choice";
		
	}
	cout<<"\nwant to do more \n press 1 to continue";
	cin>>i;
	
}while(j==1);
return 0;
} 

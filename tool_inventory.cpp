//*************************************
//IT310 GUI Programming with C++
//Programmer: Ryan Ellorin
//Program   : Tool Inventory Linked Lists
//*************************************

#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

//global variables
ifstream fin;

struct invtype
{
    int ID;
    char name[26];
    float price;
    float markup;
    float whole;
    int qty;
    float retail;
    float value;
    invtype *link;   
              
};  //don't forget   

void headerfn();  //void fn without parameters
void inputfn(invtype *&head);
void outputfn(invtype *head);
void addbegfn(invtype *&head, invtype *&nnptr);
void addmidfn(invtype *&head);
void addendfn(invtype *head, invtype *currptr, invtype *nnptr);
void deletefn(invtype *&head);

int main()
{
    headerfn();  //stand alone fn call
    
    fin.open("tools.txt");
    if(!fin)
    {
      cout<<"Input error.\n"<<endl;
      
      system("pause");
    }//error check
    
    invtype *head, *currptr, *nnptr;   //pointer declaration
    int option;
  
    inputfn(head);
    outputfn(head);    
  
    bool flag = true;
    while(true)
    {
      cout<<"\nPlease enter 1 to Add to Beginning:"<<endl
          <<"             2 to Add to Middle   :"<<endl
          <<"             3 to Add to End      :"<<endl
          <<"             4 to Delete a tool   :"<<endl
          <<"             5 to Print the Inventory List: ";
      cin>>option;
      
      switch(option)
      {
        case 1: addbegfn(head, nnptr); break;
        case 2: addmidfn(head); break;
        case 3: addendfn(head, currptr, nnptr); break;
        case 4: deletefn(head); break;
        case 5: cout<<endl;
                outputfn(head);  break;
        default: cout<<"This is not a valid option.";
      }//end of switch
    }//end of while
  
  
     
    cout<<"\nPress any key to continue.";
    getch();
    
}//end of main
//*********************************************************************************************************************
void headerfn()
{
  cout<<"***************************************"<<endl;
  cout<<"IT310 GUI Programming with C++"<<endl;
  cout<<"Programmer: Ryan Ellorin"<<endl;
  cout<<"Program   : Tool Inventory Linked Lists"<<endl;
  cout<<"***************************************"<<endl;   
      
     
     
}//end of headerfn
//********************************************************************************************************************
void inputfn(invtype *&head)
{
  invtype *currptr, *nnptr;    
  int counter = 0;   
  
  
    fin.ignore(70, '\n');  //ignores first 70 numbers in input text
    
    
    //first node declaration
    head = new invtype;  
    fin>>head->ID;
    
    fin.ignore(1, ' ');
    fin.get(head->name, 26);  //reads head node tool description
    
   
    fin>>head->whole>>head->markup>>head->qty;
    head->retail = float(head->markup * head->whole);  //first node retail calculation
    head->value =  float(head->retail * head->qty);    
    currptr = head;  
    counter ++;
     
    
    //while loop reading information into the other nodes
    while(fin)
    {
      
      nnptr = new invtype;
      fin>>nnptr->ID;
      
      fin.ignore(1, ' ');
      fin.get(nnptr->name, 26);  //reads the rest of the nodes tool description
    
         
      fin>>nnptr->whole>>nnptr->markup>>nnptr->qty;
      nnptr->retail = float(nnptr->markup * nnptr->whole);  //retail calculation
      nnptr->value = float(nnptr->retail * nnptr->qty);
            
      currptr->link = nnptr;
      currptr = nnptr;
     
      counter++;
      if(fin.peek() == '\n')fin.ignore();  
    }//end of while
    
    currptr->link = NULL;
    currptr = NULL;
    nnptr = NULL;   
          
     
}//end of inputfn
//******************************************************************************************************
void outputfn(invtype *head)
{
  invtype *currptr;
  float totalinv = 0;

  cout<<fixed<<showpoint<<setprecision(2);
  cout<<setfill('=')<<setw(80)<<('=')<<endl;
  cout<<setfill(' ');
  cout<<setw(50)<<"Inventory Linked Lists"<<endl;
  cout<<setfill('=')<<setw(80)<<('=')<<endl;
  cout<<setfill(' ');
  cout<<setw(8)<<right<<"ProdID"<<setw(17)<<"Tool Name"<<setw(21)<<"Wholesale"<<setw(10)<<"Markup%"
      <<setw(6)<<"Qty"<<setw(6)<<"Rtl"<<setw(9)<<"Value"<<endl;
  cout<<setfill('-')<<setw(80)<<('-')<<endl;
  cout<<setfill(' ');
  
  currptr = head;
  while(currptr!=NULL)
  {
    cout<<setw(7)<<currptr->ID<<setw(5)<<(' ')<<setw(25)<<left<<currptr->name<<setw(7)<<right<<currptr->whole<<setw(10)
        <<currptr->markup<<setw(7)<<currptr->qty<<setw(8)<<currptr->retail<<setw(8)<<currptr->value<<endl;
    currptr = currptr->link;
    
  }//end of while 
  
  currptr = head;
  while(currptr!=NULL)
  {
    totalinv += currptr->value;
    currptr = currptr->link;
  }//end of while
  
  
  cout<<setfill('-')<<setw(80)<<('-')<<endl;
  cout<<setfill(' ');  
  cout<<setw(3)<<(' ')<<"Total Inventory: "<<totalinv<<endl;
  cout<<setfill('=')<<setw(80)<<('=')<<endl;
  
     
}//end of outputfn
//****************************************************************************************************
void addbegfn(invtype *&head, invtype *&nnptr)
{

    nnptr = new invtype;
    cout<<"Please enter a Product ID: ";
    cin>>nnptr->ID; 
    cin.ignore();        
    cout<<"Please enter a Product Description: ";
    cin.get(nnptr->name, 26);
    cout<<"Please enter a Product Wholesale Price: ";
    cin>>nnptr->whole;
    cout<<"Please enter a Product Markup Percentage: ";
    cin>>nnptr->markup;
    cout<<"Please enter a Product Quantity: ";
    cin>>nnptr->qty;
    
    nnptr->retail = float(nnptr->markup * nnptr->whole);
    nnptr->value = float(nnptr->retail * nnptr->qty);
    
    nnptr->link = head;
    head = nnptr;
    
     
     
}//end of addbegfn
//****************************************************************************************************
void addmidfn(invtype *&head)
{
  invtype *currptr, *nnptr;
  int tID;
  
  cout<<"Please enter the tool ID you'd like to add after: ";
  cin>>tID;
  
  currptr = head;
  
  while(currptr->ID != tID && currptr!=NULL)   
  {
    currptr = currptr->link;
  }//end of while
  
  nnptr = new invtype;
  cout<<"Please enter a Product ID: ";
  cin>>nnptr->ID;
  cin.ignore();         
  cout<<"Please enter a Product Description: ";
  cin.get(nnptr->name, 26);
  cout<<"Please enter a Product Wholesale Price: ";
  cin>>nnptr->whole;
  cout<<"Please enter a Product Markup Percentage: ";
  cin>>nnptr->markup;
  cout<<"Please enter a Product Quantity: ";
  cin>>nnptr->qty;
  
  nnptr->retail = float(nnptr->markup * nnptr->whole);
  nnptr->value = float(nnptr->retail * nnptr->qty);
       
  nnptr->link = currptr->link;
  currptr->link = nnptr;
  
  currptr = NULL;
  nnptr = NULL;   
         
     
}//end of addmidfn
//**************************************************************************************************
void addendfn(invtype *head, invtype *currptr, invtype *nnptr)
{
  currptr = head;
  while(currptr->link != NULL)currptr = currptr->link;  
  
  nnptr = new invtype;
  cout<<"Please enter a Product ID: ";
  cin>>nnptr->ID;
  cin.ignore();         
  cout<<"Please enter a Product Description: ";
  cin.get(nnptr->name, 26);
  cout<<"Please enter a Product Wholesale Price: ";
  cin>>nnptr->whole;
  cout<<"Please enter a Product Markup Percentage: ";
  cin>>nnptr->markup;
  cout<<"Please enter a Product Quantity: ";
  cin>>nnptr->qty;
  
  nnptr->retail = float(nnptr->markup * nnptr->whole);
  nnptr->value = float(nnptr->retail * nnptr->qty);
  
  currptr->link = nnptr;
  currptr = currptr->link;
  
  currptr->link = NULL;
  currptr = NULL;
  nnptr = NULL;
     
         
}//end of addendfn
//*************************************************************************************************
void deletefn(invtype *&head)
{
  invtype *currptr, *nnptr, *delptr;
  int delID;
  
  currptr = head;
  delptr = currptr->link;
  
  cout<<"\nPlease enter the Product ID you wish to delete: ";
  cin>>delID;
  
  if(head->ID == delID)
  {
    head = delptr;
    
    cout<<"\nYou are about to delete "<<delptr->name<<".\nPress any key to continue.";
    getch();
    
  }//end of if     
     
  else
  {
    while(delptr->ID != delID && delptr != NULL)
    {
      currptr = currptr->link;
      delptr = delptr->link;
    }//end of while   
  
    if(delptr->link == NULL)
    {
      delete delptr;
      currptr->link = NULL;
      
      cout<<"\nYou are about to delete "<<delptr->name<<".\nPress any key to continue."<<endl;
      getch();
      
      return;
    }//end of inner if
   
   cout<<"\nYou are about to delete "<<delptr->name<<".\nPress any key to continue."<<endl;
   getch();
    
    currptr->link = currptr->link->link;
    
    delete delptr;
  
  }//end of else 
  
  delptr = NULL;
  currptr = NULL;
     
}//end of deletefn

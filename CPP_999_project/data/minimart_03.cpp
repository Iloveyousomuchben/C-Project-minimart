#include<iostream>		//for using cin-cout, left, right
#include<iomanip>		//for using format setw()
#include<cstring>		//for using string: array of char
#include<fstream>    	//for extranal file
#include<windows.h>		//for EXIT_FAILURE	
#include "menagement.cpp"	

using namespace std;

int load_data(ifstream&, product[], int&);
int dump_data(ofstream&, product[], int);
int insert_data(ofstream&, product[], int);
void menuSelect(int&);
void tableHeader(int);
void print(product[], int);
int searchIndex(product[],int,int);
void copyProduct(product[], product[], int);
void showMenuSale(product[],int);
int stockAll(product[], int, int);
int reorderList(ofstream&, product[], int&);
int addNewItem(ofstream&, product[], int&);
int saleList(ofstream&, product[], int);

//struct product {
//	string name;
//	int id,instock, cost, price;
//};
//
//struct sale {
//	string name;
//	int id, qty, cost, price;
//	int date[3];
//};

int main(){
	
	product p[1000]; //all product
	int psize=0;
	int menu;
	
	ifstream ids;  
	ofstream ods; 
	
	load_data(ids,p,psize);
	
	do
    {
		system("cls");
      	menuSelect(menu);
		switch(menu){
			case 1	: stockAll(p,psize,1);	    break;
			case 2	: addNewItem(ods,p,psize);  break;
         	case 3	: reorderList(ods,p,psize); break;  
         	case 4	: saleList(ods,p,psize);  	break;
         	case 9  : cout<<endl<<"Bye Buy!!!"<<endl<<endl;
			 		  break;
		}
      	system("pause");
    }while(menu!=5);
	
	return 0;
}



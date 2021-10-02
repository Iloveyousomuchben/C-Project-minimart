#include<iostream>		//for using cin-cout, left, right
#include<iomanip>		//for using format setw()
#include<cstring>		//for using string: array of char
#include<fstream>    	//for extranal file
#include<windows.h>		//for EXIT_FAILURE	

using namespace std;

struct product {
	string name;
	int id,instock, cost, price;
};

struct sale {
	string name;
	int id, qty, cost, price;
	int date[3];
};	

//******************************************************************
//******************************************************************
void menuSelect(int& select){
     cout<<"---- menu ----"<<endl;
     cout<<"1. stock all"<<endl;
     cout<<"2. add new goods"<<endl;
     cout<<"3. reorder"<<endl;
     cout<<"4. selling"<<endl;
     cout<<"9. end"<<endl;
     cout<<"Select : ";				cin>>select;
}
//----------------------
int load_data(ifstream& ids, product p[], int& size){
    string name; 
	int id,instock,price,cost,t_price,t_cost,profit;
	int i=0;
    ids.open("data/goods.txt");		//i = input = open for read txt.
    if(ids.fail())    {
       	cerr<<"Can't open goods.txt"<<endl;
       	system("pause");
       	return EXIT_FAILURE;           
   	}
    ids>>id;
    p[size].id = id;
    while(!ids.eof()){
        ids>>name>>instock>>cost>>price;
        p[size].name = name;
        p[size].instock = instock;
        p[size].cost = cost;
        p[size].price = price;
        
		size++;
        ids>>id;
		p[size].id = id;       
    }  
	ids.close();  
}
//----------------------
void tableHeader(int type){
	
	switch(type){
		case 1:		//for show all
		cout<<"============================================================================="<<endl;
			cout<<left<<setw(5)<<"id";  
			cout<<setw(12)<<"name";    
			cout<<right<<setw(7)<<"instock";
			cout<<setw(7)<<"cost"; 
			cout<<setw(7)<<"price"; 
			cout<<setw(10)<<"t_cost"; 
			cout<<setw(10)<<"t_price"; 
			cout<<setw(10)<<"profit"<<endl; 
			cout<<"============================================================================="<<endl;
			break;
		case 2:		//for buy
			cout<<"============================================================================="<<endl;
			cout<<left<<setw(5)<<"id";  
			cout<<setw(12)<<"name";    
			cout<<right<<setw(7)<<"instock";
			cout<<setw(7)<<"cost"<<endl;
			cout<<"============================================================================="<<endl; 
			break;
		case 3:		//for list for sale
			cout<<"==================================================================="<<endl;
			cout<<left<<setw(5)<<"id";  
			cout<<setw(12)<<"name";    
			cout<<right<<setw(7)<<"instock";
			cout<<setw(7)<<"price";
			cout<<" || ";
			cout<<left<<setw(5)<<"id";  
			cout<<setw(12)<<"name";    
			cout<<right<<setw(7)<<"instock";
			cout<<setw(7)<<"price"<<endl;
			cout<<"==================================================================="<<endl; 
			break;
		case 4:		//for item sale
			cout<<"============================================================================="<<endl;
			cout<<left;
			cout<<setw(12)<<"date";
			cout<<setw(5)<<"id";  
			cout<<setw(12)<<"name";    
			cout<<right<<setw(7)<<"qty";
			cout<<setw(7)<<"price"; 
			cout<<setw(10)<<"t_price"<<endl; 
			cout<<"============================================================================="<<endl;
			break;
		case 5:		//for show sale all
			cout<<"============================================================================="<<endl;
			cout<<left<<setw(5)<<"id";  
			cout<<setw(12)<<"name";    
			cout<<right<<setw(7)<<"instock";
			cout<<setw(7)<<"cost"; 
			cout<<setw(7)<<"price"; 
			cout<<setw(10)<<"t_cost"; 
			cout<<setw(10)<<"t_price"; 
			cout<<setw(10)<<"profit"<<endl;
			cout<<setw(12)<<"date"<<endl;
			cout<<"============================================================================="<<endl;
			break;
	}
    
}
//----------------------
void print(product p[], int size){
	int t_cost, t_price, profit;
	int gt_cost, gt_price, gt_profit;
	
	gt_cost = gt_price = gt_profit = 0;
	
	for(int i=0; i<size; i++){
		cout<<left;
		cout<<setw(5)<<p[i].id;
		cout<<setw(12)<<p[i].name;
		cout<<right;
		cout<<setw(7)<<p[i].instock;
		cout<<setw(7)<<p[i].cost;
		cout<<setw(7)<<p[i].price; 
		
		t_cost = p[i].instock * p[i].cost;
		t_price = p[i].instock * p[i].price;
		profit = t_price - t_cost;
		gt_cost += t_cost;
		gt_price += t_price;
		gt_profit += profit;
		
		cout<<setw(10)<<t_cost; 
		cout<<setw(10)<<t_price; 
		cout<<setw(10)<<profit<<endl; 
	} 	
	cout<<"============================================================================="<<endl;
	cout<<left;
	cout<<setw(5)<<"";
	cout<<setw(12)<<"";
	cout<<right;
	cout<<setw(7)<<"";
	cout<<setw(7)<<"";
	cout<<setw(7)<<""; 
	cout<<setw(10)<<gt_cost; 
	cout<<setw(10)<<gt_price; 
	cout<<setw(10)<<gt_profit<<endl; 
	cout<<"============================================================================="<<endl;	
}
//----------------------
int searchIndex(product p[],int size,int id){
	int index=0;
	while(p[index].id != id && index<size){
		index++;
	}
	return index;
}
//----------------------
int stockAll(product p[], int size, int type){
	system("cls");
	tableHeader(type);
	print(p, size);
}
//******************************************************************
//******************************************************************
int dump_data(ofstream& ods,product p[], int size){
	
	ods.open("data/goods.txt");	//o = output = open for write txt.
   	if(ods.fail()){
     	cerr<<"Can't open goods.txt"<<endl;
       	system("pause");
       	return EXIT_FAILURE;           
   	}
   	
    for(int i=0; i<size; i++){
    	ods<<left;
        ods<<setw(5)<<p[i].id;
		ods<<setw(12)<<p[i].name;
		cout<<right;
		ods<<setw(7)<<p[i].instock;
		ods<<setw(7)<<p[i].cost;
		ods<<setw(7)<<p[i].price<<endl;                      
    } 
    ods.close();
}
//----------------------
int insert_data(ofstream& ods, sale ss[], int size){
	
	ods.open("data/sallingList.txt", ios_base::app);	//o = output = open for write append txt.
   	if(ods.fail()){
     	cerr<<"Can't open reorder.txt"<<endl;
       	system("pause");
       	return EXIT_FAILURE;           
   	}	
   	for(int i=0; i<size; i++){
		ods<<left;
		ods<<setw(5)<<ss[i].id;
		ods<<setw(12)<<ss[i].name;
		ods<<right;
		ods<<setw(7)<<ss[i].qty;
		ods<<setw(7)<<ss[i].price;
		ods<<setw(10)<<ss[i].qty*ss[i].price;
		ods<<setw(5)<<ss[i].date[0];  
		ods<<setw(5)<<ss[i].date[1]; 
		ods<<setw(7)<<ss[i].date[2]<<endl; 	
	}
	ods.close();
}
//----------------------
int addNewItem(ofstream& ods, product p[], int& size){
	int id, cost, price, qty;
	string name;
	cout<<"\nLast Id : "<<p[size-1].id<<endl;
	cout<<"Insert New Id : ";	cin>>id;
	cout<<"Insert Name   : ";	cin>>name;
	cout<<"Insert QTY.   : ";	cin>>qty;
	cout<<"Insert Cost   : ";	cin>>cost;
	cout<<"Insert Price  : ";	cin>>price;
	p[size].id = id;
	p[size].name = name;
	p[size].instock = qty;
	p[size].cost = cost;
	p[size].price = price;
	size++;
	dump_data(ods,p,size);
}
//----------------------
int reorderList(ofstream& ods, product p[], int& size){
	int min, id, qty, index, type;
	char check;
	system("cls");
	cout<<"Reorder----------: "<<endl;
	cout<<"Search min stock : ";		cin>>min;
	
	do{
		system("cls");
		cout<<"Reorder----------: "<<endl;
		cout<<"Search min stock : "<<min<<endl;
		tableHeader(2);
		for(int i=0; i<size; i++){
			if(p[i].instock < min){
				cout<<left<<setw(5)<<p[i].id;  
				cout<<setw(12)<<p[i].name;    
				cout<<right<<setw(7)<<p[i].instock;
				cout<<setw(7)<<p[i].cost<<endl; 
			}
		}
		
		cout<<"\nDo you want to buy item into stock? (Y or N) : ";	cin>>check;
		
		if(check=='Y' or check=='y'){
			cout<<"--------------"<<endl;
			cout<<"Buying : "<<endl;	
			cout<<"  1. Old Item"<<endl;
			cout<<"  2. New Item"<<endl;
			cout<<"--------------"<<endl;
			cout<<"Select Type : ";		cin>>type;
			
			switch(type){
				case 1: cout<<"\t input id : ";	cin>>id;
						cout<<"\t input qty: ";	cin>>qty;
						index = searchIndex(p,size,id);
						if(index<size){
							p[index].instock += qty;
						}
						dump_data(ods,p,size);
						break;
				case 2: addNewItem(ods,p,size);
						break;
			}
			
		}
			
	} while(check=='Y' or check=='y'); 
		
}
//----------------------

//******************************************************************
//******************************************************************
void copyProduct(product copy[],product ori[],int size){
	for(int i=0; i<size; i++){
		copy[i].id = ori[i].id;
		copy[i].name = ori[i].name;
		copy[i].instock = ori[i].instock;
		copy[i].cost = ori[i].cost;
		copy[i].price = ori[i].price;	
	}
}
//----------------------
void showMenuSale(product pp[],int size){
	system("cls");
	cout<<"Selling--------: "<<endl;
	tableHeader(3);
	for(int i=0; i<size; i++){
		if(pp[i].instock>0){
			cout<<left;
			cout<<setw(5)<<pp[i].id;
			cout<<setw(12)<<pp[i].name;
			cout<<right;
			cout<<setw(7)<<pp[i].instock;
			cout<<setw(7)<<pp[i].price;	
		} else {
			cout<<left;
			cout<<setw(5)<<pp[i].id;
			cout<<setw(12)<<pp[i].name;
			cout<<right;
			cout<<setw(7)<<"-";
			cout<<setw(7)<<"-";	
		}
		if((i+1)%2 != 0){
			cout<<" || ";	
		} else {
			cout<<endl;
		}
		
	}
	cout<<"\n==================================================================="<<endl;
}
//----------------------
int saleList(ofstream& ods, product p[], int size){
	sale ss[1000];
	product pp[1000];
	char check;
	int s_size, id, qty, price, t_price, dd,mm,yyyy;
	int flag=0;
	string name,date;
	copyProduct(pp,p,size);
	
	showMenuSale(pp,size);
	s_size=0;
	t_price = 0;
	
	cout<<"\nWant to buy items? (Y or N) : ";	cin>>check;	
	while(check=='Y' or check=='y'){
		showMenuSale(pp,size);
		if(flag<1){
			cout<<"insert Date"<<endl;
			cout<<"       dd : ";		cin>>dd;
			cout<<"       mm : ";		cin>>mm;
			cout<<"     yyyy : ";		cin>>yyyy;
			flag++;
		}
		int index=0;	
		do{
			//showMenuSale(pp,size);
			cout<<"ID  : ";	cin>>id;
			index = searchIndex(pp,size,id);
			cout<<"QTY : ";	cin>>qty;
			if(pp[index].instock-qty < 0){
				cout<<"try again because of not enough items!!!"<<endl;
			} 
		}while(pp[index].instock-qty < 0);
		
		pp[index].instock = pp[index].instock-qty;
				
		ss[s_size].id = pp[index].id;
		ss[s_size].name = pp[index].name;
		ss[s_size].qty = qty;
		ss[s_size].cost = pp[index].cost;
		ss[s_size].price = pp[index].price;
		ss[s_size].date[0] = dd;
		ss[s_size].date[1] = mm;
		ss[s_size].date[2] = yyyy;
		s_size++;
		
		cout<<"Want to buy items? (Y or N) : ";	cin>>check;	
	}while(check=='Y' or check=='y');
	
	if(flag>=1){
		tableHeader(4);
		for(int i=0; i<s_size; i++){
			cout<<left;
			printf("%02d/%02d/%d", ss[i].date[0], ss[i].date[1], ss[i].date[2]);
			cout<<"  ";
			cout<<setw(5)<<ss[i].id;
			cout<<setw(12)<<ss[i].name;
			cout<<right;
			cout<<setw(7)<<ss[i].qty;
			cout<<setw(7)<<ss[i].price;
			cout<<setw(10)<<ss[i].qty*ss[i].price<<endl;
			t_price += ss[i].qty*ss[i].price;
		}
		cout<<"==================================================================="<<endl;
		cout<<left;
		cout<<setw(12)<<"";
		cout<<setw(5)<<"";
		cout<<setw(12)<<"";
		cout<<right;
		cout<<setw(7)<<"";
		cout<<setw(7)<<"";
		cout<<setw(10)<<t_price<<endl;
		cout<<"==================================================================="<<endl;
		cout<<left;
		cout<<setw(12)<<"";
		cout<<setw(5)<<"";
		cout<<setw(12)<<"";
		cout<<right;
		cout<<setw(7)<<"";
		cout<<setw(7)<<"Vat 7%:";
		cout<<setw(10)<<t_price*0.07<<endl;
		cout<<"==================================================================="<<endl;
	}
	
	insert_data(ods,ss,s_size);
	dump_data(ods,pp,size);
   	
}

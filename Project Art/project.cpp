#include<iostream>
#include<cstring>
#include<iomanip>
#include<fstream>
#include<windows.h>

using namespace std;

struct supermarket{

    string name;
    int id,price,instock,cost;

};

struct sale{
    string name;
    int id,price,qty,cost;
    int date[3];
};

// ทำการรวมข้อมูลตอนซื้อเสร็จไปเก็บใน selling.txt ----------------
int dump_data(ofstream &ods, supermarket a[], int size){

    ods.open("goods.txt"); 
    if(ods.fail()){
        cerr<<"Can't Write file goods.txt"<<endl;
        system("pause");
        return EXIT_FAILURE;
    }   

    for(int i=0; i<size; i++){
        ods<<left;
        ods<<setw(5)<<a[i].id;
		ods<<setw(12)<<a[i].name;
		cout<<right;
		ods<<setw(7)<<a[i].instock;
		ods<<setw(7)<<a[i].cost;
		ods<<setw(7)<<a[i].price<<endl; 
    }
    ods.close();

}

void copyProducts(supermarket copy[], supermarket original[],int size){

    for(int i=0; i<size; i++){
        copy[i].id = original[i].id;
		copy[i].name = original[i].name;
		copy[i].instock = original[i].instock;
		copy[i].cost = original[i].cost;
		copy[i].price = original[i].price;

    }

}


int  showmenu(int select){
    
    cout<<"--------- Menu ---------"<<endl;
    cout<<"1. Show All List Products "<<endl;
    cout<<"2. Adding New Products" <<endl;
    cout<<"3. Reorder Products"<<endl;
    cout<<"4. Selling of Products"<<endl;
    cout<<"5. Exit"<<endl;
    cout<<"Enter your Number --> : "; cin>>select;
    cout<<endl;
    

    return select;

}

// show stock items -----------------------------------------
int program1 (ifstream &ids , supermarket a[] , int &size ){

    string name;
    int id,instock,Sell_price,cost,total_sell_price,total_cost,profit;
    int gt_cost, gt_price, gt_profit;
    gt_cost = gt_price = gt_profit = 0;

    int i=0;
    ids.open("goods.txt");
    if(ids.fail()){
        cerr<<"Can't open file goods.txt"<<endl;
        system("pause");
        return EXIT_FAILURE;
    }

    
    
    ids>>id;
    a[size].id = id;
    while(!ids.eof()){
        ids>>name>>instock>>cost>>Sell_price;
        a[size].name = name;
        a[size].instock = instock;
        a[size].cost = cost;
        a[size].price = Sell_price;
        
		size++;
        ids>>id;
		a[size].id = id;       
    }  
	ids.close();  

    for(i=0; i<size; i++){
        cout<<left;
		cout<<setw(5)<<a[i].id;
		cout<<setw(12)<<a[i].name;
		cout<<right;
		cout<<setw(7)<<a[i].instock;
		cout<<setw(7)<<a[i].cost;
		cout<<setw(9)<<a[i].price;
     
        total_cost = a[i].instock * a[i].cost;
		total_sell_price = a[i].instock * a[i].price;
		profit = total_sell_price - total_cost;
		gt_cost += total_cost;
		gt_price += total_sell_price;
		gt_profit += profit;
		
		cout<<setw(16)<<total_cost; 
		cout<<setw(19)<<total_sell_price; 
		cout<<setw(17)<<profit<<endl; 
    }

    cout<<"============================================================================================="<<endl;
	cout<<left;
	cout<<"Total Baht ";
	cout<<setw(5)<<"";
	cout<<setw(12)<<"";
	cout<<right;
	cout<<setw(3)<<"";
	cout<<setw(3)<<"";
	cout<<setw(3)<<""; 
	cout<<setw(19)<<gt_cost; 
	cout<<setw(19)<<gt_price; 
	cout<<setw(17)<<gt_profit<<endl; 
	cout<<"============================================================================================="<<endl;

	


}

void headerP1(){

    cout<<"============================================================================================="<<endl;
    cout<<left<<setw(5)<<"ID";  
    cout<<setw(12)<<"Name";    
    cout<<right<<setw(7)<<"Instock";
    cout<<setw(10)<<"Buy-Cost"; 
    cout<<setw(12)<<"Sell-Price";
    cout<<setw(16)<<"Total_Buy-Cost"; 
	cout<<setw(19)<<"Total_Sell-Price"; 
	cout<<setw(11)<<"Profit"<<endl;  
    cout<<"============================================================================================="<<endl;
                                                 
}

// add new item -----------------------------------------
int program2 (ofstream& ods, supermarket a[], int &size){ 
    int id,cost,price,qty;
    string name;
    cout<<"Last ID of Products : "<<a[size-1].id<<endl;
    cout<<"Enter New Id        : "; cin>>id;
    cout<<"Enter Name Item     : "; cin>>name;
    cout<<"Enter QTY.          : "; cin>>qty;
    cout<<"Enter Buy  Cost     : "; cin>>cost;
    cout<<"Enter Sell Price    : "; cin>>price;   

    a[size].id = id;
    a[size].name = name;
    a[size].instock = qty;
    a[size].cost = cost;
    a[size].price = price;

    size++;
    dump_data(ods,a,size);

}

void headerP2(){

    cout<<"============================"<<endl;
    cout<<left<<setw(5)<<"ID";  
    cout<<setw(12)<<"Name";    
    cout<<right<<setw(7)<<"Instock";
    cout<<setw(10)<<"Buy-Cost"<<endl;
    cout<<"============================="<<endl;
}

// reorder Products ------------------------------------------------------
int program3(ofstream &ods, supermarket a[], int &size){
	
	int min,id,qty,index,type;
	char check;
	system("cls");
	
	cout<<"---- ReStock Items ----"<<endl;
	cout<<"Search Min Qty. Stock : "; cin>>min;
	
	do{
		system("cls");
		cout<<"---- ReStock Items ----"<<endl;
		cout<<"Search Min Qty. Stock : "<<min<<endl;
		headerP2();
		
		for(int i=0; i<size; i++){
			if(a[i].instock < min){
				cout<<left<<setw(5)<<a[i].id;  
				cout<<setw(12)<<a[i].name;    
				cout<<right<<setw(7)<<a[i].instock;
				cout<<setw(7)<<a[i].cost<<endl;
			}
		}
		cout<<endl;
		cout<<"Do you want to purchase item into the stock? (Y/N) : "; cin>>check;
		
		if(check == 'Y' || check == 'y'){
			cout<<"--------------"<<endl;
			cout<<"-----Menu-----"<<endl;
			cout<<"1. Old Item"<<endl;
			cout<<"2. New Item"<<endl;
			cout<<"--------------"<<endl;
			cout<<"Select Number of type : "; cin>>type;
			cout<<endl;			
			switch(type){
				case 1 : cout<<"Enter ID   : "; cin>>id;
						 cout<<"Enter Qty. : "; cin>>qty;
						 while(a[index].id != id && index<size){
							index++;
						}
						if(index < size){
							a[index].instock = a[index].instock + qty;
						}
						dump_data(ods,a,size);
						break;
				case 2 : program2(ods,a,size);
						break;
			}
		}
		
	}while(check == 'Y' || check == 'y');
}


int main(){
    
    supermarket a[1000];

    string id,name;
    int window,price,quantity,check,select,size=0,choose;

    ifstream ids;
    ofstream ods;
    
    
    

    do{ 
        system("cls");
        window = showmenu(select);
        switch(window){
            case 1 : cout<<"********************************* Show All List Products *********************************"<<endl;
                     headerP1();
                     program1(ids,a,size);
                    break;
            case 2 : cout<<"********************************* Adding New Products *************************"<<endl;
                    
                    program2(ods,a,size);
                    break;
            case 3 : cout<<"********************************* Reorder Products  *********************************"<<endl;
					program3(ods,a,size);

                    break;
            case 4 : cout<<"********************************* Selling of Products *********************************"<<endl;


                    break;
            case 5 : cout<<"********* Exit *********"<<endl;


                    break;


            
        }
       
        system("pause");
        
    }while(window != 5);
    
		
     
    return 0;
}

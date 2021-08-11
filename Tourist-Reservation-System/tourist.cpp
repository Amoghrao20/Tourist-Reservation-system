#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

char adminf[20]="Trip.txt";
char userf[20]="Reservation.txt";

struct tour{
 	char ad_place[20],ad_code[20],ad_country[20],ad_days[20],ad_prices[20];
 	char us_phone[20],us_name[20],us_people[20],us_date[20],us_status[20],us_dcode[20];
};

class Tourist{
             public:
                void ad_pack(tour r);
	            tour ad_unpack(char a[]);
	            void ad_writedata();
	            void ad_display();
	            void ad_modify();
	            void us_pack(tour r);
	            tour us_unpack(char a[]);
	            void us_writedata();
	            void us_display();
	            void us_search();
	            void us_modify();
};

// ADMIN PANEL
void Tourist ::ad_pack(tour r){
     fstream fp;
     fp.open(adminf,ios::out|ios::app);
     if(!fp){
		cout<<"\nCannot open file";
		exit(0);
     }
     char buff[45];
     strcpy(buff,r.ad_code);
     strcat(buff,"|");
     strcat(buff,r.ad_place);
     strcat(buff,"|");
     strcat(buff,r.ad_country);
     strcat(buff,"|");
     strcat(buff,r.ad_days);
     strcat(buff,"|");
     strcat(buff,r.ad_prices);
     strcat(buff,"|");
     for(int i=0;i<45-strlen(buff);i++)
            strcat(buff,"|");
     fp<<buff<<endl;
     fp.close();
}

tour Tourist::ad_unpack(char buff[]){
	tour r;
	int i=0,j=0;
	while(buff[j]!='|')
	      r.ad_code[i++]=buff[j++];
	r.ad_code[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
	      r.ad_place[i++]=buff[j++];
	r.ad_place[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
	      r.ad_country[i++]=buff[j++];
	r.ad_country[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
	      r.ad_days[i++]=buff[j++];
	r.ad_days[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
	      r.ad_prices[i++]=buff[j++];
	r.ad_prices[i]='\0';
	return(r);
}

void Tourist::ad_writedata(){
    tour s;
    cout<<"Enter the Destination Code\nD-";
    cin>>s.ad_code;
    cout<<"Enter the Destination Place\n";
    cin>>s.ad_place;
    cout<<"Enter the Country of the Destination\n";
    cin>>s.ad_country;
    cout<<"Enter the Number of days of the Trip\n";
    cin>>s.ad_days;
    cout<<"Enter the Cost of the trip\n";
    cin>>s.ad_prices;
    ad_pack(s);
}


void Tourist::ad_display(){
 	fstream fp;
   	char buff[45];
   	tour r;
    fp.open(adminf,ios::in);
    if(!fp){
		cout<<"\nCannot open file";
		exit(0);
    }
    cout<<"-------------------------------------------------------------------------------------------------\n";
    cout<<"Sr No.\t\tDEST. CODE\tPLACE\t\tCOUNTRY\t\tDAYS\t\tPRICES\n";
    cout<<"-------------------------------------------------------------------------------------------------\n";
    int c=1;
    while(1){
        fp.getline(buff,45);
        if(fp.eof())break;
       		r=ad_unpack(buff);
        cout<<c++<<"\t\t"<<r.ad_code<<"\t\t"<<r.ad_place<<"\t\t"<<r.ad_country<<"\t\t" <<r.ad_days<<"\t\t"<<r.ad_prices<<endl;
    }
    fp.close();
    return;
}


void Tourist ::ad_modify(){
    fstream fp;
    char ad_code[15],buff[45];
    int i,j,ch;
    tour s[100];
    fp.open(adminf,ios::in);
    if(!fp){
		cout<<"\nCannot open file";
		exit(0);
    }
    cout<<"\nENTER THE DESTINATION CODE TO BE MODIFIED: ";
    cin>>ad_code;
    i=0;
   	while(1){
        fp.getline(buff,45);
        if(fp.eof())break;
        s[i]=ad_unpack(buff);
        i++;
    }
   	for(j=0;j<i;j++){
       		if(strcmp(s[j].ad_code,ad_code)==0){
                    cout<<"VALUES OF THE TRIP\n";
                    cout<<"\nDestination Code: "<<s[j].ad_code;
                    cout<<"\nDestination Place: "<<s[j].ad_place;
                    cout<<"\nDestination Country: "<<s[j].ad_country;
                    cout<<"\nNo of days of Trip: "<<s[j].ad_days;
                    cout<<"\nTotal Cost of the Trip: "<<s[j].ad_prices;
                    cout<<"\nWhat you want to Update: ";
	  		cout<<"\n\n\t\tEnter 1 for changing DESTINATION PLACE\n";
	  		cout<<"\t\tEnter 2 for changing DAYS OF THE TRIP\n";
	  		cout<<"\t\tEnter 3 for changing COST OF THE TRIP\n";
	  		cout<<"\t\t\t";
	  		cin>>ch;
	  		switch(ch){
                case 1:
                    cout<<"Destination Place: ";
                    cin>>s[j].ad_place;
                    cout<<"Destination Country: ";
                    cin>>s[j].ad_country;
                    break;
                case 2:
                    cout<<"No of days of Trip: ";
                    cin>>s[j].ad_days;
                    break;
                case 3:
                    cout<<"Total Cost of the Trip: ";
                    cin>>s[j].ad_prices;
                    break;
	  		}
                    break;
            }
    }
   	if(j==i){
        cout<<"\n TRIP NOT FOUND";
        return;
    }
    fp.close();
    fstream fd;
    fd.open(adminf,ios::out|ios::trunc);
    if(!fd){
        cout<<"\nFile Not Found";
        exit(0);
    }
   	for(j=0;j<i;j++)
         ad_pack(s[j]);
   	fd.close();
}


// USER PANEL


void Tourist ::us_pack(tour r){
    fstream fp;
    fp.open(userf,ios::out|ios::app);
    if(!fp){
        cout<<"\nFile Not Found";
		exit(0);
    }
    char buff[45];
    strcpy(buff,r.us_name);
    strcat(buff,"|");
    strcat(buff,r.us_phone);
    strcat(buff,"|");
    strcat(buff,r.us_people);
    strcat(buff,"|");
    strcat(buff,r.us_dcode);
    strcat(buff,"|");
    strcat(buff,r.us_date);
    strcat(buff,"|");
    strcat(buff,r.us_status);
    strcat(buff,"|");
    for(int i=0;i<45-strlen(buff);i++)
     	strcat(buff,"|");
    fp<<buff<<endl;
    fp.close();
}


tour Tourist::us_unpack(char buff[]){
	tour r;
	int i=0,j=0;
	while(buff[j]!='|')
	      r.us_name[i++]=buff[j++];
	r.us_name[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
	      r.us_phone[i++]=buff[j++];
	r.us_phone[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
	      r.us_people[i++]=buff[j++];
	r.us_people[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
	      r.us_dcode[i++]=buff[j++];
	r.us_dcode[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
	      r.us_date[i++]=buff[j++];
	r.us_date[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
	      r.us_status[i++]=buff[j++];
	r.us_status[i]='\0';
	return(r);
}
void Tourist::us_writedata(){
    tour r;
    cout<<"ENTER YOUR NAME: ";
    cin>>r.us_name;
    cout<<"ENTER YOUR CONTACT NO.: ";
    cin>>r.us_phone;
    cout<<"ENTER NO. OF TOURIST: ";
    cin>>r.us_people;
    cout<<"ENTER THE DESTINATION CODE: D-";
    cin>>r.us_dcode;
    cout<<"ENTER DATE OF JOURNEY (DD/MM/YY): ";
    cin>>r.us_date;
    cout<<"\nENTER 'Confirm' TO CONFIRM YOUR RESERVATION: ";
    cin>>r.us_status;
    us_pack(r);
}

void Tourist::us_display(){
 	fstream fp;
   	char buff[45];
   	tour r;
    fp.open(userf,ios::in);
    if(!fp){
		cout<<"\nCannot open file";
		exit(0);
    }
    cout<<"------------------------------------------------------------------------------------------------------------------------\n";
    cout<<"Sr No.\tNAME\t\tCONTACT NO\t\tTOTAL PEOPLE\t\tDATE\t\tDEST. CODE\t\tSTATUS\n";
    cout<<"------------------------------------------------------------------------------------------------------------------------\n";
    int c=1;
    while(1){
        fp.getline(buff,45);
        if(fp.eof())break;
       		r=us_unpack(buff);
        cout<<c++<<"\t"<<r.us_name<<"\t\t"<<r.us_phone<<"\t\t"<<r.us_people<<"\t\t\t"<<r.us_date<<"\t\t"<<r.us_dcode<<"\t\t"<<r.us_status<<endl;
    }
    fp.close();
    return;
}


void Tourist ::us_modify(){
    fstream fp;
    char us_name[15],buff[45];
    int i,j;
    tour s[100];
    fp.open(userf,ios::in);
    if(!fp){
		cout<<"\nFile not Found";
		exit(0);
    }
    cout<<"\nEnter Your name to cancel  your reservation: ";
    cin>>us_name;
    i=0;
   	while(1){
        fp.getline(buff,45);
        if(fp.eof())break;
        s[i]=us_unpack(buff);
        i++;
    }
   	for(j=0;j<i;j++){
        if(strcmp(s[j].us_name,us_name)==0){
	  		cout<<"\nYour Reservation Details are:\n";
	  		cout<<"\nName: "<<s[j].us_name;
	  		cout<<"\nContact No.: "<<s[j].us_phone;
	  		cout<<"\nNo.of People: "<<s[j].us_people;
	  		cout<<"\nDestination: "<<s[j].us_dcode;
	  		cout<<"\nDate of Journey: "<<s[j].us_date;
	  		cout<<"\nStatus: "<<s[j].us_status;
	  		cout<<"\n\nENTER 'Cancel' TO CANCEL YOUR TICKET: \n";
	  		cin>>s[j].us_status;
	  		cout<<"\nYour Reservation has been Cancelled\n";
	  		cout<<"\n\nName: "<<s[j].us_name;
	  		cout<<"\nContact No.: "<<s[j].us_phone;
	  		cout<<"\nNo.of People: "<<s[j].us_people;
	  		cout<<"\nDestination: "<<s[j].us_dcode;
	  		cout<<"\nDate of Journey: "<<s[j].us_date;
	  		cout<<"\nStatus: "<<s[j].us_status;
            break;
        }
    }
   	if(j==i){
        cout<<"\nRECORD NOT FOUND";
        return;
    }
    fp.close();
    fstream fd;
    fd.open(userf,ios::out|ios::trunc);
    if(!fd){
        cout<<"\nCannot open file";
        exit(0);
    }
   	for(j=0;j<i;j++)
        us_pack(s[j]);
   	fd.close();
}

void Tourist::us_search(){
 	fstream fp;
 	char us_name[15],buff[45];
 	int i,j;
 	tour s;
    fp.open(userf,ios::in);
    if(!fp){
	 	cout<<"\nCannot open file";
		exit(0);
    }
    cout<<"\nENTER THE NAME TO BE SEARCHED: ";
    cin>>us_name;
    i=0;
   	while(1){
        fp.getline(buff,45);
        if(fp.eof())break;
        s=us_unpack(buff);
        if(strcmp(s.us_name,us_name)==0){
	  	 	cout<<"\n RESERVATION FOUND\n";
	  		cout<<"\nNAME: "<<s.us_name;
	  		cout<<"\nCONTACT NO.: "<<s.us_phone;
	  		cout<<"\nNO. OF PEOPLE: "<<s.us_people;
	  		cout<<"\nDATE OF JOURNEY: "<<s.us_date;
	  		cout<<"\nSTATUS: "<<s.us_status;
	  		return;
	 	}
    }
    cout<<"\nRESERVATION NOT FOUND";
    return;
}

int main(){
    cout<<"                              \t\t WELCOME TO TOURIST RESERVATION SYSTEM\n\n\n";
    cout<<"                                   \t    TOURIST RESERVATION SOFTWARE\n\n\n";
    cout<<"                                     \t      PRESS ENTER TO CONTINUE....\n\n";
    if(cin.get()=='\n'){
        system("cls");
        int choice,ch1,ch2;
        Tourist obj;
        cout<<"\n Who are You?\n";
        cout<<"1. ADMIN\n";
        cout<<"2. USER\n\n";
        cout<<"Enter any other key for exit\n\n\n";
        cout<<"Enter Your Option\n";
        cin>>choice;
        switch(choice){
            case 1:
                system("cls");
                cout<<"WELCOME ADMIN\n";
                cout<<"Enter your option\n";
                cout<<"1. New trips\n";
                cout<<"2. Display a Trip\n";
                cout<<"3. Display a Reservation\n";
                cout<<"4. Update Trip\n";
                cout<<"Enter any other key for exit\n\n";
                while(1){
                    cout<<"\nENTER UR CHOICE: ";
                    cin>>ch1;
                    switch(ch1){
                        case 1:
                            obj.ad_writedata();
                            break;
                        case 2:
                            obj.ad_display();
                            break;
                        case 3:
                            obj.us_display();
                            break;
                        case 4:
                            obj.ad_modify();
                            break;
                        default:
                            exit(0);
            }
        }
            case 2:
                system("cls");
                cout<<"WELCOME USER\n";
                cout<<"Enter your option\n";
                cout<<"1. New Reservation\n";
                cout<<"2. Search Reservation\n";
                cout<<"3. Cancel Reservation\n";
                cout<<"Enter any other key for exit\n\n\n";
                while(1){
                    cout<<"\nENTER UR CHOICE: ";
                    cin>>ch2;
                    switch(ch2){
                        case 1:
                            cout<<"-----------------------------------";
                            cout<<"\n Choose Your destination\n";
                            cout<<"-----------------------------------\n";
                            obj.ad_display();
                            cout<<"\n";
                            obj.us_writedata();
                            break;
                        case 2:
                            obj.us_search();
                            break;
                        case 3:
                            obj.us_modify();
                            break;
                        default:
                            exit(0);
                    }
                }
            default:
                exit(0);
        }
    }
}

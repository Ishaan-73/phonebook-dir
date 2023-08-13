#include<iostream>
#include<string.h>
using namespace std;
class Node
{
    public:
        char number[20];
        char name[40];
        Node* next;
        Node* prev;
        Node(char n[] ,char num[]){
            strcpy(name,n);
            strcpy(number,num);
            next = NULL;
            prev = NULL;
        }
        friend class dlist;
};
class dlist
{
    Node *head,*temp,* ptr;

    Node *ptr1,*ptr2,*dup;

    public:
    Node* pn;
    void insert();
    //insert new contact
    void sort();
    //sort the directory alphabetically
    void delete_contact(char name[40]);
    //delete any contact(search by name)
    void search_by_name(char name[40]);
    //search contact details
    void search_by_number(char num[20]);
    //search contact details1
    void display();
    //Display all contacts in the phonebook
    void edit_details(char s[40]);
    //Edit contact details searched by name
    dlist(){
        head = NULL;
        temp = NULL;
        ptr = NULL;
        ptr1 = NULL;
        ptr2 = NULL;
        dup = NULL;
    }
};

void dlist::insert(){
    char num[20];
    char name[40];
    char ch = 'y';
    while(ch=='y'){
        cout<<"Enter the name: ";
        cin>>name;
        //Checking whether same name exists in directory
        if(head!=NULL){
            Node* p = head;
            while(p!=NULL){
                if(strcmp(p->name,name)==0){
                    cout<<"Enter a unique Name!"<<endl;
                    cin>>name;
                }
                p = p->next;
            }
        }
        cout<<"Enter the mobile number: ";
        cin>>num;
        //Checking if the number is of 10 digits
        while(strlen(num)!=10){
            cout<<"Enter a valid number"<<endl;
            cin>>num;
        }
        //Checking if the number has non numeric characters
        for(int i=0;i<10;i++){
            if(num[i]-'0'<0 || num[i]-'0'>9){
                cout<<"Enter a valid number"<<endl;
                cin>>num;
            }
        }
        temp = new Node(name,num);
        if(head==NULL){
            head = temp;
        }
        else{
            ptr = head;
            while(ptr->next!=NULL){
                ptr = ptr->next;
            }
            ptr->next = temp;
            temp->prev = ptr;
        }
        cout<<"Do you want to continue inserting?(y/n)"<<endl;
        cin>>ch;
    }    

}
void dlist::display(){
    ptr = head;
    while(ptr!=NULL){
        cout<<"Contact Name:-------> "<<ptr->name<<endl;
        cout<<"Contact Number:------> "<<ptr->number<<endl;
        cout<<"\n";

        ptr = ptr->next;
    }
}
void dlist::sort(){
    Node *i,*j;
    char n[40];
    char num[20];
    int temp;
    for(i=head;i->next!=NULL;i=i->next){
        for(j=i->next;j!=NULL;j=j->next){
            temp = strcmp(i->name,j->name);
            if(temp>0){
                strcpy(n,i->name);
                strcpy(num,i->number);
                strcpy(i->name,j->name);
                strcpy(i->number,j->number);
                strcpy(j->name,n);
                strcpy(j->number,num);
            }
        }
    }
}
void dlist::delete_contact(char n[40]){
    int flag = 0;
    ptr = head;
    while(ptr!=NULL){
        if(strcmp(n,ptr->name)==0){
            flag=1;
            break;
        }
        ptr = ptr->next;
    }
    if(flag==1 && ptr!=head && ptr->next!=NULL){
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete(ptr);
        cout<<"Contact Deleted!"<<endl;
    }
    else if(flag==1 && ptr==head){
        ptr->next->prev = NULL;
        head = ptr->next;
        delete(ptr);
        cout<<"Contact Deleted!"<<endl;
    }
    else if(flag==1 && ptr->next==NULL){
        ptr->prev->next = NULL;
        ptr->prev = NULL;
        delete(ptr);
        cout<<"Contact Deleted!"<<endl;
    }
    else{
        cout<<"Contact Not Found in the Directory"<<endl;
    }
}
void dlist::search_by_name(char n[40]){
    int flag=0;
    ptr = head;
    while(ptr!=NULL){
        if(strcmp(ptr->name,n)==0){
            cout<<"Name Found"<<endl;
            cout<<"Contact Details:"<<endl;
            cout<<"Number: "<<ptr->number<<endl;
            flag=1; 
            break;
        }
        ptr = ptr->next;
    }
    if(flag==0){
        cout<<"Contact not Found"<<endl;
    }
}
void dlist::search_by_number(char n[20]){
    int flag=0;
    ptr = head;
    while(ptr!=NULL){
        if(strcmp(ptr->number,n)==0){
            cout<<"Number Found"<<endl;
            cout<<"Contact Details:"<<endl;
            cout<<"Name: "<<ptr->name<<endl; 
            flag=1;
            break;
        }
        ptr = ptr->next;
    }
    if(flag==0){
        cout<<"Contact not Found"<<endl;
    }
}
void dlist::edit_details(char n[40]){
    ptr = head;
    int x;
    while(ptr!=NULL){
        if(strcmp(ptr->name,n)==0){
                cout<<"1.Edit Name\n2.Edit Number"<<endl;
                cin>>x;
                if(x==1){
                    cout<<"Enter the new Name"<<endl;
                    cin>>ptr->name;
                }
                else if(x==2){
                    cout<<"Enter the new Number"<<endl;
                    cin>>ptr->number;
                    while(strlen(ptr->number)!=10){
                        cout<<"Enter valid number"<<endl;
                        cin>>ptr->number;
                    }
                }
                else{
                    cout<<"Invalid request"<<endl;
                }
            }
        ptr = ptr->next;
    }
}
int main(){
    char name[30];
    char number[20];
    dlist d;
    char ch='y';
    int x;
    cout<<"                               PHONEBOOK DIRECTORY                      "<<endl;
    while(ch=='y'){
        cout<<"1.INSERT NEW CONTACT\n2.DISPLAY PHONEBOOK\n3.DELETE CONTACT\n4.SEARCH CONTACT\n5.EDIT CONTACT"<<endl;
        cout<<"Enter your Input: ";
        cin>>x;
        switch(x){
            case 1:
                d.insert();
                d.sort();
                break;
            case 2:
                d.display();
                break;
            case 3:
                cout<<"Enter the contact name you want to delete: ";
                cin>>name;
                d.delete_contact(name);
                break;
            case 4:
                cout<<"Do you want to search contact by:\n1.NAME\n2.NUMBER"<<endl;
                int n;
                cin>>n;
                if(n==1){
                    char name[30];
                    cout<<"Enter the name: ";
                    cin>>name;
                    d.search_by_name(name);
                }
                else if(n==2){
                    char number[20];
                    cout<<"Enter the number :";
                    cin>>number;
                    d.search_by_number(number);
                }
                else{
                    cout<<"Invalid Input"<<endl;
                }
                break;
            case 5:
                cout<<"Enter the contact name you want to EDIT: ";
                char name[30];
                cin>>name;
                d.edit_details(name);
                d.sort();
                break;
            default:
                cout<<"INVALID INPUT GIVEN"<<endl;
                break;
        }
        cout<<"DO you want to continue operations(y/n): ";
        cin>>ch;
    }
    return 0;
}

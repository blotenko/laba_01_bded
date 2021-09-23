#include <iostream>
#include <fstream>
using namespace std;









struct Windmill{
    int id;
    int status;
    int pnext;
    char* name;
    char* weight;
    char* color;
    int code;
};


struct Depature{
    int adreees;
    int id;
    char* fromPoint;
    int status;
    char* finalPoint;
    int count;
    int pnext;
};


struct IndexTable{
    int KP;
    int adrres;
};
















Depature* first = new Depature[10];
Windmill* tovar = new Windmill [20];
IndexTable* First1 = new  IndexTable [10];




int saveDep(char * filename, struct Depature * st, int n){
    FILE * fp;
    char *c;
 
    int size = n * sizeof(struct Depature);
     
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }
    c = (char *)&n;
    for (int i = 0; i<sizeof(int); i++)
    {
        putc(*c++, fp);
    }
     c = (char *)st;
    for (int i = 0; i < size; i++)
    {
        putc(*c, fp);
        c++;
    }
    fclose(fp);
    return 0;
}




int saveWindmill(char * filename, struct Windmill * st, int n)
{
    FILE * fp;
    char *c;
 
    int size = n * sizeof(struct Windmill);
     
    if ((fp = fopen(filename, "wb")) == NULL){
        perror("Error occured while opening file");
        return 1;
    }
    c = (char *)&n;
    for (int i = 0; i<sizeof(int); i++){
        putc(*c++, fp);
    }
 
    c = (char *)st;
    for (int i = 0; i < size; i++){
        putc(*c, fp);
        c++;
    }
    fclose(fp);
    return 0;
}






int saveIndexTable(char * filename, struct IndexTable * st, int n){
    FILE * fp;
    char *c;

    int size = n * sizeof(struct IndexTable);

    if ((fp = fopen(filename, "wb")) == NULL){
        perror("Error occured while opening file");
        return 1;
    }
    c = (char *)&n;
    for (int i = 0; i<sizeof(int); i++){
        putc(*c++, fp);
    }

    c = (char *)st;
    for (int i = 0; i < size; i++){
        putc(*c, fp);
        c++;
    }
    fclose(fp);
    return 0;
}




int loadIndexTable(char * filename, int num){
    FILE * fp;
    char *c;
    int m = sizeof(int);
    int n, i;
    int *pti = (int *)malloc(m);
    if ((fp = fopen(filename, "r")) == NULL){
        perror("Error occured while opening file");
        return 0;
    }
    c = (char *)pti;
    while (m>0){
        i = getc(fp);
        if (i == EOF) break;
        *c = i;
        c++;
        m--;
    }
    n = *pti;
    struct IndexTable * ptr = (struct IndexTable *) malloc(n * sizeof(struct IndexTable));
    c = (char *)ptr;
    while ((i= getc(fp))!=EOF){
        *c = i;
        c++;
    }
    for (int k = 0; k<n; k++){
        if((ptr+k)->KP == num){
            return (ptr+k)->adrres;
        }
    }

    free(pti);
    free(ptr);
    fclose(fp);
    return 0;
}




 
int loadSupp(char * filename,int  ptr1){
    FILE * fp;
    char *c;
    int m = sizeof(int);
    int n, i;
    int *pti = (int *)malloc(m);
 
    if ((fp = fopen(filename, "r")) == NULL){
        perror("Error occured while opening file");
        return 1;
    }
    c = (char *)pti;
    while (m>0){
        i = getc(fp);
        if (i == EOF) break;
        *c = i;
        c++;
        m--;
    }
    n = *pti;
    Depature* ptr= new Depature[10];
    c = (char *)ptr;
    while ((i= getc(fp))!=EOF){
        *c = i;
        c++;
    }
    for (int k = 0; k<n; k++){
        if(ptr1 == ptr[k].adreees && ptr[k].status !=0){
        cout<<"ID "<<(ptr+k)->id<<endl;
        cout<<"final point "<<(ptr+k)->finalPoint<<endl;
        cout<<"From point "<<(ptr+k)->fromPoint<<endl;
        cout<<"Count "<<(ptr+k)->count<<endl;
        break;
        }
    }
    free(pti);
    fclose(fp);
    return 0;
}



int delAllTovar(int  ptr1,int countOftov);
int delSupp(char * filename,int  ptr1, int countOftov, int countofSupp){

   int n = countofSupp;
    
    for (int k = 0; k<n; k++){
        if(ptr1 == first[k].adreees){
            first[k].status = 0;
            delAllTovar(first[k].pnext,countOftov);
            saveDep(filename, first, n);
            return first[k].count;
            break;
        }
    }
    return 0;
}




int loadForaddres(char * filename,int  ptr1){
    FILE * fp;
    char *c;
    int m = sizeof(int);
    int n, i;
    int *pti = (int *)malloc(m);
 
    if ((fp = fopen(filename, "r")) == NULL){
        perror("Error occured while opening file");
        return 1;
    }
    c = (char *)pti;
    while (m>0){
        i = getc(fp);
        if (i == EOF) break;
        *c = i;
        c++;
        m--;
    }
    n = *pti;
    Depature* ptr  = new Depature[10];
    c = (char *)ptr;
    while ((i= getc(fp))!=EOF){
        *c = i;
        c++;
    }
    for (int k = 0; k<n; k++){
        if(ptr1 == ptr[k].adreees){
            return ptr[k].pnext;
        }
    }
 
    free(pti);
    fclose(fp);
    return 0;
}



int loadTovar(int  ptr1,int kodDet,int countOftov){
    char * filename = "Tovar.dat";
    FILE * fp;
    char *c;
    int m = sizeof(int);
    int n, i;
    int *pti = (int *)malloc(m);
 
    if ((fp = fopen(filename, "r")) == NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }
    c = (char *)pti;
    while (m>0)
    {
        i = getc(fp);
        if (i == EOF) break;
        *c = i;
        c++;
        m--;
    }
    n = *pti;
    Windmill* ptr = new Windmill [20];
    c = (char *)ptr;
    while ((i= getc(fp))!=EOF){
        *c = i;
        c++;
    }
    bool flag = true;
    int k = ptr1;
    while( k<=countOftov){
                if((ptr+k)->code == kodDet && (ptr+k)->status != 0){
                flag  = false;
                cout<<"ID "<<(ptr+k)->id<<endl;
                cout<<" Code "<<(ptr+k)->code<<endl;
                cout<<" color "<<(ptr+k)->color<<endl;
                cout<<"Name "<<(ptr+k)->name<<endl;
                cout<<"Weight " <<(ptr+k)->weight<<endl;
                break;
            }
            else{
                k =  (ptr+k)->pnext;
            }
    }
    if(flag) cout<<"Error"<<endl;
    free(pti);
    fclose(fp);
    return 0;
}






int delTovar(int  ptr1,int kodDet, int countOftov){
    char * filename = "Tovar.dat";
   
   int n = countOftov;
    
    bool flag = true;
    int k = ptr1;
    while( k<n || tovar[k].pnext == 10){
            if(tovar[k].code == kodDet){
                tovar[k].code = 0;
                saveWindmill(filename,tovar,n);
                flag = false;
                break;
            }
            else{
                k =  tovar[k].pnext;
            }
    }
    if(flag) cout<<"Error"<<endl;
    return 0;
}



int delAllTovar(int  ptr1, int countOftov){
    char * filename = "Tovar.dat";
    int n = countOftov;
    int k = ptr1;
    while( k<n || tovar[k].pnext == 10){
        tovar[k].code = 0;
        k =  tovar[k].pnext;
    }
    saveWindmill(filename,tovar,n);
    return 0;
}






int get_m(){
    int num;
    int code;
    cout<<"Enter the num of depature : ";
    cin>>code;
    num =loadIndexTable("indexTable.dat", code);
    loadSupp("Suppliers.dat",num);
    return 0;
}



void get_s(int countOfTov){
    int num1;
    int num2;
    int code;
    int kodDet;
    cout<<"Enter the num of depature : ";
    cin>>code;
    cout<<"Enter a code of a detail : ";
    cin>>kodDet;
    num1 =loadIndexTable("indexTable.dat", code);
    num2 =  loadForaddres("Suppliers.dat",num1);
    loadTovar(num2, kodDet,countOfTov);
}



int del_m(int countOftov,int countofSupp){
    int num;
    int code;
    cout<<"Enter the num of depature : ";
    cin>>code;
    num =loadIndexTable("indexTable.dat", code);
    int res = delSupp("Suppliers.dat",num,countOftov,countofSupp);
    return  res;
}



void del_s(int code,int kodDet,int countOftov){
    int num1;
    int num2;
    num1 =loadIndexTable("indexTable.dat", code);
    num2 =  loadForaddres("Suppliers.dat",num1);
    delTovar(num2, kodDet,countOftov);
}



int update_m(int  countofSupp){
    char * city = new char;
    char * lastName = new char;
    int num;
    int code;
    cout<<"Enter the num of depature : ";
    cin>>code;
    num =loadIndexTable("indexTable.dat", code);
    
    int  n = countofSupp;
    
    for (int k = 0; k<n; k++){
        if(num == first[k].adreees && first[k].status !=0){
        cout<<"1.KP : ";
            cin>>first[k].id;
        cout<<"2.city : ";
            cin>>city; first[k].finalPoint = city;
        cout<<"3.last_name : ";
            cin>>lastName;first[k].fromPoint=lastName;
            First1[k].KP = first[k].id;
            First1[k].adrres = first[k].adreees;
            saveIndexTable("indexTable.dat", First1, countofSupp);
            saveDep("Suppliers.dat", first, n);
            break;
        }
    }
 
    
    return 0;
}


int update_s(int countOftov){
    int num1,num2,code,kodDet;
    char* nazva = new char;
    char* vaga = new char;
    char* color = new char;
    cout<<"Enter the num of depature : ";
    cin>>code;
    cout<<"Enter a code of a detail : ";
    cin>>kodDet;
    num1 =loadIndexTable("indexTable.dat", code);
    num2 =  loadForaddres("Suppliers.dat",num1);
   
   int n = countOftov;
    
    bool flag = true;
    int k = num2;
    while( k<n){
            if(tovar[k].code == kodDet && tovar[k].status != 0){
                flag  = false;
                cout<<"id : "<<endl;
                cin>>tovar[k].id;
                cout<<"code :"<<endl;
                cin>>tovar[k].code;
                cout<<"color : "<<endl;
                cin>>color; tovar[k].color= color;
                cout<<"Name : "<<endl;
                cin>>nazva; tovar[k].name= nazva;
                cout<<"Weight : "<<endl;
                cin>>vaga ;tovar[k].weight = vaga;
                saveWindmill("Tovar.dat",tovar,n);
                break;
            }
            else{
                k =  tovar[k].pnext;
            }
    }
    if(flag) cout<<"Error"<<endl;
    return 0;
}



int insert_m(int countOfTovar, int countOfSupp){
    Depature ptr1;
    char * city = new char;
    char * lastName = new char;
    cout<<"ID : ";
    cin>>ptr1.id;
    cout<<"From  Point : ";
    cin>>lastName; ptr1.fromPoint = lastName;
    cout<<"Final Point : ";
    cin>>city; ptr1.finalPoint = city;
    ptr1.status =  1;
    ptr1.count =  0;
    ptr1.pnext = countOfTovar;
    ptr1.adreees = sizeof(ptr1) / sizeof(ptr1) + countOfSupp;
    
    
    bool flag  = true;
    for (int k = 0; k<countOfSupp; k++){
        if(first[k].status ==0){
            flag = false;
            first[k].id =ptr1.id;
            first[k].finalPoint =ptr1.finalPoint;
            first[k].fromPoint=ptr1.fromPoint;
            first[k].status =  ptr1.status;
            first[k].count = ptr1.count;
            first[k].adreees =  ptr1.adreees;
            first[k].pnext = ptr1.pnext;
            saveDep("Suppliers.dat", first, countOfSupp);
            
            First1[k].KP = first[k].id;
            First1[k].adrres = first[k].adreees;
            saveIndexTable("indexTable.dat", First1, countOfSupp);
            return first[k].id;
            break;
        }
    }
    if(flag){
        first[countOfSupp].id =ptr1.id;
        first[countOfSupp].finalPoint =ptr1.finalPoint;
        first[countOfSupp].fromPoint=ptr1.fromPoint;
        first[countOfSupp].status =  ptr1.status;
        first[countOfSupp].count = ptr1.count;
        first[countOfSupp].adreees =  ptr1.adreees;
        first[countOfSupp].pnext = ptr1.pnext;
        saveDep("Suppliers.dat", first, countOfSupp+1);
        First1[countOfSupp].KP = first[countOfSupp].id;
        First1[countOfSupp].adrres = first[countOfSupp].adreees;
        saveIndexTable("indexTable.dat", First1, countOfSupp+1);
    }
    return first[countOfSupp].id;
    
}


void insert_s(bool flag1, int  num,int  countofSupp,int countOftov){
    char* nazva = new char;
    char* vaga = new char;
    char* color = new char;
    bool flag  = true;
    for(int i =0; i<countofSupp;i++){
        if(num == first[i].id && first[i].status != 0 ){
            int  j  = first[i].pnext;
            if(flag1){
                //first[i].pnext = countOftov;
                cout<<"ID : "<<endl;
                cin>>tovar[countOftov].id;
                cout<<"code :"<<endl;
                cin>>tovar[countOftov].code;
                cout<<"color : "<<endl;
                cin>>color; tovar[countOftov].color= color;
                cout<<"Name : "<<endl;
                cin>>nazva; tovar[countOftov].name= nazva;
                cout<<"Weight : "<<endl;
                cin>>vaga ;tovar[countOftov].weight = vaga;
                tovar[countOftov].status = 1;
                tovar[countOftov].pnext = 10;
                saveWindmill("Tovar.dat",tovar,countOftov+1);
                first[i].count++;
                saveDep("Suppliers.dat", first, countofSupp);
            }
            else{
            while(flag){
                if(tovar[j].pnext == 10){
                    tovar[j].pnext = countOftov;
                    cout<<"ID : "<<endl;
                    cin>>tovar[countOftov].id;
                    cout<<"code :"<<endl;
                    cin>>tovar[countOftov].code;
                    cout<<"color : "<<endl;
                    cin>>color; tovar[countOftov].color= color;
                    cout<<"NAme : "<<endl;
                    cin>>nazva; tovar[countOftov].name= nazva;
                    cout<<"Weight : "<<endl;
                    cin>>vaga ;tovar[countOftov].weight = vaga;
                    tovar[countOftov].status = 1;
                    tovar[countOftov].pnext = 10;
                    saveWindmill("Tovar.dat",tovar,countOftov+1);
                    first[i].count++;
                    saveDep("Suppliers.dat", first, countofSupp);
                    break;
                }
                else{
                   j  = tovar[j].pnext;
                }
            }
        }
            break;
        }
    }
}




int main(){
    char * filename1 = "Suppliers.dat";
    char * filename2 = "Tovar.dat";
    
   

    
    
    
    first[0].id =  1;
    first[0].fromPoint="000";
    first[0].status = 1;
    first[0].finalPoint = "000";
    first[0].count = 2;
    first[0].pnext= 0 ;
    first[0].adreees =sizeof(first) / sizeof(first[0]);

    
    tovar[0].id = first[0].id;
    tovar[0].pnext = 2;
    tovar[0].code=1;
    tovar[0].color = "000";
    tovar[0].name="000";
    tovar[0].weight="000";
    tovar[0].status=1;
    
    tovar[2].id = first[0].id;
    tovar[2].pnext = 10;
    tovar[2].code=3;
    tovar[2].color = "003";
    tovar[2].name="003";
    tovar[2].weight="003";
    tovar[2].status=1;
    
    
    

    first[1].id =  2;
    first[1].fromPoint="001";
    first[1].status = 1;
    first[1].finalPoint = "001";
    first[1].count = 1;
    first[1].pnext = 1;
    first[1].adreees =sizeof(first) / sizeof(first[1])+1;
    
    tovar[1].id = first[1].id;
    tovar[1].pnext = 10;
    tovar[1].code=2;
    tovar[1].color = "001";
    tovar[1].name="001";
    tovar[1].weight="001";
    tovar[1].status=1;
   

    
    
    saveDep(filename1,first,2);
    saveWindmill(filename2,tovar,3);
    
   
    
    
    First1[0].KP = first[0].id;
    First1[0].adrres = first[0].adreees;
   
    
    First1[1].KP = first[1].id;
    First1[1].adrres = first[1].adreees;
   
    
    char* filename3 = "indexTable.dat";
    
    
    saveIndexTable(filename3,First1,2);
   

    while(1){
        int  nums;
        int countofSupp = 2;
        int countOftov = 3;
        cout<<"1. get_m()"<<endl;
        cout<<"2. get_s()"<<endl;
        cout<<"3. del_m()"<<endl;
        cout<<"4. del_s()"<<endl;
        cout<<"5. update_m()"<<endl;
        cout<<"6. update_s()"<<endl;
        cout<<"7. insert_m()"<<endl;
        cout<<"8. insert_s()"<<endl;
        cin>>nums;
        switch (nums) {
            case 1:
                get_m();
                break;
            case 2:
                get_s(countOftov);
                break;
            case 3:
                countOftov = del_m(countOftov, countofSupp);
                countofSupp--;
                break;
            case 4:
                cout<<"Enter the num of depature : ";
                int code;cin>>code;
                cout<<"Enter  the code of detail : ";
                int kodDet;cin>>kodDet;
                del_s(code, kodDet, countOftov);
                countOftov--;
                break;
            case 5:
                update_m(countofSupp);
                break;
                
            case 6:
                update_s(countOftov);
                break;
                
                
            case 7:
                int  num;
                 num = insert_m(countOftov, countofSupp);
                countofSupp++;
                insert_s(true,num,countofSupp,countOftov);
                countOftov++;
                break;
            
            case 8:
                cout<<"Enter the num of depature : ";
                cin>>num;
                insert_s(false,num,countofSupp,countOftov);
                countOftov++;
                break;


            default:
                break;
        }
    }
    
    
  
    
    return 0;
}

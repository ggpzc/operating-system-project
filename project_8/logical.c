#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define NUMBER_OF_PAGES 256
#define PAGE_SIZE 256
#define TLB_SIZE 16

int PageFault=0;
int Hit=0;


int TLB[TLB_SIZE][2];
int PageTable[NUMBER_OF_PAGES];
int TLB_pt;
int PageTable_pt;
char memory[PAGE_SIZE*NUMBER_OF_PAGES];


void init_TLB()
{
    int i;
    for(i=0;i<TLB_SIZE;i++){
        TLB[i][0]=-1;
        TLB[i][1]=-1;
    }
    TLB_pt=0;
}


void init_PageTable()
{
    int i;
    for(i=0;i<NUMBER_OF_PAGES;i++){
        PageTable[i]=-1;
    }
    PageTable_pt=0;
}


int get_page(int address)
{
    return (address >> 8);
}


int get_offset(int address)
{
    return (address-(address>>8<<8));
}

/* ask for page in TLB return position or -1 */
int request_TLB(int page)
{
    int flag=-1,i;
    for(i=0;i<TLB_SIZE;i++){
        if(TLB[i][0]==page){
            flag=TLB[i][1];
        }
    }
    return flag;
}

/* ask for page in PageTable return position or -1 */
int request_PageTable(int page)
{
    return PageTable[page];
}


void update_TLB(int log_page,int phy_page)
{
    TLB_pt=TLB_pt%TLB_SIZE;
    TLB[TLB_pt][0]=log_page;
    TLB[TLB_pt][1]=phy_page;
    TLB_pt++;
}


void update_PageTable(int log_page)
{
    PageTable[log_page]=PageTable_pt;
    PageTable_pt++;
}



int main(int argc,char *argv[])
{
    int i;
    int logical_address,physical_address,logical_page,physical_page,offset;
    char temp1[10],temp2[PAGE_SIZE];
    FILE *in,*back_store;
    int value;

    back_store=fopen("BACKING_STORE.bin","r");
    in=fopen(argv[1],"r");
    init_PageTable();
    init_TLB();
    
    
    while(fgets(temp1,10,in)){

        temp1[strlen(temp1)-1]='\0';
        logical_address=atoi(temp1);
        logical_page=get_page(logical_address);
        offset=get_offset(logical_address);

        if(request_TLB(logical_page)!=-1){
            physical_page=request_TLB(logical_page);
            Hit++;
        }
        else if(request_PageTable(logical_page)!=-1){
            physical_page=request_PageTable(logical_page);
            update_TLB(logical_page,physical_page);
        }
        else{
            physical_page=PageTable_pt;
            update_TLB(logical_page,physical_page);
            update_PageTable(logical_page);
            PageFault++;
        }

        physical_address=(physical_page<<8)+offset;
    
        fseek(back_store,physical_page*PAGE_SIZE,0);
        fread(temp2,sizeof(char),256,back_store);
        
        value=temp2[offset];

        printf("vistual address = %d, physical address = %d, value = %d\n",logical_address,physical_address,value);
    
    }

    printf("The rate of hit if %f\n",Hit/1000.0);
    printf("The rate of Page Fault is %f\n",PageFault/1000.0);


    fclose(back_store);
    fclose(in);
    return 0;
}
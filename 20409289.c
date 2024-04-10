/* Name: LAI KEN SIANG Student ID: 20409289 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//struct to store visitor's information
struct visitData{
char *SrNo;
char *ticketNo;
char *Name;
char *ID;
};

//struct to store the data
struct ticket {
struct visitData visitor;
struct ticket *nextPtr;
};

//function prototypes
int data();
void displaymenu();
void tonode();
void tofile();
int datacount();
void displayticket();
void searchdata();
void deletedata();
void deleteticket();
void deletename();
void deleteid();
void listofvisitor();
void ascending();
void totalvisitor();
int duplicate();

//main function which let user to choose which function to perform
int main()
{
    while(1){
    char ch;
    displaymenu();
    printf("\n\n\t\tEnter your choice : ");
    scanf("%s",&ch);
    if(ch=='1'){
        printf("\n\n\n...Adding visitor information...\n\n");
        data();
    }else if(ch=='4'){
        printf("\n\t\tDisplaying.....\n");
        displayticket();
    }else if(ch=='2'){
        searchdata();
    }else if(ch=='3'){
        deletedata();
    }else if(ch=='5'){
        printf("\n\t\t...Exiting...\n");
        return 0;
    }else{
        printf("\n\t\t...Invalid Choice...\n");
    }
    }
}

//user choose the function based on this display menu
void displaymenu()
{
    printf("\n\n\t\t *******************************************************************");
    printf("\n\t\t                    THEME PARK BOOKING SYSTEM                 ");
    printf("\n\t\t   *******************************************************************");
    printf("\n\n\n\t\t Please enter your choice from below (1-5):");
    printf("\n\n\t\t 1. Add a new visitor information");
    printf("\n\n\t\t 2. Search visitor");
    printf("\n\n\t\t 3. Delete visitor information");
    printf("\n\n\t\t 4. Display Total No. of tickets sold");
    printf("\n\n\t\t 5. EXIT");
}

//let user to enter visitor information
int data()
{
    struct ticket* head = NULL;
    char id,Name[30],temp[30],temp1[30],temp2[30],temp3[30],ticketNo[100]={},SrNo[40],ID[20],ic[20],pass[20];
    int sr=1,count=0,maxcount;
    maxcount=datacount("ticket.txt");
        printf("Total visitor : %02d\n",datacount("temp.txt"));
        //user are not allowed to enter more than 40 visitor's information
        if(maxcount==41){
            printf("\n\n\n...Total number of visitor information has reached maximum...\n\n");
            return 0;
        }
        printf("Enter name: \n");
        scanf(" %[^\n]s",Name);
        strcpy(temp2,Name);
        //if visitor's name less than 6 characters append space at the beginning
        for(int k=0; k<strlen(temp2);k++){
            if(temp2[k]!=' ')
                count++;
        }
        //convert space to '_'
        if(count=5){
            sprintf(temp3,"%6s",temp2);
            strcpy(Name,temp3);
        }else if(count=4){
            sprintf(temp3,"%5s",temp2);
            strcpy(Name,temp3);
        }else if(count=3){
            sprintf(temp3,"%4s",temp2);
            strcpy(Name,temp3);
        }else if(count=2){
            sprintf(temp3,"%3s",temp2);
            strcpy(Name,temp3);
        }else if(count=1){
            sprintf(temp3,"%2s",temp2);
            strcpy(Name,temp3);
        }

        printf("Serial number of the visitor: \n");
        char srno[100],ticketno[100],n[100],Id[100];
        FILE *ptr=fopen("ticket.txt", "r");
        while(fscanf(ptr, "%s %s %s %s\n",srno,ticketno,n,Id)==4){
        fscanf(ptr,"%s %s %s %s\n",srno,ticketno,n,Id);
        sr=atoi(srno);
        sr++;
        }
        fclose(ptr);
        printf("%02d", sr);
        puts("");
        sprintf(SrNo, "%02d", sr);

        strcpy(temp,Name);
        for(int j=0; j<6; j++){
            int num=temp[j];
            sprintf(temp1,"%d",num);
            strcat(ticketNo,temp1);
        }
        printf("ticket no :%s\n",strcat(ticketNo,SrNo));

        for(int i=0; i<strlen(Name); i++){
            if(Name[i]==' '){
                Name[i]='_';
            }
        }
        printf("Visitor name :%s\n",Name);
        puts("");
        printf("Enter 'L' for local, 'I' for international: \n");
        scanf("%s",&id);
        if(id=='L'||id=='l'){
            printf("Enter IC: \n");
            scanf("%s",ic);
            snprintf(ID, 20, "IC%s", ic);
            printf("Visitor's ID : %s\n", ID);
        }
        else if(id=='I'||id=='i'){
            printf("Enter passport: \n");
            scanf("%s",pass);
            snprintf(ID, 20, "PASS%s", pass);
            printf("Visitor's ID : %s\n", ID);
        }
        else{
            printf("INVALID INPUT");
            return 0;
        }
        tonode(&head, SrNo, ticketNo, Name, ID);
        tofile(head);
        totalvisitor();
}

//create new node
void tonode(struct ticket** head, char* SrNo, char* ticketNo, char* Name, char* ID)
{
    struct ticket* newNode = malloc(sizeof(struct ticket));
    newNode->nextPtr = NULL;
    newNode->visitor.SrNo = SrNo;
    newNode->visitor.ticketNo = ticketNo;
    newNode->visitor.Name = Name;
    newNode->visitor.ID = ID;

    struct ticket* prevnode = NULL;
    struct ticket* currnode = *head;

    while(currnode != NULL){
        prevnode = currnode;
        currnode = currnode->nextPtr;
    }

    if(prevnode == NULL){
        newNode->nextPtr = *head;
        *head = newNode;
    }else{
        prevnode->nextPtr = newNode;
        newNode->nextPtr = currnode;
    }
}

//store data to txt file
void tofile(struct ticket*head)
{
    FILE* ptr = fopen("ticket.txt", "a+");
    FILE* outptr8 = fopen("output.txt", "a+");

    if(head == NULL){
        printf("There's no visitor\n");
        fprintf(ptr, "There's no visitor.");
    }else{
        struct ticket* currnode = head;
        while(currnode != NULL){
            printf("The information of the visitor %s is recorded.\n",currnode->visitor.Name);
            fprintf(outptr8,"\nThe information of the visitor %s is recorded.\n",currnode->visitor.Name);
            fprintf(ptr, "%s %s %s %s\n", currnode->visitor.SrNo, currnode->visitor.ticketNo, currnode->visitor.Name, currnode->visitor.ID);
            currnode = currnode->nextPtr;
        }
    }
    fclose(ptr);
    fclose(outptr8);
}

//count no of line in txt file
int datacount(char *filename)
{
    FILE* ptr;
    ptr=fopen(filename, "r");
    int ch=0;
    char count=0;

    while((ch=fgetc(ptr))!=EOF){
        if(ch=='\n'){
            count++;
        }
    }
    fclose(ptr);
    return count;
}

//function to display list of visitor information
void displayticket()
{
    printf("\n\t\tTotal number of tickets sold : %d\n\n",datacount("temp.txt"));
    listofvisitor();
    puts("");
    int ch;
    printf("\t\tEnter your choice (1-2) :\n");
    printf("\t\t 1.  Display visitor information in ascending order\n");
    printf("\t\t 2.  Exit\n");
    scanf("%d",&ch);
    if(ch==1){
        ascending();
    }else if(ch==2){
        printf("\t\t...EXITING...");
    }else{
        printf("INVALID CHOICE");
    }
}

//function to search visitor information
void searchdata()
{
    char sticketno[100],sname[100],sid[100],SrNo[100],ticketNo[100],Name[100],ID[100],tempname[100],temp2[100],temp3[100];
    int ch,count=0;
    FILE* ptr;
    ptr = fopen("ticket.txt", "a+");
    if (NULL == ptr){
        printf("file can't be opened \n");
    }
    printf("\n\t\t Please enter your choice from below (1-4):");
    printf("\n\n\t\t 1. Search based on visitor's ticket number");
    printf("\n\n\t\t 2. Search based on visitor's name");
    printf("\n\n\t\t 3. Search based on visitor's ID");
    printf("\n\n\t\t 4. EXIT");
    printf("\n\n\t\tEnter your choice : ");
    scanf("%d",&ch);

    if(ch==1){
    printf("\nEnter the visitor's ticket no : \n");
    scanf("%s",sticketno);

    FILE *outptr7;
    outptr7=fopen("output.txt","a+");
    fprintf(outptr7, "\nThe following record of the visitor is found:\n\n");
    printf("The following record of the visitor is found:\n\n");
    while(fscanf(ptr,"%s %s %s %s\n", SrNo, ticketNo, Name, ID)==4){
        if(strcmp(sticketno,ticketNo)==0){
            printf("%s %s %s %s\n", SrNo, ticketNo, Name, ID);
            fprintf(outptr7,"%s %s %s %s\n", SrNo, ticketNo, Name, ID);
        }
    }fclose(outptr7);
    }else if(ch==2){
    printf("\nEnter the visitor's name : \n");
    scanf(" %[^\n]s",sname);
    strcpy(temp2,sname);
        for(int k=0; k<strlen(temp2);k++){
            if(temp2[k]!=' ')
                count++;
        }
        if(count=5){
            sprintf(temp3,"%6s",temp2);
            strcpy(sname,temp3);
        }else if(count=4){
            sprintf(temp3,"%5s",temp2);
            strcpy(sname,temp3);
        }else if(count=3){
            sprintf(temp3,"%4s",temp2);
            strcpy(sname,temp3);
        }else if(count=2){
            sprintf(temp3,"%3s",temp2);
            strcpy(sname,temp3);
        }else if(count=1){
            sprintf(temp3,"%2s",temp2);
            strcpy(sname,temp3);
        }
    for(int i=0; i<strlen(sname); i++){
        if(sname[i]==' '){
            sname[i]='_';
        }
    }
    for(int j=0; j<strlen(sname); j++){
        sname[j]=tolower(sname[j]);
    }

    FILE *outptr5;
    outptr5=fopen("output.txt","a+");
    fprintf(outptr5, "\nThe following record of the visitor is found:\n\n");
    printf("The following record of the visitor is found:\n");
    while(fscanf(ptr,"%s %s %s %s\n", SrNo, ticketNo, Name, ID)==4){
        strcpy(tempname,Name);
        for(int k=0; k<strlen(tempname); k++){
            tempname[k]=tolower(tempname[k]);
        }
        if(strcmp(sname,tempname)==0){
            printf("%s %s %s %s\n", SrNo, ticketNo, Name, ID);
            fprintf(outptr5,"%s %s %s %s\n", SrNo, ticketNo, Name, ID);
        }
    }
    fclose(outptr5);
    }else if(ch==3){
    printf("\nEnter the visitor's ID : \n");
    scanf("%s",sid);
    for(int j=0; j<strlen(sid); j++){
        sid[j]=toupper(sid[j]);
    }
    FILE *outptr4;
    outptr4=fopen("output.txt","a+");
    fprintf(outptr4, "\nThe following record of the visitor is found:\n\n");
    printf("The following record of the visitor is found:\n");
    while(fscanf(ptr,"%s %s %s %s\n", SrNo, ticketNo, Name, ID)==4){
        if(strcmp(sid,ID)==0){
            printf("%s %s %s %s\n", SrNo, ticketNo, Name, ID);
            fprintf(outptr4,"%s %s %s %s\n", SrNo, ticketNo, Name, ID);
            fclose(outptr4);
        }
    }
    }else if(ch==4){
        printf("\n\t\t...Exiting...\n");
    }
}

//display menu of delete visitor information
void deletedata()
{
    int ch;
    printf("\n\t\t Please enter your choice from below (1-4):");
    printf("\n\n\t\t 1. Delete based on visitor's ticket number");
    printf("\n\n\t\t 2. Delete based on visitor's name");
    printf("\n\n\t\t 3. Delete based on visitor's ID");
    printf("\n\n\t\t 4. EXIT");
    printf("\n\n\t\tEnter your choice : ");
    scanf("%d",&ch);

    if(ch==1){
        deleteticket();
    }else if(ch==2){
        deletename();
    }else if(ch==3){
        deleteid();
    }else if(ch==4){
        printf("\n\t\t...Exiting...\n");
    }
}

//function to delete visitor information based on ticket no
void deleteticket()
{
    char SrNo[20], ticketNo[100], Name[30], ID[20];
    char sticketno[100], sname[30], sid[20];
    int ch;
    FILE *ptr1, *ptr2, *ptr3;
    ptr1 = fopen("ticket.txt", "r");
    ptr2 = fopen("temp.txt", "w");

    while(fscanf(ptr1, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4){
        fprintf(ptr2, "%s %s %s %s\n", SrNo, ticketNo, Name, ID);
    }

    fclose(ptr1);
    fclose(ptr2);

    ptr1 = fopen("ticket.txt", "w");
    ptr2 = fopen("temp.txt", "r");

    printf("\n\t\tPlease enter the ticket number to deleted: \n");
    scanf("%s", sticketno);

    while(fscanf(ptr2, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4){
        if(strcmp(sticketno, ticketNo)==0){
            printf("Information that will be deleted.\n");
            printf("%s %s %s %s\n", SrNo, ticketNo, Name, ID);
            puts("");
            printf("The visitor with Ticket No.:%s, information is deleted.\n", ticketNo);
            FILE *outptr;
            outptr=fopen("output.txt","a+");
            fprintf(outptr, "\nThe visitor with Ticket No.:%s, information is deleted.\n", ticketNo);
            fclose(outptr);
        }else{
            fprintf(ptr1, "%s %s %s %s\n", SrNo, ticketNo, Name, ID);
        }

    }
    puts("\n\n\n");

    fclose(ptr1);
    fclose(ptr2);
}

//function to delete visitor information based on name
void deletename()
{
    char SrNo[20], ticketNo[100], Name[30], ID[20];
    char sticketno[100], sname[30], sid[20], tempname[100],temp2[100],temp3[100];
    int ch,count1=0;
    int count=0;
    FILE *ptr1, *ptr2;
    ptr1 = fopen("ticket.txt", "r");
    ptr2 = fopen("temp.txt", "w");

    while(fscanf(ptr1, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4)
    {
        fprintf(ptr2, "%s %s %s %s\n", SrNo, ticketNo, Name, ID);
    }

    fclose(ptr1);
    fclose(ptr2);

    FILE *ptr3, *ptr4;
    ptr3 = fopen("ticket.txt", "w");
    ptr4 = fopen("temp.txt", "r");

    printf("\n\t\tPlease enter visitor's name to deleted: \n");
    scanf(" %[^\n]s", sname);
    strcpy(temp2,sname);
        for(int k=0; k<strlen(temp2);k++){
            if(temp2[k]!=' ')
                count1++;
        }
        if(count1=5){
            sprintf(temp3,"%6s",temp2);
            strcpy(sname,temp3);
        }else if(count1=4){
            sprintf(temp3,"%5s",temp2);
            strcpy(sname,temp3);
        }else if(count1=3){
            sprintf(temp3,"%4s",temp2);
            strcpy(sname,temp3);
        }else if(count1=2){
            sprintf(temp3,"%3s",temp2);
            strcpy(sname,temp3);
        }else if(count1=1){
            sprintf(temp3,"%2s",temp2);
            strcpy(sname,temp3);
        }

    for(int i=0; i<strlen(sname); i++){
        if(sname[i]==' '){
            sname[i]='_';
        }
    }
    for(int j=0; j<strlen(sname); j++){
        sname[j]=tolower(sname[j]);
    }

    while(fscanf(ptr4, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4){
        strcpy(tempname,Name);
        for(int k=0; k<strlen(tempname); k++){
            tempname[k]=tolower(tempname[k]);
        }
        if(strcmp(sname, tempname)==0){
            count++;
        }
    }

    fclose(ptr3);
    fclose(ptr4);

    FILE *ptr5, *ptr6;
    ptr5 = fopen("ticket.txt", "w");
    ptr6 = fopen("temp.txt", "r");
    if(count<2){
        while(fscanf(ptr6, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4){
            strcpy(tempname,Name);
            for(int z=0; z<strlen(tempname); z++){
                tempname[z]=tolower(tempname[z]);
            }
            //if no same name count < 2 and delete the visitor information
            if(strcmp(sname, tempname)==0){
                printf("Information that will be deleted:\n\n");
                printf("%s %s %s %s\n", SrNo, ticketNo, Name, ID);
                puts("");
                printf("The visitor: %s information is deleted.\n\n", Name);
                FILE *outptr1;
                outptr1=fopen("output.txt","a+");
                fprintf(outptr1, "\nThe visitor: %s information is deleted.\n", Name);
                fclose(outptr1);
            }else{
                fprintf(ptr5, "%s %s %s %s\n", SrNo, ticketNo, Name, ID);
            }
        }
    fclose(ptr5);
    fclose(ptr6);
    //if have same name count > 2 let user to enter id to delete
    }else{
        FILE *ptr7, *ptr8, *outptr6;
        outptr6 = fopen("output.txt", "a+");
        ptr7 = fopen("ticket.txt", "w");
        ptr8 = fopen("temp.txt", "r");
        fprintf(outptr6,"\nThe following visitors have same names, Please enter the ID to deleted: \n\n");
        printf("The following visitors have same names, Please enter the ID to deleted: \n");
        while(fscanf(ptr8, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4){
            strcpy(tempname,Name);
            for(int k=0; k<strlen(tempname); k++){
                tempname[k]=tolower(tempname[k]);
            }
            if(strcmp(sname, tempname)==0){
                printf("%s %s %s %s\n", SrNo, ticketNo, Name, ID);
                fprintf(outptr6,"%s %s %s %s\n", SrNo, ticketNo, Name, ID);
            }
        }
        fclose(outptr6);
        fclose(ptr7);
        fclose(ptr8);

        FILE *ptr9, *ptr10;
        ptr9 = fopen("ticket.txt", "w");
        ptr10 = fopen("temp.txt", "r");

        printf("\n\t\tPlease enter visitor's ID to deleted: \n");
        scanf("%s", sid);

        for(int x=0; x<strlen(sid); x++){
            sid[x]=toupper(sid[x]);
        }

        while(fscanf(ptr10, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4){
            if(strcmp(sid, ID)==0){
                printf("Information that will be deleted.\n");
                printf("%s %s %s %s\n", SrNo, ticketNo, Name, ID);
                puts("");
                printf("The visitor with ID: %s, information is deleted.\n", ID);
                FILE *outptr2;
                outptr2=fopen("output.txt","a+");
                fprintf(outptr2, "\nThe visitor with ID: %s, information is deleted.\n", ID);
                fclose(outptr2);
            }else{
                fprintf(ptr9, "%s %s %s %s\n", SrNo, ticketNo, Name, ID);
            }
        }
        fclose(ptr9);
        fclose(ptr10);
    }
}

//function to delete visitor information based on ID
void deleteid()
{
    char SrNo[20], ticketNo[100], Name[30], ID[20];
    char sticketno[100], sname[30], sid[20];
    int ch;
    FILE *ptr1, *ptr2;
    ptr1 = fopen("ticket.txt", "r");
    ptr2 = fopen("temp.txt", "w");

    while(fscanf(ptr1, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4){
        fprintf(ptr2, "%s %s %s %s\n", SrNo, ticketNo, Name, ID);
    }

    fclose(ptr1);
    fclose(ptr2);

    ptr1 = fopen("ticket.txt", "w");
    ptr2 = fopen("temp.txt", "r");

    printf("\n\t\tPlease enter visitor's ID to deleted: \n");
    scanf("%s", sid);

    for(int j=0; j<strlen(sid); j++){
        sid[j]=toupper(sid[j]);
    }

    while(fscanf(ptr2, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4){
        if(strcmp(sid, ID)==0){
            printf("\nInformation that will be deleted.\n");
            printf("%s %s %s %s\n", SrNo, ticketNo, Name, ID);
            printf("\nThe visitor with ID: %s, information is deleted.\n", ID);
            FILE *outptr3;
            outptr3=fopen("output.txt","a+");
            fprintf(outptr3, "\nThe visitor with ID: %s, information is deleted.\n", ID);
            fclose(outptr3);
        }else{
            fprintf(ptr1, "%s %s %s %s\n", SrNo, ticketNo, Name, ID);
        }
    }
    puts("\n\n\n");

    fclose(ptr1);
    fclose(ptr2);
}

//function to display content of txt file
void listofvisitor()
{
    FILE *ptr, *outptr9;

    outptr9 = fopen("output.txt", "a+");
    ptr = fopen("ticket.txt", "r");

    char SrNo[20], ticketNo[100], Name[30], ID[20];
    int count=datacount("temp.txt");

    fprintf(outptr9,"\nTotal visitors: %d\n\n",count);
    while(fscanf(ptr, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4){
        printf("\t\t %s %s %s %s\n", SrNo, ticketNo, Name, ID);
        fprintf(outptr9, "%s %s %s %s\n", SrNo, ticketNo, Name, ID);
    }

    fclose(ptr);
    fclose(outptr9);
}

//function to sort the list of visitor information in ascending order based on the names
void ascending()
{
    char Name[100],temp[100],names[40][40],SrNo[100],ticketNo[100],ID[100];
    int i=0,count;
    count=datacount("ticket.txt");
    FILE *ptr,*ptr2;
    ptr=fopen("ticket.txt","r");
    ptr2=fopen("output.txt", "a+");
    while(fscanf(ptr,"%s %s %s %s",SrNo,ticketNo,Name,ID)==4){
        if(duplicate(names,Name,i)==1){
            continue;
        }else if(SrNo!="Total")
            strcpy(names[i],Name);
            i++;
        }

    for(int i=0;i<count;i++){
      for(int j=i+1;j<count;j++){
         if(strcmp(names[i],names[j])>0){
            strcpy(temp,names[i]);
            strcpy(names[i],names[j]);
            strcpy(names[j],temp);
         }
      }
    }

    printf("\nList of visitor in ascending order : \n");
    fprintf(ptr2, "\nList of visitor in ascending order.\n");

    for(int k=0;k<count;k++){
        FILE*ptr3=fopen("ticket.txt","r");
        while(fscanf(ptr3,"%s %s %s %s\n",SrNo,ticketNo,Name,ID)==4){
            if(strcmp(names[k],Name)==0&&strcmp(SrNo,"Total")!=0){
                printf("\n%s %s %s %s",SrNo,ticketNo,Name,ID);
                fprintf(ptr2,"%s %s %s %s\n",SrNo,ticketNo,Name,ID);
            }
        }
        fclose(ptr3);
    }
    fclose(ptr2);
}

//function to check whether there is duplicate names in the list
int duplicate(char names[40][40],char* Name, int k)
{
    int count=0;
    while (count<k){
        if(strcmp(names[count],Name)==0){
            return 1;
        }
        count++;
    }
    return 0;
}

//function to display total visitor
void totalvisitor()
{
    FILE *ptr1, *ptr2;
    ptr1 = fopen("ticket.txt", "r");
    ptr2 = fopen("temp.txt", "w");

    char SrNo[20], ticketNo[100], Name[30], ID[20];

    while(fscanf(ptr1, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4){
        if(strcmp(SrNo, "Total")==0){
        }else{
            fprintf(ptr2, "%s %s %s %s\n", SrNo, ticketNo, Name, ID);
        }
    }

    fclose(ptr1);
    fclose(ptr2);

    FILE *ptr3, *ptr4;
    ptr3 = fopen("ticket.txt", "w");
    ptr4 = fopen("temp.txt", "r");

    int count;
    count=datacount("temp.txt");

    fprintf(ptr3, "Total visitors : %d\n",count);

    while(fscanf(ptr4, "%s %s %s %s\n", SrNo, ticketNo, Name, ID) == 4){
        fprintf(ptr3, "%s %s %s %s\n", SrNo, ticketNo, Name, ID);
    }
    fclose(ptr3);
    fclose(ptr4);
}

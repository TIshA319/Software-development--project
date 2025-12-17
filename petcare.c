#include <stdio.h>
#include <string.h>


#define MAX_PETS 100


typedef struct {
    int id;
    char name[31];
    char category[21];
    int age;
    char owner[31];
    int Checkup;
    int Vaccine;
    int Hotel;
    int hotelDays;
    int grooming;
    int Training;
    float bill;
    int flag;
} Pet;




Pet pets[MAX_PETS];
int petCount = 0;
int nextId = 1;
float  checkup = 500.0f;
float vaccine = 800.0f;
float perdayhotel = 1000.0f;
float haircut = 300.0f;
float bath = 200.0f;
float obedience = 600.0f;
float agility = 800.0f;
float tricks = 700.0f;


float calculate_bill(Pet *p) {
    float total = 0;

    if (p->Hotel) total += p->hotelDays * perdayhotel;
    if (p->Checkup) total += checkup;
    if (p->Vaccine) total += vaccine;

    if (p->grooming == 1) total += haircut;
    if (p->grooming == 2) total += bath;
    if (p->grooming == 3) total += haircut + bath;

    
    if (p->Training == 1) total += obedience;
    if (p->Training == 2) total += agility;
    if (p->Training == 3) total += tricks;
    
    printf("\n--- Billing Preview ---\n");

    if (p->Checkup)
        printf("Checkup: %.2f\n", checkup);

    if (p->Vaccine)
        printf("Vaccine: %.2f\n", vaccine);

    if (p->Hotel)
        printf("Hotel (%d day): %.2f\n",p->hotelDays, p->hotelDays * perdayhotel);

    if (p->grooming == 1)
        printf("Grooming (Haircut): %.2f\n", haircut);

    else if (p->grooming == 2)
        printf("Grooming (Bath): %.2f\n", bath);

    else if (p->grooming == 3)
        printf("Grooming (Both): %.2f\n",
               haircut + bath);
    
    if (p->Training == 1)
        printf("Training (Obedience): %.2f\n", obedience);
    else if (p->Training == 2)
        printf("Training (Agility): %.2f\n", agility);
    else if (p->Training == 3)
        printf("Training (Tricks): %.2f\n", tricks);
               
    total += p->bill;
    printf("Total bill: %.2f\n", total);
    return total;
}


void Hotel(Pet *p){
    printf("Need Hotel service?( 1=yes 0=no): ");
    scanf("%d",&p->Hotel);
    if(p->Hotel){
    printf("Number of days you want to stay: ");
    scanf("%d", &p->hotelDays);
    }
   else{
   p->hotelDays=0;
   }
}
void Grooming(Pet *p) {
    printf("Grooming options:\n0=None \n1=Haircut \n2=Bath \n3=Both\nChoose: ");
    scanf("%d", &p->grooming);
    if (p->grooming < 0 || p->grooming > 3){
     p->grooming = 0;
     }
}
void Medical(Pet *p) {
    printf("Needs medical checkup? (1=yes 0=no): ");
    scanf("%d", &p->Checkup);
    printf("Needs vaccine? (1=yes 0=no): ");
    scanf("%d", &p->Vaccine);
}
void Training(Pet *p) {
    printf("\nTraining Options:\n");
    printf("0 = None\n");
    printf("1 = Obedience Training (600 tk)\n");
    printf("2 = Agility Training (800 tk)\n");
    printf("3 = Trick Training (700 tk)\n");
    printf("Choose: ");
    scanf("%d", &p->Training);

    if (p->Training < 0 || p->Training > 3){
        p->Training = 0;
    }
}

void Service(Pet *p){
    int option;
    int more = 1;  

    while (more) {

        printf("\nSelect service:\n");
        printf("1. Hotel\n");
        printf("2. Grooming\n");
        printf("3. Medical\n");
        printf("4. Training\n");
        printf("0. No  service\n");
        printf("Option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:Hotel(p);
            break;
        case 2:Grooming(p);
            break;
         case 3:Medical(p);
            break;
        case 4:Training(p);
           break;
        case 0: return;
        default:printf("Invalid option!\n");
            break;
        }
        printf("Add more services? (1=yes, 0=no): ");
        scanf("%d", &more);
    
        
}
}
void Petinfo(){
    Pet p;
    p.id = nextId;
    p.flag = 1;

    p.Checkup = 0;
    p.Vaccine = 0;
    p.Hotel = 0;
    p.hotelDays = 0;
    p.grooming = 0;
    p.Training = 0;
    p.bill = 0;

    printf("Enter Pet Information\n");
    getchar();
    
    printf("Pet Name:");
    fgets(p.name,sizeof(p.name),stdin);
   
    printf("Pet catagory:");
    fgets(p.category,sizeof(p.category),stdin);


    printf("Pet age:");
    scanf("%d", &p.age);
    getchar();


    printf("Owner name: ");
    fgets(p.owner, sizeof(p.owner), stdin);
     
    printf("if you want any service for your pet.\n");
    Service(&p);
               
     p.bill = calculate_bill(&p);
     pets[petCount++] = p;
     nextId++;

}


/*
Add by Seen --START--
*/


void pettoys() {
    int choice, item;
    float totalGoods = 0.0;
    int more = 1;

    while (more == 1) {
        printf("\n--- Pet Goods Shop ---\n");
        printf("1. Pet Food (300 tk)\n");
        printf("2. Pet Toy (150 tk)\n");
        printf("3. Shampoo (200 tk)\n");
        printf("4. Collar (100 tk)\n");
        
        printf("Choose: ");
        scanf("%d", &choice);


        printf("Quantity: ");
        scanf("%d", &item);

        switch (choice) {
            case 1: totalGoods += 300 * item; break;
            case 2: totalGoods += 150 * item; break;
            case 3: totalGoods += 200 * item; break;
            case 4: totalGoods += 100 * item; break;
            default: printf("Invalid choice!\n"); break;
        }

        printf("Add more goods? (1=yes, 0=no): ");
        scanf("%d", &more);
    }

    printf("\nGoods purchased! Total amount: %.2f tk\n", totalGoods);
}

void PetFood() {
    int choice, qty;
    float totalFood = 0.0;
    int more = 1;
    float dogfood = 300.0f;
    float catfood = 250.0f;
    float fishfood = 150.0f;    
    float birdfood = 200;
    while (more == 1) {
        printf("\n--- Pet Food Shop ---\n");
        printf("1. Dog Food (300 tk)\n");
        printf("2. Cat Food (250 tk)\n");
        printf("3. Fish Food (150 tk)\n");
        printf("4. Bird Food (200 tk)\n");
        printf("Choose: ");
        scanf("%d", &choice);

        printf("Quantity (in packets): ");
        scanf("%d", &qty);

        switch (choice) {
            case 1:
                totalFood += dogfood * qty;
                break;
            case 2:
                totalFood += catfood * qty;
                break;
            case 3:
                totalFood += fishfood * qty;
                break;
            case 4:
                totalFood += birdfood * qty;
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }

        printf("Add more food? (1=yes, 0=no): ");
        scanf("%d", &more);
    }

    printf("\nFood purchased! Total: %.2f tk\n", totalFood);
}
void displaypets() {
    if (petCount == 0) {
        printf("\nNo pets added yet.\n");
        return;
    }

    printf("\n--- All Pets ---\n");

    for (int i = 0; i < petCount; i++) {
        if (pets[i].flag == 1) {  
            printf("ID: %d\n", pets[i].id);
            printf("Name: %s", pets[i].name);
            printf("Category: %s", pets[i].category);
            printf("Age: %d\n", pets[i].age);
            printf("Owner: %s", pets[i].owner);
            printf("------------------------------\n");
        }
    }
}

/*--END--
*/


int main() {
    int choice;
    int service;
    printf("Pet Care Management System\n");


    while (1) {
        printf("\nMenu:\n");
        printf("1. Add new pet\n");
        printf("2. Display all pets\n");
        printf("3. Delete pet\n");
        printf("4. Search pet \n");
        printf("5.  \n");
        printf("6. Buy pet toys & accessories:\n");
        printf("7. Buypetfood\n");
        printf("0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:Petinfo();break;
            case 2: displaypets(); break;
            /*case 3: delete_pet(); break;
            case 4: Search_pet() ; break;
            case 5: ; break;*/
            case 6:pettoys(); break;
            case 7:PetFood();break; 
            case 0:  return 0;
            default: printf("Invalid.\n");
        }
    }

}


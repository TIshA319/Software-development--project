#include <stdio.h>
#include <string.h>


#define MAX_PETS 100
#define MAX_ADOPT 50

void remove_newline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

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
               
    
    printf("Total bill: %.2f\n", total);
    return total;
}

Pet EmptyPet() {
    Pet p = {0};   
    return p;
}

void SavePetToFile(Pet *p) {
    FILE *fp = fopen("pets.txt", "a");
    if (!fp) {
        printf("Error opening pets.txt\n");
        return;
    }

    fprintf(fp, "id=%d\n", p->id);
    fprintf(fp, "name=%s", p->name);
    fprintf(fp, "category=%s", p->category);
    fprintf(fp, "age=%d\n", p->age);
    fprintf(fp, "owner=%s", p->owner);

    
    if (p->Checkup)
        fprintf(fp, "checkup=1\n");

    if (p->Vaccine)
        fprintf(fp, "vaccine=1\n");

    if (p->Hotel) {
        fprintf(fp, "hotel=1\n");
        fprintf(fp, "hotelDays=%d\n", p->hotelDays);
    }

    if (p->grooming)
        fprintf(fp, "grooming=1\n");

    if (p->Training)
        fprintf(fp, "training=1\n");

    
    if (p->bill > 0)
        fprintf(fp, "bill=%.2f\n", p->bill);

    fprintf(fp, "active=%d\n", p->flag);
    fprintf(fp, "--------------------\n");

    fclose(fp);
}

void PetsFile() {
    FILE *fp = fopen("pets.txt", "r");
    if (!fp) return;

    char line[100];
    Pet p = EmptyPet();   

    petCount = 0;
    nextId = 1;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "--------------------") == 0) {
            pets[petCount++] = p;
            if (p.id >= nextId) nextId = p.id + 1;

            p = EmptyPet();  
            continue;
        }

        sscanf(line, "id=%d", &p.id);
        sscanf(line, "age=%d", &p.age);
        sscanf(line, "hotelDays=%d", &p.hotelDays);
        sscanf(line, "bill=%f", &p.bill);
        sscanf(line, "active=%d", &p.flag);

        sscanf(line, "name=%30[^\n]", p.name);
        sscanf(line, "category=%20[^\n]", p.category);
        sscanf(line, "owner=%30[^\n]", p.owner);

        if (strcmp(line, "checkup=1") == 0) p.Checkup = 1;
        if (strcmp(line, "vaccine=1") == 0) p.Vaccine = 1;
        if (strcmp(line, "hotel=1") == 0) p.Hotel = 1;
        if (strcmp(line, "grooming=1") == 0) p.grooming = 1;
        if (strcmp(line, "training=1") == 0) p.Training = 1;
    }

    fclose(fp);
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
    if (petCount >= MAX_PETS) {
        printf("Pet list full!\n");
        return;}
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
     SavePetToFile(&p);
     nextId++;

}


typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Goods;


int AdminLogin() {
    FILE *fp = fopen("admin.txt", "r");
    char fu[20], fpw[20];

    if (!fp) {
        fp = fopen("admin.txt", "w");
        fprintf(fp, "admin 1234\n");
        fclose(fp);
        fp = fopen("admin.txt", "r");
    }

    fscanf(fp, "%19s %19s", fu, fpw);
    fclose(fp);

    char u[20], p[20];
    printf("Admin ID: ");
    scanf("%19s", u);
    printf("Password: ");
    scanf("%19s", p);

    return strcmp(fu, u) == 0 && strcmp(fpw, p) == 0;
}


void ViewStock() {
    FILE *fp = fopen("goods.txt", "r");
    if (!fp) {
        printf("No goods available.\n");
        return;
    }

    char line[200];
    Goods g;

    printf("\n--- GOODS STOCK ---\n");
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d|%49[^|]|%f|%d",
                   &g.id, g.name, &g.price, &g.quantity) == 4) {
            printf("ID:%d Name:%s Price:%.2f Qty:%d\n",
                   g.id, g.name, g.price, g.quantity);
        }
    }
    fclose(fp);
} 


void AdminAddGoods() {
    FILE *fp = fopen("goods.txt", "a");
    if (!fp) return;

    printf("Previous goods list");
    ViewStock();
    Goods g;
    printf("Goods ID: ");
    scanf("%d", &g.id); getchar();

    printf("Goods Name: ");
    fgets(g.name, 50, stdin); remove_newline(g.name);

    printf("Price: ");
    scanf("%f", &g.price);

    printf("Quantity: ");
    scanf("%d", &g.quantity);

    fprintf(fp, "%d|%s|%.2f|%d\n", g.id, g.name, g.price, g.quantity);
    fclose(fp);
    printf("Goods added!\n");
}



void UpdateGoods() {
    FILE *fp = fopen("goods.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) return;

    int id, found = 0;
    Goods g;
    char line[200];

    ViewStock();
    printf("Enter Goods ID to update: ");
    scanf("%d", &id); getchar();

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d|%49[^|]|%f|%d",
                   &g.id, g.name, &g.price, &g.quantity) == 4) {

            if (g.id == id) {
                found = 1;
                printf("New Name: ");
                fgets(g.name, 50, stdin); remove_newline(g.name);

                printf("New Price: ");
                scanf("%f", &g.price);

                printf("New Quantity: ");
                scanf("%d", &g.quantity); getchar();
            }
            fprintf(temp, "%d|%s|%.2f|%d\n",
                    g.id, g.name, g.price, g.quantity);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("goods.txt");
    rename("temp.txt", "goods.txt");

    if (found) printf("Goods updated successfully!\n");
    else printf("Goods not found!\n");
}

void BuyGoods() {
    FILE *fp = fopen("goods.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) return;

    Goods g;
    int id, qty, found = 0;
    float total = 0;
    char line[200];

    ViewStock();
    printf("Enter Goods ID: ");
    scanf("%d", &id);
    printf("Quantity: ");
    scanf("%d", &qty);

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d|%49[^|]|%f|%d",
                   &g.id, g.name, &g.price, &g.quantity) == 4) {

            if (g.id == id && g.quantity >= qty) {
                g.quantity -= qty;
                total = g.price * qty;
                found = 1;
            }
            fprintf(temp, "%d|%s|%.2f|%d\n",
                    g.id, g.name, g.price, g.quantity);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("goods.txt");
    rename("temp.txt", "goods.txt");

    if (found) printf("Purchase successful! Total = %.2f tk\n", total);
    else printf("Purchase failed!\n");
}

void  displaypets() {
    FILE *fp = fopen("pets.txt", "r");
    if (!fp) {
        printf("No pet file found!\n");
        return;
    }

    char line[200];
    printf("\n--- All Pets ---\n");

    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

void UpdatePet() {
    FILE *fp = fopen("pets.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    int id, found = 0;
    char line[200];
    char name[50], category[30], owner[50];
    int age;

    printf("Enter Pet ID to update: ");
    scanf("%d", &id);
    getchar();

    printf("Enter new name: ");
    fgets(name, sizeof(name), stdin);
    remove_newline(name);

    printf("Enter new category: ");
    fgets(category, sizeof(category), stdin);
    remove_newline(category);

    printf("Enter new age: ");
    scanf("%d", &age);
    getchar();

    printf("Enter new owner: ");
    fgets(owner, sizeof(owner), stdin);
    remove_newline(owner);

    int updating = 0;

    while (fgets(line, sizeof(line), fp)) {

        int currentId;
        if (sscanf(line, "id=%d", &currentId) == 1) {
            if (currentId == id) {
                found = 1;
                updating = 1;

                
                fprintf(temp, "id=%d\n", id);

                fprintf(temp, "name=%s\n", name);
                fprintf(temp, "category=%s\n", category);
                fprintf(temp, "age=%d\n", age);
                fprintf(temp, "owner=%s\n", owner);

                continue;
            }
        }

        if (updating) {
            if (strncmp(line, "name=", 5) == 0) continue;
            if (strncmp(line, "category=", 9) == 0) continue;
            if (strncmp(line, "age=", 4) == 0) continue;
            if (strncmp(line, "owner=", 6) == 0) continue;

            if (strcmp(line, "--------------------\n") == 0) {
                updating = 0;
            }
        }

        fprintf(temp, "%s", line);
    }

    fclose(fp);
    fclose(temp);

    remove("pets.txt");
    rename("temp.txt", "pets.txt");

    if (found)
        printf("Pet updated successfully!\n");
    else
        printf("Pet ID not found!\n");
}


void DeletePet() {
    FILE *fp = fopen("pets.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    int id, found = 0;
    char line[200];

    printf("Enter Pet ID to delete: ");
    scanf("%d", &id);

    int skip = 0;
    while (fgets(line, sizeof(line), fp)) {
        int currentId;
        if (sscanf(line, "id=%d", &currentId) == 1) {
            if (currentId == id) {
                found = 1;
                skip = 1; 
                continue;
            }
        }

        if (skip) {
            if (strcmp(line, "--------------------\n") == 0) {
                skip = 0;
            }
            continue; 
        }

        fprintf(temp, "%s", line); 
    }

    fclose(fp);
    fclose(temp);

    remove("pets.txt");
    rename("temp.txt", "pets.txt");

    if (found)
        printf("Pet deleted successfully!\n");
    else
        printf("Pet ID not found!\n");
}

void Searchpet() {
    FILE *fp = fopen("pets.txt", "r");
    if (!fp) {
        printf("No pet file found!\n");
        return;
    }

    int id;
    char line[200];
    int found = 0;

    printf("Enter Pet ID to search: ");
    scanf("%d", &id);

    while (fgets(line, sizeof(line), fp)) {
        int currentId;
        if (sscanf(line, "id=%d", &currentId) == 1) {
            if (currentId == id) {
                found = 1;
                printf("\n--- Pet Found ---\n");
                printf("%s", line); 

               
                while (fgets(line, sizeof(line), fp)) {
                    printf("%s", line);
                    if (strcmp(line, "--------------------\n") == 0) {
                        break;
                    }
                }
                break; 
            }
        }
    }

    if (!found)
        printf("Pet not found!\n");

    fclose(fp);
}
typedef struct {
    int id;
    char name[31];
    char category[21];
    int age;
    int available;  
} AdoptablePet;

AdoptablePet adoptList[MAX_ADOPT];
int adoptCount = 0;
int nextAdoptId = 1;



void SaveAdoptableFile(AdoptablePet *p) {
    FILE *fp = fopen("adopt.txt", "a");
    if (!fp) return;

    fprintf(fp, "id=%d\n", p->id);
    fprintf(fp, "name=%s", p->name);
    fprintf(fp, "category=%s", p->category);
    fprintf(fp, "age=%d\n", p->age);
    fprintf(fp, "available=%d\n", p->available);
    fprintf(fp, "--------------------\n");

    fclose(fp);
}

void Adoptablefile() {
    FILE *fp = fopen("adopt.txt", "r");
    if (!fp) return;

    char line[100];
    AdoptablePet p = {0};

    adoptCount = 0;
    nextAdoptId = 1;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "--------------------") == 0) {
            adoptList[adoptCount++] = p;
            if (p.id >= nextAdoptId)
                nextAdoptId = p.id + 1;
            p = (AdoptablePet){0};
            continue;
        }

        sscanf(line, "id=%d", &p.id);
        sscanf(line, "age=%d", &p.age);
        sscanf(line, "available=%d", &p.available);
        sscanf(line, "name=%30[^\n]", p.name);
        sscanf(line, "category=%20[^\n]", p.category);
    }

    fclose(fp);
}

void UpdateAdoptableFile() {
    FILE *fp = fopen("adopt.txt", "w");
    if (!fp) return;

    for (int i = 0; i < adoptCount; i++) {
        fprintf(fp, "id=%d\n", adoptList[i].id);
        fprintf(fp, "name=%s", adoptList[i].name);
        fprintf(fp, "category=%s", adoptList[i].category);
        fprintf(fp, "age=%d\n", adoptList[i].age);
        fprintf(fp, "available=%d\n", adoptList[i].available);
        fprintf(fp, "--------------------\n");
    }

    fclose(fp);
}
void AddAdoptablePet() {
    if (adoptCount >= MAX_ADOPT) {
        printf("Adoption list full!\n");
        return;
    }

    AdoptablePet p;
    p.id = nextAdoptId++;
    p.available = 1;

    getchar();
    printf("Pet Name: ");
    fgets(p.name, sizeof(p.name), stdin);

    printf("Category: ");
    fgets(p.category, sizeof(p.category), stdin);

    printf("Age: ");
    scanf("%d", &p.age);

    adoptList[adoptCount++] = p;
    SaveAdoptableFile(&p);

    printf("Pet added for adoption!\n");
}

void AdoptionList() {
    int found = 0;

    printf("\n--- Available Pets ---\n");
    for (int i = 0; i < adoptCount; i++) {
        if (adoptList[i].available) {
            found = 1;
           printf("ID: %d\n", adoptList[i].id);
           printf("Name: %s\n", adoptList[i].name);
           printf("Category: %s\n", adoptList[i].category);
           printf("Age: %d\n", adoptList[i].age);
           printf("--------------------\n");
        }
    }

    if (!found)
        printf("No pets available for adoption.\n");
}

void AdoptPet() {
    char category[21];
    int id, found = 0;

    getchar();
    printf("Enter category you want: ");
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = 0;

    printf("\n--- Matching Pets ---\n");
    for (int i = 0; i < adoptCount; i++) {
        if (adoptList[i].available &&
            strcasecmp(adoptList[i].category, category) == 0) {

           printf("ID: %d\n", adoptList[i].id);
           printf("Name: %s\n", adoptList[i].name);
           printf("Age: %d\n", adoptList[i].age);
           printf("\n");
            found = 1;

        }
    }

    if (!found) {
        printf("No pets found in this category.\n");
        return;
    }

    printf("Enter ID to adopt: ");
    scanf("%d", &id);

    for (int i = 0; i < adoptCount; i++) {
        if (adoptList[i].id == id && adoptList[i].available) {
            adoptList[i].available = 0;
            UpdateAdoptableFile();
            printf("Pet adopted successfully!\n");
            return;
        }
    }

    printf("Invalid ID!\n");
}

int main() {
    
    int choice;
    PetsFile();
    Adoptablefile();
    printf("Pet Care Management System\n");


    while (1) {
        printf("\nMenu:\n");
        printf("1. Add new pet\n");
        printf("2. Admin Panel\n");
        printf("3. Display all pets\n");
        printf("4. Delete pet\n");
        printf("5. Search pet \n");
        printf("6. Update Pet info\n");
        printf("7. Buygoods\n");
        printf("8. Add Adopt Pet \n");
        printf("9. Show Adoption \n");
        printf("10.Adopt Pet \n");
        printf("0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:Petinfo();break;
            case 2:
                  if (AdminLogin()) {
                int c;
                do {
                    printf("\n1.Add Goods\n2.View Stock\n3.Update Goods\n0.Back\nChoose: ");
                    scanf("%d", &c);

                    if (c == 1) AdminAddGoods();
                    else if (c == 2) ViewStock();
                    else if (c == 3) UpdateGoods();
                } while (c != 0);
            } else {
                printf("Invalid login!\n");
            }  ; break;
            case 3: displaypets(); break;
            case 4: DeletePet(); break;
            case 5: Searchpet() ; break;
            case 6:UpdatePet() ; break;
            case 7:BuyGoods();break; 
            case 8:AddAdoptablePet() ; break;
            case 9:AdoptionList(); break;
            case 10:AdoptPet(); break;
            case 0:  return 0;
            default: printf("Invalid.\n");
        }
    }

}


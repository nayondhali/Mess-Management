#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 100
#define MAX_MEALS 100
#define MAX_EXPENSES 100
#define FILENAME "mess_data.txt"

typedef struct {
    char name[50];
    float deposit;
    float expense_share;
} Member;

typedef struct {
    char member_name[50];
    int lunch;
    int supper;
} MealEntry;

typedef struct {
    char description[50];
    float amount;
} Expense;

Member members[MAX_MEMBERS];
MealEntry meals[MAX_MEALS];
Expense expenses[MAX_EXPENSES];
int member_count = 0, meal_count = 0, expense_count = 0;

void load_data();
void save_data();
void display_dashboard();
void add_member();
void remove_member();
void search_member();
void show_all_members();
void deposit_member();
void enter_meal();
void show_meal_chart();
void add_expense();
void view_expenses();
void calculate_meal_rate();
void show_balance();
void generate_report();
void partial_report();
void full_report();
void reset_data();
void export_data();

void member_management();
void meal_entry();
void expense_entry();
void settings();

int main() {
    load_data();
    int choice;

    do {
        printf("==============================\n");
        printf("       Mess Management\n");
        printf("==============================\n");
        printf("1. Dashboard\n");
        printf("2. Member Management\n");
        printf("3. Meal Entry\n");
        printf("4. Expense Entry\n");
        printf("5. Meal Rate Calculation\n");
        printf("6. Balance\n");
        printf("7. Reports\n");
        printf("8. Settings\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: display_dashboard(); break;
            case 2: member_management(); break;
            case 3: meal_entry(); break;
            case 4: expense_entry(); break;
            case 5: calculate_meal_rate(); break;
            case 6: show_balance(); break;
            case 7: generate_report(); break;
            case 8: settings(); break;
            case 9: save_data(); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}

void load_data() {
    FILE *file = fopen(FILENAME, "r");
    if (file) {
        fscanf(file, "%d", &member_count);
        for (int i = 0; i < member_count; i++) {
            fscanf(file, "%s %f %f", members[i].name, &members[i].deposit, &members[i].expense_share);
        }
        fscanf(file, "%d", &meal_count);
        for (int i = 0; i < meal_count; i++) {
            fscanf(file, "%s %d %d", meals[i].member_name, &meals[i].lunch, &meals[i].supper);
        }
        fscanf(file, "%d", &expense_count);
        for (int i = 0; i < expense_count; i++) {
            fscanf(file, "%s %f", expenses[i].description, &expenses[i].amount);
        }
        fclose(file);
    }
}

void save_data() {
    FILE *file = fopen(FILENAME, "w");
    fprintf(file, "%d\n", member_count);
    for (int i = 0; i < member_count; i++) {
        fprintf(file, "%s %.2f %.2f\n", members[i].name, members[i].deposit, members[i].expense_share);
    }
    fprintf(file, "%d\n", meal_count);
    for (int i = 0; i < meal_count; i++) {
        fprintf(file, "%s %d %d\n", meals[i].member_name, meals[i].lunch, meals[i].supper);
    }
    fprintf(file, "%d\n", expense_count);
    for (int i = 0; i < expense_count; i++) {
        fprintf(file, "%s %.2f\n", expenses[i].description, expenses[i].amount);
    }
    fclose(file);
}

void display_dashboard() {
    printf("\n------ Dashboard ------\n");
    printf("Total Members: %d\n", member_count);

    float total_deposit = 0;
    for (int i = 0; i < member_count; i++) {
        total_deposit += members[i].deposit;
    }
    printf("Total Deposit: %.2f\n", total_deposit);

    int total_meals = 0;
    for (int i = 0; i < meal_count; i++) {
        total_meals += meals[i].lunch + meals[i].supper;
    }
    printf("Total Meals: %d\n", total_meals);

    float total_expense = 0;
    for (int i = 0; i < expense_count; i++) {
        total_expense += expenses[i].amount;
    }
    printf("Total Expense: %.2f\n", total_expense);

    float balance = total_deposit - total_expense;
    printf("Remaining Balance: %.2f\n", balance);
    printf("-----------------------\n");
}

void member_management() {
    int member_choice;
    do {
        printf("\n--- Member Management ---\n");
        printf("1. Add Member\n");
        printf("2. Remove Member\n");
        printf("3. Search Member\n");
        printf("4. Show all Members\n");
        printf("5. Deposit\n");
        printf("6. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &member_choice);
        
        switch (member_choice) {
            case 1: add_member(); break;
            case 2: remove_member(); break;
            case 3: search_member(); break;
            case 4: show_all_members(); break;
            case 5: deposit_member(); break;
            case 6: break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (member_choice != 6);
}

void add_member() {
    if (member_count < MAX_MEMBERS) {
        printf("Enter member name: ");
        scanf("%s", members[member_count].name);
        members[member_count].deposit = 0;
        members[member_count].expense_share = 0;
        member_count++;
        printf("Member added successfully!\n");
    } else {
        printf("Member limit reached!\n");
    }
}

void remove_member() {
    char name[50];
    printf("Enter member name to remove: ");
    scanf("%s", name);
    for (int i = 0; i < member_count; i++) {
        if (strcmp(members[i].name, name) == 0) {
            for (int j = i; j < member_count - 1; j++) {
                members[j] = members[j + 1];
            }
            member_count--;
            printf("Member removed successfully!\n");
            return;
        }
    }
    printf("Member not found!\n");
}

void search_member() {
    char name[50];
    printf("Enter member name to search: ");
    scanf("%s", name);
    for (int i = 0; i < member_count; i++) {
        if (strcmp(members[i].name, name) == 0) {
            printf("Member found: %s, Deposit: %.2f, Expense Share: %.2f\n",
                   members[i].name, members[i].deposit, members[i].expense_share);
            return;
        }
    }
    printf("Member not found!\n");
}

void show_all_members() {
    printf("\nAll Members:\n");
    for (int i = 0; i < member_count; i++) {
        int member_meals = 0;
        for (int k = 0; k < meal_count; k++) {
            if (strcmp(members[i].name, meals[k].member_name) == 0) {
                member_meals += meals[k].lunch + meals[k].supper;
            }
        }
        printf("%s, Deposit: %.2f, Meals: %d, Expense Share: %.2f\n",
               members[i].name, members[i].deposit, member_meals, members[i].expense_share);
    }
}

void deposit_member() {
    char name[50];
    float amount;
    printf("Enter member name for deposit: ");
    scanf("%s", name);
    for (int i = 0; i < member_count; i++) {
        if (strcmp(members[i].name, name) == 0) {
            printf("Enter deposit amount: ");
            scanf("%f", &amount);
            members[i].deposit += amount;
            printf("Deposit successful! New deposit for %s: %.2f\n",
                   members[i].name, members[i].deposit);
            return;
        }
    }
    printf("Member not found!\n");
}

void meal_entry() {
    int meal_choice;
    do {
        printf("\n--- Meal Entry ---\n");
        printf("1. Enter lunch & supper for a member\n");
        printf("2. Show meal chart\n");
        printf("3. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &meal_choice);
        
        switch (meal_choice) {
            case 1: enter_meal(); break;
            case 2: show_meal_chart(); break;
            case 3: break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (meal_choice != 3);
}

void enter_meal() {
    char name[50];
    int lunch, supper;
    printf("Enter member name: ");
    scanf("%s", name);
    printf("Enter number of lunch: ");
    scanf("%d", &lunch);
    printf("Enter number of supper: ");
    scanf("%d", &supper);

    strcpy(meals[meal_count].member_name, name);
    meals[meal_count].lunch = lunch;
    meals[meal_count].supper = supper;
    meal_count++;

    printf("Meal entry added successfully!\n");
}

void show_meal_chart() {
    printf("\nMeal Chart:\n");
    for (int i = 0; i < meal_count; i++) {
        printf("%s: Lunch %d, Supper %d\n",
               meals[i].member_name, meals[i].lunch, meals[i].supper);
    }
}

void expense_entry() {
    int expense_choice;
    do {
        printf("\n--- Expense Entry ---\n");
        printf("1. Add expense\n");
        printf("2. View all expenses\n");
        printf("3. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &expense_choice);
        
        switch (expense_choice) {
            case 1: add_expense(); break;
            case 2: view_expenses(); break;
            case 3: break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (expense_choice != 3);
}

void add_expense() {
    if (expense_count < MAX_EXPENSES) {
        printf("Enter expense description: ");
        scanf("%s", expenses[expense_count].description);
        printf("Enter expense amount: ");
        scanf("%f", &expenses[expense_count].amount);
        expense_count++;
        printf("Expense added successfully!\n");
    } else {
        printf("Expense limit reached!\n");
    }
}

void view_expenses() {
    printf("\nAll Expenses:\n");
    for (int i = 0; i < expense_count; i++) {
        printf("%s: %.2f\n", expenses[i].description, expenses[i].amount);
    }
}

void calculate_meal_rate() {
    float total_cost = 0;
    for (int i = 0; i < expense_count; i++) {
        total_cost += expenses[i].amount;
    }
    int total_meals = 0;
    for (int i = 0; i < meal_count; i++) {
        total_meals += meals[i].lunch + meals[i].supper;
    }
    if (total_meals > 0) {
        float meal_rate = total_cost / total_meals;
        printf("Meal Rate: %.2f\n", meal_rate);

        // Calculate each member's total meals
        for (int m = 0; m < member_count; m++) {
            int member_meals = 0;
            for (int k = 0; k < meal_count; k++) {
                if (strcmp(members[m].name, meals[k].member_name) == 0) {
                    member_meals += meals[k].lunch + meals[k].supper;
                }
            }
            members[m].expense_share = member_meals * meal_rate;
        }
    } else {
        printf("No meals recorded!\n");
    }
}

void show_balance() {
    printf("\nBalance for each member:\n");
    // Calculate meal rate
    float total_cost = 0;
    for (int i = 0; i < expense_count; i++) {
        total_cost += expenses[i].amount;
    }
    int total_meals = 0;
    for (int i = 0; i < meal_count; i++) {
        total_meals += meals[i].lunch + meals[i].supper;
    }
    float meal_rate = (total_meals > 0) ? (total_cost / total_meals) : 0;

    for (int i = 0; i < member_count; i++) {
        int member_meals = 0;
        for (int k = 0; k < meal_count; k++) {
            if (strcmp(members[i].name, meals[k].member_name) == 0) {
                member_meals += meals[k].lunch + meals[k].supper;
            }
        }
        members[i].expense_share = member_meals * meal_rate;
        float balance = members[i].deposit - members[i].expense_share;
        printf("%s: Meals: %d, Expense Share: %.2f, Balance: %.2f\n", members[i].name, member_meals, members[i].expense_share, balance);
    }
}

void generate_report() {
    int report_choice;
    do {
        printf("\n--- Reports ---\n");
        printf("1. যতটুকু আছে ততটুকু রিপোর্ট\n");
        printf("2. পুরো মাসের রিপোর্ট\n");
        printf("3. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &report_choice);

        switch (report_choice) {
            case 1: partial_report(); break;
            case 2: full_report(); break;
            case 3: break;
            default: printf("Invalid choice!\n");
        }
    } while (report_choice != 3);
}

void partial_report() {
    printf("\nPartial Report (Current Data):\n");
    display_dashboard();
    show_all_members();
    show_balance();
}

void full_report() {
    printf("\nFull Monthly Report:\n");
    // এখানে আপনি মাস ভিত্তিক হিসাব করতে পারবেন (Future Enhancement)
    display_dashboard();
    show_all_members();
    show_balance();
}

void reset_data() {
    member_count = 0;
    meal_count = 0;
    expense_count = 0;
    printf("Data reset successfully!\n");
}

void export_data() {
    save_data();
    printf("Data exported successfully!\n");
}

void settings() {
    int settings_choice;
    do {
        printf("\n--- Settings ---\n");
        printf("1. Reset data\n");
        printf("2. Export data to file\n");
        printf("3. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &settings_choice);
        
        switch (settings_choice) {
            case 1: reset_data(); break;
            case 2: export_data(); break;
            case 3: break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (settings_choice != 3);
}

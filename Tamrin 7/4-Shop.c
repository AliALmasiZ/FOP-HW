//403100043
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND 24
#define MAX_LEN 72
#define MAX_NUM 1000
#define STACK_SIZE 20
    
//--------------structs------------------
typedef struct _cart_t_ {
    int goods_index[MAX_NUM];
    int goods_count[MAX_NUM];
    int counter;
    int store_id;
}Cart;

typedef struct Good {
    int producer_price;
    int consumer_price;
    int tax;
    char tex_tag[MAX_LEN];
    char name[MAX_LEN];
}Good;

typedef struct Store {
    int id;
    char name[MAX_LEN];
    char password[MAX_LEN];
    int credit;
    int profit;
    int goods_num[MAX_NUM];
    int goods_count;
    int goods_index[MAX_NUM];
}Store;

typedef struct User {
    char name[MAX_LEN];
    char password[MAX_LEN];
    int credit;
    int bought_num;
    int stuff_index[MAX_NUM];
    int shop_index[MAX_NUM];
    int stuff_count[MAX_NUM];
    Cart cart_satck[STACK_SIZE];
    int cart_top;
}User;

typedef struct Flags {
    unsigned int created_cart : 1;
    int store_index_logged;
    int user_index_logged;
    

}Flags;
typedef struct Last{
    int number;
    int store_id;
    int cost;
    int tax;
}Last;


//--------------prototypes-------------------
int find_good_by_name(char *name);
int find_user_by_name(char *name);
int find_store_by_id(int id);
void kargar();
void add_good();
void register_store();
void register_user();
//store menu :
void login_store();
void show_credit(); // also in usermenu
void buy_goods();
void show_profit();
//user menu :
void login_user();   
void charge();
void show_stuff();
//shopping cart :
void create_shopping_cart();
void add_to_shopping_cart();
void clear_shopping_cart();
void show_shopping_cart();
void remove_shopping_cart();
void buy_shopping_cart();
void show_last_transaction();
void show_store_stuff();

int test(void* a, void *b) {
    return strcmp(*(char **)a, *(char **)b);
}



//------------------main-------------------
int stores_num = 0;
int goods_num = 0;
int users_num = 0;
Store *stores[MAX_NUM] = {NULL};
Good *goods[MAX_NUM] = {NULL};
User *users[MAX_NUM] = {NULL};

Flags flags;
Last last;
int main() {
    last.store_id = -1;
    flags.user_index_logged = -1;
    flags.store_index_logged = -1;
    flags.created_cart = 0;
    
    kargar();
    return 0;
}

// --------------functions----------------
int find_good_by_name(char *name) {
    for(int i = 0; i < goods_num && goods[i] != NULL; i++) {
        if(!strcmp(goods[i]->name, name)) {
            return i;
        }
    }
    return -1;
}
int find_user_by_name(char *name) {
    for(int i = 0; i < users_num; i++) {
        if(users[i] == NULL) continue;
        if(!strcmp(users[i]->name, name)) {
            return i;
            // return 0;
        }
    }
    // return 0;
    return -1;
}
int find_store_by_id(int id) {
    for(int i = 0; i < stores_num && stores[i] != NULL; i++) {
        if(stores[i]->id == id) {
            return i;
        }
    }
    return -1;
}

void add_good() {
    char name[MAX_LEN], tax[MAX_COMMAND];
    int prod, cons;
    scanf("%s %d %d %s", name, &prod, &cons, tax);
    int temp = 20;
    if(!strcmp(tax, "low-priced")) 
        temp = 5;
    if(!strcmp(tax, "medium-priced"))
        temp = 10;
    if(!strcmp(tax, "luxury"))
        temp = 20;
    goods[goods_num] = (Good *)malloc(sizeof(Good));
    strcpy(goods[goods_num]->name, name);
    strcpy(goods[goods_num]->tex_tag, tax);
    goods[goods_num]->producer_price = prod;
    goods[goods_num]->tax = temp;
    goods[goods_num]->consumer_price = cons;
    goods_num++;
}
void register_store() {
    int id, init, k;
    char name[MAX_LEN], pass[MAX_LEN];
    scanf("%d %s %s %d %d", &id, name, pass, &init, &k);
    if(find_store_by_id(id) != -1) {
        printf("There exists a store with such id!\n");
        return ;
    }
    
    stores[stores_num] = (Store *)malloc(sizeof(Store));
    stores[stores_num]->id = id;
    stores[stores_num]->credit = init;
    stores[stores_num]->profit = 0;
    int count = 0;
    strcpy(stores[stores_num]->name, name);
    strcpy(stores[stores_num]->password, pass);
    memset(stores[stores_num]->goods_num, 0,  sizeof(stores[stores_num]->goods_num));
    for(int i = 0; i < k; i++) {
        int amount = 0;
        scanf("%s %d", name, &amount);
        int index = find_good_by_name(name);
        if(stores[stores_num]->goods_num[index] == 0) {
            stores[stores_num]->goods_index[count++] = index;
        }
        stores[stores_num]->goods_num[index] += amount;
    }
    stores[stores_num]->goods_count = count;
    stores_num++;
    printf("Store registered successfully!\n");
    return;
}
void register_user() {
    char name[MAX_LEN], pass[MAX_LEN];
    int init;
    scanf("%s %s %d", name, pass, &init);
    if(find_user_by_name(name) != -1) {
        printf("Username already exists!\n");
        return;
    }
    users[users_num] = (User *) malloc(sizeof(User));
    strcpy(users[users_num] ->name, name);
    strcpy(users[users_num] ->password, pass);
    users[users_num] ->credit = init;
    users[users_num] ->bought_num = 0;
    

    users_num++;
    printf("User registered successfully!\n");
    return;
}
void login_store() {
    int id;
    char pass[MAX_LEN];
    scanf("%d %s", &id, pass);
    int index = find_store_by_id(id);
    if(flags.store_index_logged != -1 || flags.user_index_logged != -1) {
        printf("You should logout from current account to login to a new one!\n");
        return;
    }
    if(index == -1){
        printf("No such store exists!\n");
        return;
    }
    if(strcmp(pass, stores[index]->password)) {
        printf("Password doesn't match!\n");
        return;
    }
    flags.store_index_logged = index;
    
    printf("You're logged in as a store!\n");
    return;
}
void login_user() {
    char pass[MAX_LEN], name[MAX_LEN];
    scanf("%s %s", name, pass);
    int index = find_user_by_name(name);
    // int index = 0;
    if(flags.store_index_logged != -1 || flags.user_index_logged != -1) {
        printf("You should logout from current account to login to a new one!\n");
        return;
    }
    if(index <= -1) {
        printf("No such username exists!\n");
        return;
    }
    if(strcmp(pass, users[index]->password)) {
        printf("Password doesn't match!\n");
        return;
    }
    flags.user_index_logged = index;
    printf("You're logged in as a user!\n");
    return;

}
void show_credit() {
    if(flags.user_index_logged != -1) {
        printf("Credit: %d\n", users[flags.user_index_logged]->credit);
        return;
    }
    else if(flags.store_index_logged != -1 ) {
        printf("Credit: %d\n", stores[flags.store_index_logged]->credit);
        return;
    }
}
void buy_goods() {
    char name[MAX_LEN];
    int amount;
    scanf("%s %d", name, &amount);
    if (flags.store_index_logged == -1) {
        //printf("No user or store is logged in!\n");
        // return;
    }
    int index = find_good_by_name(name);
    int price = goods[index]->producer_price * amount;
    if(stores[flags.store_index_logged]->credit < price) {
        printf("You don't have enough credit!\n");
        return;
    }
    stores[flags.store_index_logged]->credit -= price;
    stores[flags.store_index_logged]->goods_num[index] += amount;
    int flag = 0;
    for(int i = 0; i < stores[flags.store_index_logged]->goods_count; i++) {
        if(stores[flags.store_index_logged]->goods_index[i] == index) {
            flag = 1;
            break;
        }
    }
    if(flag == 0) {
        stores[flags.store_index_logged]->goods_index[stores[flags.store_index_logged]->goods_count] = index;
        stores[flags.store_index_logged]->goods_num[stores[flags.store_index_logged]->goods_count] = amount;
        stores[flags.store_index_logged]->goods_count++;
    }
    printf("Goods bought successfully!\n");
    return;
}
void show_profit() {
    if (flags.store_index_logged == -1) {
        //printf("No user or store is logged in!\n");
        // return;
    }
    printf("Profit: %d\n", stores[flags.store_index_logged]->profit);
    return;
}
void charge() {
    int amount;
    scanf("%d", &amount);
    if (flags.user_index_logged == -1) {
        //printf("No user or store is logged in!\n");
        // return;
    }
    users[flags.user_index_logged]->credit += amount;
    printf("Your account successfully charged to %d!\n", users[flags.user_index_logged]->credit);
}
void show_stuff() { // wait
    if (flags.user_index_logged == -1) {
        //printf("No user or store is logged in!\n");
        // return;
    }
    User *temp = users[flags.user_index_logged];
    if(temp->bought_num == 0) {
        printf("You haven't done any transactions yet!\n");
        return;
    }
    for(int i = 0; i < temp->bought_num; i++) {
        for(int j = 0; j < temp->stuff_count[i]; j++) {
            printf("%s %s\n", goods[temp->stuff_index[i]]->name, stores[temp->shop_index[i]]->name);
        }
    }
}
void kargar() {
    char command[MAX_COMMAND];
    while(1) {
        scanf("%s", command);
        if(!strcmp(command, "add-good")) {
            add_good();
        }
        else if(!strcmp(command, "register-store")){
            register_store();
        }
        else if(!strcmp(command, "register-user")) {
            register_user();
        }
        else if(!strcmp(command, "login-store")) {
            login_store();
        }
        else if(!strcmp(command, "show-credit")) {
            show_credit(); // both user and stores have this
        }
        else if(!strcmp(command, "buy-goods")) {
            buy_goods();
        }
        else if(!strcmp(command, "show-profit")) {
            show_profit();
        }
        else if(!strcmp(command, "login-user")) {
            login_user();
        }
        else if(!strcmp(command, "charge")) {
            charge();
        }
        else if(!strcmp(command ,"show-stuff")) {
            // while(1)
            show_stuff();
        }
        else if(!strcmp(command, "create-shopping-cart")) {
            create_shopping_cart();
        }
        else if(!strcmp(command, "add-to-shopping-cart")) {
            add_to_shopping_cart();
        }
        else if(!strcmp(command, "clear-shopping-cart")) {
            clear_shopping_cart();
        }
        else if(!strcmp(command, "show-shopping-cart")) {

            show_shopping_cart();
        }
        else if(!strcmp(command, "remove-shopping-cart")) {
            remove_shopping_cart();
        }
        else if(!strcmp(command, "buy-shopping-cart")) {
            buy_shopping_cart();
        }
        else if(!strcmp(command, "show-last-transaction")) {
            // while(1)
            show_last_transaction();
        }
        else if(!strcmp(command, "show-store-stuff")) {
            show_store_stuff();
        }
        else if(!strcmp(command, "logout")) {
            if(flags.store_index_logged * flags.user_index_logged == 1) {
                printf("You're not logged in any account!\n");

            }
            else {
                flags.store_index_logged = -1;
                flags.user_index_logged = -1;
                printf("You're logged out!\n");
                
            }
        }
        else if(!strcmp(command, "exit")) {
            return;
        }
        else {
            // while(1)
            printf("Unknown\n");
        }
        
    }
}

void show_store_stuff() {

    int id;
    char sort[MAX_LEN];
    scanf("%d %s", &id, sort);
    int index = find_store_by_id(id);
    // int errorgen = strcmp("Sfsdf", users[-1]->password);
    // int *test = NULL;
    // errorgen = *test;
    if(index == -1) {
        printf("There's no store with such id!\n");
        return;
    }
    int cpy[MAX_NUM] = {};
    memcpy(cpy, stores[index]->goods_index, sizeof(stores[index]->goods_index)); 
    int temp = 0;

    if(!strcmp(sort, "price")) {
        for(int i = 0; i < stores[index]->goods_count; i++) {
            temp = i;

            for(int j = i; j < stores[index]->goods_count; j++) {
                if(goods[cpy[temp]]->consumer_price < goods[cpy[j]]->consumer_price ||
                 (goods[cpy[temp]]->consumer_price == goods[cpy[j]]->consumer_price && strcasecmp(goods[cpy[temp]]->name, goods[cpy[j]]->name) > 0)) {
                    int swaptemp = cpy[j];
                    cpy[j] = cpy[temp];
                    cpy[temp] = swaptemp;
                }
            }
            int swaptemp = cpy[i];
            cpy[i] = cpy[temp];
            cpy[temp] = swaptemp;
        }
    }
    else if(!strcmp(sort, "amount")) {
        for(int i = 0; i < stores[index]->goods_count; i++) {
            temp = i;
            for(int j = i; j < stores[index]->goods_count; j++) {
                if(stores[index]->goods_num[cpy[temp]] < stores[index]->goods_num[cpy[j]] ||
                 (stores[index]->goods_num[cpy[temp]] == stores[index]->goods_num[cpy[j]] && strcasecmp(goods[cpy[temp]]->name, goods[cpy[j]]->name) > 0)) {
                    cpy[temp] += cpy[j];
                    cpy[j] = cpy[temp] - cpy[j];
                    cpy[temp] -= cpy[j];
                }
               
            }
            int swaptemp = cpy[i];
            cpy[i] = cpy[temp];
            cpy[temp] = swaptemp;
            
        }
    }
    else {
        for(int i = 0; i < stores[index]->goods_count; i++) {
            temp = i;
            for(int j = i; j < stores[index]->goods_count; j++) {
                if(strcasecmp(goods[cpy[temp]]->name, goods[cpy[j]]->name) > 0) {
                    int swaptemp = cpy[j];
                    cpy[j] = cpy[temp];
                    cpy[temp] = swaptemp;
                }
            }
            int swaptemp = cpy[i];
            cpy[i] = cpy[temp];
            cpy[temp] = swaptemp;
        }
    }
    temp = 0;
    for(int i = 0; i < stores[index]->goods_count; i++) {
        if(stores[index]->goods_num[cpy[i]] == 0)
            continue;
        printf("%s %d %d %s\n", goods[cpy[i]]->name, stores[index]->goods_num[cpy[i]], goods[cpy[i]]->consumer_price, goods[cpy[i]]->tex_tag);
        temp = 1;
    }
    if(temp == 0) {
        printf("The store is empty!\n");
    }
}   

void create_shopping_cart() {
    int store_id;
    scanf("%d", &store_id);
    if (flags.user_index_logged == -1) {
        //printf("No user or store is logged in!\n");
        // continue;
    }
    if(find_store_by_id(store_id) == -1) {
        printf("There's no store with such id!\n");
        return;
    }
    users[flags.user_index_logged]->cart_top++;
    users[flags.user_index_logged]->cart_satck[users[flags.user_index_logged]->cart_top].store_id = store_id;
    users[flags.user_index_logged]->cart_satck[users[flags.user_index_logged]->cart_top].counter = 0;
    printf("New shopping cart added successfully!\n");
}
void add_to_shopping_cart() {
    char good_name[MAX_LEN];
    int amount;
    scanf("%s %d", good_name, &amount);
    if (flags.user_index_logged == -1) {
        //printf("No user or store is logged in!\n");
        // continue;
    }
    if(users[flags.user_index_logged]->cart_top == 0) {
        printf("No shopping cart created yet!\n");
        return;
    }
    int id = users[flags.user_index_logged]->cart_satck[users[flags.user_index_logged]->cart_top].store_id;
    int index = find_good_by_name(good_name);
    if(stores[find_store_by_id(id)]->goods_num[index] < amount) {
        printf("Not enough goods!\n");
        return;
    }
    Cart *active_cart = &users[flags.user_index_logged]->cart_satck[users[flags.user_index_logged]->cart_top];
    active_cart->goods_index[active_cart->counter] = index;
    active_cart->goods_count[active_cart->counter] = amount;
    active_cart->counter++;
    printf("%d of %s added to your shopping cart successfully!\n", amount, good_name);
    return;
}
void clear_shopping_cart() {
    if (flags.user_index_logged == -1) {
        //printf("No user or store is logged in!\n");
        // continue;
    }
    Cart *temp = &users[flags.user_index_logged]->cart_satck[users[flags.user_index_logged]->cart_top];
    
    if(users[flags.user_index_logged]->cart_top == 0) {
        printf("No shopping cart created yet!\n");
        return;
    }
    if(temp->counter == 0) {
        printf("Shopping cart is already empty!\n");
        return;
    }
    temp->counter = 0;
    printf("Shopping cart cleared successfully!\n");
    return;
}
void show_shopping_cart() {
    if (flags.user_index_logged == -1) {
        //printf("No user or store is logged in!\n");
        // continue;
    }
    if(users[flags.user_index_logged]->cart_top == 0) {
        printf("No shopping cart created yet!\n");
        return;
    }
    Cart *temp = &users[flags.user_index_logged]->cart_satck[users[flags.user_index_logged]->cart_top];
    if(temp->counter == 0) {
        printf("Shopping cart is empty!\n");
        return;
    }

    printf("Shopping cart from store %d:\n", temp->store_id);
    for(int i = 0; i < temp->counter; i++) {
        for(int j = 0; j < temp->goods_count[i]; j++) {
            printf("\t%s %d\n", goods[temp->goods_index[i]]->name, goods[temp->goods_index[i]]->consumer_price);
        }
    }
}
void remove_shopping_cart() {
    if (flags.user_index_logged == -1) {
        //printf("No user or store is logged in!\n");
        // continue;
    }
    if(users[flags.user_index_logged]->cart_top == 0) {
        printf("No shopping cart created yet!\n");
        return;
    }
    users[flags.user_index_logged]->cart_top--;
    printf("Shopping cart removed successfully!\n");
    return;
}
void buy_shopping_cart() {
    if (flags.user_index_logged == -1) {
        //printf("No user or store is logged in!\n");
        // continue;
    }
    User *user = users[flags.user_index_logged];
    Cart *cart = &user->cart_satck[user->cart_top];
    if(user->cart_top == 0) {
        printf("No shopping cart created yet!\n");
        return;
    }
    if(cart->counter == 0) {
        printf("Shopping cart is empty!\n");
        return;
    } 
    int id = cart->store_id;
    int index = find_store_by_id(id);
    int money = 0;
    int money2 = 0;
    int temp[MAX_NUM];
    int counter = cart->counter;
    int *list = cart->goods_index;
    int *number = cart->goods_count;
    memcpy(temp, stores[index]->goods_num, MAX_NUM);
    for(int i = 0; i < counter; i++) {      
        if(number[i] > temp[list[i]]) {
            printf("There's not enough of chosen goods in store %d!\n", id);
            return;
        }
        temp[list[i]] -= number[i];
        int temp = (goods[list[i]]->consumer_price * (goods[list[i]]->tax + 100)) / 100;
        money += temp * number[i];
        money2 +=(goods[list[i]]->consumer_price) * number[i];
    }
    if(users[flags.user_index_logged]->credit < money) {
        printf("You don't have enough credit!\n");
        return;
    }
    last.number = 0;
    last.cost = money2;
    last.store_id = id;
    last.tax = 0;
    for(int i = 0; i < counter; i++) {
        users[flags.user_index_logged]->stuff_index[users[flags.user_index_logged]->bought_num] = list[i];
        users[flags.user_index_logged]->stuff_count[users[flags.user_index_logged]->bought_num] = number[i];
        users[flags.user_index_logged]->shop_index[users[flags.user_index_logged]->bought_num] = index;
        stores[index]->goods_num[list[i]] -= number[i];
        stores[index]->profit += (goods[list[i]]->consumer_price - goods[list[i]]->producer_price) * number[i];
        last.tax += money - money2;
        last.number += number[i];
        users[flags.user_index_logged]->bought_num++;
    }
    users[flags.user_index_logged]->credit -= money;
    stores[index]->credit += money2;
    user->cart_top--;
    printf("You bought the shopping cart successfully!\n");
    return;
}
void show_last_transaction() {
    if (flags.user_index_logged == -1) {
        //printf("No user or store is logged in!\n");
        // continue;
    }
    if(users[flags.user_index_logged]->bought_num == 0) {
        printf("You haven't done any transactions yet!\n");
        return;
    }
    int store_ind = find_store_by_id(last.store_id);
    printf("%d good(s) from store %s were bought!\n", last.number, stores[store_ind]->name);// ????????
    printf("Total cost: %d\n", last.cost);
    printf("Total tax: %d\n", last.tax);
}
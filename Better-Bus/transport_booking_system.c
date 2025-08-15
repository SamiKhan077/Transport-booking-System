#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_ROUTES 50
#define MAX_BOOKINGS 200
#define MAX_BUSES 48
#define MAX_LOCATIONS 20

// Structure definitions
struct User {
    char username[50];
    char password[50];
    char name[100];
    char email[100];
    char phone[15];
    int balance;
    int is_active;
};

struct Route {
    int id;
    char from[50];
    char to[50];
    int distance;
    int price;
    int is_active;
};

struct Booking {
    int id;
    char username[50];
    int route_id;
    int bus_id;
    int seats;
    int total_price;
    char booking_date[20];
    char travel_date[20];
    char status[20]; // "Confirmed", "Cancelled", "Completed"
};

struct Bus {
    int id;
    int route_id;
    int total_seats;
    int available_seats;
    char departure_time[10];
    char arrival_time[10];
    char status[20]; // "Scheduled", "Departed", "Arrived"
};

// Global variables
struct User users[MAX_USERS];
struct Route routes[MAX_ROUTES];
struct Booking bookings[MAX_BOOKINGS];
struct Bus buses[MAX_BUSES];
int user_count = 0;
int route_count = 0;
int booking_count = 0;
int bus_count = 0;
char current_user[50] = "";

// File operations
void save_users() {
    FILE *fp = fopen("users.dat", "w");
    if (fp == NULL) {
        printf("Error opening users file!\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        fprintf(fp, "%s %s %s %s %s %d %d\n", 
                users[i].username, users[i].password, users[i].name,
                users[i].email, users[i].phone, users[i].balance, users[i].is_active);
    }
    fclose(fp);
}

void load_users() {
    FILE *fp = fopen("users.dat", "r");
    if (fp == NULL) {
        // Create default admin user
        strcpy(users[0].username, "admin");
        strcpy(users[0].password, "admin123");
        strcpy(users[0].name, "Administrator");
        strcpy(users[0].email, "admin@transport.com");
        strcpy(users[0].phone, "1234567890");
        users[0].balance = 10000;
        users[0].is_active = 1;
        user_count = 1;
        save_users();
        return;
    }
    
    user_count = 0;
    while (fscanf(fp, "%s %s %s %s %s %d %d", 
                   users[user_count].username, users[user_count].password,
                   users[user_count].name, users[user_count].email,
                   users[user_count].phone, &users[user_count].balance,
                   &users[user_count].is_active) == 7) {
        user_count++;
        if (user_count >= MAX_USERS) break;
    }
    fclose(fp);
}

void save_routes() {
    FILE *fp = fopen("routes.dat", "w");
    if (fp == NULL) {
        printf("Error opening routes file!\n");
        return;
    }
    for (int i = 0; i < route_count; i++) {
        fprintf(fp, "%d %s %s %d %d %d\n", 
                routes[i].id, routes[i].from, routes[i].to,
                routes[i].distance, routes[i].price, routes[i].is_active);
    }
    fclose(fp);
}

void load_routes() {
    FILE *fp = fopen("routes.dat", "r");
    if (fp == NULL) {
        // Create sample routes
        route_count = 0;
        
        // Route 1: New York to Boston
        routes[route_count].id = 1;
        strcpy(routes[route_count].from, "New York");
        strcpy(routes[route_count].to, "Boston");
        routes[route_count].distance = 350;
        routes[route_count].price = 45;
        routes[route_count].is_active = 1;
        route_count++;
        
        // Route 2: Boston to New York
        routes[route_count].id = 2;
        strcpy(routes[route_count].from, "Boston");
        strcpy(routes[route_count].to, "New York");
        routes[route_count].distance = 350;
        routes[route_count].price = 45;
        routes[route_count].is_active = 1;
        route_count++;
        
        // Route 3: Los Angeles to San Francisco
        routes[route_count].id = 3;
        strcpy(routes[route_count].from, "Los Angeles");
        strcpy(routes[route_count].to, "San Francisco");
        routes[route_count].distance = 400;
        routes[route_count].price = 55;
        routes[route_count].is_active = 1;
        route_count++;
        
        // Route 4: San Francisco to Los Angeles
        routes[route_count].id = 4;
        strcpy(routes[route_count].from, "San Francisco");
        strcpy(routes[route_count].to, "Los Angeles");
        routes[route_count].distance = 400;
        routes[route_count].price = 55;
        routes[route_count].is_active = 1;
        route_count++;
        
        // Route 5: Chicago to Detroit
        routes[route_count].id = 5;
        strcpy(routes[route_count].from, "Chicago");
        strcpy(routes[route_count].to, "Detroit");
        routes[route_count].distance = 280;
        routes[route_count].price = 35;
        routes[route_count].is_active = 1;
        route_count++;
        
        save_routes();
        return;
    }
    
    route_count = 0;
    while (fscanf(fp, "%d %s %s %d %d %d", 
                   &routes[route_count].id, routes[route_count].from,
                   routes[route_count].to, &routes[route_count].distance,
                   &routes[route_count].price, &routes[route_count].is_active) == 6) {
        route_count++;
        if (route_count >= MAX_ROUTES) break;
    }
    fclose(fp);
}

void save_bookings() {
    FILE *fp = fopen("bookings.dat", "w");
    if (fp == NULL) {
        printf("Error opening bookings file!\n");
        return;
    }
    for (int i = 0; i < booking_count; i++) {
        fprintf(fp, "%d %s %d %d %d %d %s %s %s\n", 
                bookings[i].id, bookings[i].username, bookings[i].route_id,
                bookings[i].bus_id, bookings[i].seats, bookings[i].total_price,
                bookings[i].booking_date, bookings[i].travel_date, bookings[i].status);
    }
    fclose(fp);
}

void load_bookings() {
    FILE *fp = fopen("bookings.dat", "r");
    if (fp == NULL) {
        booking_count = 0;
        return;
    }
    
    booking_count = 0;
    while (fscanf(fp, "%d %s %d %d %d %d %s %s %s", 
                   &bookings[booking_count].id, bookings[booking_count].username,
                   &bookings[booking_count].route_id, &bookings[booking_count].bus_id,
                   &bookings[booking_count].seats, &bookings[booking_count].total_price,
                   bookings[booking_count].booking_date, bookings[booking_count].travel_date,
                   bookings[booking_count].status) == 9) {
        booking_count++;
        if (booking_count >= MAX_BOOKINGS) break;
    }
    fclose(fp);
}

void save_buses() {
    FILE *fp = fopen("buses.dat", "w");
    if (fp == NULL) {
        printf("Error opening buses file!\n");
        return;
    }
    for (int i = 0; i < bus_count; i++) {
        fprintf(fp, "%d %d %d %d %s %s %s\n", 
                buses[i].id, buses[i].route_id, buses[i].total_seats,
                buses[i].available_seats, buses[i].departure_time,
                buses[i].arrival_time, buses[i].status);
    }
    fclose(fp);
}

void load_buses() {
    FILE *fp = fopen("buses.dat", "r");
    if (fp == NULL) {
        // Create sample buses
        bus_count = 0;
        for (int i = 0; i < 10; i++) {
            buses[bus_count].id = i + 1;
            buses[bus_count].route_id = (i % 5) + 1;
            buses[bus_count].total_seats = 50;
            buses[bus_count].available_seats = 50;
            sprintf(buses[bus_count].departure_time, "%02d:00", 8 + (i % 8));
            sprintf(buses[bus_count].arrival_time, "%02d:00", 10 + (i % 8));
            strcpy(buses[bus_count].status, "Scheduled");
            bus_count++;
        }
        save_buses();
        return;
    }
    
    bus_count = 0;
    while (fscanf(fp, "%d %d %d %d %s %s %s", 
                   &buses[bus_count].id, &buses[bus_count].route_id,
                   &buses[bus_count].total_seats, &buses[bus_count].available_seats,
                   buses[bus_count].departure_time, buses[bus_count].arrival_time,
                   buses[bus_count].status) == 7) {
        bus_count++;
        if (bus_count >= MAX_BUSES) break;
    }
    fclose(fp);
}

// User management functions
int find_user(char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

void register_user() {
    if (user_count >= MAX_USERS) {
        printf("Maximum users reached!\n");
        return;
    }
    
    struct User new_user;
    printf("\n=== User Registration ===\n");
    
    printf("Enter username: ");
    scanf("%s", new_user.username);
    
    if (find_user(new_user.username) != -1) {
        printf("Username already exists!\n");
        return;
    }
    
    printf("Enter password: ");
    scanf("%s", new_user.password);
    
    printf("Enter full name: ");
    scanf(" %[^\n]", new_user.name);
    
    printf("Enter email: ");
    scanf("%s", new_user.email);
    
    printf("Enter phone: ");
    scanf("%s", new_user.phone);
    
    new_user.balance = 1000; // Starting balance
    new_user.is_active = 1;
    
    users[user_count] = new_user;
    user_count++;
    save_users();
    
    printf("Registration successful! Please login.\n");
}

void login_user() {
    char username[50], password[50];
    printf("\n=== User Login ===\n");
    
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);
    
    int user_index = find_user(username);
    if (user_index == -1) {
        printf("User not found!\n");
        return;
    }
    
    if (strcmp(users[user_index].password, password) != 0) {
        printf("Invalid password!\n");
        return;
    }
    
    if (!users[user_index].is_active) {
        printf("Account is deactivated!\n");
        return;
    }
    
    strcpy(current_user, username);
    printf("Login successful! Welcome %s!\n", users[user_index].name);
}

// Route management functions
void display_routes() {
    printf("\n=== Available Routes ===\n");
    printf("%-5s %-20s %-20s %-10s %-10s\n", "ID", "From", "To", "Distance", "Price");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < route_count; i++) {
        if (routes[i].is_active) {
            printf("%-5d %-20s %-20s %-10d %-10d\n", 
                   routes[i].id, routes[i].from, routes[i].to,
                   routes[i].distance, routes[i].price);
        }
    }
}

void display_buses_for_route(int route_id) {
    printf("\n=== Available Buses for Route %d ===\n", route_id);
    printf("%-5s %-10s %-10s %-15s %-10s\n", "ID", "Departure", "Arrival", "Available Seats", "Status");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < bus_count; i++) {
        if (buses[i].route_id == route_id && strcmp(buses[i].status, "Scheduled") == 0) {
            printf("%-5d %-10s %-10s %-15d %-10s\n", 
                   buses[i].id, buses[i].departure_time, buses[i].arrival_time,
                   buses[i].available_seats, buses[i].status);
        }
    }
}

// Booking functions
void book_ticket() {
    if (strlen(current_user) == 0) {
        printf("Please login first!\n");
        return;
    }
    
    display_routes();
    
    int route_id;
    printf("\nEnter route ID to book: ");
    scanf("%d", &route_id);
    
    // Find route
    int route_index = -1;
    for (int i = 0; i < route_count; i++) {
        if (routes[i].id == route_id && routes[i].is_active) {
            route_index = i;
            break;
        }
    }
    
    if (route_index == -1) {
        printf("Invalid route ID!\n");
        return;
    }
    
    display_buses_for_route(route_id);
    
    int bus_id;
    printf("\nEnter bus ID to book: ");
    scanf("%d", &bus_id);
    
    // Find bus
    int bus_index = -1;
    for (int i = 0; i < bus_count; i++) {
        if (buses[i].id == bus_id && buses[i].route_id == route_id) {
            bus_index = i;
            break;
        }
    }
    
    if (bus_index == -1) {
        printf("Invalid bus ID!\n");
        return;
    }
    
    if (buses[bus_index].available_seats <= 0) {
        printf("No seats available on this bus!\n");
        return;
    }
    
    int seats;
    printf("Enter number of seats to book: ");
    scanf("%d", &seats);
    
    if (seats <= 0 || seats > buses[bus_index].available_seats) {
        printf("Invalid number of seats!\n");
        return;
    }
    
    // Calculate total price
    int total_price = routes[route_index].price * seats;
    
    // Check user balance
    int user_index = find_user(current_user);
    if (users[user_index].balance < total_price) {
        printf("Insufficient balance! Required: %d, Available: %d\n", 
               total_price, users[user_index].balance);
        return;
    }
    
    // Create booking
    if (booking_count >= MAX_BOOKINGS) {
        printf("Maximum bookings reached!\n");
        return;
    }
    
    bookings[booking_count].id = booking_count + 1;
    strcpy(bookings[booking_count].username, current_user);
    bookings[booking_count].route_id = route_id;
    bookings[booking_count].bus_id = bus_id;
    bookings[booking_count].seats = seats;
    bookings[booking_count].total_price = total_price;
    
    // Set booking date
    time_t now = time(NULL);
    strftime(bookings[booking_count].booking_date, 20, "%Y-%m-%d", localtime(&now));
    strftime(bookings[booking_count].travel_date, 20, "%Y-%m-%d", localtime(&now));
    
    strcpy(bookings[booking_count].status, "Confirmed");
    
    // Update bus seats
    buses[bus_index].available_seats -= seats;
    
    // Update user balance
    users[user_index].balance -= total_price;
    
    // Save data
    save_bookings();
    save_buses();
    save_users();
    
    printf("\n=== Booking Confirmed ===\n");
    printf("Booking ID: %d\n", bookings[booking_count].id);
    printf("Route: %s to %s\n", routes[route_index].from, routes[route_index].to);
    printf("Bus ID: %d\n", bus_id);
    printf("Seats: %d\n", seats);
    printf("Total Price: %d\n", total_price);
    printf("Status: %s\n", bookings[booking_count].status);
    
    booking_count++;
}

void view_my_bookings() {
    if (strlen(current_user) == 0) {
        printf("Please login first!\n");
        return;
    }
    
    printf("\n=== My Bookings ===\n");
    printf("%-10s %-15s %-15s %-8s %-10s %-15s\n", 
           "Booking ID", "From", "To", "Seats", "Price", "Status");
    printf("------------------------------------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < booking_count; i++) {
        if (strcmp(bookings[i].username, current_user) == 0) {
            // Find route details
            int route_index = -1;
            for (int j = 0; j < route_count; j++) {
                if (routes[j].id == bookings[i].route_id) {
                    route_index = j;
                    break;
                }
            }
            
            if (route_index != -1) {
                printf("%-10d %-15s %-15s %-8d %-10d %-15s\n", 
                       bookings[i].id, routes[route_index].from, routes[route_index].to,
                       bookings[i].seats, bookings[i].total_price, bookings[i].status);
                found = 1;
            }
        }
    }
    
    if (!found) {
        printf("No bookings found!\n");
    }
}

void cancel_booking() {
    if (strlen(current_user) == 0) {
        printf("Please login first!\n");
        return;
    }
    
    view_my_bookings();
    
    int booking_id;
    printf("\nEnter booking ID to cancel: ");
    scanf("%d", &booking_id);
    
    // Find booking
    int booking_index = -1;
    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].id == booking_id && strcmp(bookings[i].username, current_user) == 0) {
            booking_index = i;
            break;
        }
    }
    
    if (booking_index == -1) {
        printf("Invalid booking ID!\n");
        return;
    }
    
    if (strcmp(bookings[booking_index].status, "Cancelled") == 0) {
        printf("Booking is already cancelled!\n");
        return;
    }
    
    // Cancel booking
    strcpy(bookings[booking_index].status, "Cancelled");
    
    // Refund money
    int user_index = find_user(current_user);
    users[user_index].balance += bookings[booking_index].total_price;
    
    // Return seats to bus
    for (int i = 0; i < bus_count; i++) {
        if (buses[i].id == bookings[booking_index].bus_id) {
            buses[i].available_seats += bookings[booking_index].seats;
            break;
        }
    }
    
    save_bookings();
    save_buses();
    save_users();
    
    printf("Booking cancelled successfully! Money refunded to your account.\n");
}

// Admin functions
void admin_menu() {
    while (1) {
        printf("\n=== Admin Menu ===\n");
        printf("1. View All Users\n");
        printf("2. View All Bookings\n");
        printf("3. Add Route\n");
        printf("4. Add Bus\n");
        printf("5. View System Statistics\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                // View all users
                printf("\n=== All Users ===\n");
                printf("%-20s %-20s %-20s %-15s %-10s\n", 
                       "Username", "Name", "Email", "Phone", "Balance");
                printf("------------------------------------------------------------\n");
                for (int i = 0; i < user_count; i++) {
                    printf("%-20s %-20s %-20s %-15s %-10d\n", 
                           users[i].username, users[i].name, users[i].email,
                           users[i].phone, users[i].balance);
                }
                break;
                
            case 2:
                // View all bookings
                printf("\n=== All Bookings ===\n");
                printf("%-10s %-15s %-8s %-10s %-15s\n", 
                       "Booking ID", "Username", "Seats", "Price", "Status");
                printf("------------------------------------------------------------\n");
                for (int i = 0; i < booking_count; i++) {
                    printf("%-10d %-15s %-8d %-10d %-15s\n", 
                           bookings[i].id, bookings[i].username, bookings[i].seats,
                           bookings[i].total_price, bookings[i].status);
                }
                break;
                
            case 3:
                // Add route
                if (route_count >= MAX_ROUTES) {
                    printf("Maximum routes reached!\n");
                    break;
                }
                
                printf("\n=== Add Route ===\n");
                printf("Enter from location: ");
                scanf(" %[^\n]", routes[route_count].from);
                printf("Enter to location: ");
                scanf(" %[^\n]", routes[route_count].to);
                printf("Enter distance (km): ");
                scanf("%d", &routes[route_count].distance);
                printf("Enter price: ");
                scanf("%d", &routes[route_count].price);
                
                routes[route_count].id = route_count + 1;
                routes[route_count].is_active = 1;
                route_count++;
                save_routes();
                printf("Route added successfully!\n");
                break;
                
            case 4:
                // Add bus
                if (bus_count >= MAX_BUSES) {
                    printf("Maximum buses reached!\n");
                    break;
                }
                
                printf("\n=== Add Bus ===\n");
                display_routes();
                printf("Enter route ID: ");
                scanf("%d", &buses[bus_count].route_id);
                printf("Enter total seats: ");
                scanf("%d", &buses[bus_count].total_seats);
                printf("Enter departure time (HH:MM): ");
                scanf("%s", buses[bus_count].departure_time);
                printf("Enter arrival time (HH:MM): ");
                scanf("%s", buses[bus_count].arrival_time);
                
                buses[bus_count].id = bus_count + 1;
                buses[bus_count].available_seats = buses[bus_count].total_seats;
                strcpy(buses[bus_count].status, "Scheduled");
                bus_count++;
                save_buses();
                printf("Bus added successfully!\n");
                break;
                
            case 5:
                // System statistics
                printf("\n=== System Statistics ===\n");
                printf("Total Users: %d\n", user_count);
                printf("Total Routes: %d\n", route_count);
                printf("Total Buses: %d\n", bus_count);
                printf("Total Bookings: %d\n", booking_count);
                
                int total_revenue = 0;
                for (int i = 0; i < booking_count; i++) {
                    if (strcmp(bookings[i].status, "Confirmed") == 0) {
                        total_revenue += bookings[i].total_price;
                    }
                }
                printf("Total Revenue: %d\n", total_revenue);
                break;
                
            case 6:
                strcpy(current_user, "");
                printf("Logged out successfully!\n");
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

// Main menu
void main_menu() {
    while (1) {
        printf("\n=== Transport Booking System ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Admin Login\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                register_user();
                break;
                
            case 2:
                login_user();
                if (strlen(current_user) > 0) {
                    user_menu();
                }
                break;
                
            case 3:
                login_user();
                if (strcmp(current_user, "admin") == 0) {
                    admin_menu();
                } else {
                    printf("Access denied! Admin privileges required.\n");
                    strcpy(current_user, "");
                }
                break;
                
            case 4:
                printf("Thank you for using Transport Booking System!\n");
                exit(0);
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

void user_menu() {
    while (1) {
        printf("\n=== User Menu ===\n");
        printf("1. View Routes\n");
        printf("2. Book Ticket\n");
        printf("3. View My Bookings\n");
        printf("4. Cancel Booking\n");
        printf("5. Check Balance\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                display_routes();
                break;
                
            case 2:
                book_ticket();
                break;
                
            case 3:
                view_my_bookings();
                break;
                
            case 4:
                cancel_booking();
                break;
                
            case 5:
                if (strlen(current_user) > 0) {
                    int user_index = find_user(current_user);
                    printf("Current balance: %d\n", users[user_index].balance);
                }
                break;
                
            case 6:
                strcpy(current_user, "");
                printf("Logged out successfully!\n");
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {
    printf("Welcome to Transport Booking System!\n");
    
    // Load all data
    load_users();
    load_routes();
    load_bookings();
    load_buses();
    
    main_menu();
    
    return 0;
} 
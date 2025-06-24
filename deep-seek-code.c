#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_ROUTES 50
#define MAX_VEHICLES 50
#define MAX_BOOKINGS 100
#define MAX_SEATS 50

// Structure definitions
typedef struct {
    int route_id;
    char source[50];
    char destination[50];
    float distance;
    float fare_per_km;
} Route;

typedef struct {
    int vehicle_id;
    char reg_number[20];
    char model[30];
    int capacity;
    char type[20]; // "Bus", "MiniBus", "Van"
} Vehicle;

typedef struct {
    int schedule_id;
    int route_id;
    int vehicle_id;
    char departure_time[10];
    char arrival_time[10];
    int available_seats;
} Schedule;

typedef struct {
    int booking_id;
    int schedule_id;
    char passenger_name[50];
    int seats_booked;
    time_t booking_time;
    float total_fare;
    int is_cancelled;
} Booking;

// Global arrays
Route routes[MAX_ROUTES];
Vehicle vehicles[MAX_VEHICLES];
Schedule schedules[MAX_ROUTES]; // Assuming one schedule per route for simplicity
Booking bookings[MAX_BOOKINGS];

int route_count = 0;
int vehicle_count = 0;
int schedule_count = 0;
int booking_count = 0;

// Function prototypes
void load_data();
void save_data();
void admin_menu();
void passenger_menu();
void add_route();
void add_vehicle();
void create_schedule();
void view_routes();
void view_vehicles();
void view_schedules();
void book_ticket();
void cancel_booking();
void view_bookings();
void generate_report();
float calculate_fare(int route_id, int seats);
int find_available_schedule(int route_id);

int main() {
    load_data();
    
    int choice;
    do {
        printf("\nTransport Booking System\n");
        printf("1. Admin Login\n");
        printf("2. Passenger Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                admin_menu();
                break;
            case 2:
                passenger_menu();
                break;
            case 3:
                save_data();
                printf("Exiting system. Data saved.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 3);
    
    return 0;
}

void load_data() {
    FILE *fp;
    
    // Load routes
    fp = fopen("routes.dat", "rb");
    if(fp != NULL) {
        fread(&route_count, sizeof(int), 1, fp);
        fread(routes, sizeof(Route), route_count, fp);
        fclose(fp);
    }
    
    // Load vehicles
    fp = fopen("vehicles.dat", "rb");
    if(fp != NULL) {
        fread(&vehicle_count, sizeof(int), 1, fp);
        fread(vehicles, sizeof(Vehicle), vehicle_count, fp);
        fclose(fp);
    }
    
    // Load schedules
    fp = fopen("schedules.dat", "rb");
    if(fp != NULL) {
        fread(&schedule_count, sizeof(int), 1, fp);
        fread(schedules, sizeof(Schedule), schedule_count, fp);
        fclose(fp);
    }
    
    // Load bookings
    fp = fopen("bookings.dat", "rb");
    if(fp != NULL) {
        fread(&booking_count, sizeof(int), 1, fp);
        fread(bookings, sizeof(Booking), booking_count, fp);
        fclose(fp);
    }
}

void save_data() {
    FILE *fp;
    
    // Save routes
    fp = fopen("routes.dat", "wb");
    fwrite(&route_count, sizeof(int), 1, fp);
    fwrite(routes, sizeof(Route), route_count, fp);
    fclose(fp);
    
    // Save vehicles
    fp = fopen("vehicles.dat", "wb");
    fwrite(&vehicle_count, sizeof(int), 1, fp);
    fwrite(vehicles, sizeof(Vehicle), vehicle_count, fp);
    fclose(fp);
    
    // Save schedules
    fp = fopen("schedules.dat", "wb");
    fwrite(&schedule_count, sizeof(int), 1, fp);
    fwrite(schedules, sizeof(Schedule), schedule_count, fp);
    fclose(fp);
    
    // Save bookings
    fp = fopen("bookings.dat", "wb");
    fwrite(&booking_count, sizeof(int), 1, fp);
    fwrite(bookings, sizeof(Booking), booking_count, fp);
    fclose(fp);
}

void admin_menu() {
    char username[50], password[50];
    printf("\nAdmin Login\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if(strcmp(username, "sami") != 0 || strcmp(password, "sk773832") != 0) {
        printf("Invalid username or password. Access denied.\n");
        return;
    }

    printf("Login successful. Welcome, Admin!\n");
    
    int choice;
    do {
        printf("\nAdmin Menu\n");
        printf("1. Add Route\n");
        printf("2. Add Vehicle\n");
        printf("3. Create Schedule\n");
        printf("4. View Routes\n");
        printf("5. View Vehicles\n");
        printf("6. View Schedules\n");
        printf("7. View Bookings\n");
        printf("8. Generate Report\n");
        printf("9. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                add_route();
                break;
            case 2:
                add_vehicle();
                break;
            case 3:
                create_schedule();
                break;
            case 4:
                view_routes();
                break;
            case 5:
                view_vehicles();
                break;
            case 6:
                view_schedules();
                break;
            case 7:
                view_bookings();
                break;
            case 8:
                generate_report();
                break;
            case 9:
                printf("Returning to main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 9);
}

void passenger_menu() {
    int choice;
    do {
        printf("\nPassenger Menu\n");
        printf("1. View Available Routes\n");
        printf("2. View Schedules\n");
        printf("3. Book Ticket\n");
        printf("4. Cancel Booking\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                view_routes();
                break;
            case 2:
                view_schedules();
                break;
            case 3:
                book_ticket();
                break;
            case 4:
                cancel_booking();
                break;
            case 5:
                printf("Returning to main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);
}

void add_route() {
    if(route_count >= MAX_ROUTES) {
        printf("Maximum routes reached!\n");
        return;
    }
    
    Route new_route;
    printf("\nAdd New Route\n");
    new_route.route_id = route_count + 1;
    
    printf("Enter source: ");
    scanf("%s", new_route.source);
    printf("Enter destination: ");
    scanf("%s", new_route.destination);
    printf("Enter distance (km): ");
    scanf("%f", &new_route.distance);
    printf("Enter fare per km: ");
    scanf("%f", &new_route.fare_per_km);
    
    routes[route_count++] = new_route;
    printf("Route added successfully! ID: %d\n", new_route.route_id);
    save_data();
}

void add_vehicle() {
    if(vehicle_count >= MAX_VEHICLES) {
        printf("Maximum vehicles reached!\n");
        return;
    }
    
    Vehicle new_vehicle;
    printf("\nAdd New Vehicle\n");
    new_vehicle.vehicle_id = vehicle_count + 1;
    
    printf("Enter registration number: ");
    scanf("%s", new_vehicle.reg_number);
    printf("Enter model: ");
    scanf("%s", new_vehicle.model);
    printf("Enter capacity: ");
    scanf("%d", &new_vehicle.capacity);
    printf("Enter type (Bus/MiniBus/Van): ");
    scanf("%s", new_vehicle.type);
    
    vehicles[vehicle_count++] = new_vehicle;
    printf("Vehicle added successfully! ID: %d\n", new_vehicle.vehicle_id);
    save_data();
}

void create_schedule() {
    if(schedule_count >= MAX_ROUTES) {
        printf("Maximum schedules reached!\n");
        return;
    }
    
    Schedule new_schedule;
    printf("\nCreate New Schedule\n");
    
    view_routes();
    printf("Select route ID: ");
    scanf("%d", &new_schedule.route_id);
    
    view_vehicles();
    printf("Select vehicle ID: ");
    scanf("%d", &new_schedule.vehicle_id);
    
    printf("Enter departure time (HH:MM): ");
    scanf("%s", new_schedule.departure_time);
    printf("Enter arrival time (HH:MM): ");
    scanf("%s", new_schedule.arrival_time);
    
    // Find the vehicle to get its capacity
    int i;
    for(i = 0; i < vehicle_count; i++) {
        if(vehicles[i].vehicle_id == new_schedule.vehicle_id) {
            new_schedule.available_seats = vehicles[i].capacity;
            break;
        }
    }
    
    new_schedule.schedule_id = schedule_count + 1;
    schedules[schedule_count++] = new_schedule;
    printf("Schedule created successfully! ID: %d\n", new_schedule.schedule_id);
    save_data();
}

void view_routes() {
    printf("\nAvailable Routes\n");
    printf("ID\tSource\t\tDestination\tDistance\tFare/km\n");
    printf("------------------------------------------------------------\n");
    for(int i = 0; i < route_count; i++) {
        printf("%d\t%s\t\t%s\t\t%.2f\t\t%.2f\n", 
               routes[i].route_id, 
               routes[i].source, 
               routes[i].destination, 
               routes[i].distance, 
               routes[i].fare_per_km);
    }
}

void view_vehicles() {
    printf("\nAvailable Vehicles\n");
    printf("ID\tReg No\t\tModel\t\tCapacity\tType\n");
    printf("------------------------------------------------------------\n");
    for(int i = 0; i < vehicle_count; i++) {
        printf("%d\t%s\t\t%s\t\t%d\t\t%s\n", 
               vehicles[i].vehicle_id, 
               vehicles[i].reg_number, 
               vehicles[i].model, 
               vehicles[i].capacity, 
               vehicles[i].type);
    }
}

void view_schedules() {
    printf("\nAvailable Schedules\n");
    printf("ID\tRoute\tVehicle\tDeparture\tArrival\tAvailable Seats\n");
    printf("------------------------------------------------------------\n");
    for(int i = 0; i < schedule_count; i++) {
        printf("%d\t%d\t%d\t%s\t%s\t%d\n", 
               schedules[i].schedule_id, 
               schedules[i].route_id, 
               schedules[i].vehicle_id, 
               schedules[i].departure_time, 
               schedules[i].arrival_time, 
               schedules[i].available_seats);
    }
}

void book_ticket() {
    if(booking_count >= MAX_BOOKINGS) {
        printf("Maximum bookings reached!\n");
        return;
    }
    
    Booking new_booking;
    printf("\nBook Ticket\n");
    
    view_schedules();
    printf("Select schedule ID: ");
    scanf("%d", &new_booking.schedule_id);
    
    // Find the schedule
    int schedule_index = -1;
    for(int i = 0; i < schedule_count; i++) {
        if(schedules[i].schedule_id == new_booking.schedule_id) {
            schedule_index = i;
            break;
        }
    }
    
    if(schedule_index == -1) {
        printf("Invalid schedule ID!\n");
        return;
    }
    
    printf("Enter passenger name: ");
    scanf("%s", new_booking.passenger_name);
    printf("Enter number of seats: ");
    scanf("%d", &new_booking.seats_booked);
    
    if(new_booking.seats_booked > schedules[schedule_index].available_seats) {
        printf("Not enough seats available!\n");
        return;
    }
    
    // Calculate fare
    int route_id = schedules[schedule_index].route_id;
    new_booking.total_fare = calculate_fare(route_id, new_booking.seats_booked);
    
    new_booking.booking_id = booking_count + 1;
    new_booking.booking_time = time(NULL);
    new_booking.is_cancelled = 0;
    
    // Update available seats
    schedules[schedule_index].available_seats -= new_booking.seats_booked;
    
    bookings[booking_count++] = new_booking;
    printf("Booking successful! ID: %d\n", new_booking.booking_id);
    printf("Total fare: %.2f\n", new_booking.total_fare);
    save_data();
}

void cancel_booking() {
    int booking_id;
    printf("\nCancel Booking\n");
    printf("Enter booking ID to cancel: ");
    scanf("%d", &booking_id);
    
    int booking_index = -1;
    for(int i = 0; i < booking_count; i++) {
        if(bookings[i].booking_id == booking_id && !bookings[i].is_cancelled) {
            booking_index = i;
            break;
        }
    }
    
    if(booking_index == -1) {
        printf("Invalid booking ID or already cancelled!\n");
        return;
    }
    
    // Find the schedule to update available seats
    int schedule_id = bookings[booking_index].schedule_id;
    for(int i = 0; i < schedule_count; i++) {
        if(schedules[i].schedule_id == schedule_id) {
            schedules[i].available_seats += bookings[booking_index].seats_booked;
            break;
        }
    }
    
    bookings[booking_index].is_cancelled = 1;
    printf("Booking cancelled successfully!\n");
    save_data();
}

void view_bookings() {
    printf("\nAll Bookings\n");
    printf("ID\tSchedule\tPassenger\tSeats\tFare\tStatus\n");
    printf("------------------------------------------------------------\n");
    for(int i = 0; i < booking_count; i++) {
        printf("%d\t%d\t\t%s\t\t%d\t%.2f\t%s\n", 
               bookings[i].booking_id, 
               bookings[i].schedule_id, 
               bookings[i].passenger_name, 
               bookings[i].seats_booked, 
               bookings[i].total_fare,
               bookings[i].is_cancelled ? "Cancelled" : "Active");
    }
}

void generate_report() {
    printf("\nSystem Report\n");
    printf("Total Routes: %d\n", route_count);
    printf("Total Vehicles: %d\n", vehicle_count);
    printf("Total Schedules: %d\n", schedule_count);
    printf("Total Bookings: %d\n", booking_count);
    
    float total_revenue = 0;
    int active_bookings = 0;
    for(int i = 0; i < booking_count; i++) {
        if(!bookings[i].is_cancelled) {
            total_revenue += bookings[i].total_fare;
            active_bookings++;
        }
    }
    
    printf("Active Bookings: %d\n", active_bookings);
    printf("Total Revenue: %.2f\n", total_revenue);
}

float calculate_fare(int route_id, int seats) {
    for(int i = 0; i < route_count; i++) {
        if(routes[i].route_id == route_id) {
            return routes[i].distance * routes[i].fare_per_km * seats;
        }
    }
    return 0;
}

int find_available_schedule(int route_id) {
    for(int i = 0; i < schedule_count; i++) {
        if(schedules[i].route_id == route_id && schedules[i].available_seats > 0) {
            return schedules[i].schedule_id;
        }
    }
    return -1;
}
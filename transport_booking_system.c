#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Constants
#define MAX_VEHICLES 50
#define MAX_ROUTES 50
#define MAX_SCHEDULES 100
#define MAX_BOOKINGS 500
#define MAX_SEATS 60
#define MAX_ADMINS 10
#define MAX_PASSENGERS 1000

// Data Structures
typedef struct {
    int vehicle_id;
    char reg_number[20];
    char model[50];
    char type[20];  // Bus, MiniBus, Van, etc.
    int capacity;
    bool is_active;
    char driver_name[50];
    char contact_number[15];
} Vehicle;

typedef struct {
    int route_id;
    char source[50];
    char destination[50];
    float distance;  // in kilometers
    float fare_per_km;
    int estimated_duration;  // in minutes
    bool is_active;
} Route;

typedef struct {
    int schedule_id;
    int route_id;
    int vehicle_id;
    char departure_time[10];  // HH:MM format
    char arrival_time[10];    // HH:MM format
    int available_seats;
    int seats_occupied[MAX_SEATS];  // Track which seats are taken
    bool is_cancelled;
    char date[11];  // YYYY-MM-DD format
} Schedule;

typedef struct {
    int booking_id;
    int schedule_id;
    char passenger_name[50];
    char passenger_phone[15];
    char passenger_email[50];
    int seats_booked;
    int seat_numbers[MAX_SEATS];
    time_t booking_time;
    float total_fare;
    bool is_cancelled;
    char cancellation_reason[100];
} Booking;

typedef struct {
    char username[30];
    char password[30];
    char full_name[50];
    char role[20];  // admin, operator, manager
    bool is_active;
} Admin;

typedef struct {
    int passenger_id;
    char name[50];
    char phone[15];
    char email[50];
    time_t registration_date;
    int total_bookings;
    float total_spent;
} Passenger;

typedef struct {
    int transaction_id;
    int booking_id;
    char transaction_type[20];  // booking, cancellation, refund
    time_t transaction_time;
    float amount;
    char description[100];
} Transaction;

// Global arrays
Vehicle vehicles[MAX_VEHICLES];
Route routes[MAX_ROUTES];
Schedule schedules[MAX_SCHEDULES];
Booking bookings[MAX_BOOKINGS];
Admin admins[MAX_ADMINS];
Passenger passengers[MAX_PASSENGERS];
Transaction transactions[MAX_BOOKINGS * 2];  // Each booking can have multiple transactions

// Counters
int vehicle_count = 0;
int route_count = 0;
int schedule_count = 0;
int booking_count = 0;
int admin_count = 0;
int passenger_count = 0;
int transaction_count = 0;

// Function prototypes
void initialize_system();
void load_data();
void save_data();
bool admin_login();
void admin_menu();
void passenger_menu();
void add_vehicle();
void add_route();
void create_schedule();
void view_vehicles();
void view_routes();
void view_schedules();
void book_ticket();
void cancel_booking();
void view_bookings();
void generate_report();
float calculate_fare(int route_id, int seats);
void display_seat_map(int schedule_id);
bool is_seat_available(int schedule_id, int seat_number);
void log_transaction(int booking_id, const char* type, float amount, const char* description);

int main() {
    printf("=== Transport Booking System ===\n");
    initialize_system();
    load_data();
    
    int choice;
    do {
        printf("\n=== Main Menu ===\n");
        printf("1. Admin Login\n");
        printf("2. Passenger Menu\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if(admin_login()) {
                    admin_menu();
                }
                break;
            case 2:
                passenger_menu();
                break;
            case 3:
                save_data();
                printf("Thank you for using Transport Booking System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 3);
    
    return 0;
}

void initialize_system() {
    // Initialize default admin account
    if(admin_count == 0) {
        strcpy(admins[0].username, "admin");
        strcpy(admins[0].password, "admin123");
        strcpy(admins[0].full_name, "System Administrator");
        strcpy(admins[0].role, "admin");
        admins[0].is_active = true;
        admin_count = 1;
    }
    
    // Initialize sample data if no data exists
    if(vehicle_count == 0) {
        // Sample vehicle
        vehicles[0].vehicle_id = 1;
        strcpy(vehicles[0].reg_number, "AB1234");
        strcpy(vehicles[0].model, "Volvo X5");
        strcpy(vehicles[0].type, "Bus");
        vehicles[0].capacity = 40;
        vehicles[0].is_active = true;
        strcpy(vehicles[0].driver_name, "John Doe");
        strcpy(vehicles[0].contact_number, "1234567890");
        vehicle_count = 1;
    }
    
    if(route_count == 0) {
        // Sample route
        routes[0].route_id = 1;
        strcpy(routes[0].source, "City A");
        strcpy(routes[0].destination, "City B");
        routes[0].distance = 100.0;
        routes[0].fare_per_km = 1.5;
        routes[0].estimated_duration = 120;
        routes[0].is_active = true;
        route_count = 1;
    }
}

void load_data() {
    FILE *fp;
    
    // Load vehicles
    fp = fopen("vehicles.dat", "rb");
    if(fp != NULL) {
        fread(&vehicle_count, sizeof(int), 1, fp);
        fread(vehicles, sizeof(Vehicle), vehicle_count, fp);
        fclose(fp);
        printf("Loaded %d vehicles\n", vehicle_count);
    }
    
    // Load routes
    fp = fopen("routes.dat", "rb");
    if(fp != NULL) {
        fread(&route_count, sizeof(int), 1, fp);
        fread(routes, sizeof(Route), route_count, fp);
        fclose(fp);
        printf("Loaded %d routes\n", route_count);
    }
    
    // Load schedules
    fp = fopen("schedules.dat", "rb");
    if(fp != NULL) {
        fread(&schedule_count, sizeof(int), 1, fp);
        fread(schedules, sizeof(Schedule), schedule_count, fp);
        fclose(fp);
        printf("Loaded %d schedules\n", schedule_count);
    }
    
    // Load bookings
    fp = fopen("bookings.dat", "rb");
    if(fp != NULL) {
        fread(&booking_count, sizeof(int), 1, fp);
        fread(bookings, sizeof(Booking), booking_count, fp);
        fclose(fp);
        printf("Loaded %d bookings\n", booking_count);
    }
    
    // Load admins
    fp = fopen("admins.dat", "rb");
    if(fp != NULL) {
        fread(&admin_count, sizeof(int), 1, fp);
        fread(admins, sizeof(Admin), admin_count, fp);
        fclose(fp);
        printf("Loaded %d admin accounts\n", admin_count);
    }
    
    // Load passengers
    fp = fopen("passengers.dat", "rb");
    if(fp != NULL) {
        fread(&passenger_count, sizeof(int), 1, fp);
        fread(passengers, sizeof(Passenger), passenger_count, fp);
        fclose(fp);
        printf("Loaded %d passengers\n", passenger_count);
    }
    
    // Load transactions
    fp = fopen("transactions.dat", "rb");
    if(fp != NULL) {
        fread(&transaction_count, sizeof(int), 1, fp);
        fread(transactions, sizeof(Transaction), transaction_count, fp);
        fclose(fp);
        printf("Loaded %d transactions\n", transaction_count);
    }
}

void save_data() {
    FILE *fp;
    
    // Save vehicles
    fp = fopen("vehicles.dat", "wb");
    if(fp != NULL) {
        fwrite(&vehicle_count, sizeof(int), 1, fp);
        fwrite(vehicles, sizeof(Vehicle), vehicle_count, fp);
        fclose(fp);
    }
    
    // Save routes
    fp = fopen("routes.dat", "wb");
    if(fp != NULL) {
        fwrite(&route_count, sizeof(int), 1, fp);
        fwrite(routes, sizeof(Route), route_count, fp);
        fclose(fp);
    }
    
    // Save schedules
    fp = fopen("schedules.dat", "wb");
    if(fp != NULL) {
        fwrite(&schedule_count, sizeof(int), 1, fp);
        fwrite(schedules, sizeof(Schedule), schedule_count, fp);
        fclose(fp);
    }
    
    // Save bookings
    fp = fopen("bookings.dat", "wb");
    if(fp != NULL) {
        fwrite(&booking_count, sizeof(int), 1, fp);
        fwrite(bookings, sizeof(Booking), booking_count, fp);
        fclose(fp);
    }
    
    // Save admins
    fp = fopen("admins.dat", "wb");
    if(fp != NULL) {
        fwrite(&admin_count, sizeof(int), 1, fp);
        fwrite(admins, sizeof(Admin), admin_count, fp);
        fclose(fp);
    }
    
    // Save passengers
    fp = fopen("passengers.dat", "wb");
    if(fp != NULL) {
        fwrite(&passenger_count, sizeof(int), 1, fp);
        fwrite(passengers, sizeof(Passenger), passenger_count, fp);
        fclose(fp);
    }
    
    // Save transactions
    fp = fopen("transactions.dat", "wb");
    if(fp != NULL) {
        fwrite(&transaction_count, sizeof(int), 1, fp);
        fwrite(transactions, sizeof(Transaction), transaction_count, fp);
        fclose(fp);
    }
    
    printf("All data saved successfully!\n");
}

bool admin_login() {
    char username[30];
    char password[30];
    
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    
    for(int i = 0; i < admin_count; i++) {
        if(strcmp(admins[i].username, username) == 0 && strcmp(admins[i].password, password) == 0) {
            printf("Login successful!\n");
            return true;
        }
    }
    
    printf("Invalid username or password!\n");
    return false;
}

void admin_menu() {
    int choice;
    do {
        printf("\n=== Admin Menu ===\n");
        printf("1. Add Vehicle\n");
        printf("2. Add Route\n");
        printf("3. Create Schedule\n");
        printf("4. View Vehicles\n");
        printf("5. View Routes\n");
        printf("6. View Schedules\n");
        printf("7. View Bookings\n");
        printf("8. Generate Report\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                add_vehicle();
                break;
            case 2:
                add_route();
                break;
            case 3:
                create_schedule();
                break;
            case 4:
                view_vehicles();
                break;
            case 5:
                view_routes();
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
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 9);
}

void passenger_menu() {
    int choice;
    do {
        printf("\n=== Passenger Menu ===\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Booking\n");
        printf("3. View Bookings\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                book_ticket();
                break;
            case 2:
                cancel_booking();
                break;
            case 3:
                view_bookings();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 4);
}

void add_vehicle() {
    if(vehicle_count >= MAX_VEHICLES) {
        printf("Maximum number of vehicles reached!\n");
        return;
    }
    
    Vehicle new_vehicle;
    printf("\n=== Add New Vehicle ===\n");
    
    // Auto-generate vehicle ID
    new_vehicle.vehicle_id = vehicle_count + 1;
    
    printf("Enter registration number: ");
    scanf("%s", new_vehicle.reg_number);
    
    printf("Enter model: ");
    scanf("%s", new_vehicle.model);
    
    printf("Enter type (Bus/MiniBus/Van): ");
    scanf("%s", new_vehicle.type);
    
    printf("Enter capacity: ");
    scanf("%d", &new_vehicle.capacity);
    
    printf("Enter driver name: ");
    scanf("%s", new_vehicle.driver_name);
    
    printf("Enter contact number: ");
    scanf("%s", new_vehicle.contact_number);
    
    new_vehicle.is_active = true;
    
    vehicles[vehicle_count++] = new_vehicle;
    printf("Vehicle added successfully! ID: %d\n", new_vehicle.vehicle_id);
    save_data();
}

void add_route() {
    if(route_count >= MAX_ROUTES) {
        printf("Maximum number of routes reached!\n");
        return;
    }
    
    Route new_route;
    printf("\n=== Add New Route ===\n");
    
    // Auto-generate route ID
    new_route.route_id = route_count + 1;
    
    printf("Enter source city: ");
    scanf("%s", new_route.source);
    
    printf("Enter destination city: ");
    scanf("%s", new_route.destination);
    
    printf("Enter distance (km): ");
    scanf("%f", &new_route.distance);
    
    printf("Enter fare per km: ");
    scanf("%f", &new_route.fare_per_km);
    
    printf("Enter estimated duration (minutes): ");
    scanf("%d", &new_route.estimated_duration);
    
    new_route.is_active = true;
    
    routes[route_count++] = new_route;
    printf("Route added successfully! ID: %d\n", new_route.route_id);
    save_data();
}

void create_schedule() {
    if(schedule_count >= MAX_SCHEDULES) {
        printf("Maximum number of schedules reached!\n");
        return;
    }
    
    Schedule new_schedule;
    printf("\n=== Create New Schedule ===\n");
    
    // Auto-generate schedule ID
    new_schedule.schedule_id = schedule_count + 1;
    
    // Show available routes
    printf("Available Routes:\n");
    for(int i = 0; i < route_count; i++) {
        if(routes[i].is_active) {
            printf("%d. %s to %s\n", routes[i].route_id, routes[i].source, routes[i].destination);
        }
    }
    
    printf("Enter route ID: ");
    scanf("%d", &new_schedule.route_id);
    
    // Validate route ID
    bool valid_route = false;
    for(int i = 0; i < route_count; i++) {
        if(routes[i].route_id == new_schedule.route_id && routes[i].is_active) {
            valid_route = true;
            break;
        }
    }
    
    if(!valid_route) {
        printf("Invalid route ID!\n");
        return;
    }
    
    // Show available vehicles
    printf("Available Vehicles:\n");
    for(int i = 0; i < vehicle_count; i++) {
        if(vehicles[i].is_active) {
            printf("%d. %s (%s) - Capacity: %d\n", 
                   vehicles[i].vehicle_id, vehicles[i].reg_number, 
                   vehicles[i].model, vehicles[i].capacity);
        }
    }
    
    printf("Enter vehicle ID: ");
    scanf("%d", &new_schedule.vehicle_id);
    
    // Validate vehicle ID
    bool valid_vehicle = false;
    int vehicle_capacity = 0;
    for(int i = 0; i < vehicle_count; i++) {
        if(vehicles[i].vehicle_id == new_schedule.vehicle_id && vehicles[i].is_active) {
            valid_vehicle = true;
            vehicle_capacity = vehicles[i].capacity;
            break;
        }
    }
    
    if(!valid_vehicle) {
        printf("Invalid vehicle ID!\n");
        return;
    }
    
    printf("Enter departure time (HH:MM): ");
    scanf("%s", new_schedule.departure_time);
    
    printf("Enter arrival time (HH:MM): ");
    scanf("%s", new_schedule.arrival_time);
    
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", new_schedule.date);
    
    // Initialize all seats as available
    new_schedule.available_seats = vehicle_capacity;
    for(int i = 0; i < MAX_SEATS; i++) {
        new_schedule.seats_occupied[i] = 0;
    }
    
    new_schedule.is_cancelled = false;
    
    schedules[schedule_count++] = new_schedule;
    printf("Schedule created successfully! ID: %d\n", new_schedule.schedule_id);
    save_data();
}

void view_vehicles() {
    printf("=== Vehicles ===\n");
    for(int i = 0; i < vehicle_count; i++) {
        printf("ID: %d, Registration: %s, Model: %s, Type: %s, Capacity: %d, Active: %s, Driver: %s, Contact: %s\n",
               vehicles[i].vehicle_id, vehicles[i].reg_number, vehicles[i].model, vehicles[i].type,
               vehicles[i].capacity, vehicles[i].is_active ? "Yes" : "No", vehicles[i].driver_name, vehicles[i].contact_number);
    }
}

void view_routes() {
    printf("=== Routes ===\n");
    for(int i = 0; i < route_count; i++) {
        printf("ID: %d, Source: %s, Destination: %s, Distance: %.2f km, Fare per km: %.2f, Duration: %d minutes, Active: %s\n",
               routes[i].route_id, routes[i].source, routes[i].destination, routes[i].distance, routes[i].fare_per_km,
               routes[i].estimated_duration, routes[i].is_active ? "Yes" : "No");
    }
}

void view_schedules() {
    printf("=== Schedules ===\n");
    for(int i = 0; i < schedule_count; i++) {
        printf("ID: %d, Route ID: %d, Vehicle ID: %d, Departure: %s, Arrival: %s, Available Seats: %d, Seats Occupied: ",
               schedules[i].schedule_id, schedules[i].route_id, schedules[i].vehicle_id, schedules[i].departure_time,
               schedules[i].arrival_time, schedules[i].available_seats);
        for(int j = 0; j < MAX_SEATS; j++) {
            printf("%d ", schedules[i].seats_occupied[j]);
        }
        printf(", Cancelled: %s, Date: %s\n", schedules[i].is_cancelled ? "Yes" : "No", schedules[i].date);
    }
}

void book_ticket() {
    if(booking_count >= MAX_BOOKINGS) {
        printf("Maximum bookings reached!\n");
        return;
    }
    
    printf("\n=== Book Ticket ===\n");
    
    // Show available schedules
    printf("Available Schedules:\n");
    printf("ID\tRoute\t\tDeparture\tArrival\t\tAvailable Seats\tDate\n");
    for(int i = 0; i < schedule_count; i++) {
        if(!schedules[i].is_cancelled && schedules[i].available_seats > 0) {
            // Find route details
            for(int j = 0; j < route_count; j++) {
                if(routes[j].route_id == schedules[i].route_id) {
                    printf("%d\t%s to %s\t%s\t\t%s\t\t%d\t\t%s\n",
                           schedules[i].schedule_id,
                           routes[j].source, routes[j].destination,
                           schedules[i].departure_time, schedules[i].arrival_time,
                           schedules[i].available_seats, schedules[i].date);
                    break;
                }
            }
        }
    }
    
    int schedule_id;
    printf("Enter schedule ID: ");
    scanf("%d", &schedule_id);
    
    // Find the schedule
    int schedule_index = -1;
    for(int i = 0; i < schedule_count; i++) {
        if(schedules[i].schedule_id == schedule_id && !schedules[i].is_cancelled) {
            schedule_index = i;
            break;
        }
    }
    
    if(schedule_index == -1) {
        printf("Invalid schedule ID or schedule is cancelled!\n");
        return;
    }
    
    if(schedules[schedule_index].available_seats <= 0) {
        printf("No seats available for this schedule!\n");
        return;
    }
    
    Booking new_booking;
    new_booking.booking_id = booking_count + 1;
    new_booking.schedule_id = schedule_id;
    
    printf("Enter passenger name: ");
    scanf("%s", new_booking.passenger_name);
    
    printf("Enter passenger phone: ");
    scanf("%s", new_booking.passenger_phone);
    
    printf("Enter passenger email: ");
    scanf("%s", new_booking.passenger_email);
    
    printf("Enter number of seats to book: ");
    scanf("%d", &new_booking.seats_booked);
    
    if(new_booking.seats_booked > schedules[schedule_index].available_seats) {
        printf("Not enough seats available! Only %d seats left.\n", schedules[schedule_index].available_seats);
        return;
    }
    
    // Show seat map
    display_seat_map(schedule_id);
    
    // Select specific seats
    printf("Select %d seat numbers (1-%d):\n", new_booking.seats_booked, MAX_SEATS);
    for(int i = 0; i < new_booking.seats_booked; i++) {
        int seat_num;
        printf("Enter seat %d: ", i + 1);
        scanf("%d", &seat_num);
        
        if(seat_num < 1 || seat_num > MAX_SEATS) {
            printf("Invalid seat number!\n");
            return;
        }
        
        if(!is_seat_available(schedule_id, seat_num)) {
            printf("Seat %d is already occupied!\n", seat_num);
            return;
        }
        
        new_booking.seat_numbers[i] = seat_num;
    }
    
    // Calculate fare
    int route_id = schedules[schedule_index].route_id;
    new_booking.total_fare = calculate_fare(route_id, new_booking.seats_booked);
    
    new_booking.booking_time = time(NULL);
    new_booking.is_cancelled = false;
    
    // Update schedule
    schedules[schedule_index].available_seats -= new_booking.seats_booked;
    for(int i = 0; i < new_booking.seats_booked; i++) {
        schedules[schedule_index].seats_occupied[new_booking.seat_numbers[i] - 1] = new_booking.booking_id;
    }
    
    // Add booking
    bookings[booking_count++] = new_booking;
    
    // Log transaction
    log_transaction(new_booking.booking_id, "booking", new_booking.total_fare, "Ticket booking");
    
    printf("\n=== Booking Confirmed ===\n");
    printf("Booking ID: %d\n", new_booking.booking_id);
    printf("Passenger: %s\n", new_booking.passenger_name);
    printf("Seats: %d\n", new_booking.seats_booked);
    printf("Total Fare: %.2f\n", new_booking.total_fare);
    printf("Booking Time: %s", ctime(&new_booking.booking_time));
    
    save_data();
}

void cancel_booking() {
    printf("\n=== Cancel Booking ===\n");
    
    int booking_id;
    printf("Enter booking ID: ");
    scanf("%d", &booking_id);
    
    // Find the booking
    int booking_index = -1;
    for(int i = 0; i < booking_count; i++) {
        if(bookings[i].booking_id == booking_id && !bookings[i].is_cancelled) {
            booking_index = i;
            break;
        }
    }
    
    if(booking_index == -1) {
        printf("Booking not found or already cancelled!\n");
        return;
    }
    
    printf("Booking Details:\n");
    printf("ID: %d\n", bookings[booking_index].booking_id);
    printf("Passenger: %s\n", bookings[booking_index].passenger_name);
    printf("Seats: %d\n", bookings[booking_index].seats_booked);
    printf("Total Fare: %.2f\n", bookings[booking_index].total_fare);
    
    char confirm;
    printf("Are you sure you want to cancel this booking? (y/n): ");
    scanf(" %c", &confirm);
    
    if(confirm == 'y' || confirm == 'Y') {
        // Update schedule
        int schedule_id = bookings[booking_index].schedule_id;
        int schedule_index = -1;
        
        for(int i = 0; i < schedule_count; i++) {
            if(schedules[i].schedule_id == schedule_id) {
                schedule_index = i;
                break;
            }
        }
        
        if(schedule_index != -1) {
            // Free up seats
            schedules[schedule_index].available_seats += bookings[booking_index].seats_booked;
            for(int i = 0; i < bookings[booking_index].seats_booked; i++) {
                int seat_num = bookings[booking_index].seat_numbers[i];
                schedules[schedule_index].seats_occupied[seat_num - 1] = 0;
            }
        }
        
        // Cancel booking
        bookings[booking_index].is_cancelled = true;
        printf("Enter cancellation reason: ");
        scanf("%s", bookings[booking_index].cancellation_reason);
        
        // Log transaction
        log_transaction(booking_id, "cancellation", -bookings[booking_index].total_fare, "Booking cancellation");
        
        printf("Booking cancelled successfully!\n");
        save_data();
    } else {
        printf("Cancellation cancelled.\n");
    }
}

void view_bookings() {
    printf("\n=== All Bookings ===\n");
    printf("ID\tPassenger\tSeats\tFare\tStatus\tBooking Time\n");
    
    for(int i = 0; i < booking_count; i++) {
        printf("%d\t%s\t\t%d\t%.2f\t%s\t%s",
               bookings[i].booking_id,
               bookings[i].passenger_name,
               bookings[i].seats_booked,
               bookings[i].total_fare,
               bookings[i].is_cancelled ? "Cancelled" : "Active",
               ctime(&bookings[i].booking_time));
    }
}

void generate_report() {
    printf("\n=== System Report ===\n");
    
    // Vehicle statistics
    printf("Vehicles: %d total\n", vehicle_count);
    int active_vehicles = 0;
    for(int i = 0; i < vehicle_count; i++) {
        if(vehicles[i].is_active) active_vehicles++;
    }
    printf("Active vehicles: %d\n", active_vehicles);
    
    // Route statistics
    printf("Routes: %d total\n", route_count);
    int active_routes = 0;
    for(int i = 0; i < route_count; i++) {
        if(routes[i].is_active) active_routes++;
    }
    printf("Active routes: %d\n", active_routes);
    
    // Schedule statistics
    printf("Schedules: %d total\n", schedule_count);
    int active_schedules = 0;
    for(int i = 0; i < schedule_count; i++) {
        if(!schedules[i].is_cancelled) active_schedules++;
    }
    printf("Active schedules: %d\n", active_schedules);
    
    // Booking statistics
    printf("Bookings: %d total\n", booking_count);
    int active_bookings = 0;
    float total_revenue = 0;
    for(int i = 0; i < booking_count; i++) {
        if(!bookings[i].is_cancelled) {
            active_bookings++;
            total_revenue += bookings[i].total_fare;
        }
    }
    printf("Active bookings: %d\n", active_bookings);
    printf("Total revenue: %.2f\n", total_revenue);
    
    // Transaction statistics
    printf("Transactions: %d total\n", transaction_count);
    
    printf("\n=== Recent Transactions ===\n");
    printf("ID\tBooking\tType\t\tAmount\tDescription\n");
    for(int i = transaction_count - 1; i >= 0 && i >= transaction_count - 10; i--) {
        printf("%d\t%d\t%s\t%.2f\t%s\n",
               transactions[i].transaction_id,
               transactions[i].booking_id,
               transactions[i].transaction_type,
               transactions[i].amount,
               transactions[i].description);
    }
}

float calculate_fare(int route_id, int seats) {
    // Find the route
    for(int i = 0; i < route_count; i++) {
        if(routes[i].route_id == route_id) {
            return routes[i].distance * routes[i].fare_per_km * seats;
        }
    }
    return 0.0; // Route not found
}

void display_seat_map(int schedule_id) {
    // Find the schedule
    int schedule_index = -1;
    for(int i = 0; i < schedule_count; i++) {
        if(schedules[i].schedule_id == schedule_id) {
            schedule_index = i;
            break;
        }
    }
    
    if(schedule_index == -1) {
        printf("Schedule not found!\n");
        return;
    }
    
    // Find vehicle capacity
    int vehicle_id = schedules[schedule_index].vehicle_id;
    int capacity = 0;
    for(int i = 0; i < vehicle_count; i++) {
        if(vehicles[i].vehicle_id == vehicle_id) {
            capacity = vehicles[i].capacity;
            break;
        }
    }
    
    printf("\n=== Seat Map ===\n");
    printf("X = Occupied, O = Available\n\n");
    
    for(int i = 0; i < capacity; i++) {
        if(i % 4 == 0) printf("\n"); // New row every 4 seats
        
        if(schedules[schedule_index].seats_occupied[i] != 0) {
            printf("X\t");
        } else {
            printf("O\t");
        }
    }
    printf("\n\n");
}

bool is_seat_available(int schedule_id, int seat_number) {
    // Find the schedule
    int schedule_index = -1;
    for(int i = 0; i < schedule_count; i++) {
        if(schedules[i].schedule_id == schedule_id) {
            schedule_index = i;
            break;
        }
    }
    
    if(schedule_index == -1) return false;
    
    // Check if seat is available (0 means available)
    if(seat_number < 1 || seat_number > MAX_SEATS) return false;
    
    return schedules[schedule_index].seats_occupied[seat_number - 1] == 0;
}

void log_transaction(int booking_id, const char* type, float amount, const char* description) {
    if(transaction_count >= MAX_BOOKINGS * 2) {
        printf("Transaction log full!\n");
        return;
    }
    
    Transaction new_transaction;
    new_transaction.transaction_id = transaction_count + 1;
    new_transaction.booking_id = booking_id;
    strcpy(new_transaction.transaction_type, type);
    new_transaction.transaction_time = time(NULL);
    new_transaction.amount = amount;
    strcpy(new_transaction.description, description);
    
    transactions[transaction_count++] = new_transaction;
} 
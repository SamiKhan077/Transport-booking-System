#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ROUTES 20
#define MAX_VEHICLES 20
#define MAX_BOOKINGS 200
#define MAX_SEATS 50
#define MAX_STOPS 10
#define MAX_ADMINS 5

// Structure definitions
typedef struct {
    char name[50];
    float distance_from_source; // km from route start
} Stop;

typedef struct {
    int route_id;
    char source[50];
    char destination[50];
    float total_distance;
    float fare_per_km;
    Stop stops[MAX_STOPS];
    int stop_count;
    bool is_return_route; // true for return trips
    int base_route_id; // original route ID for return trips
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
    int seats_occupied[MAX_SEATS]; // Track which seats are taken
} Schedule;

typedef struct {
    int booking_id;
    int schedule_id;
    char passenger_name[50];
    int seats_booked;
    time_t booking_time;
    float total_fare;
    int is_cancelled;
    char boarding_stop[50];
    char destination_stop[50];
} Booking;

typedef struct {
    char username[30];
    char password[30];
} Admin;

// Global arrays
Route routes[MAX_ROUTES];
Vehicle vehicles[MAX_VEHICLES];
Schedule schedules[MAX_ROUTES * 2]; // Accounting for return trips
Booking bookings[MAX_BOOKINGS];
Admin admins[MAX_ADMINS] = {
    {"admin1", "password1"},
    {"admin2", "password2"},
    {"supervisor", "transport123"},
    {"manager", "securepass"},
    {"operator", "bus456"}
};

int route_count = 0;
int vehicle_count = 0;
int schedule_count = 0;
int booking_count = 0;
int admin_count = MAX_ADMINS;

// Function prototypes
void initialize_system();
void load_data();
void save_data();
bool admin_login();
void admin_menu();
void passenger_menu();
void add_route_with_stops();
void add_return_route(int base_route_id);
void add_vehicle();
void create_schedule();
void view_routes_with_stops();
void view_vehicles();
void view_schedules();
void book_ticket_with_stops();
void cancel_booking();
void view_bookings();
void generate_report();
float calculate_fare_with_stops(int route_id, char* boarding, char* destination, int seats);
int find_available_schedule(int route_id);
void display_seat_map(int schedule_id);
bool authenticate_admin(char* username, char* password);

int main() {
    initialize_system();
    load_data();
    
    int choice;
    do {
        printf("\nTransport Booking System\n");
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
                printf("Exiting system. Data saved.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 3);
    
    return 0;
}

void initialize_system() {
    // Initialize with sample data if files don't exist
    if(route_count == 0) {
        // Sample route 1
        routes[0].route_id = 1;
        strcpy(routes[0].source, "CityA");
        strcpy(routes[0].destination, "CityB");
        routes[0].total_distance = 100.0;
        routes[0].fare_per_km = 1.5;
        routes[0].stop_count = 3;
        routes[0].is_return_route = false;
        
        // Stops for route 1
        strcpy(routes[0].stops[0].name, "TownX");
        routes[0].stops[0].distance_from_source = 30.0;
        
        strcpy(routes[0].stops[1].name, "TownY");
        routes[0].stops[1].distance_from_source = 60.0;
        
        strcpy(routes[0].stops[2].name, "TownZ");
        routes[0].stops[2].distance_from_source = 80.0;
        
        route_count = 1;
        
        // Create return route automatically
        add_return_route(1);
    }
    
    if(vehicle_count == 0) {
        // Sample vehicle
        vehicles[0].vehicle_id = 1;
        strcpy(vehicles[0].reg_number, "AB1234");
        strcpy(vehicles[0].model, "Volvo X5");
        vehicles[0].capacity = 40;
        strcpy(vehicles[0].type, "Bus");
        vehicle_count = 1;
    }
}

bool admin_login() {
    char username[30], password[30];
    printf("\nAdmin Login\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    
    if(authenticate_admin(username, password)) {
        printf("Login successful!\n");
        return true;
    } else {
        printf("Invalid credentials. Access denied.\n");
        return false;
    }
}

bool authenticate_admin(char* username, char* password) {
    for(int i = 0; i < admin_count; i++) {
        if(strcmp(admins[i].username, username) == 0 && 
           strcmp(admins[i].password, password) == 0) {
            return true;
        }
    }
    return false;
}

void add_route_with_stops() {
    if(route_count >= MAX_ROUTES) {
        printf("Maximum routes reached!\n");
        return;
    }
    
    Route new_route;
    printf("\nAdd New Route\n");
    new_route.route_id = route_count + 1;
    
    printf("Enter source city: ");
    scanf("%s", new_route.source);
    printf("Enter destination city: ");
    scanf("%s", new_route.destination);
    printf("Enter total distance (km): ");
    scanf("%f", &new_route.total_distance);
    printf("Enter fare per km: ");
    scanf("%f", &new_route.fare_per_km);
    
    printf("Enter number of intermediate stops (max %d): ", MAX_STOPS);
    scanf("%d", &new_route.stop_count);
    
    for(int i = 0; i < new_route.stop_count; i++) {
        printf("\nStop %d:\n", i+1);
        printf("Enter stop name: ");
        scanf("%s", new_route.stops[i].name);
        printf("Enter distance from %s (km): ", new_route.source);
        scanf("%f", &new_route.stops[i].distance_from_source);
    }
    
    new_route.is_return_route = false;
    routes[route_count++] = new_route;
    printf("Route added successfully! ID: %d\n", new_route.route_id);
    
    // Automatically create return route
    add_return_route(new_route.route_id);
    save_data();
}

void add_return_route(int base_route_id) {
    if(route_count >= MAX_ROUTES) {
        printf("Cannot add return route - maximum routes reached!\n");
        return;
    }
    
    Route base_route = routes[base_route_id - 1];
    Route return_route;
    
    return_route.route_id = route_count + 1;
    strcpy(return_route.source, base_route.destination);
    strcpy(return_route.destination, base_route.source);
    return_route.total_distance = base_route.total_distance;
    return_route.fare_per_km = base_route.fare_per_km;
    return_route.stop_count = base_route.stop_count;
    return_route.is_return_route = true;
    return_route.base_route_id = base_route_id;
    
    // Reverse the stops
    for(int i = 0; i < base_route.stop_count; i++) {
        strcpy(return_route.stops[i].name, base_route.stops[base_route.stop_count - 1 - i].name);
        return_route.stops[i].distance_from_source = 
            base_route.total_distance - base_route.stops[base_route.stop_count - 1 - i].distance_from_source;
    }
    
    routes[route_count++] = return_route;
    printf("Return route added successfully! ID: %d\n", return_route.route_id);
}

void book_ticket_with_stops() {
    if(booking_count >= MAX_BOOKINGS) {
        printf("Maximum bookings reached!\n");
        return;
    }
    
    Booking new_booking;
    printf("\nBook Ticket\n");
    
    view_routes_with_stops();
    printf("Select route ID: ");
    scanf("%d", &new_booking.schedule_id); // Using schedule_id temporarily
    
    // Find the route
    int route_index = -1;
    for(int i = 0; i < route_count; i++) {
        if(routes[i].route_id == new_booking.schedule_id) {
            route_index = i;
            break;
        }
    }
    
    if(route_index == -1) {
        printf("Invalid route ID!\n");
        return;
    }
    
    // Show available schedules for this route
    printf("\nAvailable Schedules for Route %d:\n", routes[route_index].route_id);
    printf("ID\tDeparture\tArrival\tAvailable Seats\n");
    for(int i = 0; i < schedule_count; i++) {
        if(schedules[i].route_id == routes[route_index].route_id && schedules[i].available_seats > 0) {
            printf("%d\t%s\t%s\t%d\n", 
                   schedules[i].schedule_id,
                   schedules[i].departure_time,
                   schedules[i].arrival_time,
                   schedules[i].available_seats);
        }
    }
    
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
    
    // Show boarding points
    printf("\nBoarding Points:\n");
    printf("0. %s (Start)\n", routes[route_index].source);
    for(int i = 0; i < routes[route_index].stop_count; i++) {
        printf("%d. %s (%.1f km)\n", i+1, routes[route_index].stops[i].name, 
               routes[route_index].stops[i].distance_from_source);
    }
    
    int boarding_choice;
    printf("Select boarding point (0-%d): ", routes[route_index].stop_count);
    scanf("%d", &boarding_choice);
    
    if(boarding_choice < 0 || boarding_choice > routes[route_index].stop_count) {
        printf("Invalid choice!\n");
        return;
    }
    
    if(boarding_choice == 0) {
        strcpy(new_booking.boarding_stop, routes[route_index].source);
    } else {
        strcpy(new_booking.boarding_stop, routes[route_index].stops[boarding_choice-1].name);
    }
    
    // Show destination points (must be after boarding point)
    printf("\nDestination Points:\n");
    if(boarding_choice == 0) {
        // Can go to any stop or final destination
        for(int i = 0; i < routes[route_index].stop_count; i++) {
            printf("%d. %s (%.1f km)\n", i+1, routes[route_index].stops[i].name, 
                   routes[route_index].stops[i].distance_from_source);
        }
        printf("%d. %s (End)\n", routes[route_index].stop_count+1, routes[route_index].destination);
    } else {
        // Can only go to stops after boarding or final destination
        for(int i = boarding_choice; i < routes[route_index].stop_count; i++) {
            printf("%d. %s (%.1f km)\n", i+1, routes[route_index].stops[i].name, 
                   routes[route_index].stops[i].distance_from_source);
        }
        printf("%d. %s (End)\n", routes[route_index].stop_count+1, routes[route_index].destination);
    }
    
    int dest_choice;
    printf("Select destination point: ");
    scanf("%d", &dest_choice);
    
    // Validate destination choice
    if(boarding_choice == 0) {
        if(dest_choice < 1 || dest_choice > routes[route_index].stop_count+1) {
            printf("Invalid choice!\n");
            return;
        }
    } else {
        if(dest_choice <= boarding_choice || dest_choice > routes[route_index].stop_count+1) {
            printf("Destination must be after boarding point!\n");
            return;
        }
    }
    
    if(dest_choice == routes[route_index].stop_count+1) {
        strcpy(new_booking.destination_stop, routes[route_index].destination);
    } else {
        strcpy(new_booking.destination_stop, routes[route_index].stops[dest_choice-1].name);
    }
    
    printf("Enter passenger name: ");
    scanf("%s", new_booking.passenger_name);
    printf("Enter number of seats: ");
    scanf("%d", &new_booking.seats_booked);
    
    if(new_booking.seats_booked > schedules[schedule_index].available_seats) {
        printf("Not enough seats available!\n");
        return;
    }
    
    // Show seat map
    display_seat_map(schedules[schedule_index].schedule_id);
    
    // Calculate fare
    new_booking.total_fare = calculate_fare_with_stops(
        routes[route_index].route_id, 
        new_booking.boarding_stop, 
        new_booking.destination_stop, 
        new_booking.seats_booked
    );
    
    new_booking.booking_id = booking_count + 1;
    new_booking.booking_time = time(NULL);
    new_booking.is_cancelled = 0;
    
    // Update available seats
    schedules[schedule_index].available_seats -= new_booking.seats_booked;
    
    // Mark seats as occupied (simplified - in real system would track individual seats)
    for(int i = 0; i < new_booking.seats_booked; i++) {
        for(int j = 0; j < MAX_SEATS; j++) {
            if(schedules[schedule_index].seats_occupied[j] == 0) {
                schedules[schedule_index].seats_occupied[j] = new_booking.booking_id;
                break;
            }
        }
    }
    
    bookings[booking_count++] = new_booking;
    printf("\nBooking successful!\n");
    printf("Booking ID: %d\n", new_booking.booking_id);
    printf("Route: %s to %s\n", routes[route_index].source, routes[route_index].destination);
    printf("Boarding: %s\n", new_booking.boarding_stop);
    printf("Destination: %s\n", new_booking.destination_stop);
    printf("Seats: %d\n", new_booking.seats_booked);
    printf("Total fare: %.2f\n", new_booking.total_fare);
    save_data();
}

float calculate_fare_with_stops(int route_id, char* boarding, char* destination, int seats) {
    Route route;
    int route_index = -1;
    
    // Find the route
    for(int i = 0; i < route_count; i++) {
        if(routes[i].route_id == route_id) {
            route = routes[i];
            route_index = i;
            break;
        }
    }
    
    if(route_index == -1) return 0;
    
    float boarding_distance = 0;
    float destination_distance = route.total_distance;
    
    // Find boarding distance
    if(strcmp(boarding, route.source) == 0) {
        boarding_distance = 0;
    } else {
        for(int i = 0; i < route.stop_count; i++) {
            if(strcmp(boarding, route.stops[i].name) == 0) {
                boarding_distance = route.stops[i].distance_from_source;
                break;
            }
        }
    }
    
    // Find destination distance
    if(strcmp(destination, route.destination) == 0) {
        destination_distance = route.total_distance;
    } else {
        for(int i = 0; i < route.stop_count; i++) {
            if(strcmp(destination, route.stops[i].name) == 0) {
                destination_distance = route.stops[i].distance_from_source;
                break;
            }
        }
    }
    
    float travel_distance = destination_distance - boarding_distance;
    if(travel_distance < 0) travel_distance = -travel_distance; // For return routes
    
    return travel_distance * route.fare_per_km * seats;
}

void display_seat_map(int schedule_id) {
    int schedule_index = -1;
    for(int i = 0; i < schedule_count; i++) {
        if(schedules[i].schedule_id == schedule_id) {
            schedule_index = i;
            break;
        }
    }
    
    if(schedule_index == -1) return;
    
    printf("\nSeat Map (X = Occupied, O = Available)\n");
    int capacity = vehicles[schedules[schedule_index].vehicle_id - 1].capacity;
    
    for(int i = 0; i < capacity; i++) {
        if(i % 4 == 0) printf("\n"); // New row every 4 seats
        
        if(schedules[schedule_index].seats_occupied[i] != 0) {
            printf("X\t");
        } else {
            printf("O\t");
        }
    }
    printf("\n");
    
}

// [Other functions remain similar but would need updates to handle stops and return routes]
// [Load/Save functions would need to handle the new data structures]
// [View functions would need to display stop information]
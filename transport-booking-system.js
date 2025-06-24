const fs = require('fs');
const readline = require('readline-sync');

// Utility functions for file read/write
function readData(file) {
    if (!fs.existsSync(file)) return [];
    return JSON.parse(fs.readFileSync(file, 'utf8'));
}
function writeData(file, data) {
    fs.writeFileSync(file, JSON.stringify(data, null, 2));
}

// Data file paths
const VEHICLES_FILE = './data/vehicles.json';
const ROUTES_FILE = './data/routes.json';
const SCHEDULES_FILE = './data/schedules.json';
const BOOKINGS_FILE = './data/bookings.json';

// Admin functions
function adminMenu() {
    while (true) {
        console.log('\n--- Admin Menu ---');
        console.log('1. Add Vehicle');
        console.log('2. Add Route');
        console.log('3. Add Schedule');
        console.log('4. View Reports');
        console.log('5. Logout');
        const choice = readline.question('Select option: ');
        if (choice === '1') addVehicle();
        else if (choice === '2') addRoute();
        else if (choice === '3') addSchedule();
        else if (choice === '4') viewReports();
        else if (choice === '5') break;
        else console.log('Invalid option.');
    }
}

// Passenger functions
function passengerMenu() {
    while (true) {
        console.log('\n--- Passenger Menu ---');
        console.log('1. Browse Routes');
        console.log('2. Book Ticket');
        console.log('3. Cancel Booking');
        console.log('4. Exit');
        const choice = readline.question('Select option: ');
        if (choice === '1') browseRoutes();
        else if (choice === '2') bookTicket();
        else if (choice === '3') cancelBooking();
        else if (choice === '4') break;
        else console.log('Invalid option.');
    }
}

// Placeholder functions for features to be implemented
function addVehicle() {
    console.log('\n--- Add Vehicle ---');
    const type = readline.question('Enter vehicle type (e.g., Bus, Van): ');
    const capacity = parseInt(readline.question('Enter vehicle capacity: '), 10);
    const registrationNumber = readline.question('Enter registration number: ');
    if (!type || isNaN(capacity) || !registrationNumber) {
        console.log('Invalid input.');
        return;
    }
    const vehicles = readData(VEHICLES_FILE);
    const id = vehicles.length > 0 ? vehicles[vehicles.length - 1].id + 1 : 1;
    vehicles.push({ id, type, capacity, registrationNumber });
    writeData(VEHICLES_FILE, vehicles);
    console.log('Vehicle added successfully!');
}
function addRoute() {
    console.log('\n--- Add Route ---');
    const from = readline.question('Enter origin: ');
    const to = readline.question('Enter destination: ');
    const distance = parseFloat(readline.question('Enter distance (km): '));
    if (!from || !to || isNaN(distance) || distance <= 0) {
        console.log('Invalid input.');
        return;
    }
    const routes = readData(ROUTES_FILE);
    const id = routes.length > 0 ? routes[routes.length - 1].id + 1 : 1;
    routes.push({ id, from, to, distance });
    writeData(ROUTES_FILE, routes);
    console.log('Route added successfully!');
}
function addSchedule() {
    console.log('\n--- Add Schedule ---');
    const routes = readData(ROUTES_FILE);
    const vehicles = readData(VEHICLES_FILE);
    if (routes.length === 0 || vehicles.length === 0) {
        console.log('Add at least one route and one vehicle first.');
        return;
    }
    // List routes
    console.log('Available Routes:');
    routes.forEach(r => console.log(`${r.id}: ${r.from} -> ${r.to} (${r.distance} km)`));
    const routeId = parseInt(readline.question('Enter route ID: '), 10);
    const route = routes.find(r => r.id === routeId);
    if (!route) {
        console.log('Invalid route ID.');
        return;
    }
    // List vehicles
    console.log('Available Vehicles:');
    vehicles.forEach(v => console.log(`${v.id}: ${v.type} (${v.registrationNumber}, Capacity: ${v.capacity})`));
    const vehicleId = parseInt(readline.question('Enter vehicle ID: '), 10);
    const vehicle = vehicles.find(v => v.id === vehicleId);
    if (!vehicle) {
        console.log('Invalid vehicle ID.');
        return;
    }
    const departureTime = readline.question('Enter departure time (e.g., 2024-06-01 09:00): ');
    if (!departureTime) {
        console.log('Invalid departure time.');
        return;
    }
    const schedules = readData(SCHEDULES_FILE);
    const id = schedules.length > 0 ? schedules[schedules.length - 1].id + 1 : 1;
    schedules.push({
        id,
        routeId,
        vehicleId,
        departureTime,
        availableSeats: vehicle.capacity,
        status: 'Scheduled'
    });
    writeData(SCHEDULES_FILE, schedules);
    console.log('Schedule added successfully!');
}
function viewReports() {
    console.log('\n--- Reports ---');
    const vehicles = readData(VEHICLES_FILE);
    const routes = readData(ROUTES_FILE);
    const schedules = readData(SCHEDULES_FILE);
    const bookings = readData(BOOKINGS_FILE);
    const totalRevenue = bookings.filter(b => b.status === 'Booked').reduce((sum, b) => sum + b.fare, 0);
    console.log(`Total Vehicles: ${vehicles.length}`);
    console.log(`Total Routes: ${routes.length}`);
    console.log(`Total Schedules: ${schedules.length}`);
    console.log(`Total Bookings: ${bookings.length}`);
    console.log(`Total Revenue: ${totalRevenue}`);
}
function browseRoutes() {
    console.log('\n--- Browse Routes ---');
    const routes = readData(ROUTES_FILE);
    const schedules = readData(SCHEDULES_FILE);
    if (routes.length === 0 || schedules.length === 0) {
        console.log('No routes or schedules available.');
        return;
    }
    routes.forEach(route => {
        console.log(`\nRoute ${route.id}: ${route.from} -> ${route.to} (${route.distance} km)`);
        const routeSchedules = schedules.filter(s => s.routeId === route.id && s.status === 'Scheduled');
        if (routeSchedules.length === 0) {
            console.log('  No scheduled trips.');
        } else {
            routeSchedules.forEach(sch => {
                console.log(`  Schedule ${sch.id}: Vehicle ${sch.vehicleId}, Departure: ${sch.departureTime}, Available Seats: ${sch.availableSeats}`);
            });
        }
    });
}
function bookTicket() {
    console.log('\n--- Book Ticket ---');
    const schedules = readData(SCHEDULES_FILE);
    const routes = readData(ROUTES_FILE);
    if (schedules.length === 0) {
        console.log('No schedules available.');
        return;
    }
    // List all available schedules
    schedules.filter(s => s.status === 'Scheduled' && s.availableSeats > 0).forEach(sch => {
        const route = routes.find(r => r.id === sch.routeId);
        if (route) {
            console.log(`Schedule ${sch.id}: ${route.from} -> ${route.to}, Departure: ${sch.departureTime}, Available Seats: ${sch.availableSeats}`);
        }
    });
    const scheduleId = parseInt(readline.question('Enter schedule ID to book: '), 10);
    const schedule = schedules.find(s => s.id === scheduleId && s.status === 'Scheduled');
    if (!schedule || schedule.availableSeats === 0) {
        console.log('Invalid or unavailable schedule.');
        return;
    }
    const passengerName = readline.question('Enter your name: ');
    const seatsRequested = parseInt(readline.question('Number of seats to book: '), 10);
    if (!passengerName || isNaN(seatsRequested) || seatsRequested <= 0 || seatsRequested > schedule.availableSeats) {
        console.log('Invalid input or not enough seats.');
        return;
    }
    // Fare calculation (e.g., 10 per km per seat)
    const route = routes.find(r => r.id === schedule.routeId);
    const farePerSeat = 10; // Example fare per km
    const fare = route.distance * farePerSeat * seatsRequested;
    // Update schedule
    schedule.availableSeats -= seatsRequested;
    writeData(SCHEDULES_FILE, schedules);
    // Save booking
    const bookings = readData(BOOKINGS_FILE);
    const id = bookings.length > 0 ? bookings[bookings.length - 1].id + 1 : 1;
    bookings.push({
        id,
        scheduleId,
        passengerName,
        seatsBooked: seatsRequested,
        fare,
        status: 'Booked'
    });
    writeData(BOOKINGS_FILE, bookings);
    console.log(`Booking successful! Total fare: ${fare}`);
}
function cancelBooking() {
    console.log('\n--- Cancel Booking ---');
    const bookings = readData(BOOKINGS_FILE);
    if (bookings.length === 0) {
        console.log('No bookings found.');
        return;
    }
    bookings.filter(b => b.status === 'Booked').forEach(b => {
        console.log(`Booking ${b.id}: Schedule ${b.scheduleId}, Name: ${b.passengerName}, Seats: ${b.seatsBooked}, Fare: ${b.fare}`);
    });
    const bookingId = parseInt(readline.question('Enter booking ID to cancel: '), 10);
    const booking = bookings.find(b => b.id === bookingId && b.status === 'Booked');
    if (!booking) {
        console.log('Invalid booking ID.');
        return;
    }
    // Update booking status
    booking.status = 'Cancelled';
    writeData(BOOKINGS_FILE, bookings);
    // Update schedule seat availability
    const schedules = readData(SCHEDULES_FILE);
    const schedule = schedules.find(s => s.id === booking.scheduleId);
    if (schedule) {
        schedule.availableSeats += booking.seatsBooked;
        writeData(SCHEDULES_FILE, schedules);
    }
    console.log('Booking cancelled and seats released.');
}

// Main menu
function mainMenu() {
    while (true) {
        console.log('\n--- Transport Booking System ---');
        console.log('1. Admin Login');
        console.log('2. Passenger');
        console.log('3. Exit');
        const choice = readline.question('Select option: ');
        if (choice === '1') adminMenu();
        else if (choice === '2') passengerMenu();
        else if (choice === '3') break;
        else console.log('Invalid option.');
    }
}

mainMenu();
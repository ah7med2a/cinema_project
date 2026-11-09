#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <exception>

using namespace std;

// --- Custom Exceptions ---
class CinemaException : public exception {
protected:
    string message;
public:
    CinemaException(string msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidCredentialsException : public CinemaException {
public:
    InvalidCredentialsException() : CinemaException("Error: Invalid ID or password!") {}
};

class AdminAlreadyExistsException : public CinemaException {
public:
    AdminAlreadyExistsException() : CinemaException("Error: Admin ID already exists!") {}
};

class NotFoundException : public CinemaException {
public:
    NotFoundException(string item) : CinemaException("Error: " + item + " not found!") {}
};

class SeatAlreadyReservedException : public CinemaException {
public:
    SeatAlreadyReservedException() : CinemaException("Error: Selected seat is already reserved!") {}
};


// --- Forward Declarations ---
class Admin;
class MovieHall;
class ShowTime;
class Seat;


// --- Movie Class ---
class Movie {
    int movieId;
    int duration;
    int ageRating;
    double price;
    string title;
    string releaseDate;
    string genre;
    string language;
    string description;

public:
    Movie(int movieId, int duration, string releaseDate, double price, int ageRating, string title, string genre, string language, string description = "No description available.") {
        this->movieId = movieId;
        this->duration = duration;
        this->releaseDate = releaseDate;
        this->price = price;
        this->ageRating = ageRating;
        this->title = title;
        this->genre = genre;
        this->language = language;
        this->description = description;
    }

    int getId() const { return movieId; }
    int getDuration() const { return duration; }
    double getPrice() const { return price; }
    int getAgeRating() const { return ageRating; }
    string getTitle() const { return title; }
    string getReleaseDate() const { return releaseDate; }
    string getGenre() const { return genre; }
    string getLanguage() const { return language; }
    string getDescription() const { return description; }

    void display() const {
        cout << "[ID: " << movieId << "] " << title << " (" << genre << ") - " 
             << duration << " mins | Age: +" << ageRating << " | Price: $" << price << " | Lang: " << language << "\n";
    }

protected:
    friend class Admin;
    void setId(int movieId) { this->movieId = movieId; }
    void setDuration(int duration) { this->duration = duration; }
    void setPrice(double price) { this->price = price; }
    void setAgeRating(int ageRating) { this->ageRating = ageRating; }
    void setTitle(string title) { this->title = title; }
    void setReleaseDate(string releaseDate) { this->releaseDate = releaseDate; }
    void setGenre(string genre) { this->genre = genre; }
    void setLanguage(string language) { this->language = language; }
    void setDescription(string description) { this->description = description; }
};


// --- MovieHall Class ---
class MovieHall {
    int hallId;
    int capacity;
    string name;

public:
    MovieHall(int hallId, int capacity, string name) {
        this->hallId = hallId;
        this->capacity = capacity;
        this->name = name;
    }

    int getHallId() const { return hallId; }
    int getCapacity() const { return capacity; }
    string getName() const { return name; }

    void display() const {
        cout << "[Hall ID: " << hallId << "] " << name << " (Capacity: " << capacity << " seats)\n";
    }

protected:
    friend class Admin;
    void setId(int hallId) { this->hallId = hallId; }
    void setCapacity(int capacity) { this->capacity = capacity; }
    void setName(string name) { this->name = name; }
};


// --- Seat Class ---
class Seat {
    int seatId;
    string seatNumber; // e.g., "A1", "B4"

public:
    Seat(int seatId, string seatNumber) {
        this->seatId = seatId;
        this->seatNumber = seatNumber;
    }

    int getSeatId() const { return seatId; }
    string getSeatNumber() const { return seatNumber; }

protected:
    friend class Admin;
    void setId(int seatId) { this->seatId = seatId; }
    void setSeatNumber(string seatNumber) { this->seatNumber = seatNumber; }
};


// --- ShowTime Class ---
class ShowTime {
    int showTimeId;
    string startTime;
    string endTime;
    Movie* movie;
    MovieHall* movieHall;
    // Track reserved seat IDs for this specific showtime (seatId -> isReserved)
    map<int, bool> reservedSeats;

public:
    ShowTime(int showTimeId, string startTime, string endTime, Movie* movie, MovieHall* movieHall) {
        this->showTimeId = showTimeId;
        this->startTime = startTime;
        this->endTime = endTime;
        this->movie = movie;
        this->movieHall = movieHall;
    }

    int getShowTimeId() const { return showTimeId; }
    string getStartTime() const { return startTime; }
    string getEndTime() const { return endTime; }
    Movie* getMovie() const { return movie; }
    MovieHall* getMovieHall() const { return movieHall; }

    bool isSeatReserved(int seatId) const {
        auto it = reservedSeats.find(seatId);
        if (it != reservedSeats.end()) {
            return it->second;
        }
        return false; // Default is available
    }

    void reserveSeat(int seatId) {
        if (isSeatReserved(seatId)) {
            throw SeatAlreadyReservedException();
        }
        reservedSeats[seatId] = true;
    }

    void display() const {
        cout << "[Showtime ID: " << showTimeId << "] Movie: " << movie->getTitle() 
             << " | Hall: " << movieHall->getName() 
             << " | Time: " << startTime << " - " << endTime << "\n";
    }

protected:
    friend class Admin;
    void setId(int showTimeId) { this->showTimeId = showTimeId; }
    void setStartTime(string startTime) { this->startTime = startTime; }
    void setEndTime(string endTime) { this->endTime = endTime; }
    void setMovie(Movie* movie) { this->movie = movie; }
    void setMovieHall(MovieHall* movieHall) { this->movieHall = movieHall; }
};


// --- Ticket Class ---
class Ticket {
    int ticketId;
    Seat* seat;
    MovieHall* movieHall;
    ShowTime* showTime;

public:
    Ticket(int ticketId, Seat* seat, MovieHall* movieHall, ShowTime* showTime) {
        this->ticketId = ticketId;
        this->seat = seat;
        this->movieHall = movieHall;
        this->showTime = showTime;
    }

    int getTicketId() const { return ticketId; }
    Seat* getSeat() const { return seat; }
    MovieHall* getMovieHall() const { return movieHall; }
    ShowTime* getShowTime() const { return showTime; }

    void display() const {
        cout << "--- TICKET DETAILS ---\n"
             << "Ticket ID: " << ticketId << "\n"
             << "Movie: " << showTime->getMovie()->getTitle() << "\n"
             << "Hall: " << movieHall->getName() << "\n"
             << "Seat: " << seat->getSeatNumber() << "\n"
             << "Time: " << showTime->getStartTime() << " to " << showTime->getEndTime() << "\n"
             << "Price: $" << showTime->getMovie()->getPrice() << "\n----------------------\n";
    }

protected:
    friend class Admin;
    void setId(int ticketId) { this->ticketId = ticketId; }
    void setSeat(Seat* seat) { this->seat = seat; }
    void setMovieHall(MovieHall* movieHall) { this->movieHall = movieHall; }
    void setShowTime(ShowTime* showTime) { this->showTime = showTime; }
};


// --- BookingDetails Class ---
class BookingDetails {
    int bookingId;
    Ticket* ticket;

public:
    BookingDetails(int bookingId, Ticket* ticket) {
        this->bookingId = bookingId;
        this->ticket = ticket;
    }

    int getBookingId() const { return bookingId; }
    Ticket* getTicket() const { return ticket; }

    void display() const {
        cout << "Booking ID: " << bookingId << "\n";
        ticket->display();
    }
};


// --- Admin Class ---
class Admin {
    int adminId;
    string password;

public:
    Admin(int adminId, string password) {
        this->adminId = adminId;
        this->password = password;
    }

    int getAdminId() const { return adminId; }
    bool authenticate(int id, string pwd) const {
        return (this->adminId == id && this->password == pwd);
    }

    // Additions
    void addMovie(vector<Movie*>& movies, int id, int duration, string date, double price, int age, string title, string genre, string lang, string desc) {
        movies.push_back(new Movie(id, duration, date, price, age, title, genre, lang, desc));
        cout << "Success: Movie added successfully!\n";
    }

    void addMovieHall(vector<MovieHall*>& halls, int id, int capacity, string name) {
        halls.push_back(new MovieHall(id, capacity, name));
        cout << "Success: Movie Hall added successfully!\n";
    }

    void addShowTime(vector<ShowTime*>& showtimes, int id, string start, string end, Movie* movie, MovieHall* hall) {
        showtimes.push_back(new ShowTime(id, start, end, movie, hall));
        cout << "Success: Showtime scheduled successfully!\n";
    }
};


// --- SEARCH FUNCTIONS ---
vector<Movie*> searchMoviesByTitle(const vector<Movie*>& movies, const string& query) {
    vector<Movie*> results;
    string lowerQuery = query;
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (Movie* m : movies) {
        string title = m->getTitle();
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        if (title.find(lowerQuery) != string::npos) {
            results.push_back(m);
        }
    }
    return results;
}

vector<Movie*> searchMoviesByGenre(const vector<Movie*>& movies, const string& genreQuery) {
    vector<Movie*> results;
    string lowerQuery = genreQuery;
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (Movie* m : movies) {
        string genre = m->getGenre();
        transform(genre.begin(), genre.end(), genre.begin(), ::tolower);
        if (genre.find(lowerQuery) != string::npos) {
            results.push_back(m);
        }
    }
    return results;
}

MovieHall* searchMovieHallById(const vector<MovieHall*>& halls, int hallId) {
    for (MovieHall* hall : halls) {
        if (hall->getHallId() == hallId) {
            return hall;
        }
    }
    throw NotFoundException("Movie Hall");
}

MovieHall* searchMovieHallByName(const vector<MovieHall*>& halls, const string& name) {
    for (MovieHall* hall : halls) {
        if (hall->getName() == name) {
            return hall;
        }
    }
    throw NotFoundException("Movie Hall");
}

Movie* searchMovieById(const vector<Movie*>& movies, int movieId) {
    for (Movie* movie : movies) {
        if (movie->getId() == movieId) {
            return movie;
        }
    }
    throw NotFoundException("Movie");
}

ShowTime* searchShowTimeById(const vector<ShowTime*>& showtimes, int showTimeId) {
    for (ShowTime* st : showtimes) {
        if (st->getShowTimeId() == showTimeId) {
            return st;
        }
    }
    throw NotFoundException("ShowTime");
}


// --- MAIN CONSOLE APP ---
int main() {
    // Seed sample data
    vector<Movie*> movies;
    vector<MovieHall*> halls;
    vector<ShowTime*> showtimes;
    vector<Seat*> seats;
    vector<BookingDetails*> bookings;
    vector<Admin*> admins;

    // Default Admin (ID: 1, Password: admin123)
    admins.push_back(new Admin(1, "admin123"));

    // Sample Movies & Halls
    movies.push_back(new Movie(101, 148, "2023-07-21", 12.50, 13, "Inception", "Sci-Fi", "English", "A thief who steals corporate secrets..."));
    movies.push_back(new Movie(102, 169, "2014-11-07", 14.00, 13, "Interstellar", "Sci-Fi", "English", "A team of explorers travel through a wormhole..."));
    
    halls.push_back(new MovieHall(1, 5, "IMAX Hall"));
    halls.push_back(new MovieHall(2, 4, "Standard Hall 1"));

    // Sample Seats for Hall 1 & 2 (Seats 1 to 5)
    for (int i = 1; i <= 5; ++i) {
        seats.push_back(new Seat(i, "Seat-" + to_string(i)));
    }

    // Sample Showtime
    showtimes.push_back(new ShowTime(1, "18:00", "20:30", movies[0], halls[0]));

    int ticketCounter = 1000;
    int bookingCounter = 5000;

    cout << "=========================================\n";
    cout << "   WELCOME TO CINEMA MANAGEMENT SYSTEM   \n";
    cout << "=========================================\n";

    bool running = true;
    while (running) {
        cout << "\nSelect Role:\n";
        cout << "1. Admin\n";
        cout << "2. Customer\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        
        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting.\n";
            break;
        }

        if (choice == 1) {
            // Admin Menu
            cout << "\n--- Admin Portal ---\n";
            cout << "1. Sign In\n";
            cout << "2. Sign Up (Register New Admin)\n";
            cout << "Enter choice: ";
            int adminChoice;
            cin >> adminChoice;

            try {
                if (adminChoice == 1) {
                    int id;
                    string pwd;
                    cout << "Enter Admin ID: ";
                    cin >> id;
                    cout << "Enter Password: ";
                    cin >> pwd;

                    Admin* loggedInAdmin = nullptr;
                    for (Admin* a : admins) {
                        if (a->authenticate(id, pwd)) {
                            loggedInAdmin = a;
                            break;
                        }
                    }

                    if (!loggedInAdmin) {
                        throw InvalidCredentialsException();
                    }

                    cout << "\nLogin Successful! Welcome Admin #" << id << "\n";
                    bool adminSession = true;
                    while (adminSession) {
                        cout << "\nAdmin Menu:\n";
                        cout << "1. Add Movie\n";
                        cout << "2. Add Movie Hall\n";
                        cout << "3. Schedule Showtime\n";
                        cout << "4. View All Movies\n";
                        cout << "5. View All Halls\n";
                        cout << "6. Logout\n";
                        cout << "Enter choice: ";
                        int act;
                        cin >> act;

                        if (act == 1) {
                            int id, dur, age;
                            double price;
                            string date, title, genre, lang, desc;
                            cout << "Movie ID: "; cin >> id;
                            cout << "Duration (mins): "; cin >> dur;
                            cout << "Release Date (YYYY-MM-DD): "; cin >> date;
                            cout << "Price ($): "; cin >> price;
                            cout << "Age Rating (+): "; cin >> age;
                            cin.ignore();
                            cout << "Title: "; getline(cin, title);
                            cout << "Genre: "; getline(cin, genre);
                            cout << "Language: "; getline(cin, lang);
                            cout << "Description: "; getline(cin, desc);

                            loggedInAdmin->addMovie(movies, id, dur, date, price, age, title, genre, lang, desc);
                        } 
                        else if (act == 2) {
                            int id, cap;
                            string name;
                            cout << "Hall ID: "; cin >> id;
                            cout << "Capacity: "; cin >> cap;
                            cin.ignore();
                            cout << "Hall Name: "; getline(cin, name);
                            loggedInAdmin->addMovieHall(halls, id, cap, name);
                        } 
                        else if (act == 3) {
                            int stId, mId, hId;
                            string start, end;
                            cout << "Showtime ID: "; cin >> stId;
                            cout << "Movie ID: "; cin >> mId;
                            cout << "Hall ID: "; cin >> hId;
                            cin.ignore();
                            cout << "Start Time (HH:MM): "; getline(cin, start);
                            cout << "End Time (HH:MM): "; getline(cin, end);

                            try {
                                Movie* m = searchMovieById(movies, mId);
                                MovieHall* h = searchMovieHallById(halls, hId);
                                loggedInAdmin->addShowTime(showtimes, stId, start, end, m, h);
                            } catch (const exception& e) {
                                cout << e.what() << "\n";
                            }
                        } 
                        else if (act == 4) {
                            cout << "\n--- Current Movies ---\n";
                            for (auto m : movies) m->display();
                        } 
                        else if (act == 5) {
                            cout << "\n--- Current Halls ---\n";
                            for (auto h : halls) h->display();
                        } 
                        else if (act == 6) {
                            adminSession = false;
                            cout << "Logged out successfully.\n";
                        }
                    }

                } else if (adminChoice == 2) {
                    int newId;
                    string newPwd;
                    cout << "Choose Admin ID: ";
                    cin >> newId;
                    cout << "Choose Password: ";
                    cin >> newPwd;

                    for (Admin* a : admins) {
                        if (a->getAdminId() == newId) {
                            throw AdminAlreadyExistsException();
                        }
                    }

                    admins.push_back(new Admin(newId, newPwd));
                    cout << "Admin account created successfully! Please log in.\n";
                }
            } catch (const exception& e) {
                cout << e.what() << "\n";
            }

        } else if (choice == 2) {
            // Customer Menu
            bool customerSession = true;
            while (customerSession) {
                cout << "\n--- Customer Portal ---\n";
                cout << "1. Search Movies by Title\n";
                cout << "2. Search Movies by Genre\n";
                cout << "3. View All Showtimes\n";
                cout << "4. Book a Ticket (Check Seat Availability)\n";
                cout << "5. Return to Main Menu\n";
                cout << "Enter choice: ";
                int custChoice;
                cin >> custChoice;

                if (custChoice == 1) {
                    string query;
                    cout << "Enter title keyword: ";
                    cin.ignore();
                    getline(cin, query);
                    vector<Movie*> found = searchMoviesByTitle(movies, query);
                    if (found.empty()) {
                        cout << "No movies found matching that title.\n";
                    } else {
                        cout << "\nSearch Results:\n";
                        for (auto m : found) m->display();
                    }
                } 
                else if (custChoice == 2) {
                    string genre;
                    cout << "Enter genre: ";
                    cin.ignore();
                    getline(cin, genre);
                    vector<Movie*> found = searchMoviesByGenre(movies, genre);
                    if (found.empty()) {
                        cout << "No movies found in that genre.\n";
                    } else {
                        cout << "\nSearch Results:\n";
                        for (auto m : found) m->display();
                    }
                } 
                else if (custChoice == 3) {
                    cout << "\n--- Available Showtimes ---\n";
                    if (showtimes.empty()) {
                        cout << "No showtimes available at the moment.\n";
                    } else {
                        for (auto st : showtimes) st->display();
                    }
                } 
                else if (custChoice == 4) {
                    cout << "\n--- Book a Ticket ---\n";
                    if (showtimes.empty()) {
                        cout << "No showtimes available to book.\n";
                        continue;
                    }
                    for (auto st : showtimes) st->display();

                    int stId, sId;
                    cout << "Enter Showtime ID: ";
                    cin >> stId;

                    try {
                        ShowTime* selectedShow = searchShowTimeById(showtimes, stId);
                        MovieHall* hall = selectedShow->getMovieHall();

                        cout << "\nSeats for Hall: " << hall->getName() << " (Capacity: " << hall->getCapacity() << ")\n";
                        cout << "Seat Status:\n";
                        for (Seat* seat : seats) {
                            bool reserved = selectedShow->isSeatReserved(seat->getSeatId());
                            cout << " [Seat ID " << seat->getSeatId() << " (" << seat->getSeatNumber() << ")] -> " 
                                 << (reserved ? "RESERVED" : "AVAILABLE") << "\n";
                        }

                        cout << "Enter Seat ID to book: ";
                        cin >> sId;

                        Seat* selectedSeat = nullptr;
                        for (Seat* s : seats) {
                            if (s->getSeatId() == sId) {
                                selectedSeat = s;
                                break;
                            }
                        }

                        if (!selectedSeat) {
                            throw NotFoundException("Seat");
                        }

                        // Attempt reservation
                        selectedShow->reserveSeat(sId);

                        // Generate Ticket & Booking
                        Ticket* newTicket = new Ticket(ticketCounter++, selectedSeat, hall, selectedShow);
                        BookingDetails* newBooking = new BookingDetails(bookingCounter++, newTicket);
                        bookings.push_back(newBooking);

                        cout << "\nBooking Confirmed Successfully!\n";
                        newBooking->display();

                    } catch (const exception& e) {
                        cout << e.what() << "\n";
                    }
                } 
                else if (custChoice == 5) {
                    customerSession = false;
                }
            }
        } else if (choice == 3) {
            running = false;
            cout << "Thank you for using the Cinema Management System. Goodbye!\n";
        }
    }

    // Clean up allocated memory
    for (auto m : movies) delete m;
    for (auto h : halls) delete h;
    for (auto st : showtimes) delete st;
    for (auto s : seats) delete s;
    for (auto b : bookings) {
        delete b->getTicket();
        delete b;
    }
    for (auto a : admins) delete a;

    return 0;
}

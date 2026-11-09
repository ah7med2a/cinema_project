#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;



class Movie {	
	int movieId,
		duration,
		ageRating;
	double price;
	string title,
		   releaseDate,
		   genre,
		   language,
		   description;

public:
	Movie(int movieId, int duration, string releaseDate, double price, int ageRating, string title, string genre, string language) {
		this->movieId = movieId;
		this->duration = duration;
		this->releaseDate = releaseDate;
		this->price = price;
		this->ageRating = ageRating;
		this->title = title;
		this->genre = genre;
		this->language = language;
	}
	int getId() {
		return movieId;
	}
	int getDuration() {
		return duration;
	}
	double getPrice() {
		return price;
	}
	int getAgeRating() {
		return ageRating;
	}
	string getTitle() {
		return title;
	}
	string getReleaseDate() {
		return releaseDate;
	}
	string getGenre() {
		return genre;
	}
	string getLanguage() {
		return language;
	}
	string getDescription() {
		return description;
	}
protected:
	friend class Admin;
	void setId(int movieId) {
		this->movieId = movieId;
	}
	void setDuration(int duration) {
		this->duration = duration;
	}
	void setPrice(int price) {
		this->price = price;
	}
	void setAgeRating(int ageRating) {
		this->ageRating = ageRating;
	}
	void setTitle(string title) {
		this->title = title;
	}
	void setReleaseDate(string releaseDate) {
		this->releaseDate = releaseDate;
	}
	void setGenre(string genre) {
		this->genre = genre;
	}
	void setLanguage(string language) {
		this->language = language;
	}
	void setDescription(string description) {
		this->description = description;
	}
	
	
};




class MovieHall {
	int hallId,
		capacity;
	string name;
public:
	MovieHall(int hallId, int capacity, string name) {
		this->hallId = hallId;
		this->capacity = capacity;
		this->name = name;
	}
	int getHallId() {
		return hallId;
	}
	int getCapacity() {
		return capacity;
	}
	string getName() {
		return name;
	}
protected:
	friend class Admin;
	void setId(int hallId) {
		this->hallId = hallId;
	}
	void setCapacity(int capacity) {
		this->capacity = capacity;
	}
	void setName(string name) {
		this->name = name;
	}
};





class ShowTime {
	int showTimeId;
	string startTime,
		endTime;
	Movie* movie;
	MovieHall* movieHall;
public:
	ShowTime(int showTimeId, string startTime, string endTime, Movie* movie, MovieHall* movieHall) {
		this->showTimeId = showTimeId;
		this->startTime = startTime;
		this->endTime = endTime;
		this->movie = movie;
		this->movieHall = movieHall;
	}
	int getShowTimeId() {
		return showTimeId;
	}
	string getStartTime() {
		return startTime;
	}
	string getEndTime() {
		return endTime;
	}
	Movie* getMovie() {
		return movie;
	}
	MovieHall* getMovieHall() {
		return movieHall;
	}
protected:
	friend class Admin;
	void setId(int showTimeId) {
		this->showTimeId = showTimeId;
	}
	void setStartTime(string startTime) {
		this->startTime = startTime;
	}
	void setEndTime(string endTime) {
		this->endTime = endTime;
	}
	void setMovie(Movie* movie) {
		this->movie = movie;
	}
	void setMovieHall(MovieHall* movieHall) {
		this->movieHall = movieHall;
	}
};
class Seat {
	int seatId;
public:
	Seat(int seatId) {
		this->seatId = seatId;
	}
	int getSeatId() {
		return seatId;
	}
protected:
	friend class Admin;
	void setId(int seatId) {
		this->seatId = seatId;
	}
};
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
	int getTicketId() {
		return ticketId;
	}
	Seat* getSeat() {
		return seat;
	}
	MovieHall* getMovieHall() {
		return movieHall;
	}
	ShowTime* getShowTime() {
		return showTime;
	}
protected:
	friend class Admin;
	void setId(int ticketId) {
		this->ticketId = ticketId;
	}
	void setSeat(Seat* seat) {
		this->seat = seat;
	}
	void setMovieHall(MovieHall* movieHall) {
		this->movieHall = movieHall;
	}
	void setShowTime(ShowTime* showTime) {
		this->showTime = showTime;
	}
};
class BookingDetials {
	int bookingId;
	Ticket* ticket;
	Seat* seat;
	ShowTime* showTime;
public:	
	BookingDetials(int bookingId, Ticket* ticket, Seat* seat, ShowTime* showTime) {
		this->bookingId = bookingId;
		this->ticket = ticket;
		this->seat = seat;
		this->showTime = showTime;
	}
	int getBookingId() {
		return bookingId;
	}
	Ticket* getTicket() {
		return ticket;
	}
	Seat* getSeat() {
		return seat;
	}
	ShowTime* getShowTime() {
		return showTime;
	}
protected:
	friend class Admin;
	void setId(int bookingId) {
		this->bookingId = bookingId;
	}
	void setTicket(Ticket* ticket) {
		this->ticket = ticket;
	}
	void setSeat(Seat* seat) {
		this->seat = seat;
	}
	void setShowTime(ShowTime* showTime) {
		this->showTime = showTime;
	}
};

class Admin {
	int adminId;
	string password;


	Admin(int adminId, string password) {
		this->adminId = adminId;
		this->password = password;
	}
public:
	// Movie related functions
	void setMovieId(Movie* movie, int movieId) {
		movie->setId(movieId);
	}
	void setMovieDuration(Movie* movie, int duration) {
		movie->setDuration(duration);
	}
	void setMoviePrice(Movie* movie, int price) {
		movie->setPrice(price);
	}
	void setMovieAgeRating(Movie* movie, int ageRating) {
		movie->setAgeRating(ageRating);
	}
	void setMovieTitle(Movie* movie, string title) {
		movie->setTitle(title);
	}
	void setMovieReleaseDate(Movie* movie, string releaseDate) {
		movie->setReleaseDate(releaseDate);
	}
	void setMovieGenre(Movie* movie, string genre) {
		movie->setGenre(genre);
	}
	void setMovieLanguage(Movie* movie, string language) {
		movie->setLanguage(language);
	}
	void setMovieDescription(Movie* movie, string description) {
		movie->setDescription(description);
	}

	//MovieHall related functions

	void setHallId(MovieHall* movieHall, int hallId) {
		movieHall->setId(hallId);
	}
	void setCapacity(MovieHall* movieHall, int capacity) {
		movieHall->setCapacity(capacity);
	}
	void setName(MovieHall* movieHall, string name) {
		movieHall->setName(name);
	}

	// ShowTime related functions
	void setShowTimeId(ShowTime* showTime, int showTimeId) {
		showTime->setId(showTimeId);
	}
	void setStartTime(ShowTime* showTime, string startTime) {
		showTime->setStartTime(startTime);
	}
	void setEndTime(ShowTime* showTime, string endTime) {
		showTime->setEndTime(endTime);
	}
	void setMovie(ShowTime* showTime, Movie* movie) {
		showTime->setMovie(movie);
	}
	void setMovieHall(ShowTime* showTime, MovieHall* movieHall) {
		showTime->setMovieHall(movieHall);
	}
	// Seat related functions
	void setSeatId(Seat* seat, int seatId) {
		seat->setId(seatId);
	}
	// Ticket related functions
	void setTicketId(Ticket* ticket, int ticketId) {
		ticket->setId(ticketId);
	}
	void setTicketSeat(Ticket* ticket, Seat* seat) {
		ticket->setSeat(seat);
	}
	void setTicketMovieHall(Ticket* ticket, MovieHall* movieHall) {
		ticket->setMovieHall(movieHall);
	}
	void setTicketShowTime(Ticket* ticket, ShowTime* showTime) {
		ticket->setShowTime(showTime);
	}
	// BookingDetials related functions
	void setBookingId(BookingDetials* bookingDetials, int bookingId) {
		bookingDetials->setId(bookingId);
	}
	void setBookingTicket(BookingDetials* bookingDetials, Ticket* ticket) {
		bookingDetials->setTicket(ticket);
	}
	void setBookingSeat(BookingDetials* bookingDetials, Seat* seat) {
		bookingDetials->setSeat(seat);
	}
	void setBookingShowTime(BookingDetials* bookingDetials, ShowTime* showTime) {
		bookingDetials->setShowTime(showTime);
	}
	void setAdminId(int adminId) {
		this->adminId = adminId;
	}
	void setPassword(string password) {
		this->password = password;
	}


};

int main()
{
	

    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

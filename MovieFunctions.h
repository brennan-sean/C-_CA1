#include <iostream>
#include <vector>
#include <list>
#include "Movie.h"
#pragma once
using namespace std;

class MovieFunctions
{
private:
	vector<Movie> movieList;

	void printMovieHeader();
	void printSingleMovie(Movie& i);

	void sortByMovieID();
	void sortByMovieTitle();
	void sortByMovieLeadActor();
	void sortByMovieDirector();
	void sortByMovieGenre();
	void sortByMovieReleaseYear();
	void sortByMovieRating();
	
	void setMovieName();
	void setLeadActor();
	void setDirector();
	void setGenre();
	void setReleaseYear();
	void setRating(float rating);
	int getMovieID();
	string getMovieName();
	string getLeadActor();
	string getDirector();
	string getGenre();
	int getReleaseYear();
	float getRating();
	int getCurrentYear();


public:
	bool fileExists(const std::string& file);
	void readFile(string fileName);
	void writeToFile(string fileName);

	void createNewMovie();
	void removeMovie(int movieNumber);
	void updateMovie(int movieNumber);
	void sortByMovieFields(int userInput);

	void searchMovieByID(int movieNumber);
	void searchMovieByTitle(string title);
	void searchMovieByDirector(string directorName);
	void searchMovieByLeadActor(string actorName);
	
	string inputString(string prompt);
	int inputInteger(string prompt);
	int inputInteger2(const string prompt, const int minNum, const int maxNum);
	int inputYear(string prompt);
	float inputRating(string prompt);

	void endApplication(string fileName);
	void printMessage(string message);

	void printMovies();
};

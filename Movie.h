#include <string>
#pragma once

using namespace std;

class Movie
{
	private:
		static int max_movie_id;
		int movieID;
		string movieName;
		string leadActor;
		string director;
		string genre;
		int releaseYear;
		float rating;

	public:
		Movie(int movieID, string movieName, string leadActor, string director, string genre, int releaseYear, float rating);
		
		void setMovieID(int movieID)
		{
			this -> movieID = movieID;
		}

		void setMovieName(string movieName)
		{
			this -> movieName = movieName;
		}

		void setLeadActor(string leadActor)
		{
			this -> leadActor = leadActor;
		}

		void setDirector(string director)
		{
			this -> director = director;
		}

		void setGenre(string genre)
		{
			this -> genre = genre;
		}

		void setReleaseYear(int releaseYear)
		{
			this -> releaseYear = releaseYear;
		}

		void setRating(float rating)
		{
			this -> rating = rating;
		}

		int getMovieID() const
		{
			return movieID;
		}

		string getMovieName() const
		{
			return movieName;
		}

		string getLeadActor() const
		{
			return leadActor;
		}

		string getDirector() const
		{
			return director;
		}

		string getGenre() const
		{
			return genre;
		}

		int getReleaseYear() const
		{
			return releaseYear;
		}

		float getRating() const
		{
			return rating;
		}
};
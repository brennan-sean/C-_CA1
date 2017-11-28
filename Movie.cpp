#include "Movie.h"

int Movie::max_movie_id = 0;

Movie::Movie(int movieID, string movieName, string leadActor, string director, string genre, int releaseYear, float rating)
{
		this -> movieName = movieName;
		this -> leadActor = leadActor;
		this -> director = director;
		this -> genre = genre;
		this -> releaseYear = releaseYear;
		this -> rating = rating;

		switch(movieID)
        {
        	case 0:
        	       Movie::max_movie_id++;
                   this -> movieID = Movie::max_movie_id;
                   break;
            default:
                    this -> movieID = movieID;
                    if (movieID > Movie::max_movie_id)
                    {
                        Movie::max_movie_id = movieID;
                    }
        }

} 


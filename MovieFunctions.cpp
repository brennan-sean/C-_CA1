#include <iostream>
#include <fstream>
#include <sstream>   
#include <algorithm>
#include <list>
#include <iomanip>
#include <sys/stat.h>
#include <time.h>
#include "MovieFunctions.h"
#include "Movie.h"

void MovieFunctions::printMovieHeader()
{
    cout  << endl;
    cout  << "ID,  Movie Name,   Lead Actor,  Director,  Genre,  Year, Rating " << endl;
    cout  << "------------------------------------------------------------------" << endl;
}

void MovieFunctions::printSingleMovie(Movie& i)
{
	cout << i.getMovieID() << ", " 
		 << i.getMovieName() << ", " 
		 << i.getLeadActor() << ", " 
		 << i.getDirector() << ", "
		 << i.getGenre() << ", "
		 << i.getReleaseYear() << ", "
		 << fixed << setprecision(2) << i.getRating() 
		 << endl;
}

void MovieFunctions::printMovies()
{
    printMovieHeader();
    for (vector<Movie>::iterator i = movieList.begin(); i != movieList.end(); ++i)
    {
        printSingleMovie(*i);
    }
}

void MovieFunctions::sortByMovieID()
{
	sort(movieList.begin(), movieList.end(), [](const Movie &lhs, const Movie &rhs)
	{
		return lhs.getMovieID() < rhs.getMovieID();
    });
}

void MovieFunctions::sortByMovieTitle()
{
	sort(movieList.begin(), movieList.end(), [](const Movie &lhs, const Movie &rhs)
	{		
		return lhs.getMovieName() < rhs.getMovieName();
	});
}

void MovieFunctions::sortByMovieLeadActor()
{
	sort(movieList.begin(), movieList.end(), [](const Movie &lhs, const Movie &rhs)
	{
		return lhs.getLeadActor() < rhs.getLeadActor();
	});
}

void MovieFunctions::sortByMovieDirector()
{
	sort(movieList.begin(), movieList.end(), [](const Movie &lhs, const Movie &rhs)
	{
		return lhs.getDirector() < rhs.getDirector();
	});
}

void MovieFunctions::sortByMovieGenre()
{
	sort(movieList.begin(), movieList.end(), [](const Movie &lhs, const Movie &rhs)
	{
		return lhs.getGenre() < rhs.getGenre();
	});
}

void MovieFunctions::sortByMovieReleaseYear()
{
	sort(movieList.begin(), movieList.end(), [](const Movie &lhs, const Movie &rhs)
	{
		return lhs.getReleaseYear() < rhs.getReleaseYear();
	});
}

void MovieFunctions::sortByMovieRating()
{
	sort(movieList.begin(), movieList.end(), [](const Movie &lhs, const Movie &rhs)
	{
		return lhs.getRating() < rhs.getRating();
	});
}

bool MovieFunctions::fileExists(const std::string& fileName)
{   // return true if the file exists reference 
    struct stat buf;
    return (stat(fileName.c_str(), &buf) == 0);
}

void MovieFunctions::readFile(string fileName)
{
	try
	{
		string line;
		string token;
		ifstream infile;
		infile.open(fileName);
				
		while(getline(infile, line))
        {
        	istringstream ss(line);

        	string movieIDstring; 
        	getline(ss, movieIDstring, ',');
        	string movieName; 
        	getline(ss, movieName, ',');
        	string leadActor;
        	getline(ss, leadActor, ',');
        	string director;
        	getline(ss, director, ',');
        	string genre;
        	getline(ss, genre, ',');
        	string releaseYear ;
        	getline(ss, releaseYear, ',');
        	string rating;
        	getline(ss, rating, ',');
        	
        	Movie movie(stoi(movieIDstring), movieName, leadActor, director, genre, stoi(releaseYear), stof(rating));

        	this -> movieList.push_back(movie);

        }
    }catch(const exception& e ) {
    	std::cerr << "exception occured" << endl;
    }
}

void MovieFunctions::writeToFile(string fileName)
{
	sortByMovieID();

	ofstream movieWriter;
	movieWriter.open(fileName);
	string movieData;

	string id;
	string year;
	string rating;

	for (vector<Movie>::iterator i = movieList.begin(); i != movieList.end(); ++i)
    {
    	id = to_string(i->getMovieID());
    	year = to_string(i->getReleaseYear());
		rating = to_string(i->getRating());

		movieData = id + "," + i->getMovieName() + "," + i->getLeadActor() + "," + i->getDirector() + "," + i->getGenre() + "," + year + "," + rating + "\n";

		movieWriter << movieData;

    }
    printMessage("Movie list succesfully written to file");
    movieWriter.close();
}


void MovieFunctions::createNewMovie()
{

	bool movieCreated = false;
	bool alreadyExsisting = false;

	string movieName;
	string leadActor;
	string director;
	string genre;
	int releaseYear;
	float rating;

	movieName = inputString("Enter the movie's Title: ");

	for (vector<Movie>::iterator i = movieList.begin(); i != movieList.end(); ++i)
    {
    	if ( i->getMovieName() 	== movieName )
    	{
			alreadyExsisting = true;
		}
	}

	if(alreadyExsisting)
	{
		printMessage("Movie has already been created!");
	}

	if(!alreadyExsisting)
	{
	    leadActor = inputString("Enter the movie's Lead Actor: ");
		director = inputString("Enter the movie's Director: ");
		genre = inputString("Enter the movie's genre: ");
		releaseYear = inputYear("Enter the movie's Release Year: ");
		rating = inputRating("Enter the movie's rating: ");
		movieCreated = true;
	}

	if(movieCreated)
	{
		printMessage("Movie added succesfully");
		Movie movie(0, movieName, leadActor, director, genre, releaseYear, rating);
		this-> movieList.push_back(movie);
	}
}

void MovieFunctions::removeMovie(int movieNumber)
{
	int userInput;
	bool movieFound = false;
    for (vector<Movie>::iterator i = movieList.begin(); i != movieList.end(); ++i)
    {
    	if (i->getMovieID() == movieNumber)
		{
			printMovieHeader();
            printSingleMovie(*i);


			userInput = inputInteger("\nIs this the movie you want to remove? YES.......<1> / No.......<2>: ");

			if(userInput == 1)
    		{
        		i = movieList.erase(i);
        		--i;
        		printMessage("Movie removed");
        		movieFound = true;
        	}
        	else
        	{
        		printMessage("Movie not removied!");
        		movieFound = true;
			}
        }
    }   
                
    if (!movieFound) 
    {
    	printMessage("Movie ID not found");
	}

}

void MovieFunctions::updateMovie(int movieNumber)
{
	int userInput;
	int prompt;
	string movieTitle;
	string leadActor;
	string director;
	string genre;
	int releaseYear;
	float newRating;
    
    bool movieFound = false;
    for (vector<Movie>::iterator i = movieList.begin(); i != movieList.end(); ++i)
    {
    	if ( i->getMovieID() == movieNumber )
    	{
    		printMovieHeader();
            printSingleMovie(*i);

    		userInput = inputInteger("\nIs this the movie you want to update? YES.......<1> / No.......<2>: ");
    		cout << endl;

    		if(userInput == 1)
    		{
    			cout << "Update by: " << endl;
    			cout << "-Title.........<1>" << endl 
    				 <<	"-Lead Actor....<2>" << endl
    				 << "-Director......<3>" << endl 
    				 << "-Genre.........<4>" << endl
    				 << "-Release Year..<5>" << endl
    				 << "-Rating........<6>"  << endl;
    			prompt = inputInteger2("Enter what you want to update <1-6>: ", 1, 6);
    			cout << endl;

    			switch(prompt)
    			{
    				case 1:
    				{
    					cout << "Title = " << i->getMovieName() << endl;
    					movieTitle = inputString("Enter your new movie title: ");

        				i->setMovieName(movieTitle);

        				printMessage("Movie updated");
    					break;
    				}

    				case 2:
    				{
    					cout << "Lead Actor = " << i->getLeadActor() << endl;
    					leadActor = inputString("Enter your new movie lead actor: ");

        				i->setLeadActor(leadActor);

        				printMessage("Movie updated");
    					break;
    				}

    				case 3:
    				{
    					cout << "Director = " << i->getDirector() << endl;
    					director = inputString("Enter your new movie director: ");

        				i->setDirector(director);

        				printMessage("Movie updated");
    					break;
    				}

    				case 4:
    				{
    					cout << "Genre = " << i->getGenre() << endl;
    					genre = inputString("Enter your new movie genre: ");

        				i->setGenre(genre);

        				printMessage("Movie updated");
    					break;
    				}

    				case 5:
    				{
    					cout << "Release Year = " << i->getReleaseYear() << endl;
    					releaseYear = inputYear("Enter your new movie release year: ");

        				i->setReleaseYear(releaseYear);

        				printMessage("Movie updated");
    					break;
    				}

    				case 6:
    				{
    					cout << "Rating = " << i->getRating() << endl;
    					newRating = inputRating("Enter your new movie rating: ");

        				i->setRating(newRating);

        				printMessage("Movie updated");
    					break;
    				}
    			}
    			movieFound = true;
        	}
        	
        	else
        	{
        		printMessage("Movie not updated!");
        		movieFound = true;
			}
        }
    }   
                
    if (!movieFound) 
    {
    	printMessage("Movie ID not found");
	}
}

void MovieFunctions::searchMovieByID(int movieNumber)
{
	bool movieFound = false;
    for (vector<Movie>::iterator i = movieList.begin(); i != movieList.end(); ++i)
    {
    	if ( i->getMovieID() == movieNumber )
    	{
    		printMovieHeader();
            printSingleMovie(*i);

        	movieFound = true;
        }
    }   
                
    if (!movieFound) 
    {
    	printMessage("Movie ID not found");
	}

}

void MovieFunctions::searchMovieByTitle(string title)
{

	bool movieFound = false;
	for(vector<Movie>::iterator i = movieList.begin(); i != movieList.end(); ++i)
	{
		if(i->getMovieName() == title)
		{
        	printMovieHeader();
            printSingleMovie(*i);

        	movieFound = true;
        }
    }   
                
    if (!movieFound) 
    {
    	printMessage("No movies found with name <" + title + ">");
    }
}

void MovieFunctions::searchMovieByDirector(string directorName)
{
    int looper = 0;
    bool movieFound = false;
    for(vector<Movie>::iterator i = movieList.begin(); i != movieList.end(); ++i)
    {
        if(i->getDirector() == directorName)
        {
            looper++;
            if (looper == 1) 
            {
                 printMovieHeader(); 
            }
            printSingleMovie(*i);
            movieFound = true;
        }
    }

    if (!movieFound)
    {
        printMessage("No movies found for director <" + directorName + ">" );
    }
}

void MovieFunctions::searchMovieByLeadActor(string actorName)
{
    int looper = 0;
    bool movieFound = false;
    for(vector<Movie>::iterator i = movieList.begin(); i != movieList.end(); ++i)
    {
        if(i->getLeadActor() == actorName)
        {
            looper++;
            if (looper == 1) 
            {
                printMovieHeader(); 
            }
            printSingleMovie(*i);
            movieFound = true;
        }
    }

    if (!movieFound)
    {
        printMessage("No movies found with lead actor <" + actorName + ">" );
    }
}

void MovieFunctions::sortByMovieFields(int userInput)
{
	switch(userInput)
	{
		case 1:
		{
			sortByMovieID();
			break;
		}
		
		case 2:
		{
			sortByMovieTitle();
			break;
		}
		
		case 3:
		{
			sortByMovieLeadActor();
			break;
		}
		
		case 4:
		{
			sortByMovieDirector();
			break;
		}
		
		case 5:
		{
			sortByMovieGenre();	
			break;
		}
		
		case 6:
		{
			sortByMovieReleaseYear();
			break;
		}
		
		case 7:
		{
			sortByMovieRating();
			break;
		}
		default:
			printMessage("Invalid entry - try again!");
	}

	printMovies();
}

void MovieFunctions::endApplication(string fileName)
{
	int userInput;

    userInput = inputInteger("Would you like to save the Movie list to file? Yes....<1> / No....<2>: ");	cout << endl;

	if(userInput == 1)
	{
        if (movieList.empty())
        {
            printMessage("No movies in list to write to file!");
        }
        else
        {
		writeToFile(fileName);
		printMessage("Leaving program - Thank you!");
	    }
    }   
    else
	{
		printMessage("Leaving program - Thank you!");
	}
}

void MovieFunctions::printMessage(string message) //Algorithm got on https://stackoverflow.com/questions/17988493/while-loop-to-create-a-border-of-asterisks-around-text
{
	int pad = 1; //padding
	const int rows = pad * 2 + 3;  //desired rows/columns

	const string::size_type cols = message.size() + pad * 2 + 2;
	cout << endl; // seperate output from input
	int r = 0; // invariants

	while (r != rows) 
	{
		string::size_type c = 0;
		while(c != cols) 
		{
   			if (r == 0 || r == rows -1 || c == 0 || c == cols -1) // if in bordering column or row
   			{	 
        		cout << "*";   //output *
    		} 
    		else 
    		{
        		if (r == pad + 1 && c == pad + 1) //if on row for greeting
        		{ 
           		 	cout << message; // write greeting
            		c += (message.size()-1); // adjust invariant
        		} 
        		else 
        		{
            		cout << " ";
        		}
    		}
        		++c;
    	}
    		++r;
    		cout << endl;
	}
}

string MovieFunctions::inputString(string prompt)
{
  	string userInput = "";

	cout << prompt;
	getline(cin, userInput);
	return userInput;
}

int MovieFunctions::inputInteger(string prompt)
{
  string userInput = "";

  while (true)
  {
	userInput = "";
	cout << prompt;
	getline(cin, userInput);

	// check user input for all number values 
	if(userInput.find_first_not_of("1234567890") != string::npos )
	{
	  	printMessage("Invalid integer, try again... ");
    }
	else 
	{
		if(userInput == "")
		{
			printMessage("No number found");
		}
		else
		{
			break;
		}
   	}
  }
  return stoi(userInput);
}

int MovieFunctions::inputInteger2(const string prompt, const int minNum, const int maxNum)
{
	string userInput = "";
	int iNumber = 0;
	string strMin = to_string(minNum);
	string strMax = to_string(maxNum);

  	while (true)
  	{
    	userInput = "";
        cout << endl << prompt;
        getline(cin, userInput);

        // This code converts from string to number safely.
        stringstream myStream(userInput);
        if (myStream >> iNumber)
        {
        	if ((iNumber < minNum) || (iNumber > maxNum))
            {
            	printMessage("Invalid. Valid range [" + strMin + ".." + strMax + "], try again");
            }
            else
            { // All good
            	break;
            }
        }
        else
        {
  	        printMessage("Invalid number, please try again");
        }
    }
  return iNumber;
}

int MovieFunctions::getCurrentYear() //Reference http://www.cplusplus.com/reference/ctime/tm/ to understand struct tm
{
	time_t rawtime;
  	struct tm * timeinfo;

    time (&rawtime);
	timeinfo = localtime ( &rawtime );
    return 1900 + timeinfo->tm_year;
}

int MovieFunctions::inputYear(string prompt)
{
	string userInput = "";
	int iNumber = 0;
	int currentYear = getCurrentYear();
	string strMaxYear = to_string(currentYear);

  	while (true)
  	{
    	userInput = "";
        cout << prompt;
        getline(cin, userInput);

        // This code converts from string to number safely.
        stringstream myStream(userInput);
        if (myStream >> iNumber) 
        {
        	if ((iNumber < 1920) || (iNumber > currentYear))
            {
            	printMessage("Invalid year. Range [1920 .. " + strMaxYear + "], please try again");
            }
            else 
            { 
            	break;
            }
        }
        else 
        {
  	        printMessage("Invalid number for year, please try again");
        }
    }
  return iNumber;
}

float MovieFunctions::inputRating(string prompt)
{
  	string userInput = "";
  	float fltNumber = 0.0;

	while (true)
	{
		cout << prompt;
		getline(cin, userInput);

		// This code converts from string to float safely.
	   stringstream myStream(userInput);
	   if (myStream >> fltNumber) {
		  if ((fltNumber < 0) || (fltNumber > 10)) {
		  	printMessage( "Invalid rating - range [0 .. 10], please try again" );
		  }
		  else 
          { 
	     	  break;
	      }
   	   }
   	   else {
	      cout << "Invalid number for rating, please try again" << endl;
       }
  }
  return fltNumber;
}
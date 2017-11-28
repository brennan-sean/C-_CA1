#include <iostream>
#include <list>
#include "Movie.h"
#include "MovieFunctions.h"

int main(int argc, char *argv[])
{
	MovieFunctions movieFunctions;

	string fileName = "test1.txt";

	if (movieFunctions.fileExists(fileName))
	{
    	movieFunctions.printMessage( "Reading Movie file:  <" + fileName + ">");
    	movieFunctions.readFile(fileName);
	} 
	else
	{
		movieFunctions.printMessage("Movie file <" + fileName + "> Not Found!");
	}
     
    bool doNotExit = true;

	while(doNotExit)
	{
		int choice;

        cout << "\n-- MAIN MENU -- " << endl;

        cout << "\n-Write movie list to file.......................<1> " << endl;
        cout << "-Return list off all movies.....................<2> " << endl;
		cout << "-Insert a new movie.............................<3> " << endl;
		cout << "-Remove a movie.................................<4> " << endl;
		cout << "-Edit movie info................................<5> " << endl;
		cout << "-Search for a movie by ID.......................<6> " << endl;
		cout << "-Search for a movie by title/actor/director.....<7> " << endl;
		cout << "-Sort movies....................................<8> " << endl;
		cout << "-Exit application...............................<9> " << endl;


		cout << endl;
		choice = movieFunctions.inputInteger2("Enter Selection <1-9>: ", 1, 9);
		cout << endl;

		switch(choice)
		{
			case 1:
			{
				movieFunctions.writeToFile(fileName);	
				break;
			}
			case 2:
			{
				movieFunctions.printMovies();
				break;
			}
			
			case 3:
			{
				movieFunctions.createNewMovie();
				break;
			}
			
			case 4:
			{
				int movieNumber;
				
				movieNumber = movieFunctions.inputInteger("Enter a movie ID to search for: ");
				cout << endl;
				movieFunctions.removeMovie(movieNumber);
				break;
			}

			case 5:
			{
				int movieNumber;

				movieNumber = movieFunctions.inputInteger("Enter a movie ID to search for: ");
				cout << endl;

				movieFunctions.updateMovie(movieNumber);
				break;
			}

			case 6:
			{
				int movieNumber;

				movieNumber = movieFunctions.inputInteger("Enter a movie ID to search for: ");
				movieFunctions.searchMovieByID(movieNumber);
				break;
			}

			case 7:
			{
				int searchInput;
				string searchString;

				cout << "Search Movie List by: " << endl;
				cout << "-Movie Name.....<1>" << endl
					 << "-Lead Actor.....<2>" << endl
					 << "-Director.......<3>" << endl;
				searchInput = movieFunctions.inputInteger2("\nEnter search selection <1-3>: ", 1, 3);
				cout << endl;

				switch (searchInput)
				{
					case 1:
					{
						searchString = movieFunctions.inputString("Enter Movie name to find: ");
						movieFunctions.searchMovieByTitle(searchString);
						break;
					}

					case 2:
					{
						searchString = movieFunctions.inputString("Enter actor name to find: ");
						movieFunctions.searchMovieByLeadActor(searchString);
						break;
					}

					case 3:
					{
						searchString = movieFunctions.inputString("Enter director name to find: ");
						movieFunctions.searchMovieByDirector(searchString);
						break;
					}
				}
				break;
			}

			case 8:
			{
				int userInput;

				cout << "Sort by: " << endl;
				cout << "-ID............<1> " << endl
				     << "-Title.........<2>" << endl 
    				 <<	"-Lead Actor....<3>" << endl
    				 << "-Director......<4>" << endl 
    				 << "-Genre.........<5>" << endl
    				 << "-Release Year..<6>" << endl
    				 << "-Rating........<7>"  << endl;
				userInput = movieFunctions.inputInteger2("\nEnter your selection <1-7>: ", 1, 7);
				cout << endl;
				movieFunctions.sortByMovieFields(userInput);
				break;
			}

			case 9:
			{
				doNotExit = false;
				break;
			}
			default:
				movieFunctions.printMessage("\nInvalid entry - try again!");
		}	
	}
	movieFunctions.endApplication(fileName);
}
//Created by: Hsi-En Hong, Kyle Larson, R. Ross Palmer, Thomas Schucker
//Date Completed: December 7th 2011
//Portion for interface that the user initially encounters

#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node_s{//creates data type for a specific movie
	char title[100];		
	char director[100];
	char genre[100];
	int duration;
	int year;
	char MPAA[100];
	float ave_rating;
	int number_ratings;
	struct node_s *leftp;
	struct node_s *rightp;
}movie;

void scan_fun(movie *m1,FILE *inp) //scans a movie from a database file 
{
	fscanf(inp,"%s",m1->title);//scan from file
		fscanf(inp,"%s",m1->director);
		fscanf(inp,"%s",m1->genre);
		fscanf(inp,"%d",&m1->duration);
		fscanf(inp,"%d",&m1->year);
		fscanf(inp,"%s",m1->MPAA);
		fscanf(inp,"%d",&m1->number_ratings);
		fscanf(inp,"%f",&m1->ave_rating);
}

void print_movie(movie *m2,FILE *inp)//prints a movie from data type movie into a file
{
	fprintf(inp,"%s\n",m2->title);//print to file
	fprintf(inp,"%s\n",m2->director);	
	fprintf(inp,"%s\n",m2->genre);
	fprintf(inp,"%d\n",m2->duration);
	fprintf(inp,"%d\n",m2->year);
	fprintf(inp,"%s\n",m2->MPAA); 
	fprintf(inp,"%d\n",m2->number_ratings);
	if(m2->rightp!=NULL)//makes sure that format is correct
	{
		fprintf(inp,"%.2f\n",m2->ave_rating);
	}
	else
	{
		fprintf(inp,"%.2f",m2->ave_rating);
	}
	
}
void print_rate(movie *m2)//printing title and rating
{
	printf("%s\n",m2->title);//print to screen
	printf("%.2f\n",m2->ave_rating);
}

void print_g(movie *m2)//printing title and genre
{
	printf("%s\n",m2->title);
	printf("\t%s\n",m2->genre);
}

void print_list1(movie *hl,FILE *inp)//prints the entire list of movies to a file
{
	
	while(hl!=NULL)
	{
		print_movie(hl,inp);
		hl=hl->rightp;//updates pointer
	}
}

void print_list2(movie *hl)//prints all of the movies on the screen highest rating first
{
	while(hl!=NULL)
	{
		print_rate(hl);
		hl=hl->leftp;
	}
}

void print_list(movie *hl)//prints all of the movies on the screen lowest rating first
{
	while(hl!=NULL)
	{
		print_rate(hl);
		hl=hl->rightp;
	}
}

void print_listg(movie *hl)//prints all movies and their genre on the screen
{
	while(hl!=NULL)
	{
		print_g(hl);
		hl=hl->rightp;
	}
}

void add_movie(movie *end,movie *hl,movie *hr)//function for useres to add movies to the database
{
	movie *temp;
	temp = (movie *)malloc(sizeof (movie));
	temp->number_ratings=1;
	printf("enter title: ");//elements of movie
	scanf("%s",temp->title);
	printf("enter director: ");
	scanf("%s",temp->director);
	printf("enter genre: ");
	scanf("%s",temp->genre);
	printf("enter duration: ");
	scanf("%d",&temp->duration);
	printf("enter year: ");
	scanf("%d",&temp->year);
	printf("enter MPAA rating: ");
	scanf("%s",temp->MPAA);
	printf("enter budda rating: ");
	scanf("%f",&temp->ave_rating);
	if(hl==NULL)//attaches pointers to the movie if it is the first one in the database
	{
		temp->rightp=NULL;
		temp->leftp=NULL;
		hl=temp;
		hr=temp;
	}
	else//attaches movie to the movie before it
	{
		temp->leftp=end;
		end->rightp=temp;
		temp->rightp=NULL;
		hr=temp;
	}
}

void delete_movie(movie *pass, movie *hl,movie *hr)//function for deleting a movie from the database
{
	if(pass == hl)//if it is the first element
	{
		hl=pass->rightp;
	}
	else
	{
		pass->leftp->rightp=pass->rightp;
	}
	if(pass==hr)//if last element
	{
		hr=pass->leftp;
	}
	else
	{
		pass->rightp->leftp=pass->leftp;
	}
	free(pass);//removes from memory
}

void swap1(movie *x, movie *y)//swap function for bubblesort
{
	movie temp;//copy y to temp
	strcpy(temp.title,y->title);
	strcpy(temp.director,y->director);
	strcpy(temp.genre,y->genre);
	temp.duration=y->duration;
	temp.year=y->year;
	strcpy(temp.MPAA,y->MPAA);
	temp.ave_rating=y->ave_rating;
	temp.number_ratings=y->number_ratings;
	
	strcpy(y->title,x->title);//copy x to y
	strcpy(y->director,x->director);
	strcpy(y->genre,x->genre);
	y->duration=x->duration;
	y->year=x->year;
	strcpy(y->MPAA,x->MPAA);
	y->ave_rating=x->ave_rating;
	y->number_ratings=x->number_ratings;
	
	strcpy(x->title,temp.title);//copy temp to x
	strcpy(x->director,temp.director);
	strcpy(x->genre,temp.genre);
	x->duration=temp.duration;
	x->year=temp.year;
	strcpy(x->MPAA,temp.MPAA);
	x->ave_rating=temp.ave_rating;
	x->number_ratings=temp.number_ratings;
}
	
void bubblesorttitle(movie *hl, movie *hr)//sort by alphabetically
{
	int flag = 1;
	int i;
	movie *p = hl;
	while(flag == 1)//goes throught the list untill no more swaps
	{
		flag = 0;
		while(p->rightp!=NULL)//goes through all elements of list
		{
			if(strcmp(p->title, p->rightp->title)>0)//compares 2 elements
			{
				swap1(p, p->rightp);
				flag = 1;
				
			}
			p = p->rightp;
		}
		p=hl;//returns to beggining of list
	}
}

void bubblesortgenre(movie *hl, movie *hr)//sort by primary genre alphabetically
{
	int flag = 1;
	int i;
	movie *p = hl;
	while(flag == 1)
	{
		flag = 0;
		while(p->rightp!=NULL)
		{
			if(strcmp(p->genre, p->rightp->genre)>0)
			{
				swap1(p, p->rightp);
				flag = 1;
				
			}
			p = p->rightp;
		}
		p=hl;
	}
}

void sort_nums(movie *hl,movie *hr)//sort rating starting at highest
{
	int flag = 1;
	int i;
	movie *p = hl;
	while(flag == 1)
	{
		flag = 0;
		while(p->rightp!=NULL)
		{
			if(p->ave_rating < p->rightp->ave_rating)
			{
				swap1(p, p->rightp);
				flag = 1;
				
			}
			p = p->rightp;
		}
		p=hl;
	}
}

void add_rating(movie *r)//function for adding a user rating to a specific movie
{
	float x;
	printf("enter your rating between 1 and 5: ");
	scanf("%f",&x);
	while (x<1 || x>5)
	{
		printf("this entry is invalid\n");
		printf("enter your rating between 1 and 5: ");
		scanf("%f",&x);
	}
	r->ave_rating=((r->ave_rating)*(r->number_ratings)+x)/(r->number_ratings +1);
	r->number_ratings=r->number_ratings+1;
}

movie find_y(movie *hl, movie *hr)//finds all movies in a specific year
{
	int target;
	movie *current=hl;
	printf("Enter year: ");
	scanf("%d",&target);
	bubblesorttitle(hl,hr);
	
	while(current!=NULL)
	{
		if(target==current->year)
		{
			printf("%s\n",current->title);
			current=current->rightp;
			
		}
		else
		{
			current=current->rightp;
		}
	}
	
}
movie find_dur(movie *hl, movie *hr)//sorts by minimum duration and displays alphabetically
{
	int target;
	movie *current=hl;
	printf("Enter minimum duration: ");
	scanf("%d",&target);
	bubblesorttitle(hl,hr);
	
	while(current!=NULL)
	{
		if(target<=current->duration)
		{
			printf("%s\n",current->title);
			current=current->rightp;
			
		}
		else
		{
			current=current->rightp;
		}
	}
	
}

movie deletesm(movie *hl, movie *hr)//delets a single movie from the database
{
	char target[100];
	movie *current=hl;
	char answ4;
	printf("Enter title: ");
	scanf("%s",target);
	bubblesorttitle(hl,hr);
	
	while(current!=NULL)
	{
		if(strcmp(target,current->title)==0)
		{
			printf("%s\n",current->title);
			printf("Are you sure that you want to delete this movie? (y/n)\n");
			fflush(stdin);
			scanf("%c", &answ4);
			if(answ4=='y')
			{
				delete_movie(current,hl,hr);
			}
			current=current->rightp;
			
		}
		else
		{
			current=current->rightp;
		}
	}
}

movie deletemg(movie *hl, movie *hr)//delets movie by genre
{
	char arry[100];
	movie *current=hl;
	char answ4;
	int i,j,sum=0;
	printf("Enter genre: ");
	scanf("%s",arry);
	bubblesorttitle(hl,hr);
	printf("Are you sure that you want to delete these movies? (y/n)\n");
	fflush(stdin);
	scanf("%c", &answ4);
	if(answ4=='y')
	{
		while(current!=NULL)//finds query in a string
	{
		for(i=0;i<(strlen(current->genre));i++)
		{
			for(j=i;j<(strlen(arry)+i);j++)
			{
				if(current->genre[j]==arry[j-i])
				{
					sum++;
				}
			}
			if(sum==strlen(arry))//if maches deletes movie
			{
				delete_movie(current,hl,hr);
				
			}
			sum=0;
		}
		current=current->rightp;
	}
	}
}

movie find_t(movie *hl, movie *hr)//finds a movie by title and asks for user rating
{
	char target[100];
	char answ3;
	movie *current=hl;
	
	printf("Enter title: ");
	scanf("%s",target);
	bubblesorttitle(hl,hr);
	
	while(current!=NULL)
	{
		if(strcmp(target,current->title)==0)//finds exact title
		{
			printf("%s\n",current->title);//prints all info
			printf("%s\n",current->director);	
			printf("%s\n",current->genre);
			printf("%d\n",current->duration);
			printf("%d\n",current->year);
			printf("%s\n",current->MPAA); 
			printf("%d\n",current->number_ratings);
			printf("%.2f\n",current->ave_rating);
			printf("would you like to add a user rating?(y/n): ");// prompts for user rating
			fflush(stdin);
			scanf("%c",&answ3);
			if(answ3=='y')
			{
				add_rating(current);
			}
			else
			{
			}
			current=current->rightp;
			
		}
		else
		{
			current=current->rightp;
		}
	}
	
}

movie find_d(movie *hl, movie *hr)//find movie by a specific director
{
	char target[100];
	movie *current=hl;
	
	printf("Enter director: ");
	scanf("%s",target);
	bubblesorttitle(hl,hr);
	
	while(current!=NULL)
	{
		if(strcmp(target,current->director)==0)//finds all movies by the director
		{
			printf("%s\n",current->title);
			printf("%.2f\n",current->ave_rating);
			current=current->rightp;//keeps going through the list once one is found untill hits end of list
			
		}
		else
		{
			current=current->rightp;
		}
	}
	
}

movie find_m(movie *hl, movie *hr)//finds a movie based on MPAA rating
{
	char target[100];
	movie *current=hl;
	
	printf("Enter MPAA rating: ");
	scanf("%s",target);
	bubblesorttitle(hl,hr);
	
	while(current!=NULL)
	{
		if(strcmp(target,current->MPAA)==0)
		{
			printf("%s\n",current->title);
			current=current->rightp;
			
		}
		else
		{
			current=current->rightp;
		}
	}
	
}

void find_g(movie *hl, movie *hr)//finds a movie based on genre
{
	char arry[30];
	bubblesorttitle(hl,hr);
	printf("enter genre: ");
	scanf("%s",arry);
	int sum=0,i,j;
	movie *current=hl;
	while(current!=NULL)//finds gere in string of multiple genres
	{
		for(i=0;i<(strlen(current->genre));i++)
		{
			for(j=i;j<(strlen(arry)+i);j++)
			{
				if(current->genre[j]==arry[j-i])
				{
					sum++;
				}
			}
			if(sum==strlen(arry))
			{
				print_rate(current);
				
			}
			sum=0;
		}
		current=current->rightp;
	}
}	

int main(void){
	char answ='a', answ2, answ3, answ4;
	int z;
	char export_dest[100];	//name of the export destination of the database
	
							//initial welcome message
	printf("*****************************************************************************\n");
	printf("\n\t\tWelcome to the Smiling Buddha Movie Database!\n\n");
	printf("\tCreated by: Hsi-En Hong, Kyle Larson, R. Ross Palmer, Thomas Schucker\n\n");
	printf("\t\t\tDate Completed: December 7th 2011\n\n");
	printf("*****************************************************************************\n");
	printf("When entering movie titles,directors,genres capitalize the first letter and\n"); 
	printf("Do NOT use spaces. When entering MPAA ratings use capital letters only and no '-'\n\n\n");
	
	//insert scan function to create linked list	
	
		FILE *inp,*inp2,*outp,*dummy;
		inp=fopen("movies.dat","r");
		movie *hl=NULL,*hr,*prev;
		
		while(!feof(inp))//while loop adds new membes to list
		{
			movie *temp;
			temp = (movie *)malloc(sizeof (movie));
			scan_fun(temp,inp);
			if( hl == NULL)
			{
				temp->leftp=NULL;
				temp->rightp=NULL;
				hl=temp;
				hr=temp;
				prev=temp;
				
			}
			else
			{
				temp->leftp=prev;
				prev->rightp=temp;
				temp->rightp=NULL;
				hr=temp;
				prev=temp;
				
			}
		}
		fclose(inp);
		
	
	printf("What would you like to do?\n\ta) Search the SBMD/Add user rating\n\tb) Sort movies(by title/director/ect.)\n\tc) See all movies inside the database\n\td) Export the database\n\te) Add/delete a movie\n\tf) Quit the SBMD :'(\n\n");
	
	scanf("%c", &answ);
	
	while(answ!='q'){		//basic menu for the program, prompts the user to the proper sub menu based on their initial response
		
		switch (answ){
		
			case 'a':
			case 'A':		//If the user chooses to SEARCH the movies in the database
				printf("You have chosen to search the SBMD. What do you want to search by?\n\ta)Title/Add rating\n\tb)Director\n\tc)Genre\n\td)Duration\n\te)Year\n\tf)MPAA rating\n\tg)Highest Buddha rating\n\th)Lowest Buddha rated\n");
				fflush(stdin);
				scanf("%c", &answ2);
					
					switch (answ2){
				
						case 'a':
						case 'A':	//searches for specfic titles
							find_t(hl,hr);
							//return ALL movies containing the keyword(s)
							break;
						
						case 'b':
						case 'B':	//searches for Director
							find_d(hl,hr);
							//call the search function with director name
							//return any movies that have that director
							break;
						
						case 'c':
						case 'C':	//searches for Genre
							find_g(hl,hr);
							//search movies by genre
							break;
							
						case 'd':
						case 'D':	//search for Duration
							find_dur(hl,hr);
							//return all movies with matching durations
							break;
						
						case 'e':
						case 'E':	//searches for movies in specific year
							find_y(hl,hr);
							//return all movies with matching years
							break;
							
						case 'f':
						case 'F':	//search for MPAA rating
							find_m(hl,hr);
							//return all movies by specified rating
							break;
						
						case 'g':	
						case 'G':	//searches for HIGHEST budda rating
							sort_nums(hl,hr);
							//call search function for the highest rated movie
							printf("The movie with the highest average Buddha rating is %s with %.2f Buddhas", hl->title, hl->ave_rating);
							//sort movies by rating, and return the HIGHEST rated movie
							break;
							
						case 'h':
						case 'H':	//searches for LOWEST buddha rating
							sort_nums(hl,hr);
							//call search function for lowest rated movie
							printf("The movie with the lowest average Buddha rating is %s with %.2f Buddhas", hr->title, hr->ave_rating);
							//sort movies by rating, return LOWEST rated movie
							break;
						
						default:
							printf("You have chosen an invalid option\n");
							break;
					}
				printf("would you like to do something else?\n\ta) Search the SBMD/Add user rating\n\tb) Sort movies(by title/director/ect.)\n\tc) See all movies inside the database\n\td) Export the database\n\te) Add/delete a movie\n\tf) Quit the SBMD :'(\n\n");
				fflush(stdin);
				scanf("%c",&answ);
				break;
			
			case 'b':
			case 'B':		//If the user chooses to SORT the movies in the database

				printf("You have chosen to sort the SBMD. What do you want to sort by?\n\ta)Title\n\tb)Genre\n\tc)Highest rated\n\td)Lowest rated\n\te)Back\n");
				fflush(stdin);
				scanf("%c", &answ2);
					
					switch (answ2){
					
						case 'a':
						case 'A':	//sort alphabetically by titles
							//call sort alphabetical sort function
							bubblesorttitle(hl,hr);
							print_list(hl);
							printf("\nDo you want to do anything else to this list? Such as delete a movie?(y/n)\n");
							fflush(stdin);
							scanf("%c", &answ3);
							
							if (answ3=='y'||answ3=='Y'){
								
								deletesm(hl,hr);
							}
							break;
							
						case 'b':
						case 'B':	//sort alphabetically by genre
							//same as title just switch title for genre inside function call function
							bubblesortgenre(hl,hr);
							print_listg(hl);
							printf("\nDo you want to do anything else to this list? Such as a mass delete?(y/n)\n");
							fflush(stdin);
							scanf("%c", &answ3);
							
							if (answ3=='y'){
								deletemg(hl,hr);
							}
							break;
							
						case 'c':
						case 'C':	//sort by highest rated
							//sort using an inequality
							
							sort_nums(hl,hr);
							print_list(hl);
							break;
							
						case 'd':
						case 'D':	//sort lowest rated
							//use same algorythm as highest budda rating, but print the lowest 
							
							sort_nums(hl,hr);
							print_list2(hr);
							break;
					}
				printf("would you like to do something else?\n\ta) Search the SBMD/Add user rating\n\tb) Sort movies(by title/director/ect.)\n\tc) See all movies inside the database\n\td) Export the database\n\te) Add/delete a movie\n\tf) Quit the SBMD :'(\n\n");
				fflush(stdin);
				scanf("%c",&answ);
				break;
			
			case 'c':
			case 'C':		//If the user chooses to SEE all the movies currently inside the database
				bubblesorttitle(hl,hr);
				z=1;
				print_list(hl);
				//print all movies inside the database
				printf("would you like to do something else?\n\ta) Search the SBMD/Add user rating\n\tb) Sort movies(by title/director/ect.)\n\tc) See all movies inside the database\n\td) Export the database\n\te) Add/delete a movie\n\tf) Quit the SBMD :'(\n\n");
				fflush(stdin);
				scanf("%c",&answ);
				break;
			
			case 'd':	//*********************CHECK TO MAKE SURE OPERATES CORRECTLY **********************
			case 'D':		//If the user chooses to EXPORT the data base
				
				printf("Export the database\n\n");
				printf("What file should the Smiling Buddha export to the database to? ");
				fflush(stdin);
				scanf("%s", export_dest);
				
				
					FILE *open_movies;		//opening movies.dat for writing
					open_movies=fopen(export_dest, "w");
					bubblesorttitle(hl,hr);
					print_list1(hl,open_movies);
					fclose(open_movies);	//closing movies .dat	
				
				printf("would you like to do something else?\n\ta) Search the SBMD/Add user rating\n\tb) Sort movies(by title/director/ect.)\n\tc) See all movies inside the database\n\td) Export the database\n\te) Add/delete a movie\n\tf) Quit the SBMD :'(\n\n");
				fflush(stdin);
				scanf("%c",&answ);
				break;
			
			case 'e':
			case 'E':		//If the user chooses to ADD/DELETE movies to the database
				
				printf("Do you want to add or delete movies?\n\ta)add\n\tb)delete\n\tc)mass delete\n\n");
				fflush(stdin);
				scanf("%c", &answ2);
				
				if(answ2=='a'){
					printf("You have chosen to add a movie to Smiling Buddha");
					add_movie(hr,hl,hr);
					//call add movie function
				}else if(answ2=='b' || answ2=='B'){
					deletesm(hl, hr);
					//call the delete single movie function
				}else if(answ2=='c' || answ2=='C')
				{
					printf("You have chosen to mass delete movies. Do you want to delete all movies in the database? (y/n)\n");
					fflush(stdin);
					scanf("%c", &answ3);
					if(answ3=='y' || answ3=='Y'){
						printf("Are you sure that you want to delete all movies inside the database?(y/n)\n");
						fflush(stdin);
						scanf("%c", &answ4);
						if(answ4=='y'){
							hl=NULL;
							hr=NULL;
							FILE *p=fopen("movies.dat","w");
							fclose(p);
						}
						//call mass delete function
					}
					else if(answ3=='n' || answ3=='N')
					{
						
					}
					else
					{
						printf("You have chosen an invalid option, please try again.\n");
						scanf("%c", &answ3);
					}
				}
				else{
					printf("You have chosen an invalid option\n\n");
					printf("Do you want to add or delete movies?\n\ta)add\n\tb)delete\n\tc)mass delete\n\n");
					fflush(stdin);
					scanf("%c", &answ2);
					
				}
				printf("would you like to do something else?\n\ta) Search the SBMD/Add user rating\n\tb) Sort movies(by title/director/ect.)\n\tc) See all movies inside the database\n\td) Export the database\n\te) Add/delete a movie\n\tf) Quit the SBMD :'(\n\n");
				fflush(stdin);
				scanf("%c",&answ);
				break;
			
			case 'f':
			case 'F':		//If the user chooses to EXIT the database
				
				answ='q';
				break;
			
			default:		//If the  user chooses an invalid option
				
				printf("You have chosen an invalid option. please select again.\n");
				fflush(stdin);
				scanf("%c", &answ);
				break;
		}
	}
	
	FILE *open_movie;
	open_movie=fopen("movies.dat", "w");
	print_list1(hl,open_movie);
	fclose(open_movie);
	//MAKE SURE TO EXPORT TO MOVIES.DAT BEFORE EXITING aka SAVE
	printf("You have selected to exit the SBMD :'( . Please use us again soon.\n");
	
	return(0);
}


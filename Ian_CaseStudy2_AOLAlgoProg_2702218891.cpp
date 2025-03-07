#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//The structure used to hold all the data from the file.
//All of it uses strings, but some number based data are converted when used as such.
typedef struct{
	char location[30];
	char city[30];
	char price[20];
	char rooms[10];
	char bathrooms[10];
	char carpark[10];
	char type[20];
	char furnish[20];
} info;

//Declares menuSelect first so all subsequent functions can call it.
void menuSelect(info data[], int line_count);

//This is a function to print the table header, so all the titles are there.
//Used whenever there is a function requiring the table header to be printed to console.
void printHeader(){
	//The character limit is matched based on the file based on strlen + 1 (except in cases where the table header exceeds the strlen of the data).
	printf("Location                  "); //26 characters, prints location column header.
	printf("City         "); //13 characters, prints city column header.
	printf("Price    "); //9 characters, prints price column header.
	printf("Rooms "); //6 characters, prints rooms column header.
	printf("Bathroom "); //9 characters, prints bathroom column header.
	printf("Carpark "); //8 characters, prints carpark column header.
	printf("Type      "); //10 characters, prints type column header.
	printf("Furnish\n"); //Prints furnish column header.
}

//This is a function to print the lines within the table, consituting data from the file.
//Used whenever there is a function requiring the data to be printed to console.
void printData(info data[], int i){
	//The character limit is matched based on the file based on strlen + 1 (except in cases where the table header exceeds the strlen of the data).
	printf("%-26s", data[i].location); //Prints location and append with spaces until 26 characters.
	printf("%-13s", data[i].city); //Prints city and append with spaces until 13 characters.
	printf("%-9s", data[i].price); //Prints price and append with spaces until 9 characters.
	printf("%-6s", data[i].rooms); //Prints rooms and append with spaces until 6 characters.
	printf("%-9s", data[i].bathrooms); //Prints bathrooms and append with spaces until 9 characters.
	printf("%-8s", data[i].carpark); //Prints carpark and append with spaces until 8 characters.
	printf("%-10s", data[i].type); //Prints type and append with spaces until 10 characters.
	printf("%s\n", data[i].furnish); //Prints furnish.
}

//Function for swapping between elements of array of structure (in this case, info data[]).
//Used in c) SortBy, this is a function used within the sorting process.
void swap(info *a, info *b){
	info temp; 
	//Memcpy is used to copy the data per the memory size of structure "info".
	memcpy(&temp, a, sizeof(info));
	memcpy(a, b, sizeof(info));
	memcpy(b, &temp, sizeof(info));
	
}

//Function to compare if the column specified is labelled as such (i.e. Location, Price, etc.).
//The edge case of "column" not being any of these is already caught in c) SortBy (the sorting function), so no need to check it here.
//Works by returning the value of comparison (strcmp) between two strings back to the sorting process.
//This function is used during c) SortBy, in the sorting process.
int compareSort(info *a, info *b, char column[]){
	//Matches with column to check specified column.
	if(strcmp(column, "Location") == 0) return strcmp(a->location, b->location);
    else if(strcmp(column, "City") == 0) return strcmp(a->city, b->city);
    else if(strcmp(column, "Price") == 0) return strcmp(a->price, b->price);
    else if(strcmp(column, "Rooms") == 0) return strcmp(a->rooms, b->rooms);
    else if(strcmp(column, "Bathroom") == 0) return strcmp(a->bathrooms, b->bathrooms);
    else if(strcmp(column, "Carpark") == 0) return strcmp(a->carpark, b->carpark);
    else if(strcmp(column, "Type") == 0) return strcmp(a->type, b->type);
    else if(strcmp(column, "Furnish") == 0) return strcmp(a->furnish, b->furnish);
    return 0;
}

//Function as a part of Quick Sorting; a partition used to seperate the sorted data and unsorted data via a pivot.
//Pretty much follows what a generic partition function looks like normally.
//This is the partition function if the user chooses the "ascending" sorting method.
//This function is used during c) SortBy, in the sorting process.
int partitionAsc(info data[], int left, int right, char column[], int line_count){
	//Pivot is typed as a structure pointer info* to make it store &data[right].
	info *pivot = &data[right];
	int i = left;
	//The following checks for the number based data, such as price, rooms, bathroom, and carpark.
	//This is because strcmp is unable to differentiate between power of tens. (ex. In strlen, 999999 is bigger than 1000000).
	if(strcmp(column, "Price") == 0 || strcmp(column, "Rooms") == 0 || strcmp(column, "Bathroom") == 0 || strcmp(column, "Carpark") == 0){
		for(int j = left; j < line_count; j++){
			int a, b;
			if(strcmp(column, "Price") == 0){
				a = atoi(data[j].price); //atoi() is a function from strlib.h used to convert string to integer.
				b = atoi(pivot->price);
			}
			else if(strcmp(column, "Rooms") == 0){
				a = atoi(data[j].rooms);
				b = atoi(pivot->rooms);
			}
			else if(strcmp(column, "Bathroom") == 0){
				a = atoi(data[j].bathrooms);
				b = atoi(pivot->bathrooms);
			}
			if(strcmp(column, "Carpark") == 0){
				a = atoi(data[j].carpark);
				b = atoi(pivot->carpark);
			}
			//Actual integer swap check.
			if(a < b){ //Main difference: <, which allows it to sort ascendingly.
				swap(&data[i], &data[j]);
				i++;
			}
		}
	}
	//Here's where all the string swap checks go (using strcmp through the function).
	else{
		for(int j = left; j < line_count; j++){
			//Jams the following to compareSort, where it returns the strcmp of &data[j] and pivot.
			if(compareSort(&data[j], pivot, column) < 0){ //Main difference: <, which allows it to sort ascendingly.
				swap(&data[i], &data[j]);
				i++;
			}
		}
	}
	swap(&data[i], pivot);
	return i;
}

//Function as a part of Quick Sorting; a partition used to seperate the sorted data and unsorted data via a pivot.
//Pretty much follows what a generic partition function looks like normally.
//This is the partition function if the user chooses the "descending" sorting method.
//This function is used during c) SortBy, in the sorting process.
int partitionDesc(info data[], int left, int right, char column[], int line_count){
	//Pivot is typed as a structure pointer info* to make it store &data[right].
	info *pivot = &data[right];
	int i = left;
	//The following checks for the number based data, such as price, rooms, bathroom, and carpark.
	//This is because strcmp is unable to differentiate between power of tens. (ex. In strlen, 999999 is bigger than 1000000).
	if(strcmp(column, "Price") == 0 || strcmp(column, "Rooms") == 0 || strcmp(column, "Bathroom") == 0 || strcmp(column, "Carpark") == 0){
		for(int j = left; j < line_count; j++){
			int a, b;
			if(strcmp(column, "Price") == 0){
				a = atoi(data[j].price); //atoi() is a function from strlib.h used to convert string to integer.
				b = atoi(pivot->price);
			}
			else if(strcmp(column, "Rooms") == 0){
				a = atoi(data[j].rooms);
				b = atoi(pivot->rooms);
			}
			else if(strcmp(column, "Bathroom") == 0){
				a = atoi(data[j].bathrooms);
				b = atoi(pivot->bathrooms);
			}
			if(strcmp(column, "Carpark") == 0){
				a = atoi(data[j].carpark);
				b = atoi(pivot->carpark);
			}
			//Actual integer swap check.
			if(a > b){ //Main difference: >, which allows it to sort descendingly.
				swap(&data[i], &data[j]);
				i++;
			}
		}
	}
	//Here's where all the string swap checks go (using strcmp through the function).
	else{
		for(int j = left; j < line_count; j++){
			//Jams the following to compareSort, where it returns the strcmp of &data[j] and pivot.
			if(compareSort(&data[j], pivot, column) > 0){ //Main difference: >, which allows it to sort descendingly.
				swap(&data[i], &data[j]);
				i++;
			}
		}
	}
	swap(&data[i], pivot);
	return i;
}

//Function to Quick Sort the data in its entirety.
//Follows what a generic quick sort function looks like.
//This function is used during c) SortBy, in the sorting process.
void quickSort(info data[], int left, int right, char updown[], int line_count, char column[]){
	if(left >= right) return; //Checks if left >= right, and if so, no need to sort anymore.
	
	int p;
	//If the user chose the "ascending" sorting method, set p as partitionAsc, the partition using the ascending sort.
	if(strcmp(updown, "asc") == 0){
		p = partitionAsc(data, left, right, column, line_count);
	}
	//If the user chose the "descending" sorting method, set p as partitionDesc, the partition using the descending sort.
	else if(strcmp(updown, "desc") == 0){
		p = partitionDesc(data, left, right, column, line_count);
	} 
	//If updown (user choice) does not fall under asc or desc, display error message and return to menu.
	else{
		printf("Invalid sorting method!\n");
		printf("Returning to menu...\n");
		puts("");
		menuSelect(data, line_count);
	}
	//Quick sort procedure to cover all segmented partitions.
	quickSort(data, left, p-1, updown, line_count, column);
	quickSort(data, p+1, right, updown, line_count, column);
}

//a) Display
//This is a function used to display the data in a table per the number of rows required.
//Works by just printing the specified amount of data per line/row.
void dataDisplay(info data[], int line_count){
	//Asks user for number of rows to display.
	int rows;
	printf("Number of rows: ");
	scanf("%d", &rows);
	puts("");
	
	//If the user inputs a number larger than the number of lines within the file,
	//set the rows to the line count negated by 1. In essence, it just allows the function to print everything in the file.
	if(rows >= line_count) rows = line_count-1;
	
	//Calls the function printHeader function to print the table header.
	//This works on display, but to prevent automatic text wrapping on console, need to configure the .exe to see.
	//To do this, click the title bar > properties > layout > screen buffer size.
	printHeader();
	
	//Repeats the printing of data until the final row of data requested is reached.
	for(int i = 1; i < rows+1; i++){
		//Calls the function printData to print the line of data.
		printData(data, i);
	}
	
	//Returns back to the menu selection.
	puts("");
	menuSelect(data, line_count);
}

//b) SelectRow (Searching)
//This function searches a specific column (inputted by the user) for a specified data (inputted by the user), 
//then displays all data with the matching criteria.
//Works by matching the query of the user with available column and data, then displays the results.
void dataSearch(info data[], int line_count){
	//Inputs which column to search data in.
	char column[8] = {};
	printf("Columns: Location, City, Price, Rooms, Bathroom, Carpark, Type, Furnish\n"); //Handy note for selection.
	printf("Choose column: ");
	scanf("%s", &column);

	//Checks if the column is valid or not. If not, returns to menu.
	if(strcmp(column, "Location") != 0 
	&& strcmp(column, "City") != 0 
	&& strcmp(column, "Price") != 0 
	&& strcmp(column, "Rooms") != 0 
	&& strcmp(column, "Bathroom") != 0 
	&& strcmp(column, "Carpark") != 0 
	&& strcmp(column, "Type") != 0 
	&& strcmp(column, "Furnish") != 0){
		printf("Column invalid!\n");
		printf("Returning to menu...\n");
		puts("");
		menuSelect(data, line_count);
	}
	
	//Inputs which data to find in the column specified.
	char search_value[30] = {};
	printf("What data do you want to find? ");
	scanf("%s", &search_value);
	
	//A char pointer to point towards the data specified later.
	//Doesn't use structure pointer because we only need one piece of data from the structure.
	char *str_ptr;
	
	//header_state variable to print the header once if data is found.
	char header_state = '1';
	for(int i = 1; i < line_count; i++){
		//A check to update str_ptr.
		//Again, we only need one data to compare so no need to jam it into a function (and using return like in sorting).
		if(strcmp(column, "Location") == 0) str_ptr = data[i].location;
		else if(strcmp(column, "City") == 0) str_ptr = data[i].city;
		else if(strcmp(column, "Price") == 0) str_ptr = data[i].price;
		else if(strcmp(column, "Rooms") == 0) str_ptr = data[i].rooms;
		else if(strcmp(column, "Bathroom") == 0) str_ptr = data[i].bathrooms;
		else if(strcmp(column, "Carpark") == 0) str_ptr = data[i].carpark;
		else if(strcmp(column, "Type") == 0) str_ptr = data[i].type;
		else if(strcmp(column, "Furnish") == 0) str_ptr = data[i].furnish;
		
		//If there a line of data matching, print the header, then print the data following that.
		//As this is a loop, if the header is already printed, it doesn't print anymore.
		if(strcmp(str_ptr, search_value) == 0){
			if(header_state == '1'){
				printf("Data found. Detail of data:\n");
				puts("");
				printHeader(); //Calls the function printHeader function to print the table header.
				header_state = '0'; //Sets the header_state to '0' to ensure the header is printed 1 time only.
			}
			//Calls the function printData to print the line of data.
			printData(data, i);
		}
	}
	
	//If the header_state is not changed (read: no matching data), then display that data is not found and return to menu selection.
	if(header_state == '1'){
		printf("Data not found!\n");
		printf("Returning to menu...\n");
	}
	
	//Returns back to the menu selection.
	//If data is not found, just immediately proceed here.
	puts("");
	menuSelect(data, line_count);
}

//c) SortBy (Sorting)
//This is a function to sort the stored data in the structure imported from the file according to the specified column and sorting method.
//It works by sorting the data per the specified column, and then swapping the afformentioned data recursively according to the sorting method.
void dataSort(info data[], int line_count){
	//If there is nothing on the file, then line_count is 0. Ergo, data not found.
	if(line_count == 0){
		printf("Data not found!\n");
		printf("Returning to menu...\n");
		puts("");
		menuSelect(data, line_count);
	}
	
	//Inputs which column to search data in.
	char column[8] = {};
	printf("Columns: Location, City, Price, Rooms, Bathroom, Carpark, Type, Furnish\n"); //Handy note for selection.
	printf("Choose column: ");
	scanf("%s", &column);
	
	//Check if column is valid or not. If not, returns to menu.
	if(strcmp(column, "Location") != 0 
	&& strcmp(column, "City") != 0 
	&& strcmp(column, "Price") != 0 
	&& strcmp(column, "Rooms") != 0 
	&& strcmp(column, "Bathroom") != 0 
	&& strcmp(column, "Carpark") != 0 
	&& strcmp(column, "Type") != 0 
	&& strcmp(column, "Furnish") != 0){
		printf("Column invalid!\n");
		printf("Returning to menu...\n");
		puts("");
		menuSelect(data, line_count);
	}
	
	//Inputs the sorting method, whether it's ascending or descending.
	char updown[4] = {};
	printf("Sort ascending (asc) or descending (desc)? ");
	scanf("%s", &updown);
	
	//Calls quickSort, a function to sort the data from row 1 to the final row.
	quickSort(data, 1, line_count-1, updown, line_count, column);
	
	//Obviously, since the state of "no data" was already checked before, no need to check it here.
	printf("Data found. Detail of data:\n");
	puts("");
	//Calls the function printHeader function to print the table header.
	printHeader();
	//Prints a view of the data (10 rows), by calling the printData function.
	for(int i = 1; i < 11; i++){
		printData(data, i);
	}
	
	//Returns back to menu selection.
	puts("");
	menuSelect(data, line_count);
}

//d) Export
//This is a function to export the stored data in the structure to a user named .csv file.
//It works by taking the data and writing it to a file line per line.
void dataExport(info data[], int line_count){
	//Inputs file name.
	char file_name[35] = {};
	printf("File name: ");
	scanf("%[^\n]", &file_name);
	//Appends the file name with .csv, so the file is recognized as such.
	strcat(file_name, ".csv");
	
	//Opens a new file in write mode with the file name, then copies all the stored data from the info structure into the user-named file.
	FILE* fp = fopen(file_name, "w");
	
	//Prints everything (per line) in the array of structure to the file.
	for(int i = 0; i < line_count; i++){
		fprintf(fp, "%s,", data[i].location);
		fprintf(fp, "%s,", data[i].city);
		fprintf(fp, "%s,", data[i].price);
		fprintf(fp, "%s,", data[i].rooms);
		fprintf(fp, "%s,", data[i].bathrooms);
		fprintf(fp, "%s,", data[i].carpark);
		fprintf(fp, "%s,", data[i].type);
		fprintf(fp, "%s\n", data[i].furnish);
	}
	
	//Closes the file, since we don't need it anymore.
	fclose(fp);
	
	//Obviously, even if there is nothing stored in the structure (and thus the file it read from),
	//'\0' or absolutely nothing is printed into the file in that regard (the file it read from is blank, for example). 
	//But it still prints from the structure into the file even if it's empty, so no need for an error message here.
	//Well, the case above shouldn't happen anyway, since the file is preloaded before any actions can be taken on the menu.
	
	//Prints that data is successfully written to the user-named file.
	printf("Data successfully written to file %s!\n", file_name);
	
	//Returns back to menu selection.
	puts("");
	menuSelect(data, line_count);
}

//This is a function functioning as a menu, to select what the program will do within the menu, 
//and serves as a hub to return to after a task is completed.
void menuSelect(info data[], int line_count){
	//Just prints the menu display.
	printf("What do you want to do?\n");
	printf("1. Display Data\n");
	printf("2. Search Data\n");
	printf("3. Sort Data\n");
	printf("4. Export Data\n");
	printf("5. Exit\n");
	printf("Your choice: ");
	
	//Scans for menu selection.
	int choice;
	scanf("%d", &choice); getchar();
	
	switch(choice){
		case 1: //Displays data according to number of rows. Calls dataDisplay.
			dataDisplay(data, line_count);
			break;
		case 2: //Searches data based on specified criteria. Calls dataSearch.
			dataSearch(data, line_count);
			break;
		case 3: //Sorts data based on specified criteria. Calls dataSort.
			dataSort(data, line_count);
			break;
		case 4: //Exports the data to a user-named file. Calls dataExport.
			dataExport(data, line_count);
			break;
		case 5: //Exits the program.
			printf("Exiting the program...\n");
			exit(0);
			break;
		default: //Just in case of edge cases, for invalid choices only.
			printf("Invalid choice!\n");
			printf("Returning to menu...\n");
			puts("");
			menuSelect(data, line_count);
	}
}

//This is the main function, the first function the program starts in and the final function
//returned to after the program is exited.
int main(){
	//Opens the file (file.csv) and scans the entire file to store the data in a structure.
	FILE* fp = fopen("file.csv", "r");
	
	//Gets how many lines the file has, until the end of the file.
	int line_count = 0;
	while(!feof(fp)){
		char scan_char = fgetc(fp);
		if(scan_char == '\n') line_count++; //When it encounters a '\n', adds to line count. Should result in 3940.
	}
	//Sets the file pointer back to the start, just in case.
	rewind(fp);
	
	//Creates an array of structure called data[]. Data itself should range from 0 to 3939. 
	//Element 0 is unusable, because it doesn't actually contain any data.
	info data[line_count];
	
	//Reads all the data from the file, and stores them accordingly.
	for(int i = 0; i < line_count; i++){
		fscanf(fp, "%[^,]", data[i].location); fgetc(fp);
		fscanf(fp, "%[^,]", data[i].city); fgetc(fp);
		fscanf(fp, "%[^,]", data[i].price); fgetc(fp);
		fscanf(fp, "%[^,]", data[i].rooms); fgetc(fp);
		fscanf(fp, "%[^,]", data[i].bathrooms); fgetc(fp);
		fscanf(fp, "%[^,]", data[i].carpark); fgetc(fp);
		fscanf(fp, "%[^,]", data[i].type); fgetc(fp);
		fscanf(fp, "%[^\n]", data[i].furnish); fgetc(fp);
	}	
	
	//Closes the file, as we don't need it anymore.
	fclose(fp);
	
	//Displays the menu for first time, thus calling menuSelect.
	//If exit or an invalid number is selected, the program ends.
	menuSelect(data, line_count); 
	
	return 0;
}

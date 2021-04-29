#include <iostream>
#include <fstream>
#include <string> 
using namespace std;
//input name of board and directory
string board;
string folder;
//Initialize the interation counter variable
int i=0;
 

void print(int arr[9][9])
{
    for (int i = 0; i < 9; i++) 
    {
        if(i % 3 == 0)
			cout<<"-------+------+-------"<<endl;
        for (int j = 0; j < 9; j++){
            if(j % 3 == 0)
				cout<<"|";
            cout << arr[i][j] << " ";
           }
        cout<<"|"<<endl;
    }
    cout<<"-------+------+-------"<<endl;
}
 
// Checks whether the given row, col are in safe state
bool isSafe(int grid[9][9], int row, int col, int num)
{
    if (grid[row][col] != 0) return false;
	bool status = true;
	//get starting index of 3x3 subgrids
	int gridx = (col / 3) * 3;
	int gridy = (row / 3) * 3;
	// check if number is already in the row, col or 3x3 subgrid
	for (int i = 0; i < 9; i++) {
        // check full row for num
		if (grid[row][i] == num) { 
            status = false; 
            break; 
        }
        // check full col for num
		if (grid[i][col] == num) { 
            status = false; 
            break; 
        }
		//will go from (0,0) index to (2,2) index in subgrid 
		if (grid[gridy + i / 3][gridx + i % 3] == num) { 
            status = false; 
            break; 
        }
	}
    // return if valid
	return status;
}
 
//Backtracking
bool solveSuduko(int grid[9][9], int row, int col)
{
    //increment the iteration counter
    i++;
    if(i%100 == 0){
    system("clear");
    print(grid);
    // cout << i ;
    system("clear");
    
    }
    // Check if we have reached the 8th  row and 9th column (0 indexed matrix) , we are returning true to avoid further backtracking
    if (row == 8 && col == 9)
      return true;
 
    // Check if column value  becomes 9 , we move to next row and column start from 0
    if (col == 9) {
        row++;
        col = 0;
    }
   
    // Check if the current position of the grid already contains value >0, we iterate for next column
     if (grid[row][col] > 0)
         return solveSuduko(grid, row, col + 1); 
 
     for (int num = 1; num <= 9; num++) 
     {
         
        // Check if it is safe to place the num (1-9)  in the given row ,col  ->we  move to next column
        if (isSafe(grid, row, col, num)) 
        {
             
           // Assigning the num in the current (row,col) position of the grid and assuming our assined num in the position is correct     
            grid[row][col] = num;
           
            //  Checking for next possibility with next column
            if (solveSuduko(grid, row, col + 1))
                return true;
        }
       
        // Removing the assigned num , since our assumption was wrong , and we go for next assumption with diff num value
        grid[row][col] = 0;
    }
    return false;
}

//Main fucntion with UI
int main()
{   
  
    int choice;
    cout << "+-----------------------------------------------+" << endl;
    cout << "|             Welcome to Sudoku Solver          |" << endl ;
    cout << "|----------------Select an option:--------------|"<< endl ;
    cout << "| 1. List available sudoku board                |"<< endl ;
    cout << "| 2. Manually enter 81 values ofr 9x9 board     |"<< endl ;
    cout << "| 3. To exit or Ctrl + z anytime to terminate   |"<< endl ;
    cout << "+-----------------------------------------------+" << endl;
    while(true){
    cin >> choice;
    switch(choice){

    case 1:{
        cout <<  "+--------------------------------------------------------------+" << endl;
        cout <<  "| To add your own Sudoku Matrix add it to /'All boards' folder |" << endl ;
        cout <<  "|               Choose The difficuly level of board            |" << endl;
         cout << "+--------------------------------------------------------------+" << endl;
        menu:
        cout << "Currently available board directories"<< endl ;
        cout << "+-----------------+" << endl;
       // cout << system("ls ./boards");
        cout << system("ls ./'All boards'");
        cout << "-----------------+" << endl;
        cin >> folder;
        if(folder == "easy" || folder == "Easy")
        {
             cout << "+------------------------+" << endl;            
             cout << system("ls ./'All boards'/Easy");
             cout << "+-----------------------+" << endl;
        }
        else if(folder == "medium" || folder == "Medium")
        {
             cout << "-------------------------" << endl;
             cout << system("ls ./'All boards'/Medium");
             cout << "-------------------------" << endl;
        }
        else if(folder == "hard" || folder == "Hard")
        {
             cout << "-------------------------" << endl;
             cout << system("ls ./'All boards'/Hard");
             cout << "-------------------------" << endl;
       }

        //cout << endl << endl ;
        cout << "+------------------------------------------------------------+" << endl;
        cout << "|          Choose a board file with .txt extension           |" << endl ;
        cout << "+------------------------------------------------------------+" << endl;
        cin >> board ;
        int grid[9][9];
        ifstream data;
         
        data.open("boards/"+board);
            for( int i=0;i<9;i++){
                 for(int j=0;j<9;j++){
                    data >> grid[i][j];
                   // cout << grid[i][j];
       }
     // cout << endl;
   }
   data.close();
       
    for (int i = 0; i < 9; i++) 
    {
        if(i % 3 == 0)
			cout<<"-------+------+-------"<<endl;
        for (int j = 0; j < 9; j++){
            if(j % 3 == 0)
				cout<<"|";
            cout << grid[i][j] << " ";
       
    
        }
        cout<<"|"<<endl;
    }
   cout<<"-------+------+-------"<<endl << endl ;
   cout <<"+--------------------------------------------------------------+" << endl;   
   cout <<"|                   This is the input board                     |" << endl ;
   cout <<"|                       Enter c to solve                        |"<< endl ;
   cout <<"+---------------------------------------------------------------+" << endl; 
     
    char keystroke ;
    cin >> keystroke;
    if(keystroke =='c')
    {
    if (solveSuduko(grid, 0, 0))
        print(grid);
    else 
        cout << "no solution  exists " << endl; 
   
   cout << endl ;
   cout << i << " Iterations"<< endl ;
   cout << endl ;
   cout <<"+--------------------------------------------------------------+" << endl;   
   cout <<"|                Press c to solve another board                |" << endl ;
   cout <<"|                     Ctrl + z to terminate                    |"<< endl ;
   cout <<"+--------------------------------------------------------------+" << endl; 
   char key2;
   cin >> key2;
   if(key2=='c'){ goto menu; }
   else{ break; }
       
    } 
   }
     break;
    case 2: 
     menu2:
         int grid[9][9];
                       cout<<"enter 9 x 9 Grid(Use 0 for empty)"<<endl;
                       for(int i=0;i<9;i++){
                       	for(int j=0;j<9;j++){
                       		cout<<"Enter values for["<<i<<"]["<<j<<"]"<<" : ";
                       		cin>>grid[i][j];
						   }
					
					   }
            for (int i = 0; i < 9; i++) 
            {
                if(i % 3 == 0)
			        cout<<"-------+------+-------"<<endl;
                        for (int j = 0; j < 9; j++){
                            if(j % 3 == 0)
				                cout<<"|";
                                cout << grid[i][j] << " ";
                            }
                                cout<<"|"<<endl;

            }
			 if (solveSuduko(grid, 0, 0))
             print(grid);
                else
            cout << "no solution  exists " << endl; 
   
             cout << endl ;
             cout << i << " iterations"<< endl ;
             cout << endl ;   
             cout <<("Press c to solve another board ") << endl ;
             cout << "3. Ctrl + z to terminate "<< endl ;
             char key2;
             cin >> key2;
             if(key2=='c'){ goto menu; }
             else if(key2== 'r'){  goto menu2; }
             break;		
          
        break;
      }
    
    } 

}

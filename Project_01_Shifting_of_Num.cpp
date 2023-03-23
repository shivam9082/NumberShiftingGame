#include<iostream>
#include<unistd.h>
#include <termios.h>
#define STDIN_FILENO 0
using namespace std;
void game_Rules()
{
   cout<<"                              MATRIX PUZZLE"<<endl<<endl;
    cout<<"\033[0;31m"<<"                             RULES OF THIS GAME"<<endl<<endl;
    cout<<"\033[0;31m"<<"1.You can move only 1 step at a time by arrow key"<<endl;
    cout<<"\033[1;37m"<<"          Move Up  : by Up arrow key"<<endl;
    cout<<"\033[1;37m"<<"          Move Down : by Down arrow key"<<endl;
    cout<<"\033[1;37m"<<"          Move Right : by Right arrow key"<<endl;
    cout<<"\033[1;37m"<<"          Move Left : by Left arrow key"<<endl;
    cout<<"\033[0;31m"<<"2.You can move number at empty position only"<<endl<<endl;
    cout<<"\033[0;31m"<<"3. For each valid move : your total number of move will decrease by 1"<<endl;
    cout<<"\033[0;31m"<<"4. Winning Situation : Number in a 4*4 matrix should be in order from 1 to 15"<<endl<<endl;
    cout<<"\033[1;37m"<<"                  Winning Situation :"<<endl;
    int k=0,num=1;
    int arr[4][4] = { {1,2,3,4},
                     {5,6,7,8},
                     {9,10,11,12},
                     {13,14,15,' '}
    };
    for(int i=1;i<=22;i++)
      cout<<"-";
    cout<<endl;
    for(int i=0;i<4;i++)
    {
      for(int j=0;j<4;j++)
      {
        if(arr[i][j]>9 && arr[i][j]<=15)
         cout<<"\033[1;33m"<<"| "<<arr[i][j]<<" ";
        else if(arr[i][j]<=9)
         cout<<"\033[1;33m"<<"|  "<<arr[i][j]<<" ";
        else
         cout<<"|  "<<char(arr[i][j])<<" ";
      }
      cout<<"\033[1;33m"<<" |"<<endl;
    }
    for(int i=1;i<23;i++)
     cout<<"\033[1;37m"<<"-";
    cout<<endl<<endl;
    cout<<"\033[1;37m"<<"5. You can exit the game at any time by pressing 'E' or 'e'"<<endl;
    cout<<"So Try to win in minimum no of move"<<endl<<endl;
    cin.ignore();
    cout<<"\033[0;37m"<<"Press "<<"\033[1;37m"<<"ENTER"<<"\033[0;37m"<<" key to start..."<<endl;
    //system("read");
    cin.get();
}

void matrix(int a[16],int m[4][4])
{
  int new_random,min=0,max=15,k=0;
  bool f;
  srand(time(NULL) * getpid());
  int b[16];
  for(int i=0;i<16;i++)
   {
    do
    {
      new_random = (rand() % (max-min+1)) + min;
      f=true;
      for(int j=0;j<i;j++)
       if(b[j]==new_random)
        f=false;
    } while (!f);
    
     b[i] = new_random;
   }
   
   for(int i=0;i<4;i++)
   {
    for(int j=0;j<4;j++)
    {
      m[i][j] = a[b[k]];
      k++;
    }
   }
   }

void show_matrix(int m[4][4])
   {
    for(int i=0;i<22;i++) 
    cout<<"-";
   cout<<endl;
   for(int i=0;i<4;i++)
   {
    for(int j=0;j<4;j++)
     {
       if(m[i][j]<=9)
        cout<<"|  "<<m[i][j]<<" ";
       else if(m[i][j]>9 && m[i][j]<16)
        cout<<"| "<<m[i][j]<<" ";
       else
        cout<<"|  "<<char(m[i][j])<<" ";
     }
     cout<<"|"<<endl;
   }
   for(int i=0;i<22;i++)
    cout<<"-";
   cout<<endl;
   }

int read_key()
{
  // Black magic to prevent Linux from buffering keystrokes.
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

// Once the buffering is turned off, the rest is simple.
    //cout << "Enter a character: ";
    char c,d,e;
    cin >> c;
    if(c =='e' || c =='E')
     return (int)c;
    cin >> d;
    cin >> e;
    //cout << "\nYour character was ";
// Using 3 char type, Cause up down right left consist with 3 character
    if ((c==27)&&(d=91)) {
        return (int)e;
    }
    else
    return 0;
}

void shift_up(int m[4][4])
{
  int f=0;
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++)
    {
      if(m[i][j] == 32 && i+1 < 4 )
      {
         int temp = m[i][j];
         m[i][j] = m[i+1][j];
         m[i+1][j] = temp;
         f=1;
         break;
      }
    }
    if(f==1)
     break;
  }
}

void shift_down(int m[4][4])
{
 int f=0;
 for(int i=0;i<4;i++)
 {
  for(int j=0;j<4;j++)
  {
    if(m[i][j]==32 && i>0)
    {
      int temp = m[i][j];
      m[i][j] = m[i-1][j];
      m[i-1][j] = temp;
      f=1;
      break;
    }
  }
  if(f==1)
   break;
 }
}

void shift_left(int m[4][4])
{
  int f=0;
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++)
    {
      if(m[i][j] == 32 && j<4)
      {
        int temp = m[i][j];
        m[i][j] = m[i][j+1];
        m[i][j+1] = temp;
        f=1;
        break;
      }
    }
    if(f==1)
     break;
  }
}

void shift_right(int m[4][4])
{
  int f=0;
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++)
    {
      if(m[i][j]==32 && j>-1)
      {
        int temp = m[i][j];
        m[i][j] = m[i][j-1];
        m[i][j-1] = temp;
        f=1;
        break;
      }
    }
    if(f==1)
     break;
  }
}

bool winner(int m[][4])
{
  int check_m[4][4] = { {1,2,3,4},
                         {5,6,7,8},
                         {9,10,11,12},
                         {13,14,15,' '}

  },j;
  for(int i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      if(check_m[i][j] != m[i][j])
        return false;
    }
  }
  if(j==4)
   return true;
return false;
}

int main()
{
   int arr[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,' ' } ;
   int mat[4][4],exit=0,move_exit=0;
  string player_name;
  int input;
  int move_number=5;
  cout<<"Player Name : "<<endl;
  fflush(stdin);
  cin>>player_name;
  system("clear");
  game_Rules();
  system("clear");
  cout<<"Player Name : "<<player_name<<" , "<<" Move Remaining : "<<move_number<<endl<<endl<<endl;
  matrix(arr,mat);
  while(true)
  {
    show_matrix(mat);
    while(!winner(mat))
    {
     int n;
     n = read_key();
     if(move_number==0)
     {
      system("clear");
      move_exit=1;
      cout<<"Player Name : "<<player_name<<" , "<<" Move Remaining : "<<move_number<<endl<<endl<<endl;
      show_matrix(mat);
      break;
     }
     move_number--;
     switch(n)
     {
      case 65 :
       system("clear");
       cout<<"Player Name : "<<player_name<<" , "<<" Move Remaining : "<<move_number<<endl<<endl<<endl;
       shift_up(mat);
       //move_number--;
       show_matrix(mat);
       break;
      case 66 :
       system("clear");
       cout<<"Player Name : "<<player_name<<" , "<<" Move Remaining : "<<move_number<<endl<<endl<<endl;
       shift_down(mat);
       //move_number--;
       show_matrix(mat);
       break;
      case 67 :
       system("clear");
       cout<<"Player Name : "<<player_name<<" , "<<" Move Remaining : "<<move_number<<endl<<endl<<endl;
       shift_right(mat);
       //move_number--;
       show_matrix(mat);
       break;
      case 68 :
       system("clear");
       cout<<"Player Name : "<<player_name<<" , "<<" Move Remaining : "<<move_number<<endl<<endl<<endl;
       shift_left(mat);
       //move_number--;
       show_matrix(mat);
       break;
      case 101 :
      case 69 :
       system("clear");
       //cin.ignore();
       cout<<"Do you wanna exit the game..if sure press 'ENTER' key.."<<endl;
       cin.get();
       exit = 1;
       break;
     }
     
     if(exit)
      break;
    }
     char n1;
     if(move_exit)
     {
       cout<<endl<<endl<<"\033[1;31m"<<"You lost the game..!!"<<endl;
       cout<<"\033[0;37m"<<"Do you wanna play again, Enter 'y' or 'Y' for yes.. "<<endl;
       cin>>n1;
     }
    if(winner(mat))
    {
      cout<<"\033[1;32m;"<<"Congratulations....! You are a winner.....!!!"<<endl;
      cout<<"\033[0;37m"<<"Do you wanna play again, Enter 'y' or 'Y' for yes  OR  'n' or 'N' for no..";
      cin>>n1;
    }
    if(n1=='y' || n1=='Y')
     {
      system("clear");
       move_number = 5;
      cout<<"Player Name : "<<player_name<<" , "<<" Move Remaining : "<<move_number<<endl<<endl;
      cout<<endl;
     }
    else
     break;

    if(exit)
     break;
  }
  cout<<"\nThankyou for playing the game.."<<endl;
  cout<<endl;
  return 0;
}
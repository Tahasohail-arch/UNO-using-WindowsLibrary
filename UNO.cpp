/*Taha sohail (24i-3165)*/
#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<ctime>
#include<windows.h>
#include <fstream>
#include <string>
using namespace std;
// colours 
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int YELLOW = 6;
const int WHITE = 7;
// global constants 

int deck[8][15] , player1[108] , player2[108] , deck2[108] , pile[108] , topCard , counter=1 , moveID , wildColour=0 , Plyr1WinCount=0 , Plyr2WinCount=0 ;
bool unoCall=true;
//function for colours

void setColor( int textColor , int bgColor )
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
// function  for clearing screen 

void clearScreen() 
{
	system("CLS"); 
}

// function for the credits 

void displayCredits()
{
	cout<<endl<<"\t\t\t==========================="<<"Made by="<<"Taha Sohail (24i-3165)"<<"==============================="<<endl;
    cout<<endl<<"\t\t\t==========================="<<"Made by="<<"Abdullah Adnan (24i-3020)"<<"============================="<<endl;
    cout<<"Press Enter to continue "<<endl;
    getchar();
   return;
}

// delay function

void delay (  )
{
	for ( int j=0 ; j<100 ; j++ )
	{
		for ( int i=0 ; i<=150000 ; i++ )
		{
			
		}
	}
}

// function to decode the colour 

int decode_colour( int cardID )
{
    int colour = cardID / 1000;
    switch (colour)
	{
        case 1: return RED;
        case 2: return GREEN;
        case 3: return BLUE;
        case 4: return YELLOW;
        case 5: return WHITE;
        default: return BLACK;
    }
}
// function to decode the number 

string decode_type( int cardID )
{
    int typ = cardID % 100;
    switch (typ)
	{
        case 0: return "0 ";
        case 1: return "1 ";
        case 2: return "2 ";
        case 3: return "3 ";
        case 4: return "4 ";
        case 5: return "5 ";
        case 6: return "6 ";
        case 7: return "7 ";
        case 8: return "8 ";
        case 9: return "9 ";
        case 10: return "S ";
        case 11: return "R ";
        case 12: return "D2";
        case 13: return "W ";
        case 14: return "D4";
        default: return "??";
    }
}

// function for string to int conversion of card type

int decodeType( int moveID )
{
	string typ;
	int type;
	typ=decode_type( moveID );
	if      ( typ=="0 " ) { type=0; }
	else if ( typ=="1 " ) { type=1; }
	else if ( typ=="2 " ) { type=2; }
	else if ( typ=="3 " ) { type=3; }
	else if ( typ=="4 " ) { type=4; }
	else if ( typ=="5 " ) { type=5; }
	else if ( typ=="6 " ) { type=6; }
	else if ( typ=="7 " ) { type=7; }
	else if ( typ=="8 " ) { type=8; }
	else if ( typ=="9 " ) { type=9; }
	else if ( typ=="S " ) { type=10; }
	else if ( typ=="R " ) { type=11; }
	else if ( typ=="D2" ) { type=12; }
	else if ( typ=="W " ) { type=13; }
	else if ( typ=="D4" ) { type=14; }
	return type;
}
// function for decoding the wild colour

string decodeWildColour()
{
	string color;
	if      (wildColour==1) { color="RED"; }
	else if (wildColour==2) { color="GREEN"; }
	else if (wildColour==3) { color="BLUE"; }
	else if (wildColour==4) { color="YELLOW"; }
	return color;
}
 //function for decoding the wild colour
 
int DecodeWildColour( int wildColour )
{
	switch ( wildColour )
	{
		case 1: return RED;
        case 2: return GREEN;
        case 3: return BLUE;
        case 4: return YELLOW;
	}
}
// function for counting cards in plyers hand

int count_cards( int player[] )
{
    int countar = 0;
    for (int i = 0; i < 108; i++)
	{
        if (player[i] != 0)
		{
            countar++;
        }
    }
    return countar;
}
// function to convert deck to from 2D TO 1D 

void flattenArray(int deck[][15], int deck2[108])
{
    int index = 0; 
	for ( int i=0 ; i<108 ; i++ )
	{
		deck2[i]=0;
	}
    //  8x15 array
    
    for ( int i=0 ; i<8 ; i++ )
    { // for rows
    
        for ( int j=0; j<15; j++ )
        
        { // for columns in each row
            if ( deck[i][j]!=0 )
            {  
            
                deck2[index] = deck[i][j]; 
                index++;  
            }
        }
    }
    return;
}
// function to shif array backwards

void shiftArray( int array[], int length )
{
    int nonZeroIndex = 0; 
    for ( int i = 0 ; i<length ; i++ )
    {
        if (array[i] != 0)
        {
            array[nonZeroIndex] = array[i];
            nonZeroIndex++;
        }
    }
    while ( nonZeroIndex<length )
    {
        array[nonZeroIndex++] = 0; // Fill remaining positions with zeros
    }
    return;
}
//function to convert players move to cardID

int moveToID( int move , int player[] )
{
	int moveID;
	if ( move==0 )
	{
		moveID=0;
		return moveID;
	}
	else if ( move==-1 )
	{
		moveID=-1;
		return moveID;
	}
	else
	{
		move--;
		moveID=player[move];
		return moveID;
	}
}
// initilizing of the deck

void initializeDeck (int deck[8][15])
{

	for ( int i=0 ; i<8 ; i++ )
	{
		for ( int j=0 ; j<15 ; j++ )
		{
			deck[i][j]=0;
		}
	}
	
	for ( int i=0 ; i<8 ; i++ )
	{
		int index=0;
		if ( i==0 )
		{
			index=1100;
			for ( int j=0 ; j<13 ; j++ )
			{
				deck[i][j]=index;
				index++;
			}
		}
		else if ( i==1 )
		{
			index=1200;
			for ( int j=0 ; j<13 ; j++ )
			{
				deck[i][j]=index;
				index++;
			}
		}
		else if ( i==2 )
		{
			index=2100;
			for ( int j=0 ; j<13 ; j++ )
			{
				deck[i][j]=index;
				index++;
			}
		}
		else if ( i==3 )
		{
			index=2200;
			for ( int j=0 ; j<13 ; j++ )
			{
				deck[i][j]=index;
				index++;
			}
		}
		else if ( i==4 )
		{
			index=3100;
			for ( int j=0 ; j<13 ; j++ )
			{
				deck[i][j]=index;
				index++;
			}
		}
		else if ( i==5 )
		{
			index=3200;
			for ( int j=0 ; j<13 ; j++ )
			{
				deck[i][j]=index;
				index++;
			}
		}
		else if ( i==6 )
		{
			index=4100;
			for ( int j=0 ; j<13 ; j++ )
			{
				deck[i][j]=index;
				index++;
			}
		}
		else if ( i==7 )
		{
			index=4200;
			for ( int j=0 ; j<13 ; j++ )
			{
				deck[i][j]=index;
				index++;
			}
		}		
	}
	for ( int i=0 ; i<8 ; i++ )
	{
		if ( i%2==0 )
		{
			continue;
		}
		else
		{
			for ( int j=0 ; j<1 ; j++ )
			{
				deck[i][j]=0;
			}
		}
	}
	for ( int i=0 ; i<4 ; i++ )
	{
		int index=5113;
		for ( int j=13 ; j<14 ; j++ )
		{
			deck[i][j]=index;
			index+=100;
		}
	}
	for ( int i=0 ; i<4 ; i++ )
	{
		int index=5114;
		for ( int j=14 ; j<15 ; j++ )
		{
			deck[i][j]=index;
			index+=100;
		}
	}
	return;
}
//function for shuffling of deck

void shuffleDeck( int deck[][15] )
{
	// to generate randoms number 
	
	srand(time(0));
	// shuffling 
	for ( int i=0 ; i<8 ; i++ )
	{
		for ( int j=0 ; j<15 ; j++ )
		{
			int x= rand() % 8 ;
			int y= rand() % 15 , temp=0;
			if ( deck[i][j] != 0 && deck[x][y] != 0 )
			{
				temp=deck[i][j];
				deck[i][j]=deck[x][y];
				deck[x][y]=temp;
			}
		}
	}
	return;
}
 // to complete the deck once again
 
void reIntializeDeck( )
{
	srand(time(0));
	for ( int i=0 ; i<108 ; i++ )
	{
		int x= rand() % 108 , temp=0;
		pile[i]=temp;
		pile[i]=pile[x];
		pile[x]=temp;
	}
	for ( int i=0 ; i<108 ; i++ )
	{
		deck2[i]=pile[i];
		pile[i]=0;
	}
	return; 
}
// Function to deal cards alternately

void dealCards( int deck[] , int player1[] , int player2[] )
{
	int p1Index=0 , p2Index=0;
	for ( int i=0 ; i<108 ; i++ )
    {
    	player1[i]=0;
    	player2[i]=0;
	}
    for ( int i=0 ; i<14 ; i++ )
    {
    	if ( i%2==0 )
    	{
    		player2[p2Index]=deck[i];
    		p2Index++;
    	 	deck[i]=0;
		}
		else if ( i%2!=0 )
		{
			player1[p1Index]=deck[i];
			p1Index++;
    		deck[i]=0;
		}
	}
	shiftArray( deck , 108 );
	return;
}
// function to print cards in users hand

void PrintPlayerHand(int player[])
{
    int cards = count_cards(player);
    int cardID, colour;
    string type;
	cout<<endl;
    for (int i = 1; i <= 5; i++)
	{
        for (int card = 0; card < cards; card++)
		{
			if ( card==27 )
			{
				break;
			}
            cardID = player[card];
            colour = decode_colour(cardID);
            type = decode_type(cardID);

            if (i == 1 || i == 5)
			{
                setColor(0, colour);
                cout << "-------";
            }
			else if (i == 2 || i == 4)
			{
                setColor(0, colour);
                cout << "-     -";
            }
			else if (i == 3)
			{
                setColor(0, colour);
                cout << "- ";
                if (colour == WHITE)
				{
                    setColor(BLACK, colour);
                } else
				{
                    setColor(WHITE, colour);
                }
                cout << type;
                setColor(0, colour);
                cout << "  -";
            }
            setColor(WHITE, BLACK);
            cout << " ";
        }
        cout << endl;
    }
    setColor(WHITE, BLACK);
    cout<<endl;
    if ( cards>27 )
    {
    	for (int i = 1; i <= 5; i++)
		{
        	for (int card = 27; card < cards; card++)
			{
				if ( card==54 )
				{
					break;
				}
            	cardID = player[card];
            	colour = decode_colour(cardID);
            	type = decode_type(cardID);

            	if (i == 1 || i == 5)
				{
                	setColor(0, colour);
                	cout << "-------";
           	 	}
				else if (i == 2 || i == 4)
				{
                	setColor(0, colour);
                	cout << "-     -";
            	}
				else if (i == 3)
				{
                	setColor(0, colour);
                	cout << "- ";
                	if (colour == WHITE)
					{
                    	setColor(BLACK, colour);
                	} else
					{
                    	setColor(WHITE, colour);
                	}
                	cout << type;
                	setColor(0, colour);
                	cout << "  -";
            	}
            	setColor(WHITE, BLACK);
            	cout << " ";
        	}
        	cout << endl;
    	}
    	setColor(WHITE, BLACK);
    	cout<<endl;
    	if (cards>54)
    	{
    		for (int i = 1; i <= 5; i++)
			{
        		for (int card = 54; card < cards; card++)
				{
					if ( card==81 )
					{
						break;
					}
            		cardID = player[card];
            		colour = decode_colour(cardID);
            		type = decode_type(cardID);

            		if (i == 1 || i == 5)
					{
                		setColor(0, colour);
                		cout << "-------";
           	 		}
					else if (i == 2 || i == 4)
					{
                		setColor(0, colour);
                		cout << "-     -";
            		}
					else if (i == 3)
					{
                		setColor(0, colour);
                		cout << "- ";
                		if (colour == WHITE)
						{
                    		setColor(BLACK, colour);
                		} else
						{
                    		setColor(WHITE, colour);
                		}
                		cout << type;
                		setColor(0, colour);
                			cout << "  -";
            		}
            		setColor(WHITE, BLACK);
            		cout << " ";
        		}
        		cout << endl;
    		}
    		setColor(WHITE, BLACK);
    		cout<<endl;
    		if ( cards>81 )
    		{
    			for (int i = 1; i <= 5; i++)
				{
        			for (int card = 81; card < cards; card++)
					{
            			cardID = player[card];
            			colour = decode_colour(cardID);
            			type = decode_type(cardID);

            			if (i == 1 || i == 5)
						{
                			setColor(0, colour);
                			cout << "-------";
           	 			}
						else if (i == 2 || i == 4)
						{
                			setColor(0, colour);
                			cout << "-     -";
            			}
						else if (i == 3)
						{
                			setColor(0, colour);
                			cout << "- ";
	                		if (colour == WHITE)
							{
                    			setColor(BLACK, colour);
                			} else
							{
                    			setColor(WHITE, colour);
                			}
                			cout << type;
                			setColor(0, colour);
                			cout << "  -";
            			}
            			setColor(WHITE, BLACK);
            			cout << " ";
        			}
        			cout << endl;
    			}
    			setColor(WHITE, BLACK);
    			cout<<endl;
			}
		}
	}
    return;
}

//function to print card on top of discard pile

void Print_topCard ( int topCard )
{
	int cardID=topCard;
	int colour;
	string type;
	colour = decode_colour(cardID);
    type = decode_type(cardID);
    // printing process
    cout<<"\t\t\t";
    if ( colour==7 )
	{
		setColor(0, colour);
	}
	else
	{
		setColor(7, colour);
	}
    cout << "-------";
    setColor(WHITE, BLACK);
    cout<<" "<<endl;
    cout<<"\t\t\t";
    if ( colour==7 )
	{
		setColor(0, colour);
	}
	else
	{
		setColor(7, colour);
	}
    cout << "-     -";
    setColor(WHITE, BLACK);
    cout<<" "<<endl;
    cout<<"\t\t\t";
    if ( colour==7 )
	{
		setColor(0, colour);
	}
	else
	{
		setColor(7, colour);
	}
    cout << "- "<<type<<"  -";
    setColor(WHITE, BLACK);
    cout<<" "<<endl;
    cout<<"\t\t\t";
    if ( colour==7 )
	{
		setColor(0, colour);
	}
	else
	{
		setColor(7, colour);
	}
    cout << "-     -";
    setColor(WHITE, BLACK);
    cout<<" "<<endl;
    cout<<"\t\t\t";
    if ( colour==7 )
	{
		setColor(0, colour);
	}
	else
	{
		setColor(7, colour);
	}
    cout << "-------";
    setColor(WHITE, BLACK);
    cout<<" "<<endl;
    return;
}

// function to print hidden cards 

void printHiddencards ( int player[] )
{
	int cards = count_cards(player);
    int cardID, colour;
    string type;
	cout<<endl;
    for (int i = 1; i <= 5; i++)
	{
        for (int card = 0; card < cards; card++)
		{
			if ( card==27 )
			{
				break;
			}
            cardID = player[card];

            if (i == 1 || i == 5)
			{
                cout << "------- ";
            }
			else if (i == 2 || i == 4)
			{
                cout << "-     - ";
            }
            else if ( i==3 )
            {
            	cout<<"- UNO - ";
			}
        }
        cout<<endl;
    }
    cout<<endl;
    if ( cards>27 )
    {
    	for (int i = 1; i <= 5; i++)
		{
        	for (int card = 27; card < cards; card++)
			{
				if ( card==54 )
				{
					break;
				}
            	cardID = player[card];

            	if (i == 1 || i == 5)
				{
                	cout << "------- ";
            	}
				else if (i == 2 || i == 4)
				{
              		cout << "-     - ";
            	}
            	else if ( i==3 )
            	{
            		cout<<"- UNO - ";
				}
        	}
        	cout<<endl;
    	}
    	cout<<endl;
    	if ( cards>54 )
    	{
    		for (int i = 1; i <= 5; i++)
			{
        		for (int card = 54; card < cards; card++)
				{
					if ( card==81 )
					{
						break;
					}
            		cardID = player[card];

            		if (i == 1 || i == 5)
					{
                		cout << "------- ";
            		}
					else if (i == 2 || i == 4)
					{
              			cout << "-     - ";
            		}
            		else if ( i==3 )
            		{
            			cout<<"- UNO - ";
					}
        		}
        		cout<<endl;
    		}
    		cout<<endl;
    		if ( cards>81 )
    		{
    			for (int i = 1; i <= 5; i++)
				{
        			for (int card = 81; card < cards; card++)
					{
            			cardID = player[card];

            			if (i == 1 || i == 5)
						{
                			cout << "------- ";
            			}
						else if (i == 2 || i == 4)
						{
              				cout << "-     - ";
            			}
            			else if ( i==3 )
            			{
            				cout<<"- UNO - ";
						}
        			}
        			cout<<endl;
    			}
    			cout<<endl;
			}
		}
	}
    return;
    
}

//function to make discard pile

void discardPile ( int (&topCard) , int deck2[] )
{
	topCard=0;
	for ( int i=0 ; i<108 ; i++ )
	{
		if ( deck2[i]!=0 && (deck2[i]/1000)!=5 && (deck2[i]%100)!=10 &&(deck2[i]%100)!=11 &&(deck2[i]%100)!=12 &&(deck2[i]%100)!=13 &&(deck2[i]%100)!=14 )
		{
			topCard=deck2[i];
			deck2[i]=0;
			break;
		}
	}
	shiftArray( deck2 , 108 );
	return;
}

//function to update discard pile

void UpdateDiscardPile( int (&topCard) , int moveID )
{
	int a=0;
	for ( int i=0 ; i<108 ; i++ )
	{
		if ( pile[i]!=0 )
		{
			a++;
		}
	}
	
    if (moveID != 0)
	{
		pile[a]=topCard;
        topCard = moveID;
    }
    return;
}
void UpdatePlayerHand ( int player[] , int move )
{
	move--;
	player[move]=0;
	shiftArray( player , 108 );
	return;
}
// function to validate the users move

bool isValidPlay(int playerCard, int topCard) 
{
    int typeTop, typePlayer, colorTop, colorPlayer;
    typeTop = decodeType(topCard);
    typePlayer = decodeType(playerCard);
    colorTop = decode_colour(topCard);
    colorPlayer = decode_colour(playerCard);

   
    if (moveID == 0 || moveID == -1)
	{
        return true;
    }

   
    if (typeTop == 13 || typeTop == 14)
	{
        if (colorPlayer == DecodeWildColour( wildColour ) || typePlayer == 13 || typePlayer == 14)
		{
            return true;
        }
		else
		{
            return false;
        }
    }

    // fpr match type or colour 
    if (typeTop == typePlayer || colorTop == colorPlayer) 
	{
        return true;
    }

    // Players card is a wildcard
    if (typePlayer == 13 || typePlayer == 14)
	 {
        return true;
    }

    // If no conditions are met the move is invalid
    return false;
}

// function to draw card from the deck

void drawCard ( int player[] , int deck[] )
{
	int countar=0 , a=0;
	for ( int i=0 ; i<108 ; i++ )
	{
		if ( deck[i]!=0 )
		{
			countar++;
		}
	}
	if ( countar==0 )
	{
		
		for ( int i=0 ; i<108 ; i++ )
		{
			if ( pile[i]!=0 )
			{
				a++;
			}
		}
		if ( a==0 )
		{
			cout<<endl<<"There are no cards in the deck to draw and pile is empty all cards are in players hand"<<endl;
			delay();
		}
		else
		{
			cout<<endl<<"Reinitializing deck...."<<endl;
			delay();
			reIntializeDeck();
		}
		return;
	}
	else
	{
		for (int i = 0; i < 108; i++)
		{
    		if (player[i] == 0)
			{
       			player[i] = deck[0];
       			deck[0]=0;
       			shiftArray( deck , 108 );
       			break;
    		}
		}
	}
	return;
}

// function to handle the wildcard 

void handelWild( int &topCard, int deck[] )
{
	cout<<"Choose the colour you want to put on card: "<<endl<<"1.RED"<<endl<<"2.GREEN"<<endl<<"3.BLUE"<<endl<<"4.YELLOW"<<endl;
	cin>>wildColour;
	while ( wildColour<0 || wildColour>4 )
	{
		cout<<endl<<"INVALID INPUT!!"<<endl;
		cout<<"Choose the colour you want to put on card: "<<endl<<"1.RED"<<endl<<"2.GREEN"<<endl<<"3.BLUE"<<endl<<"4.YELLOW"<<endl;
		cin>>wildColour;
	}
	return;
}
// function to handle the wild cards

void handelD4( int deck[] , int player[] )
{
	// int count;
	// count=count_cards( player );
	cout<<"Choose the colour you want to put on card: "<<endl<<"1.RED"<<endl<<"2.GREEN"<<endl<<"3.BLUE"<<endl<<"4.YELLOW"<<endl;
	cin>>wildColour;
	while ( wildColour<0 || wildColour>4 )
	{
		cout<<endl<<"INVALID INPUT!!"<<endl;
		cout<<"Choose the colour you want to put on card: "<<endl<<"1.RED"<<endl<<"2.GREEN"<<endl<<"3.BLUE"<<endl<<"4.YELLOW"<<endl;
		cin>>wildColour;
	}
	if ( counter%2==0 )
	{
		for ( int i=0 ; i<4 ; i++ )
		{
			drawCard ( player2 , deck2 );
		}
	}
	else if ( counter%2!=0 )
	{
		for ( int i=0 ; i<4 ; i++ )
		{
			drawCard ( player1 , deck2 );
		}
	}
	return;
}
// function to handle special cards 

void handleSpecialCard(int specialCardType)
{
	if ( specialCardType==10 )
	{
		counter++;
		return;
	}
	else if ( specialCardType==11 )
	{
		// reverse
		counter++;
		return;
	}
	else if ( specialCardType==12 )
	{
		//draw 2
		if ( counter%2==0 )
		{
			drawCard ( player2 , deck2 );
			drawCard ( player2 , deck2 );
		}
		else if ( counter%2!=0 )
		{
			drawCard ( player1 , deck2 );
			drawCard ( player1 , deck2 );
		}
		counter++;
		return;
	}
	else if ( specialCardType==13 )
	{
		handelWild( topCard , deck2 );
		return;
	}
	else if ( specialCardType==14 )
	{
		if ( counter%2==0 )
		{
			handelD4( deck2 , player2 );
		}
		else if ( counter%2!=0 )
		{
			handelD4( deck2 , player1 );
		}
		counter++;
		return;
	}
}
// function for calling UNO

void unoCallCheck ()
{
	if ( counter%2==0  )
	{
		int a=0;
		for ( int i=0 ; i<108 ; i++ )
		{
			if ( player1[i]!=0 )
			{
				a++;
			}
		}
		if ( a==1 && unoCall==false )
		{
			drawCard ( player1 , deck2 );
			drawCard ( player1 , deck2 );
		}
	}
	else

	{
		int a=0;
		for ( int i=0 ; i<108 ; i++ )
		{
			if ( player2[i]!=0 )
			{
				a++;
			}
		}
		if ( a==1 && unoCall==false )
		{
			drawCard ( player2 , deck2 );
			drawCard ( player2 , deck2 );
		}
	}
}

// function to call UNO 

bool callUno(  )
{
	bool playable;
	if ( counter%2==0  )
	{
		int a=0;
		for ( int i=0 ; i<108 ; i++ )
		{
			if ( player1[i]!=0 )
			{
				a++;
			}
		}
		if ( a==2 )
		{
			if ( (player1[0]/1000)==( topCard/1000 ) || (player1[0]%100)==( topCard%100 ) || (player1[1]/1000)==( topCard/1000 ) || (player1[1]%100)==( topCard%100 ) )
			{
				playable=true;
			}
		}
		if ( a==2 && playable==true )
		{
			unoCall=true;
			cout<<endl<<"Player 1 called uno"<<endl;
		}
		else
		{
			unoCall=false;
			cout<<endl<<"Player 1 called invalid uno"<<endl;
		}
	}
	else
	{
		int a=0;
		for ( int i=0 ; i<108 ; i++ )
		{
			if ( player2[i]!=0 )
			{
				a++;
			}
		}
		if ( a==2 )
		{
			if ( (player2[0]/1000)==( topCard/1000 ) || (player2[0]%100)==( topCard%100 ) || (player2[1]/1000)==( topCard/1000 ) || (player2[1]%100)==( topCard%100 ) )
			{
				playable=true;
			}
		}
		if ( a==2 && playable==true )
		{
			unoCall=true;
			cout<<endl<<"Player 2 called uno"<<endl;
		}
		else
		{
			unoCall=false;
			cout<<endl<<"Player 2 called invalid uno"<<endl;
		}
	}
}

// function to save game result 

void saveLoadGameResult(int &Plyr1WinCount, int &Plyr2WinCount)
{
    
    ofstream statsFile("match_records.txt"); 
    if (statsFile.is_open()) 
	{
        statsFile<<"Match Summary:\n";
        statsFile<<"Wins by Player A: "<<Plyr1WinCount <<endl;
        statsFile<<"Wins by Player B: "<<Plyr2WinCount <<endl;
        statsFile<<"\n";
      //  statsFile.close();
         cout<< "Match records successfully saved. " <<endl;
        
    } else
	{
        cout<<"Error: Could not write to the match records file.\n";
        return;
    }

}
// function to print board 

void printBoard ( int player1[] , int player2[] , int topCard , int player )
{
	if ( player==1 )
	{
		cout<<endl<<"cards in player 1 hand: "<<endl;
		PrintPlayerHand(player1);
		if ( (topCard/1000)==5 )
		{
			string color;
			color=decodeWildColour();
			cout<<"Wild colour is: "<<color<<endl;
			cout<<endl<<"discard pile"<<endl<<endl;
			Print_topCard ( topCard );
		}
		else
		{
			cout<<endl<<"discard pile"<<endl<<endl;
			Print_topCard ( topCard );
		}
		cout<<endl<<"cards in player 2 hand: "<<endl;
		printHiddencards ( player2 );
	}
	else
	{
		cout<<endl<<"cards in player 1 hand: "<<endl;
		printHiddencards ( player1 );
		if ( (topCard/1000)==5 )
		{
			string color;
			color=decodeWildColour();
			cout<<"Wild colour is: "<<color<<endl;
			cout<<endl<<"discard pile"<<endl<<endl;
			Print_topCard ( topCard );
		}
		else
		{
			cout<<endl<<"discard pile"<<endl<<endl;
			Print_topCard ( topCard );
		}
		cout<<endl<<"cards in player 2 hand: "<<endl;
		PrintPlayerHand(player2);
	}
}
int turn( int counter )
{
	int player;
	if ( counter%2!=0 )
	{
		return player=1;
	}
	else if ( counter%2==0 )
	{
		return player=2;
	}
}
// function for the play turn 

void playTurn(  )
{
	int  choice , move  , size , size2 , cards , cards1 , cards2 , player , moveType ;
    bool valid;
    int drawTracker1=0 , drawTracker2=0;
	char choice1;
	while ( true )
	{
		cout<<endl<<endl<<endl;
		cout<<"\t\t\t\tP.play";
		cout<<"\t\t\t\tU.Call Uno"<<endl<<endl;
		cout<<"\t\t\t\tE.exit";
		cout<<"\t\t\t\tR.Return to main menu";
		cout<<endl;
		cin>>choice1;
		cin.ignore(1000,'\n');
		while ( choice1!='P' && choice1!='U' && choice1!='E' && choice1!='R' )
		{
			cout<<endl<<"INVALID INPUT!!"<<endl;
			cin>>choice1;
			cin.ignore(1000,'\n');
		}
		switch ( choice1 )
		{
			case 'P':
				clearScreen();
				{
					player=turn( counter );
					counter++;
					if ( player==1 )
					{
						printBoard ( player1 , player2 , topCard , player );
						cards=count_cards( player1 );
						if ( cards==1 )
						{
							unoCallCheck ();
						}
						cout<<"Player "<<player<<" choose a card from 1 to "<<cards<<" or enter 0 to draw or -1 to skip: ";
						cin>>move;
						while ( move<-1 || move>cards )
						{
							cout<<endl<<"INVALID INPUT!!"<<endl;
							cout<<"Player "<<player<<" choose a card from 1 to "<<cards<<" or enter 0 to draw or -1 to skip: ";
							cin>>move;
						}
						moveID=moveToID( move , player1 );
						valid=isValidPlay( moveID , topCard );
						while ( !valid )
						{
							cout<<endl<<"INVALID CARD!!"<<endl;
							cout<<"Player "<<player<<" choose a card from 1 to "<<cards<<" or enter 0 to draw or -1 to skip: ";
							cin>>move;
							moveID=moveToID( move , player1 );
							valid=isValidPlay( moveID , topCard );
						}
						moveType=decodeType( moveID );
						if ( moveID==0 )
						{
							if ( drawTracker1>0 )
							{
								drawTracker1=0;
								counter+=2;
							}
							else
							{
								drawCard ( player1 , deck2 );
								drawTracker1++;
								counter++;
							}
						}
						else if ( moveID==-1 )
						{
							
						}
						else
						{
							if ( moveType>=0 && moveType<=9 )
							{
								UpdateDiscardPile( topCard , moveID );
								UpdatePlayerHand ( player1 , move );
							}
							else if ( moveType>=10 && moveType<=14 )
							{
								UpdateDiscardPile( topCard , moveID );
								UpdatePlayerHand ( player1 , move );
								handleSpecialCard( moveType );
							}
						}
					}
					else if ( player==2 )
					{
						printBoard ( player1 , player2 , topCard , player );
						cards=count_cards( player2 );
						if ( cards==1 )
						{
							unoCallCheck ();
						}
						cout<<"Player "<<player<<" choose a card from 1 to "<<cards<<" or enter 0 to draw or -1 to skip: ";
						cin>>move;
						while ( move<-1 || move>cards )
						{
							cout<<endl<<"INVALID INPUT!!"<<endl;
							cout<<"Player "<<player<<" choose a card from 1 to "<<cards<<" or enter 0 to draw or -1 to skip: ";
							cin>>move;
						}
						moveID=moveToID( move , player2 );
						valid=isValidPlay( moveID , topCard );
						while ( !valid )
						{
							cout<<endl<<"INVALID CARD!!"<<endl;
							cout<<"Player "<<player<<" choose a card from 1 to "<<cards<<" or enter 0 to draw or -1 to skip: ";
							cin>>move;
							moveID=moveToID( move , player2 );
							valid=isValidPlay( moveID , topCard );
						}
						moveType=decodeType( moveID );
						if ( moveID==0 )
						{
							if ( drawTracker2>0 )
							{
								drawTracker2=0;
								counter+=2;
							}
							else
							{
								drawCard ( player2 , deck2 );
								drawTracker2++;
								counter++;
							}
						}
						else if ( moveID==-1 )
						{
						
						}
						else
						{
							if ( moveType>=0 && moveType<=9 )
							{
								UpdateDiscardPile( topCard , moveID );
								UpdatePlayerHand ( player2 , move );
							}
							else if ( moveType>=10 && moveType<=14 )
							{
								UpdateDiscardPile( topCard , moveID );
								UpdatePlayerHand ( player2 , move );
								handleSpecialCard( moveType );
							}
						}
					}
					
					// winning conditions for users
					cards1=count_cards( player1 );
					cards2=count_cards( player2 );
					if ( cards1==0 )
					{
						cout<<"CONGRATULATIONS Player 1 have won!!!!"<<endl;
						Plyr1WinCount++;
						return;
					}
					if ( cards2==0 )
					{
						cout<<"CONGRATULATIONS Player 2 have won!!!!"<<endl;
						Plyr1WinCount++;
						return;
					}
				}
				break;
			case 'U':
				clearScreen();
				callUno(  );
				break;
			case 'E':
				char choice3;
				cout<<endl<<"Do you really want to exit press 'Y' for yes an 'N' for no"<<endl;
				cin>>choice3;
				cin.ignore(1000,'\n'); 
				while ( choice3!='Y' && choice3!='N' )
				{
					cout<<endl<<"INVALID"<<endl;
					cout<<endl<<"Do you really want to exit press 'Y' for yes an 'N' for no"<<endl;
					cin>>choice3;
					cin.ignore(1000,'\n'); 
				}
				if ( choice3=='Y' )
				{
					exit(0);
				}
				else
				{
					clearScreen();
				}
				break;
			case 'R':
				clearScreen();
				return;
		}
	}
}
int main()
{
	int count=0;
	if ( count<1 )
	{
		count++;
	    initializeDeck(deck);
	    shuffleDeck(deck);
		flattenArray( deck , deck2 ); // flatening of deck to make handeling possible
		dealCards( deck2 , player1 , player2 ); // dealing cards to players alternatly
		discardPile( topCard , deck2 );
		 cout<<"\t\t\t\t\t"<<"                                   ________          "          <<endl;
        cout<<"\t\t\t\t\t"<<"|"<<"          "<<"|"<<"      "<<"|"<<"\\"<<"       |"<<"      / "        <<"       \\"<<endl;
        cout<<"\t\t\t\t\t"<<"|"<<"          "<<"|"<<"      "<<"|"<<" \\"<<"      |"<<"     /     "        <<"     \\"<<endl;
        cout<<"\t\t\t\t\t"<<"|"<<"          "<<"|"<<"      "<<"|"<<"  \\"<<"     |"<<"    /        "        <<"    \\"<<endl;
        cout<<"\t\t\t\t\t"<<"|"<<"          "<<"|"<<"      "<<"|"<<"   \\"<<"    |"<<"    |          "         <<"   |"<<endl;
        cout<<"\t\t\t\t\t"<<"|"<<"          "<<"|"<<"      "<<"|"<<"    \\"<<"   |"<<"     \\           "        <<"/"<<endl;
        cout<<"\t\t\t\t\t"<<"|"<<"          "<<"|"<<"      "<<"|"<<"     \\"<<"  |"<<"      \\         "        <<"/"<<endl;
        cout<<"\t\t\t\t\t"<<"|"<<"          "<<"|"<<"      "<<"|"<<"      \\"<<" |"<<"       \\_______"<<"/"<<endl;
        cout<<"\t\t\t\t\t"<<"|"<<"__________"<<"|"<<"      "<<"|"<<"       \\"<<"|"<<"               "<<""<<endl;
	  // making discard pile
	}
	
	int choice;
	while ( true )
	{
		cout<<endl<<endl<<endl;
		cout<<"\t\t\t\t1.play UNO";
		cout<<"\t\t\t\t2.Game History"<<endl<<endl;
		cout<<"\t\t\t\t3.Credits";
		cout<<"\t\t\t\t4.Exit";
		cout<<endl;
		cin>>choice;
		while ( choice<0 && choice>4 )
		{
			cout<<endl<<"INVALID!!"<<endl;
			cin>>choice;
		}
		switch (choice)
		{
			case 1:
				clearScreen();
				playTurn(  );
				break;
			case 2:
    			saveLoadGameResult(Plyr1WinCount, Plyr2WinCount);
				break;
			case 3:
				clearScreen();
				displayCredits();
				break;
			case 4:
				clearScreen();
				return 0;
				break;
		}
	}
    return 0;
}

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
void display();
void enemymove();
int checkalive(int x, int y);
char map[8][8];
int eloc[20][2];
int i,j;

int main(){
	// Generate the map
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			map[i][j]='.';
		}
	}
	// Set Player's inital position and Goal's position 
	map[0][0]='P';
	map[7][7]='G';

	srand((time(0)));
	// Create random traps in the map
	int traps = 4;
	for(i=0;i<traps;i++){
		map[rand()%6+1][rand()%6+1]='T';
	}
	// Create random enemys in the map
	for(i=0;i<20;i++){
		for(j=0;j<2;j++){
			eloc[i][j] = rand()%6+1;
		}
		map[eloc[i][0]][eloc[i][1]]='E';
	}

	cout<< endl;
	cout<< "You are Player(P), and you need to reach Goal(G), without touching Traps(T)."<< endl;
	cout<< "You cannot touch Enemy(E) either.  Additonally Enemy can move every round as well"<< endl;
	cout<< "Enter W for move up, D for move right, A for move left, S for move down."<< endl;
	display();

	int x=0, y=0;
	int goal=1;
	char move;

	while(1){
		cout<< "Please enter you move: ";
		cin>> move;
		cout<< endl;
		if(move == 'w' && x != 0){
			map[x][y]='.';
			x--;
			if(checkalive(x,y)){
				break;
			}
		}
		else if(move == 's' && x != 7){
			map[x][y]='.';
			x++;
			if(checkalive(x,y)){
				break;
			}
		}
		else if(move == 'a' && y != 0){
			map[x][y]='.';
			y--;
			if(checkalive(x,y)){
				break;
			}
		}
		else if(move == 'd' && y != 7){
			map[x][y]='.';
			y++;
			if(checkalive(x,y)){
				break;
			}

		}
		enemymove();
		
		if (map[x][y] == 'E'){
			map[x][y] = 'X';
			cout<< "You are caught by an enemy hahahaha!!"<<endl;
			display();
			break;
		}

		display();

	}

	return 0;
}

int checkalive(int x, int y){
	if(map[x][y]=='.'){
		map[x][y]='P';
		return 0;
	}
	else {
		if(map[x][y]=='T'){
			cout<< "You are traped!!"<<endl;
			map[x][y]='X';
		}
		else if(map[x][y]=='E'){
			cout<< "You are caught by an enemy!!"<<endl;
			map[x][y]='X';
		}
		else if(map[x][y]=='G'){
			cout<< "You did it!!"<< endl;
			map[x][y]='P';
		}
		display();
		return 1;
	}
}

void enemymove(){
	int next,out;
	for(i=0;i<20;i++){
		do{
			next = rand()%4;
			if(next == 0 && eloc[i][0] != 0 
				&& map[eloc[i][0]-1][eloc[i][1]] != 'T'
				&& map[eloc[i][0]-1][eloc[i][1]] != 'E')
			{
				map[eloc[i][0]][eloc[i][1]]='.';
				eloc[i][0]--;
				out = 0;
			}
			else if(next == 1 && eloc[i][0] !=7
				&& map[eloc[i][0]+1][eloc[i][1]] != 'T'
				&& map[eloc[i][0]+1][eloc[i][1]] != 'E'
				&& map[eloc[i][0]+1][eloc[i][1]] != 'G')
			{
				map[eloc[i][0]][eloc[i][1]]='.';
				eloc[i][0]++;
				out = 0;
			}
			else if(next == 2 && eloc[i][1] != 0
				&& map[eloc[i][0]][eloc[i][1]-1] != 'T'
				&& map[eloc[i][0]][eloc[i][1]-1] != 'E')
			{
				map[eloc[i][0]][eloc[i][1]]='.';
				eloc[i][1]--;
				out = 0;
			}
			else if(next == 3 && eloc[i][1] != 7
				&& map[eloc[i][0]][eloc[i][1]+1] != 'T'
				&& map[eloc[i][0]][eloc[i][1]+1] != 'E'
				&& map[eloc[i][0]][eloc[i][1]+1] != 'G')
			{
				map[eloc[i][0]][eloc[i][1]]='.';
				eloc[i][1]++;
				out = 0;
			}
		}while(out);	

		map[eloc[i][0]][eloc[i][1]]='E';
	}
}

void display(){
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			cout<<map[i][j];
			if(j!=7){
				cout<<"    ";
			}
		}
		cout<< endl<< endl;
	}
}

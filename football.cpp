#include<stdio.h>
#undef SEEK_SET
#undef SEEK_END
#undef SEEK_CUR
#include<mpi.h>
#include<iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{	
	//For MPI
	MPI_Status status;
	int pid;	
	int TAG = 0;
	int players = 0; //players total in game;
	int power[5]; 	 //buffer
	int kicks[110];  //array of random kicks

	//Fill array with random numbers:
	srand( time(NULL) );	
	for( int i = 0; i < 110; i++ ) kicks[i] = rand() % 100;
	
	//Enter the MPI:
	MPI_Init( &argc, &argv );
	MPI_Comm_size(MPI_COMM_WORLD, &players);
	MPI_Comm_rank( MPI_COMM_WORLD, &pid);
	if ( pid != 0){
		//Player code here:
		for ( int i = 0; i < 5; i++ ) power[i] = kicks[ ( pid - 1) * 5 + i ];
		MPI_Send( &power, 5, MPI_INT, 0, TAG, MPI_COMM_WORLD);		
	} else {
		//Ball code here:
		int teamsRes[2] = {0, 0}; //Array for result of game
		for(int i = 1; i < players; i++ ){
			MPI_Recv( &power, 5, MPI_INT, i, TAG, MPI_COMM_WORLD, &status ); //Add listeners
			float teamNum = i; //Kicking player team number
			cout << "Kicks: | ";
			int summ = 0; //Sum power of kicks of current player
			for ( int j = 0; j < 5; j++ ){
				summ += power[j]; //calculate summ				
				cout << power[j] << " ";
			}
			//find team number of player:
			teamNum /= 11;
			if ( teamNum <= 1) teamNum = 1;
			else teamNum = 2;
			//show results:
			cout << " | summ power: " << summ << " from player " << i << " team " << teamNum << endl;
			//add kick power to the team array:
			teamsRes[ int(teamNum-1) ] += summ;
		}
		//Show Game Results:
		cout << "Results " << teamsRes[0] << " - " << teamsRes[1] << endl;
		if ( teamsRes[0] > teamsRes[1] ) cout << "The first team wins!" << endl;
		else cout << "The second team wins!" << endl;
		return 0;
	}
	MPI_Finalize();
}




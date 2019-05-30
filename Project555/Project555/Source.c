#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>


#define  ARR_SIZE 21

typedef struct player {
	char name[ARR_SIZE]; // player's name, up to 20 chars
	int age; // player's age, 0 - 120
	int defense; // defense power, 1 - 100
	int attack; // attack power, 1 - 100
	struct player* next; // next player in the list
}player;


typedef struct team {
	char name[ARR_SIZE]; // team's name
	player *teamPlayers; // pointer to the team players list
	int points; // the team points in the league
	int wins; // number of wins
	int draws; // number of draws
	int losses; // number of losses
	struct team* next; // Next team in the list
}team;



team* create_team(char name[], player *teamPlayers, int points, int wins, int draws, int losses, struct team* next)
{
	team team = { name,teamPlayers,points,wins,draws,losses,next };
}

player* create_player(char name[], int age, int defense, int attack, struct player* next)
{
	player player = { name, age, defense,  attack,next };
}


void add_Players(team *team, FILE *fPlayers) {
	player *p_head = {0}, *new_player = { 0 };
	char line_p[70] = { 0 };
	char name[ARR_SIZE] = { 0 };
	while (fgets(line_p, sizeof line_p, fPlayers) != (NULL))
	{
		for (int i = 0; i < ARR_SIZE; i++) {
			name[i] = line_p[i];
		}

		if ((name) == (team->name)){
			new_player = create_player(  name ,atoi(line_p,22,26), atoi(line_p, 27,34 ), atoi(line_p,35 ,42 ),p_head);
			p_head = new_player;
		}
	}
}

int list_len(player *player) {
	int sum=0;
	while (player != NULL) {
		player = player->next;
		sum++;
	}
	return sum;
}

team* list_index_t(team *team,int index) {
	for (index; index > 0; index--) {
		team = team->next;
	}
	return team;

}

player* list_index_p(player *player, int index) {
	for (index; index > 0; index--) {
		player = player->next;
	}
	return player;

}


void play_Game(team *team1, team *team2,FILE *fResult)
{
	fResult = open("results.txt","w");
		if (team1->name == team2->name)
			fprintf(fResult,"Team can't play against itself\n");
		else
		{
			int power1 = 0;
			int power2 = 0;
			int temp_power = 0;
			for (int i = 0; i < list_len(team1->teamPlayers); i++)
			{
				int attack1 = list_index_p(team1->teamPlayers,i)->attack;
				int defense1 = list_index_p(team1->teamPlayers, i)->defense;
				temp_power = attack1 + defense1;
				power1 += temp_power;
			}
			for (int i = 0; i < list_len(team1->teamPlayers); i++)
			{
				int attack2 = list_index_p(team2->teamPlayers, i)->attack;
				int defense2 = list_index_p(team2->teamPlayers, i)->defense;
				temp_power = attack2 + defense2;
				power2 += temp_power;
			}
			if (power1 > power2)
			{
				fprintf(fResult,"Team %s WON the game\n", team1->name);
				team1->points += 3;
				team1->wins++;
				team2->losses++;
			}
			else if (power2 > power1)
			{
				fprintf(fResult,"Team %s WON the game\n", team2->name);
				team2->points += 3;
				team2->wins++;
				team1->losses++;
			}
			else
			{
				fprintf(fResult,"Team %s and Team %s finished the match in a draw\n", team1->name, team2->name);
				team1->points += 1;
				team2->points += 1;
				team1->draws++;
				team2->draws++;
			}
		
	}
}

team* find_team(team *team1,team *teams) {
	while (team1!=teams) {
		teams = teams->next;
	}
	return teams;
}


int main(int argc, char* argv[]) {
	FILE *fTeams = fopen(argv[1], "r");
	FILE *fPlayers = fopen(argv[2], "r");
	FILE *fGames = fopen(argv[3], "r");
	FILE *fTable = fopen(argv[4], "w");
	FILE *fResult = fopen("results.txt", "w");
	team *t_head = NULL, *new_team = NULL;
	
	char line_t[ARR_SIZE] = { 0 };
	char line_g[ARR_SIZE*2] = { 0 };
	char name[ARR_SIZE] = { 0 };
	player players[] = { 0 };
	fprintf(fResult, "lol");
	while (fgets(line_t, ARR_SIZE, fTeams) != (NULL))
	{
		fprintf(fResult,"%s",line_t);
		new_team=create_team(line_t,players,0,0,0,0,t_head);
		add_Players(new_team, fPlayers);
		t_head = new_team;
	}
	fclose(fTeams);
	char team1[ARR_SIZE] = {0};
	char team2[ARR_SIZE] = { 0 };
	char ch = { 0 };
	while (fgets(line_g, sizeof line_g, fGames) != (NULL))
	{
		int j = 0;
		while (ch != ":") {
			team1[j] = line_g[j];
		}
		for (int i = strlen(team1) + 1; i < ARR_SIZE; i++) {
			team2[i] = line_g[i];
		}
		for (int i = 0; i < ARR_SIZE - strlen(team1); i++) {
			strcat(team1," ");
		}
		play_Game(find_team(t_head,team1),find_team(t_head,team2),fResult);
	}
	return 0;
}
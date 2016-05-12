#include "main.h"
#include "Controller.h"
#include "Runner.h"
#include "Driver.h"
#include "delay.h"

byte current_direction_global;
byte current_position_global[2];
byte maze_array_global[MAZE_SIZE][MAZE_SIZE];
byte maze_dist_array_global[MAZE_SIZE][MAZE_SIZE];
byte path_1_global[MAZE_SIZE*MAZE_SIZE];
byte general_purpose_array_1[GENERAL_ARRAY_SIZE];
byte general_purpose_array_2[GENERAL_ARRAY_SIZE];
byte path_run_global[MAZE_SIZE * MAZE_SIZE];

int main(void) {

	byte i;
	byte j;
	
	// 1. HARDWARE INITIALIZE
	Controller_hardware_init();
	LED4_ON;
	
	// 2. INITIALIZE GLOABL VARIABLES
	// a. current postion global, current direction global
	current_position_global[ROW_INDEX] = 0;
	current_position_global[COLUMN_INDEX] = 0;
	current_direction_global = START_DIRECTION;

	// b. maze distance array global
	for(i = 0; i < MAZE_SIZE; i++){
		for(j = 0; j < MAZE_SIZE; j++){
			maze_dist_array_global[i][j] = 0;
			maze_array_global[i][j] = 0;
		}
	}
	
	// c. maze walls info array
	for(i = 0 ; i < MAZE_SIZE; i++){
		SET_B(maze_array_global[i][0],WEST);
		SET_B(maze_array_global[0][i],NORTH);
		SET_B(maze_array_global[i][MAZE_SIZE-1], EAST);
		SET_B(maze_array_global[MAZE_SIZE-1][i], SOUTH);
	}
	SET_B(maze_array_global[0][0], SOUTH);

	
	// 3. START PROGRAM ---
  while (1){

		switch (MODE){
		
			case MODE_EXPLORE:
																Runner_explore(60);
																MODE = MODE_SPEED_RUN;
																LED1_ON;
																break;
			case MODE_SPEED_RUN:
																Runner_run(80);
																MODE = MODE_DEFAULT;
																LED2_ON;
																break;
				
			case MODE_2:
																LED3_ON;
																break;
				
			case MODE_3:
					//Runner_run_onpost(80);
																LED4_ON;												
																break;
				
			case MODE_4:
				//Runner_run_onpost(80);
																LED5_ON;
																break;
				
			case MODE_CALIBRATE:
																Controller_maze_calibrate();
																LED6_ON;
																break;
			default:
																LED4_ON;
																break;
		

		}
	
		
	}


}

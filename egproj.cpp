#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>


using namespace std;

const int POPULATION = 100;
const int MAX_TRAIT = 9;
const int MIN_TRAIT = 0;
const int killArray[] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
	                     1, 1, 0, 1, 1, 0, 1, 1, 1, 1,
			    		 1, 1, 1, 0, 1, 1, 1, 1, 1, 0,
					     1, 1, 1, 1, 0, 1, 1, 0, 1, 1,
					     1, 0, 1, 0, 1, 1, 1, 0, 1, 1,
					     0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
					     0, 0, 1, 0, 0, 1, 0, 0, 0, 0,
					     1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
					     0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
					     0, 1, 0, 0, 0, 0, 0, 0, 0, 0};

struct Creature
{
	int furLength, numEyes;
	int diff; //difference in traits from ideal conditions
	bool isAlive;
};



void getConditions(int &temperature, int &darkness);

int Random(int parameter, int parameter2);

void printMenu();

void generate(vector <Creature> &creatures, int temperature, int darkness);

void displayCreatures(vector <Creature> creatures);

void displayStats(vector <Creature> creatures, int temperature, int darkness);

void sort(vector <Creature> &creatures);

void kill(vector <Creature> &creatures);

void reproduce(vector <Creature> &creatures, int temperature, int darkness);

int mutation(int trait);

int changeTemperature();

int changeLight();

void updateDiff(vector <Creature> &creatures, int temperature, int darkness);

	int main()
	{
		int temperature = 0;
		int darkness = 0;
		char choice = '2';
	//	srand(time(0));
		getConditions(temperature, darkness);
		vector <Creature> creatures (POPULATION);
		
						   
		generate(creatures, temperature, darkness);
		while (choice != 'q' && choice!= 'Q'){
	    	
		
	        if (choice == '1')
	    	    displayCreatures(creatures);
	    	else if(choice == '2') {
	    		displayStats(creatures, temperature, darkness);
	    	}
        	else if(choice == '3') {
        		sort(creatures);
	        	kill(creatures);
	    	    reproduce(creatures, temperature, darkness);
	    	    cout<<"\nOne year has passed.\n"<<endl;
			}
			else if(choice == '4') {
				int years;
				cout<<"\nEnter the number of years you want to pass: ";
				cin>>years;
				for(int i = 0; i < years; i++) {
            		sort(creatures);
	            	kill(creatures);
	    	        reproduce(creatures, temperature, darkness);
	    	    }
	    	    cout<<"\nThe time has passed.\n"<<endl;
			}
			else if(choice == '5') {
				int years;
				int randomChance = 0;
				cout<<"\nEnter the number of years you want to pass: ";
				cin>>years;
				for(int i = 0; i < years; i++) {
					randomChance = Random(0, 99); //find if temperature shall change
					if(randomChance < 5){
						int newTemp = mutation(temperature);
						if(newTemp != temperature){
						    temperature = newTemp;
						    updateDiff(creatures, temperature, darkness);
						    cout<<"The temperature has changed to be "<<temperature<<endl;
					    }
					}
					randomChance = Random(0, 99);//find if darkness level shall change
					if(randomChance < 5){
						if(randomChance < 5){
						int newLight = mutation(darkness);
						if(newLight != darkness){
						    darkness = newLight;
						    updateDiff(creatures, temperature, darkness);
						    cout<<"The darkness has changed to be "<<darkness<<endl;
					    }
				    }
            		sort(creatures);
	            	kill(creatures);
	    	        reproduce(creatures, temperature, darkness);
	    	        }
	    	        
			    }
				cout<<"\nThe time has passed.\n"<<endl;
		    }
			else if(choice == '6') {
        	    temperature = changeTemperature();
        	    updateDiff(creatures, temperature, darkness);
			}
        	else if(choice == '7') {
        	    darkness = changeLight();
        	    updateDiff(creatures, temperature, darkness);
			}
        	printMenu();
		    cout<<"Enter your Choice: ";
	  		cin>>choice;
	    }
	
	}
	//----------------------------------------------------------------------------
	void getConditions(int &temperature, int &darkness)
	{
		cout<<"Creatures have fur to keep warm. If they have too little, they will freeze, and if they have too much, they will be too hot.\n"
		    <<"0 is cold and 9 is freezing. Enter the temperature you want the creatures to start with:  ";
		cin>>temperature;
		while(temperature > MAX_TRAIT || temperature < MIN_TRAIT){
			cout<<"That is outside the allowed range of temperature. Please enter a value from 0 to 9:  ";
	    	cin>>temperature;
		}
		cout<<"\nCreatures also have eyes to see in darkness. Too few eyes make it difficult to see in darkness, and too many are\ninefficient. "
		    <<"The number of eyes directly corresponds to the darkness level.\n"
		    <<"From a bright 0 to a lightless 9, enter the darkness level you want the creatures to start with:  ";
		cin>>darkness;
		while(darkness > MAX_TRAIT || darkness < MIN_TRAIT){
			cout<<"That is outside the allowed range of darkness. Please enter a value from 0 to 9:  ";
	    	cin>>darkness;
		}
	
		cin.get();
		//system("cls");	
	}
	
	int Random(int parameter, int parameter2)
	{
		int random_number;
		random_number = rand()%(parameter2 - parameter + 1) + parameter;
		return random_number;
	}
	
	void printMenu(){
		cout<<"Main Menu for Creature Interaction\n";
		cout<<"1) View Creature Details\n";
		cout<<"2) View Population Stats\n";
		cout<<"3) Skip one year\n";
		cout<<"4) Skip many years with no environment changes\n";
		cout<<"5) Skip many years with environment changes\n";
		cout<<"6) Change temperature\n";
		cout<<"7) Change darkness level\n";
	  	cout<<"Q) Quit\n";
	 	cout<<'\n'<<'\n';
	}
	
	void generate(vector <Creature> &creatures, int temperature, int darkness)
	{
		for(int i = 0; i < POPULATION; i++){
			creatures[i].furLength = Random(MIN_TRAIT, MAX_TRAIT);
			creatures[i].numEyes = Random(MIN_TRAIT, MAX_TRAIT);
			creatures[i].isAlive = true;
			
			creatures[i].diff = (int) (abs(creatures[i].furLength - temperature) + abs(creatures[i].numEyes - darkness));
		}
	}
	
	void sort(vector <Creature> &creatures){
	//insertion sort, adapted from the Clausentech version
	    int j;
	    Creature toInsert;
	    bool stillLooking;
	    for (int k = 1; k < creatures.size(); ++k) {
	        toInsert = creatures[k];
	        j = k - 1;
	        stillLooking = true;
	        while ((j >= 0) && stillLooking)
	            if (toInsert.diff < creatures[j].diff){
	                creatures[j + 1] = creatures[j];
	                --j;
	            }
	            else
	                stillLooking = false;
	        creatures[j + 1] = toInsert;
	    }
	}
	
	void kill(vector <Creature> &creatures){
		for(int i = 0; i < creatures.size(); i++){
			if(killArray[i] == 0)
			    creatures[i].isAlive = false;
		}
	}
	
	void reproduce(vector <Creature> &creatures, int temperature, int darkness){
		for(int i = 0; i < creatures.size(); i++){
			if(creatures[i].isAlive){
				creatures[POPULATION - 1 - i] = creatures[i];
				creatures[POPULATION - 1 - i].furLength = mutation(creatures[POPULATION - 1 - i].furLength);	
				creatures[POPULATION - 1 - i].numEyes = mutation(creatures[POPULATION - 1 - i].numEyes);
				creatures[POPULATION - 1 - i].diff = (int) (abs(creatures[POPULATION - 1 - i].furLength - temperature) + abs(creatures[POPULATION - 1 - i].numEyes - darkness));
			}
		}
	}
	
	int mutation(int trait){
		int type = Random(0, 99);
		int change = 0;
		
		if(type < 50)
		    return trait;
		else if(type < 70)
		    change = 1;
		else if(type < 90)
		    change = -1;
		else if(type < 95)
		    change = 2;
		else
		    change = -2;
		    
		if(trait + change > MAX_TRAIT || trait + change < MIN_TRAIT) //make sure trait is in bounds
		   	return trait - change;
		else
	        return trait + change;

		    
		return trait;
	}
	
	void displayCreatures(vector <Creature> creatures) {
		for(int j = 0; j < POPULATION; j++) {
			if(creatures[j].isAlive == 1)
	   		cout<<creatures[j].furLength<<" = fur length, "<<creatures[j].numEyes<<" = number of eyes for creature "<<j<<endl;	
	   	}
	}
	void displayStats(vector <Creature> creatures, int temperature, int darkness){
		cout<<"The temperature is "<<temperature<<" and the darkness level is "<<darkness<<endl;
		int fur [MAX_TRAIT + 1];
		int eyes [MAX_TRAIT + 1];
		
		for(int i = 0; i < MAX_TRAIT + 1; i++){//initialize all values to 0
			fur[i] = 0;
			eyes[i] = 0;
		}
		
		for(int i = 0; i < POPULATION; i++){
			fur[creatures[i].furLength]++;
			eyes[creatures[i].numEyes]++;
		}
		cout<<"\nFur length      Number of creatures"<<endl;
		for(int i = 0; i < MAX_TRAIT + 1; i++)
		    cout<<"        "<<i<<"         "<<fur[i]<<endl;
		cout<<"\nEyes            Number of creatures"<<endl;
		for(int i = 0; i < MAX_TRAIT + 1; i++)
		    cout<<"        "<<i<<"         "<<eyes[i]<<endl;
		    
		cout<<endl;
		    
		delete[] fur;
		delete[] eyes;
	}
	
	int changeTemperature(){
		int temperature;
		cout<<"\nPlease enter a temperature from 0 (warmest) to 9 (coldest):  ";
        cin>>temperature;
	       	while(temperature > MAX_TRAIT || temperature < MIN_TRAIT){
		        cout<<"That is outside the allowed range of temperature. Please enter a value from 0 to 9:  ";
	    	    cin>>temperature;
	        }
	        return temperature;
	}

    int changeLight(){
    	int darkness;
    	cout<<"\nPlease enter a darkness level from 0 (brightest) to 9 (darkest):  ";
    	cin>>darkness;
	    while(darkness > MAX_TRAIT || darkness < MIN_TRAIT){
	        cout<<"That is outside the allowed range of darkness. Please enter a value from 0 to 9:  ";
    	        cin>>darkness;
	    }
	    return darkness;
	}

    void updateDiff(vector <Creature> &creatures, int temperature, int darkness){
    	for(int i = 0; i < POPULATION; i++)	
			creatures[i].diff = (int) (abs(creatures[i].furLength - temperature) + abs(creatures[i].numEyes - darkness));
	}

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>
#include <math.h>


using namespace std;

const int movementPrice = 1;


int map[20][20];
int pos[2];
int start[2];
int target[2]={19,19};
int posLookingAt[2];

class block;

list<block> openList;
list<block> closedList;

class block
{
	private:
		int blockPos[2];
		int blockParentPos[2];
		double f;
		double g;
		double h;
	
	public:
		void set(int blockPosAd[], int blockParentPosAd[])
		{
			blockPos[0]=blockPosAd[0];
			blockPos[1]=blockPosAd[1];
			blockParentPos[0]=blockParentPosAd[0];
			blockParentPos[1]=blockParentPosAd[1];

			block tmp;
			for(list<block>::iterator iter=closedList.begin(); iter != closedList.end(); iter++)
			{
				tmp = *iter;
				if((tmp.getPos()[0] == blockParentPos[0]) && (tmp.getPos()[1] == blockParentPos[1]))
				{
					g = tmp.getG()+1;
				}
			}
			h=sqrt(pow((static_cast<double>(blockPos[0])-static_cast<double>(target[0])),2) + pow((static_cast<double>(blockPos[1])-static_cast<double>(target[1])), 2.0));
			f=g+h;
		}
		
		void set(int blockPosAd[])
		{
			blockPos[0]=blockPosAd[0];
			blockPos[1]=blockPosAd[1];
			
			g=0;
			h=0;
			f=0;
		}
		
		double getF()
		{
			return f;
		}
		
		double getG()
		{
			return g;
		}
		
		double getH()
		{
			return h;
		}
		
		int * getParent()
		{
			return blockParentPos;
		}
		
		int * getPos()
		{
			return blockPos;
		}
		
		bool operator==(const block& other) const
		{
			if ((blockPos[0]==other.blockPos[0]) && (blockPos[1]==other.blockPos[1]))
				return true;
			return false;
		}
		
		void changeParent(int newParentPos[])
		{
			blockParentPos[0]=newParentPos[0];
			blockParentPos[1]=newParentPos[1];
		}
};

block currentBlock;
block currentBlockLookingAt;

// do usuniecia
block tmp2;


void mapGenerator()
{
	int currentLoc;
	srand(time(NULL));
	int col[20]; 
	for(int i = 0; i < 20; i++)
	{
		for(int o=0; o < 20; o++)
		{
			currentLoc = rand() % 101;
			if (currentLoc % 5 == 0)
				map[i][o] = 5;
			else
				map[i][o] = 0;
		}
	}
	map[0][0]=0;
	map[19][19]=0;
}

void moveUp()
{
	pos[0]--;
}
void moveDown()
{
	pos[0]++;
}
void moveLeft()
{
	pos[1]--;
}
void moveRight()
{
	pos[1]++;
}

bool checkLists(block check)
{
	block tmp;
	for(list<block>::iterator iter=openList.begin(); iter != openList.end(); iter++)
	{
		tmp = *iter;
		if((tmp.getPos()[0] == check.getPos()[0]) && (tmp.getPos()[1] == check.getPos()[1]))
		{
			if(tmp.getF() > check.getF())
			{
				openList.insert(iter, check);
				openList.remove(tmp);
			}
			return false;
		}
	}
	
	for(list<block>::iterator iter=closedList.begin(); iter != closedList.end(); iter++)
	{
		tmp = *iter;
		if((tmp.getPos()[0] == check.getPos()[0]) && (tmp.getPos()[1] == check.getPos()[1]))
		{
			return false;
		}
	}
	
	return true;
}

void lookAround()
{
	if(pos[0]>0)
	{
		//lookUp
		if(map[pos[0]-1][pos[1]] == 0)
		{
			posLookingAt[0]=pos[0]-1;
			posLookingAt[1]=pos[1];
			currentBlockLookingAt.set(posLookingAt, pos);
			if(checkLists(currentBlockLookingAt))
			{
				openList.push_back(currentBlockLookingAt);
			}
		}
	}
	if(pos[0]<19)
	{
		//lookDown
		if(map[pos[0]+1][pos[1]] == 0)
		{
			posLookingAt[0]=pos[0]+1;
			posLookingAt[1]=pos[1];
			currentBlockLookingAt.set(posLookingAt, pos);
			if(checkLists(currentBlockLookingAt))
			{
				openList.push_back(currentBlockLookingAt);
			}
		}
	}
	if(pos[1]>0)
	{
		//lookLeft
		if(map[pos[0]][pos[1]-1] == 0)
		{
			posLookingAt[0]=pos[0];
			posLookingAt[1]=pos[1]-1;
			currentBlockLookingAt.set(posLookingAt, pos);
			if(checkLists(currentBlockLookingAt))
			{
				openList.push_back(currentBlockLookingAt);
			}
		}
	}
	if(pos[1]<19)
	{
		//lookRight
		if(map[pos[0]][pos[1]+1] == 0)
		{
			posLookingAt[0]=pos[0];
			posLookingAt[1]=pos[1]+1;
			currentBlockLookingAt.set(posLookingAt, pos);
			if(checkLists(currentBlockLookingAt))
			{
				openList.push_back(currentBlockLookingAt);
			}
		}
	}
}

block pickTheSmallestF()
{
	block tmp;
	block smallestF;
	double min = 100;
	for(list<block>::iterator iter=openList.begin(); iter != openList.end(); iter++)
	{
		tmp = *iter;
		if((tmp.getF() < min) && (tmp.getF() > 0))
		{
			min = tmp.getF();
			smallestF = tmp;
		}
	}
	return smallestF;
}

int main(int argc, char** argv) 
{

	cout<<"This is a random map:"<<endl<<endl;
	
	start[0]=0;
	start[1]=0;
	
	pos[0]=start[0];
	pos[1]=start[1];
	
	mapGenerator();
	
	
	for(int i = 0; i < 20; i++)
	{
		for(int o=0; o < 20; o++)
		{
			cout<<map[i][o]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<endl;
	
	currentBlock.set(start);
	closedList.push_back(currentBlock);
	
	lookAround();
	
	while(((pos[0] != target[0]) || (pos[1] != target[1])) && !(openList.empty()))
	{

		
		currentBlock = pickTheSmallestF();
		openList.remove(currentBlock);
		closedList.push_back(currentBlock);

		pos[0] = currentBlock.getPos()[0];
		pos[1] = currentBlock.getPos()[1];
		
		lookAround();

	}
	
	if((pos[0] == 19) && (pos[1] == 19))
	{
		cout<<"Uda³o sie"<<endl;
		while(pos[0]!=0 || pos[1]!=0)
		{
			map[pos[0]][pos[1]]=3;
			pos[0] = currentBlock.getPos()[0];
			pos[1] = currentBlock.getPos()[1];
			for(list<block>::iterator iter=closedList.begin(); iter != closedList.end(); iter++)
			{
				tmp2 = *iter;
				if((tmp2.getPos()[0] == currentBlock.getParent()[0]) && (tmp2.getPos()[1] == currentBlock.getParent()[1]))
				{
					currentBlock = tmp2;
				}
				
			}
		}
	}
	else
		cout<<"nope"<<endl;
	map[pos[0]][pos[1]] = 3; 
	
	for(int i = 0; i < 20; i++)
	{
		for(int o=0; o < 20; o++)
		{
			cout<<map[i][o]<<" ";
		}
		cout<<endl;
	}
	
	system("pause");
	return 0;
}


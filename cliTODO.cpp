#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
using std::cout;
using std::endl;
using std::string;
using std::find;

char* getArg(char** begin,char** end,const string& opt){
	char** itr=find(begin,end,opt);
	if(itr!=end && ++itr != end){return *itr;}
	return 0;
}
bool argExists(char** begin,char** end,const string& opt){
	return find(begin,end,opt) != end;
}


int main(int argc,char** argv){
	std::ifstream infile("todo.txt");
	std::ofstream outfile;
	std::map<int,string[4]> listing;
	if (argc>=2){//make sure there's argument
		for(string line;getline(infile,line);){//load data
			int idx=std::stoi(line.substr(0,1),nullptr,0);//ID
			
			listing[idx][0]=line.substr(2,1);//completion
			listing[idx][1]=line.substr(5,1);//priority
			listing[idx][2]=line.substr(8,14);//due
			listing[idx][3]=line.substr(22);//task
		}
		infile.close();
		
		if (argExists(argv,argv+2,"list")){//list argument
			cout<<"listing"<<std::endl;
			if(listing.empty()){//if map is empty there's no task 
				cout<<"no task available!"<<endl;
			}
			else{//else print
				string result;
				for(auto x:listing){
					result=std::to_string(x.first)+" ";//get ID key
					for(int i=0;i<4;i++){//get the rest of data
						result+=x.second[i];
					}
					cout<<result<<endl;
				}
			}
		}
		
		else if (argExists(argv,argv+2,"add")){//add argument
			outfile.open("todo.txt",std::fstream::app);
			int taskID=listing.size()+1;
			char* task = getArg(argv,argv+argc,"add");
			if(!task){//make sure task is specified
				cout<<"no task added\n";
				return 0;
			}else{
				outfile<<taskID<<"[.](_) due:========== "<<task<<"\n";
				cout<<"Created task: \n|"<<taskID<<"|"<<task<<endl;
			}
			outfile.close();
		}

		else if(argExists(argv,argv+argc,"done")){//done argument
			outfile.open("todo.txt",std::ofstream::trunc);
			int taskID=std::stoi(argv[1],nullptr,0);
			listing[taskID][0]="x";
			for(auto key:listing){
				string completion=listing[key.first][0];
				string priority=listing[key.first][1];
				string due=listing[key.first][2];
				string task=listing[key.first][3];
				outfile<<key.first<<"["<<completion<<"]"<<"("<<priority<<") "<<due<<" "<<task<<endl;
			}
			outfile.close();
		}

		else if(argExists(argv,argv+1,"prune")){//prune argument
			//TODO:create prune to remove tasks that are done from text file
		}
		
		else{
			cout<<"Invalid argument(s)!\n";
		}
	}
	else{
		cout<<"No arguments specified"<<endl;
	}
	
	return 0;
}


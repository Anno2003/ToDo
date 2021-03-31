#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
using std::cout;
using std::endl;
using std::string;
using std::find;

string getArg(char** begin,char** end,const string& opt){
	char** itr=find(begin,end,opt);
	if(itr!=end && ++itr != end){return *itr;}
	return 0;
}
bool argExists(char** begin,char** end,const string& opt){
	return find(begin,end,opt) != end;
}


int main(int argc,char** argv){
	std::ifstream infile("todo.txt");
	std::ofstream outfile("todo.txt",std::fstream::app);
	std::map<int,string[4]> listing;
	if (argc>=2){//make sure there's argument
		for(string line;getline(infile,line);){//load data
			int idx=std::stoi(line.substr(0,1),nullptr,0);//ID
			
			listing[idx][0]=line.substr(2,0);//completion
			listing[idx][1]=line.substr(5,0);//priority
			listing[idx][2]=line.substr(8,14);//due
			listing[idx][3]=line.substr(22);//task
			infile.close();
		}
		
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
		
		if (argExists(argv,argv+2,"add")){//add argument
			int taskID=listing.size()+1;
			string task = getArg(argv,argv+argc,"add");
			outfile<<taskID<<"[.](_) due:========== "<<task<<"\n";
			outfile.close();
			cout<<"Created task: \n"<<task<<endl;
		}
	}
	else{
		cout<<"Invalid argument(s)!"<<std::endl;
	}
	
	return 0;
}


#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

#define NO_OF_ATTRIBUTE 85

class attrNode
{
public:

	vector<attrNode*> vec; 
	int attribute;	

};

int arr2[NO_OF_ATTRIBUTE+1],maximum[NO_OF_ATTRIBUTE+1],minimum[NO_OF_ATTRIBUTE+1],arr3[NO_OF_ATTRIBUTE+1];;
	
	
// slpit function to convert string to int 
void split(string lines){

		string arr[NO_OF_ATTRIBUTE+1];
		
   		int j = 0;
   		stringstream ssin(lines);
   		while ( j < NO_OF_ATTRIBUTE+1){
       		ssin >> arr[j];
       		arr2[j] = atoi(arr[j].c_str());      				
       		j++;
   		}

   		//return arr1;
}

int test_func(attrNode *test_node){
	//cout << "[]][]"<<test_node->attribute<<endl;
	
	if (test_node->attribute== -1 || test_node->attribute== -2){
		return (test_node->attribute== -1)?1:0;
	}
	
	else{
		if (minimum[test_node->attribute]==1){
			//cout << "[]"<<arr3[test_node->attribute]<<endl;
			test_func(test_node->vec[arr3[test_node->attribute]-1]);	
		}else{
			test_func(test_node->vec[arr3[test_node->attribute]]);	
		}
		
	}
	
	
}

// Information gain calculator

int information_gain(int attribute_arr[NO_OF_ATTRIBUTE],vector<string> examples){
	
	

	double pos_class,neg_class,value_count;
	double entropy;

	for(int i=0;i<examples.size()-2;i++){

		string arr[NO_OF_ATTRIBUTE+1];
		int arr1[NO_OF_ATTRIBUTE+1];
   		int j = 0;
   		stringstream ssin(examples[i]);
   		while ( j < NO_OF_ATTRIBUTE+1){
       		ssin >> arr[j];
       		arr1[j] = atoi(arr[j].c_str());      				
       		j++;
   		}

		if (arr1[NO_OF_ATTRIBUTE]==1)
			pos_class++;
		else
			neg_class++;

	}
	//cout<<pos_class<<" pos_class"<<endl;
	//cout<<neg_class<<" pos_class"<<endl;
	
	entropy = (-1)*(pos_class/(neg_class+pos_class))*(log2(pos_class/(neg_class+pos_class))) + (-1)*(neg_class/(neg_class+pos_class))*(log2(neg_class/(neg_class+pos_class)));
	//-----cout<<"parent entropy"<<entropy<<endl;
	string arr[NO_OF_ATTRIBUTE+1];
	
	stringstream ssin(examples[examples.size()-2]);
	int j=0;
	while ( j < NO_OF_ATTRIBUTE+1){
    	ssin >> arr[j];
    	maximum[j] = atoi(arr[j].c_str());      				
    
		j++;
    	
   	}
   	
	stringstream ssin2(examples[examples.size()-1]);
	j=0;
	
	while ( j < NO_OF_ATTRIBUTE+1){
       	ssin2 >> arr[j];
    	minimum[j] = atoi(arr[j].c_str());      				
    	j++;
   	}
	
	double IG,maximum_IG=0,index_IG=0;

	for (int i=0;i<NO_OF_ATTRIBUTE;i++){
	
		if (attribute_arr[i]==1)
		{
			//cout << "i"<<i <<endl;
			continue;		
		}			
		
		int pos_value[maximum[i]-minimum[i]+1],neg_value[maximum[i]-minimum[i]+1];
		fill_n(pos_value,maximum[i]-minimum[i]+1, 0);
		fill_n(neg_value,maximum[i]-minimum[i]+1, 0);
		for (int j=0;j<examples.size()-2;j++){

				//int row[NO_OF_ATTRIBUTE+1];
				split(examples[j]);
				
				
				if (arr2[NO_OF_ATTRIBUTE]==1){

					if (minimum[i]==1){
						//cout <<"####"<<arr2[i]<<"qwe"<<j<<endl;
					pos_value[arr2[i]-1]+=1;

					//cout<<"asdf"<<pos_value[28]<<endl;
					
					}
					else
						pos_value[arr2[i]]+=1;
				}

				else{
					if (minimum[i]==1){
						//cout <<"####"<<arr2[i]<<"qwe"<<j<<endl;
					neg_value[arr2[i]-1]+=1;
					//cout<<"as"<<neg_value[40]<<endl;
					}
					
					else
						neg_value[arr2[i]]+=1;	
				}
		

		}

		//IG = entropy;
		//cout<<pos_value[1]<<"e(((())))"<<endl;
		//double entropy_v[maximum[i]-minimum[i]+1];
		//fill_n(entropy_v,maximum[i]-minimum[i]+1, 0);
		double sum=0,entropy_v;

		for (int k=0; k < (maximum[i]-minimum[i]+1); k++){
			if (neg_value[k]==0|| pos_value[k]==0){
				entropy_v=0;
			}

			else{
				entropy_v = (-1)*((double)pos_value[k]/((double)neg_value[k]+(double)pos_value[k]))*(log2((double)pos_value[k]/((double)neg_value[k]+(double)pos_value[k]))) + (-1)*((double)neg_value[k]/((double)neg_value[k]+(double)pos_value[k]))*(log2((double)neg_value[k]/((double)neg_value[k]+(double)pos_value[k])));
				
			}	
		//	cout << (((double)maximum[i]-(double)minimum[i]+1))<< "sf"<<" i "<<i<< endl;
			sum = sum + ((entropy_v)*(pos_value[k]+neg_value[k]))/((double)examples.size()-2);
			
		}
		//cout<<sum<<"s"<<endl;
		IG = entropy-sum;
		//cout<<" IG "<<IG<<" index "<< i<<"pos_value "<<pos_value[0]<<"neg_value "<<neg_value[0]<<endl;
		//break;
		if (maximum_IG<=IG){
				
				maximum_IG = IG;
				index_IG = i;
		}
		//cout << "entropy_v: "<< entropy_v<<endl;
		//cout << "IG: "<< IG<<endl;
		
	}

	cout << "max IG: "<< index_IG<<endl;
	return index_IG;

}

// ID3 implementation
attrNode *id3(vector<string> examples,char taget_attribute, int attribute_arr[NO_OF_ATTRIBUTE]){
	attrNode *Root = new attrNode();
	int pos_count=0,neg_count=0;
	//--------cout<<"examples size"<<examples.size()-2<<endl;

	for (int i=0; i<examples.size()-2;i++){
		string arr[NO_OF_ATTRIBUTE+1];
		int arr1[NO_OF_ATTRIBUTE+1];
   		int j = 0;
   		stringstream ssin(examples[i]);
   		while ( j < NO_OF_ATTRIBUTE+1){

       		ssin >> arr[j];
       		arr1[j] = atoi(arr[j].c_str());      				
       		j++;
   		}

   		if (arr1[NO_OF_ATTRIBUTE]==1){
       			pos_count++;
       		}

       		if (arr1[NO_OF_ATTRIBUTE]==0){
       			neg_count++;
       	}
	}
	
		
	//----cout <<"13 "<<"pos_count "<<pos_count<<" neg count "<<neg_count<<endl;
	if (pos_count==(examples.size()-2)||neg_count==(examples.size()-2)){

		if (pos_count==(examples.size()-2)){	
			Root->attribute=-1;
			return Root;
		}
		if(neg_count==(examples.size()-2)){
	//		cout<<"12"<<endl;
			Root->attribute=-2;
			return Root;
			
		} 
		//cout<<"13"<<endl;
	}
	else{
		int majority_pos=0,majority_neg=0;
		
		for (int i=0;i<examples.size()-2;i++){
			//cout<<"5"<<endl;
			split(examples[i]);
			if (arr2[NO_OF_ATTRIBUTE]==1){
				majority_pos++;
			}
		
			else{
				majority_neg++;
			}
		}


		int count = 0; 
		for (int c=0;c<NO_OF_ATTRIBUTE;c++){
			if (attribute_arr[c]==1){
				count++;
			}
		}
		if (count==NO_OF_ATTRIBUTE){
			Root->attribute = (majority_neg>=majority_pos)?-2:-1;
			return Root;
		}
		int IG = information_gain(attribute_arr,examples);
		
		
		//attribute_arr[IG]=1;
		
		Root->attribute = IG;
	

		int no_of_values = maximum[Root->attribute]-minimum[Root->attribute]+1;
		//----cout << "[][]"<<no_of_values<<endl;
		for (int i=0;i<no_of_values;i++){
			int new_att_arr [NO_OF_ATTRIBUTE];
			
			for (int c = 0; c < NO_OF_ATTRIBUTE; c++){
				if (c!=IG){
					new_att_arr[c] = attribute_arr[c];
				}else{
					new_att_arr[c]=1;
				}
			}
			vector<string> examples_v;
			//attrNode *node_v = new attrNode();
			//Root->vec.push_back(node_v);

			for (int j=0;j<examples.size()-2;j++){
					//cout<<"3"<<endl;
					split(examples[j]);
					if (minimum[Root->attribute]==0){
	//					cout<<"3"<<endl;
						if(arr2[Root->attribute] == i){
							examples_v.push_back(examples[j]);
						}	
					}
					else{

						if(arr2[Root->attribute] == i+1){
	//						cout<<"else"<<endl;
							examples_v.push_back(examples[j]);
						}
					}
					  
					
			}

			examples_v.push_back(examples[examples.size()-2]);
			examples_v.push_back(examples[examples.size()-1]);
			//----cout<<"examples_v "<<examples_v.size()-2<<endl;
			if (examples_v.size()-2==0){
		
				attrNode *node_v = new attrNode();
				node_v->attribute = (majority_neg>=majority_pos)?-2:-1;
				
				Root->vec.push_back(node_v);
					
				/*if (majority_neg>=majority_pos){
					Root->vec[Root->vec.size()-1]->attribute=-2;
					
				}
				else{

					Root->vec[Root->vec.size()-1]->attribute=-1;	
				}*/
				//-----cout << "00" << Root->vec[Root->vec.size()-1]->attribute<<" da "<<Root->vec.size()<<endl;
		
			}

	//	cout<<"6"<<endl;
		else{
			//cout<<"6"<<endl;
			//cout <<examples_v.size()<<endl;
			//cout << "vec size" <<Root->vec.size()<<endl;
			//Root->vec[Root->vec.size()-1]=id3(examples_v,-1,attribute_arr);
			Root->vec.push_back(id3(examples_v,-1,new_att_arr));
		}
		
		}
	
	}
	return Root;
		
}

int main(){
	fill_n(maximum,NO_OF_ATTRIBUTE+1, 0);
	fill_n(minimum,NO_OF_ATTRIBUTE+1, 0);
	string line;
	int i=0;
	vector<string> examples;
	// Training file read
	ifstream myfile ("train_set.txt");
  	if (myfile.is_open())
  	{
    	while ( getline (myfile,line) )
    	{
      		examples.push_back(line);
      		
    		i++;
    	}

    	myfile.close();
  	}

	ifstream myfile1 ("abc.txt");
  	if (myfile1.is_open())
  	{
  		
    	while ( getline (myfile1,line) )
    	{
      		examples.push_back(line);
      		
    		i++;
    	}

    	myfile1.close();
  	}

  	int attribute_arr[NO_OF_ATTRIBUTE];
  	cout <<examples.size()<<endl;
  	
  	fill_n(arr2,NO_OF_ATTRIBUTE+1, 0);
  	fill_n(attribute_arr,NO_OF_ATTRIBUTE, 0);
  	
  	attrNode *parent_root = id3(examples,-1,attribute_arr);
	//cout << (parent_root->vec[1])->attribute<<endl;
  	//cout <<"end"<<root_node->attribute<<endl;
  	
  	//---TEst set
  	vector<string> test_examples;
  	ifstream myfile2 ("1000.txt");
  	if (myfile2.is_open())
  	{
  		
    	while ( getline (myfile2,line) )
    	{
      		test_examples.push_back(line);
      		
    		i++;
    	}

    	myfile2.close();
  	}


	int corr=0, fal=0, total=test_examples.size();
  	for (int i=0;i<test_examples.size();i++){
  		
  		string arr[NO_OF_ATTRIBUTE+1];
		int j = 0;
		stringstream ssin(test_examples[i]);
		while ( j < NO_OF_ATTRIBUTE+1){
			ssin >> arr[j];
			arr3[j] = atoi(arr[j].c_str());      				
			j++;
		}
  		
  		int output = test_func(parent_root); 
  		if (output==arr3[NO_OF_ATTRIBUTE]){
  			corr++;
		  }else{
		  	fal++;
		  }
	}
  	  
	cout <<"true "<<corr<<endl;   	
	cout << "false "<<fal<<endl;
	cout <<(double)corr/(double)total<<endl;
	
	
}

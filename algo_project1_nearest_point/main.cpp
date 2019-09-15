#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include<algorithm>
using namespace std;

struct point {
    double x;
    double y;

    bool operator < (point const & p) const {
        return (x < p.x) || ((x == p.x) && (y < p.y));
    }

    friend ostream& operator << (ostream & o, const point & p) {
        return o << "(" << p.x << ", " << p.y << ")";
    }
};

void nearest_neighbour_algorithm(vector<point> point_vec, int number_of_lines);
void exhaustive_algorithm(vector<point>point_vec, int number_of_lines);
void print_result(string nameOftheAlgo, vector<point> sorted_points, double total_distance, int number_of_lines);
double distance (point first, point second){
    return sqrt( pow (first.x-static_cast<double>(second.x),2) + pow(first.y-static_cast<double>(second.y) ,2 )  );
}
int main(){
    
    ifstream fin;
    fin.open("input.txt");
    int number_of_lines;
    fin>>number_of_lines;//reading in the number of lines 
    vector<double> x_cordinates;
    vector<double> y_cordinates;
    double x,y;
    int algo_choice;
    while(!fin.eof()){ //reading in the points according to their x,y coordinates. 
        fin>>x;
        x_cordinates.push_back(x);
        fin>>y;
        y_cordinates.push_back(y);
    }
    fin.close();
    vector<point> point_vec;
    for(int i=0;i<number_of_lines;i++){
        point apoint;
        apoint.x = x_cordinates[i];
        apoint.y = y_cordinates[i];
        point_vec.push_back(apoint);//making the initial vector to work with
    }
    cout<<"Which algorithm do you want to run"<<endl<<"[1] Nearest neighbour algorithm"<<endl<<"[2] Exhaustive Algorithm"<<endl;
    cin>>algo_choice;
     clock_t start, stop; //time stamp
    if(algo_choice == 1){
        start = clock();
        nearest_neighbour_algorithm(point_vec, number_of_lines);  //calling nearest algorithm 
        stop = clock();
        double seconds = (stop - start) / double(CLOCKS_PER_SEC);
        cout<<"It took "<<seconds*1000<<" miliseconds"<< endl;
    }
    else if (algo_choice ==2){
        start = clock();
        exhaustive_algorithm(point_vec, number_of_lines); //calling exhaustive algorithm
        stop = clock();
        double seconds = (stop - start) / double(CLOCKS_PER_SEC);
        cout<<"It took "<<seconds*1000<<" miliseconds"<< endl;
    }
    return 0;
    
}


void nearest_neighbour_algorithm(vector<point> point_vec, int number_of_lines){
    double total_distance=0;
    vector<point>sorted_points;
    sorted_points.push_back(point_vec[0]); //initialize the first point as the starting point
    point_vec.erase(point_vec.begin());
    
    int i=0;
  while(i < number_of_lines-1){ //as I am removing the points that has been sorted in the sorted vector, this while loop goes through as long as there are element in the point_vec
    int counter_for_ongoing=0;//reset the counter
   double min_distance=999999;
   int postion_to_remove=0;
    while(counter_for_ongoing<number_of_lines){
         min_distance =  distance(sorted_points[i], point_vec[counter_for_ongoing]); //set the minimum distance to last element of the sorted array and the first element of the remaining points. 
        if(distance(sorted_points.back(), point_vec[counter_for_ongoing]) < min_distance){
            min_distance = distance(sorted_points.back(), point_vec[counter_for_ongoing]); //if a new minimum distance is found, reset the value to it, and have the position to remove the point from the point_vac
            postion_to_remove=counter_for_ongoing;
        }
        counter_for_ongoing++;
    }
    sorted_points.push_back(point_vec[postion_to_remove]);//push it in the back of the sorted_points vector
    total_distance+=min_distance;//add up the total distance 
    i++;
  }
  //sorted_points.erase(sorted_points.begin(),sorted_points.begin()+1 );//removing the initial/first point,,otherwise it will show up twice 
    total_distance+= distance(sorted_points.back(), sorted_points[0]); //and figuring out the distance to go back to first point
  sorted_points.push_back(sorted_points[0]); //to go back to the initial point, adding the first point to the last of vector

  print_result("Nearest Neighbour Algorithm", sorted_points, total_distance, number_of_lines);
}

void exhaustive_algorithm(vector<point>point_vec, int number_of_lines){
    double min_distance=9999999;
    vector<point> sorted_points;
    point dummy = point_vec[0];// i am keeping the first point in a dummy variable, so that I sort the other without the first point, as the firts point is always the beginning point. 
    point_vec.erase(point_vec.begin(), point_vec.begin()+1);
    sort(point_vec.begin(), point_vec.end());
    point_vec.insert(point_vec.begin(), dummy);
    int count;
    do{
        count++;
        double temp_distance=0;
        for(int i=0;i<number_of_lines-1;i++){
            temp_distance+=distance(point_vec[i], point_vec[i+1]);//get the distance traveled in this path
        }
        temp_distance += distance(point_vec.back(), point_vec[0]); //the distance to go back to initial point
        if(temp_distance < min_distance){
            min_distance = temp_distance;
            sorted_points = point_vec;
        }
        
    } while(next_permutation(point_vec.begin(), point_vec.end())); //as long as there are permutations to go through, keep going
    sorted_points.push_back(sorted_points[0]); //adding the initial point that we are going to go back to. 
    print_result("Exhaustive algorithm", sorted_points, min_distance, number_of_lines);
    cout<<count<<endl;
}


void print_result(string nameOftheAlgo, vector<point> sorted_points, double total_distance, int number_of_lines){
    cout<<"Result of "<<nameOftheAlgo<<endl<<"The path of the points are"<<endl;
    for(int i=0;i<number_of_lines+1;i++) { //+1 becasue I want to show the whole path
        cout<<sorted_points[i]<<endl;
    }
    cout<<"The total distance is: "<<total_distance<<endl;
}
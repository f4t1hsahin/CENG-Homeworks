#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <utility>
#include <functional>
#include <unordered_set>
#include <queue>
#include <algorithm>
using namespace std;


class Solver {
private:
	vector<vector<int>> undirected_adj_mat;
	vector<vector<int> > directed_adj_mat;
	vector<vector<pair<int, int> > > directed_adj_list;
	unordered_set<int> odds, evens;
	unordered_set<int> rewarded;
	vector<pair<int,int>> rewards;
	int ammo, v, bunnie, scientiest, key;
public:

	void read_inp(){
		ifstream myfile("the3.inp");
		int ammo, v, bunnie, scientiest, key;
		unordered_set<int> odds, evens;
		unordered_set<int> rewarded;
		vector<pair<int,int>> rewards;
		myfile >> ammo;
		myfile >> v;
		myfile >> bunnie;
		myfile >> key;
		myfile  >> scientiest;
		int num_evens, num_odds;
		myfile >> num_odds;
		for(int i = 0; i < num_odds; ++i){
			int temp;
			myfile >> temp;
			odds.insert(temp);
		}
		myfile >> num_evens;
		for(int i = 0; i < num_evens; ++i){
			int temp;
			myfile >> temp;
			evens.insert(temp);
		}
		vector<vector<int> > directed_adj_mat(v + 1, vector<int>(v + 1,INT_MAX));
		vector<vector<int> > undirected_adj_mat(v + 1, vector<int>(v + 1,INT_MAX));
		vector<vector<pair<int, int> > > adj_list(v + 1,vector<pair<int, int>>());
		int num_edges;
		myfile >> num_edges;
		for(int i = 0; i < num_edges; ++i){
			int from, to, weight;
			myfile >> from >> to >> weight;
			undirected_adj_mat[from][to] = undirected_adj_mat[to][from] = weight;
			directed_adj_mat[from][to] = directed_adj_mat[to][from] = weight;
			adj_list[from].push_back(make_pair(to, weight));
			adj_list[to].push_back(make_pair(from, weight));
		}
		int num_rewards;
		myfile >> num_rewards;
		for(int i = 0; i < num_rewards; ++i){
			int temp_v, temp_reward;
			myfile >> temp_v >> temp_reward;
			rewards.push_back(make_pair(temp_v, temp_reward));
			rewarded.insert(temp_v);
		}


		myfile.close();

		this -> undirected_adj_mat = undirected_adj_mat;
		this -> directed_adj_mat = directed_adj_mat;
		this -> directed_adj_list = adj_list;
		this -> odds = odds;
		this -> evens = evens;
		this -> v = v;
		this -> ammo = ammo;
		this -> rewards = rewards;
		this -> bunnie = bunnie;
		this -> scientiest = scientiest;
		this -> key = key;
		this -> rewarded = rewarded;
	}

	void print_2d_array(vector<vector<int>> & arr){
		for(int i = 0; i < arr.size(); i++){
			for(int j = 0; j < arr[i].size(); j++){
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}
	void print_adj_list(vector<vector<pair<int, int> > > & arr){
		for(int i = 0; i < arr.size(); ++i){
			if(arr[i].size() == 0)
				cout << endl;
			for(int j = 0; j < arr[i].size(); ++j){
				cout << "Vertex:  " << arr[i][j].first << " Weight:  " << arr[i][j].second << " ";
			}
			cout << endl;
		}
	}

	void print_variables(){
		cout << "Ammo: " << this -> ammo << endl;
		cout << "V: " << this -> v << endl;
		cout << "Bunnie: " << this -> bunnie << endl;
		cout << "Scientiest: " << this -> scientiest << endl;
		cout << "Key: " << this -> key << endl;
		cout << "Undirected Adj Mat: " << endl;
		print_2d_array(this -> undirected_adj_mat);
		cout << "Directed Adj Mat: " << endl;
		print_2d_array(this -> directed_adj_mat);
		cout << "Adj list:" << endl;
		print_adj_list(this -> directed_adj_list);
		cout << "Odds:" << endl;
		for(auto odd: this -> odds)
			cout << odd << " ";
		cout << endl;
		cout << "Evens:" << endl;
		for(auto even: this -> evens)
			cout << even << " ";
		cout << endl;
		cout << "Rewards: " << endl;
		for(auto reward: rewards)
			cout << reward.first << " " << reward.second << " ";
		cout << endl;

	}


	void make_it_directed(){
		
		for(int i = 0; i < this -> rewards.size(); ++i){
			int vertex, reward;
			vertex = rewards[i].first;
			reward = rewards[i].second;
			for(int j = 0; j < this -> directed_adj_mat.size(); ++j){
				if(this -> directed_adj_mat[j][vertex] != INT_MAX)
					this -> directed_adj_mat[j][vertex] -= reward;
			}
			for(int j = 0; j < this -> v; ++j){
				for(int k = 0; k < this -> directed_adj_list[j].size(); ++k){
					if((this -> directed_adj_list[j][k]).first == vertex){
						(this -> directed_adj_list[j][k]).second -= reward;
					}
				}

			}
		}
	}

	bool isContainReward(unordered_set<int> rewarded,int vertex){
		auto res = (rewarded).find(vertex);
		return (res != (rewarded).end());
	}

	bool isLockOdd(int vertex){
		auto res = (this -> odds).find(vertex);
		return (res != (this -> odds).end());
	}

	bool isLockEven(int vertex){
		auto res = (this -> evens).find(vertex);
		return (res != (this -> evens).end());
	}

	void showpq(priority_queue< pair<int, int>, vector< pair<int, int> >, greater<pair<int, int>> > gq) 
	{ 
		cout << "PRINTING QUEUE" << endl;
	    priority_queue< pair<int, int>, vector< pair<int, int> >, greater<pair<int, int>> > g = gq;
	    if(g.empty()){
	    	cout << "QUEUE IS EMPTY" <<endl;
	    }
	    while (!g.empty()) 
	    { 
	        cout << "VERTEX:  " <<  g.top().second << " WEIGHT:  " << g.top().first << endl; 
	        g.pop(); 
	    } 
	}

	bool mycomparer(std::pair<int, int> lhs, std::pair<int, int> rhs) {
	    return lhs.first < rhs.first;
	}

	pair<vector<int>, pair<int, int> > shortest_path(int start, int end, int start_time){
		priority_queue< pair<int, int>, vector< pair<int, int> >, greater<pair<int, int>> > pq;
		vector<int> distances(this -> v + 1, INT_MAX);
		distances[start] = 0;
		pq.push(make_pair(0, start));
		auto temp_directed_adj_mat = this -> directed_adj_mat;
		auto temp_directed_adj_list = this -> directed_adj_list;
		vector<int> visited;
		vector<int> parents(this -> v + 1, -1);
		vector<vector<int> > all_parents(this -> v + 1);
		int iteration = 0;
		unordered_set<int> temp_rewarded = this -> rewarded;
		while(!pq.empty()){
			//start_time++;
			//showpq(pq);
			bool isTimeOdd = (start_time % 2) == 1;
			bool isTimeEven = (start_time % 2) == 0;
			auto temp = pq.top();
			pq.pop();
			int vertex = temp.second;
			int weight = temp.first;
			//cout << "Time:  " << start_time << "  Vertes:  " << vertex << "  Weight: " << weight << endl;
			if(isTimeOdd){
				vector<int> temp_vertices;
				vector<int> temp_weights;
				//cout << "IN ODDS" << endl; 
				//cout << "Vertex:  " << vertex << "  Is lock ?  " << isLockOdd(vertex) << endl;
				//showpq(pq);
				while(isLockOdd(vertex)){
					//cout << "IN LOCK ODD" << endl;
					temp_vertices.push_back(vertex);
					temp_weights.push_back(weight);
					auto temp_pair = pq.top();
					vertex = temp_pair.second;
					weight = temp_pair.first;
					//cout << "AFTER CHANGE " <<endl;
					//cout << "Vertex:  " << vertex << "  Weight:  " << weight << "  Is lock ? " << isLockOdd(vertex) << endl;
					//for(auto odd : this -> odds){
					//	cout << odd << " ";
					//}
					//cout << endl;
					pq.pop();
				}
				for(int i = 0; i < temp_vertices.size(); ++i){
					pq.push(make_pair(temp_weights[i], temp_vertices[i]));
				}					
			}
			if(isTimeEven){
				vector<int> temp_vertices;
				vector<int> temp_weights;
				//cout << "IN EVENS" << endl; 
				//cout << "Vertex:  " << vertex << "  Is lock ?  " << isLockEven(vertex) << endl;
				//showpq(pq);
				while(isLockEven(vertex)){
					//cout << "IN LOCK EVEN" << endl;
					temp_vertices.push_back(vertex);
					temp_weights.push_back(weight);
					auto temp_pair = pq.top();
					vertex = temp_pair.second;
					weight = temp_pair.first;
					//cout << "AFTER CHANGE " <<endl;
					//cout << "Vertex:  " << vertex << "  Weight:  " << weight << "  Is lock ? " << isLockOdd(vertex) << endl;
					//for(auto even : this -> evens){
					//	cout << even << " ";
					//}
					//cout << endl;
					//showpq(pq);
					pq.pop();
				}
				for(int i = 0; i < temp_vertices.size(); ++i){
					pq.push(make_pair(temp_weights[i], temp_vertices[i]));
				}
			}
			//cout << "AFTER CHOOSING THE VERTEX" << endl;
			//cout << "Vertex:  " << vertex << "  Weight:  " << weight << endl;
			//cout << "is contain reward   " << isContainReward(temp_rewarded, vertex) << endl;
			if(isContainReward(temp_rewarded, vertex)){
				//cout << "CONTAIN REWARD CHANGING GRAPH VERTEX IS   " << vertex << endl;
				//print_variables();
				for(auto it = (temp_rewarded).begin(); it != (temp_rewarded).end(); ++it){
					if(*it == vertex){
						(temp_rewarded).erase(it);
						break;
					}
				}
				for(int i = 0; i < this -> v; ++i){
					temp_directed_adj_mat[i][vertex] = this -> undirected_adj_mat[i][vertex];

				}
				for(int j = 0; j < this -> v; ++j){
					for(int k = 0; k < temp_directed_adj_list[j].size(); ++k){
						if((temp_directed_adj_list[j][k]).first == vertex){
							(temp_directed_adj_list[j][k]).second = this -> undirected_adj_mat[j][vertex];
						}
					}

				}
				//cout << "AFTER CHANGE" << endl;
				//print_variables();
			}
			//showpq(pq);
			if(vertex == end){
				//cout << "FOUND VERTEX" << endl;
				//cout << "DISTANCES" << endl;
				//for(auto dist : distances){
					//cout << dist << " ";
				//}
				//cout << endl;
				break;
			}
			auto edges = temp_directed_adj_list[vertex];
			//cout << "EDGES" << endl;
			//for(auto edge : edges)
			//	cout << edge.first << " " << edge.second << endl;
			//cout << endl;
			//cout << "DISTANCES" << endl;
			//for(auto dist : distances){
			//	cout << dist << " ";
			//}
			//cout << endl;
			for(auto edge : edges){
				int temp_vertex = edge.first;
				int temp_weight = edge.second;
				//cout << "EDGE   " << edge.first << endl;
				//cout << "WEIGHT  " << edge.second << endl; 
				//cout << "Dist   " <<  distances[temp_vertex] << endl;
				if(distances[temp_vertex] > distances[vertex] + temp_weight){
					//cout << "IS IN ?  " << endl;
					distances[temp_vertex] = distances[vertex] + temp_weight;
					//cout << "New dist  " << distances[temp_vertex] << endl;
					//cout << "Temp vertex  " << temp_vertex << endl;
					parents[temp_vertex] = vertex;
					all_parents[temp_vertex].push_back(vertex);
					pq.push(make_pair(distances[temp_vertex], temp_vertex));

				}
			}
			start_time++;
			//showpq(pq);
		}
		//cout << "END_TIME   " << start_time << endl;
		//cout << "DISTANCES" << endl;
			//for(auto dist : distances){
			//	cout << dist << " ";
			//}
			//cout << endl;

		//cout << "PARENTS "<< endl;
		//for(auto parent: parents)
		//	cout << parent << " ";
		//cout << endl;
		/*
		int indexx = 0;
		for(auto parentso : all_parents){
			cout << "Parents of " << indexx++ << endl;
			for(auto parent : parentso){
				cout << parent << " ";
			}
			cout << endl;
		}
		
		
		cout << "Start  " << start << " End   " << end << endl;
		cout << "Enddd   " << parents[58] << endl;
		cout << "Endddo " << parents[parents[end]] << endl;
		cout << "Enddasddo " << parents[parents[parents[end]]] << endl;
		cout << "Enddasddo " << parents[parents[parents[parents[end]]]] << endl;
		cout << "Enddasddo " << parents[parents[parents[parents[parents[end]]]]] << endl;
		cout << "Enddasddo " << parents[parents[parents[parents[parents[parents[end]]]]]] << endl;
		cout << "Enddasddo " << parents[parents[parents[parents[parents[parents[parents[end]]]]]]] << endl;
		cout << "Enddasddo " << parents[parents[parents[parents[parents[parents[parents[parents[end]]]]]]]] << endl;
		*/

		vector<int> seens;
		seens.push_back(end);
		visited.push_back(end);
		int parent_temp = parents[end];
		/*
		cout << "Parent temp  " << parent_temp << endl;
		for(auto parent : parents)
			cout << parent << " ";
		cout << endl;
		cout << "START  " << start << endl;
		cout << "END   " << end << endl;
		cout << "Enddd   " << parents[34] << endl;
		cout << "SEENS  " << endl;
		for(auto seen : seens)
			cout << seen << " ";
		cout << endl;
		*/
		while(1){
			//cout << "ENTER  Parent temp  " << parent_temp << endl;
			int temp_index = 0;
			int temp_parent_temp;

			if(parent_temp == start)
				break;
			seens.push_back(parent_temp);
			visited.insert(visited.begin(), parent_temp);
			//cout << "Parent temp  " << parent_temp << endl;
			//cout << "Parent parent temp  " << all_parents[parent_temp][all_parents[parent_temp].size() - 1] << endl;
			parent_temp = parents[parent_temp];

			if(find(seens.begin(), seens.end(), parent_temp) != seens.end()){
				//cout << "SEEN BEFORE  " << parent_temp << endl;
				auto temp_parents = all_parents[parent_temp];
				if(temp_parents.size() >= 2){
					temp_parent_temp = temp_parents[temp_parents.size() - 2];
					//cout << "TEMP PARENT TEMP  " << temp_parent_temp << endl;
					temp_index = 0;
					while(find(seens.begin(), seens.end(), temp_parent_temp) != seens.end()){
						//cout << "SEEN BEFORE SEEN BEFORE  " << temp_parent_temp << endl;
						if(temp_index + 2 <= temp_parents.size())
							temp_parent_temp = temp_parents[temp_parents.size() - 2 - temp_index++];
						else{
							temp_parent_temp = temp_parents[0];
							break;
						}
					}
					parent_temp = temp_parent_temp;
					//cout << "Choosen parent  " << parent_temp << endl;
				}
				else
					parent_temp = temp_parents[0];
			}
		}
		//cout << "START  " << start << "   END  " << end << endl;
		//cout << "BEFORE" << endl << endl;;
		//print_variables();
		for(auto vertexs : visited){
			if(isContainReward(this -> rewarded, vertexs)){

				for(int i = 0; i < this -> v; ++i){
							this -> directed_adj_mat[i][vertexs] = this -> undirected_adj_mat[i][vertexs];
						}
						for(int j = 0; j < this -> v; ++j){
							for(int k = 0; k < directed_adj_list[j].size(); ++k){
								if((directed_adj_list[j][k]).first == vertexs){
									(this -> directed_adj_list[j][k]).second = this -> undirected_adj_mat[j][vertexs];
								}
							}

						}
			}
		}
		//cout << "AFTER" << endl << endl;;

		//print_variables();
		return make_pair(visited, make_pair(distances[end], start_time));
	}

	void solve_all(){
		read_inp();
		//print_variables();
		make_it_directed();
		//print_variables();
		vector<int> all_route;
		int total_weight = 0;
		all_route.push_back(1);
		auto first_result = shortest_path(1, this -> key, 1);
		for(auto y : first_result.first){
			all_route.push_back(y);
		}
		total_weight += first_result.second.first;
		//print_variables();
		auto second_result = shortest_path(this -> key, this -> scientiest, first_result.second.first);
		for(auto y : second_result.first){
			all_route.push_back(y);
		}
		total_weight += second_result.second.first;
		//print_variables();
		auto third_result = shortest_path(this -> scientiest, this -> bunnie, second_result.second.first);
		for(auto y : third_result.first){
			all_route.push_back(y);
		}
		total_weight += third_result.second.first;
		//print_variables();

		cout << this -> ammo - total_weight << endl;
		cout << all_route.size() << endl;
		for(auto route : all_route)
			cout << route << " ";
		cout << endl;

	}


};




int main(){
	Solver solver;
	solver.solve_all();
	/*
	solver.read_inp();
	solver.print_variables();
	solver.make_it_directed();
	solver.print_variables();
	auto x = solver.shortest_path(1, 3, 1);
	vector<int> all_route;
	all_route.push_back(1);
	int total_weight = 0;
	cout << "VISITED" << endl;
	for(auto y : x.first){
		cout << y << " ";
		all_route.push_back(y);
	}
	cout << endl;
	total_weight += x.second.first;
	cout << "Distance:  " << x.second.first << endl;
	cout << "TIME   " << x.second.second << endl;
	cout << "********************************************************" << endl;
	auto w = solver.shortest_path(3, 4, x.second.second);
	cout << "VISITED" << endl;
	for(auto y : w.first){
		cout << y << " ";
		all_route.push_back(y);
	}
	cout << endl;
	total_weight += w.second.first;

	cout << "Distance:  " << w.second.first << endl;
	cout << "TIME   " << w.second.second << endl;

	cout << "********************************************************" << endl;
	auto t = solver.shortest_path(4, 6, w.second.second);
	cout << "VISITED" << endl;
	for(auto y : t.first){
		cout << y << " ";
		all_route.push_back(y);
	}
	cout << endl;
	total_weight += t.second.first;

	cout << "Distance:  " << t.second.first << endl;
	cout << "TIME   " << w.second.second << endl;
	cout << "********************************************************" << endl;

	cout <<"ANSWER" << endl;

	for(auto vertex : all_route)
		cout << vertex << " ";
	cout << endl;
	
	cout << "ALL Distance:  " << total_weight << endl;
	*/


}

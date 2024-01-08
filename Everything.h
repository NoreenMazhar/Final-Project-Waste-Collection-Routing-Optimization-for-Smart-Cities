#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <vector>	
using namespace std;

void Unique(vector<string> &str)
{
	for (int i = 0; i < str.size(); i++)
	{
		for (int j = i + 1; j < str.size(); j++)
		{
			if (str[i] == str[j])
			{
				str.erase(str.begin() + j);
				j--;
			}
		}
	}
}

struct Bin
{
	string name;
	float fillLevel;
	string location;
	string region;
	bool Collected;
};

template <typename T, typename U>
struct Pair {
	T first;
	U second;
	bool operator<(const Pair<T, U>& other) const {
		return (second < other.second) || (second == other.second);
	}
};

template <typename T, typename U>
Pair<T, U> Make_pair(T f, U s)
{
	Pair<T, U> temp;
	temp.first = f;
	temp.second = s;
	return temp;
}

vector<string> split(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while (getline(ss, tok, delimiter))
	{
		internal.push_back(tok);
	}

	return internal;
}

template <typename T>
class PriorityQueue {
private:
	vector<T> heap;

	void heapifyUp(int index) {
		int parent = (index - 1) / 2;
		while (index > 0 && heap[index] < heap[parent]) {
			swap(heap[index], heap[parent]);
			index = parent;
			parent = (index - 1) / 2;
		}
	}

	void heapifyDown(int index) {
		int leftChild, rightChild, minIndex;
		while (true) {
			leftChild = 2 * index + 1;
			rightChild = 2 * index + 2;
			minIndex = index;

			if (leftChild < heap.size() && heap[leftChild] < heap[minIndex])
				minIndex = leftChild;

			if (rightChild < heap.size() && heap[rightChild] < heap[minIndex])
				minIndex = rightChild;

			if (minIndex != index) {
				swap(heap[index], heap[minIndex]);
				index = minIndex;
			}
			else {
				break;
			}
		}
	}

public:
	bool empty()  {
		return heap.empty();
	}

	int size()  {
		return heap.size();
	}

	const T& top()  {
		if (heap.empty()) {
			throw out_of_range("PriorityQueue is empty");
		}
		return heap[0];
	}

	void push(const T& value) {
		heap.push_back(value);
		heapifyUp(heap.size() - 1);
	}

	void pop() {
		if (heap.empty()) {
			throw out_of_range("PriorityQueue is empty");
		}

		heap[0] = heap.back();
		heap.pop_back();
		heapifyDown(0);
	}
};

class Graph
{
public:
	Graph()
	{
		vector<string> locations;
		fstream file;
		file.open("Data.csv");
		string line;
		bool flag = true;
		int k = 0;
		while (getline(file, line))
		{
			if (flag)
			{
				flag = false;
				locations = split(line, ',');
				locations.erase(locations.begin());
				V = locations.size();
				coordinate.resize(V);
				for (int i = 0; i < V; i++)
				{
					coordinate[i].resize(V);
				}
				for (int i = 0; i < V; i++)
				{
					for (int j = 0; j < V; j++)
					{
						coordinate[i][j].first = locations[j];
						coordinate[i][j].second = INFINITY;
					}
				}
				continue;
			}
			vector<string> temp = split(line, ',');
			temp.erase(temp.begin());

			for (int i = 0; i < temp.size(); i++)
			{
				if ((temp[i] != " ") && (temp [i] != ""))
				{
					cout << temp[i] << "->";
					coordinate[k][i].second = stof(temp[i]);
				}
				else {
					coordinate[k][i].second = INFINITY;
				}
			}
			k++;
		}
		file.close();

		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				coordinate[j][i].second = coordinate[i][j].second;
			}
		}

		file.open("Region.csv");
		flag = true;
		while (getline(file, line))
		{
			Pair<string, string> temp;
			if (flag)
			{
				flag = false;
				continue;
			}
			vector<string> temp2 = split(line, ',');
			temp.first = temp2[1];
			temp.second = temp2[0];
			region.push_back(temp);
		}
		file.close();

		file.open("Bin.csv");
		flag = true;
		while (getline(file, line))
		{
			Bin temp;
			if (flag)
			{
				flag = false;
				continue;
			}
			vector<string> temp2 = split(line, ',');
			temp.name = temp2[0];
			temp.fillLevel = stof(temp2[1]);
			temp.location = temp2[2];
			temp.region = temp2[3];
			temp.Collected = stoi(temp2[4]);
			bins.push_back(temp);
		}
		file.close();
	}
	void Print()
	{
		cout << endl;
		cout << endl;
		//displaying the graph with cost to travel from one vertex to another
		cout << "\t\t\t\t";
		for (int i = 0; i < region.size(); i++)
		{
			cout << region[i].first << "\t";
		}
		cout << endl;
		for (int i = 0; i < coordinate.size(); i++)
		{
			cout << "\t\t\t";
			cout << region[i].first << "\t";
			for (int j = 0; j < coordinate[i].size(); j++)
			{
				if (coordinate[i][j].second != INT_MAX)
					cout << coordinate[i][j].second << "\t";
				else
					cout << "\t";
			}
			cout << endl;
		}
	}
	void PrintInRegion(string region)
	{
		int j = 1;
		cout << endl;
		cout << endl;
		cout << "\t\t\tVertex in Region" << endl;
		cout << "\t\t\tName FillLevel Location Region" << endl;
		for (int i = 0; i < bins.size(); i++)
		{
			if (bins[i].region == region)
			{
				cout << "\t\t\t" << j << ". " << bins[i].name << " " << bins[i].fillLevel << " " << bins[i].location << " " << bins[i].region << endl;
				j++;
			}
		}
	}
	void PrintRegion()
	{
		for (int i = 0; i < region.size(); i++)
		{
			cout << region[i].first << " " << region[i].second << endl;
		}
	}
	vector<Pair<string, float>> findShortestPath(string start, string end) {
		vector<float> dist(V, INFINITY);
		vector<int> prev(V, -1);
		vector<bool> visited(V, false);

		int startIndex = -1, endIndex = -1;

		for (int i = 0; i < region.size(); ++i) {
			if (region[i].first == start) {
				startIndex = i;
			}
			if (region[i].first == end) {
				endIndex = i;
			}
		}

		if (startIndex == -1 || endIndex == -1) {
			cout << "Start or end state not found in the graph." << endl;
			return vector<Pair<string, float>>();
		}

		dist[startIndex] = 0;
		PriorityQueue<Pair<float, int>> minHeap;
		minHeap.push(Make_pair<float, int>(0, startIndex));

		while (!minHeap.empty()) {
			int u = minHeap.top().second;
			minHeap.pop();

			if (visited[u]) continue;
			visited[u] = true;

			for (int v = 0; v < V; ++v) {
				if (!visited[v] && coordinate[u][v].second != INFINITY) {
					if (dist[v] > dist[u] + coordinate[u][v].second) {
						dist[v] = dist[u] + coordinate[u][v].second;
						prev[v] = u;
						minHeap.push(Make_pair(dist[v], v));
					}
				}
			}
		}

		if (dist[endIndex] == INFINITY) {
			cout << "There is no path between the given states." << endl;
			return vector<Pair<string, float>>();
		}

		vector<Pair<string, float>> shortestPath; //saving path taken and time taken
		for (int at = endIndex; at != -1; at = prev[at]) {
			//shortestPath.push_back(Make_pair<string,float>(region[at].first,));
			shortestPath.push_back(Make_pair<string, float>(region[at].first, dist[at]));
		}
		reverse(shortestPath.begin(), shortestPath.end());

		//Bin collection if the level is above 75%
		for (int i = 0; i < shortestPath.size(); i++)
		{
			for (int j = 0; j < bins.size(); j++)
			{
				if (bins[j].region == shortestPath[i].first && bins[j].fillLevel > 75 && bins[i].Collected == false)
				{
					bins[j].Collected = true;
					bins[j].fillLevel = 0;
				}
			}
		}

		return shortestPath;
	}
	vector<Pair<string, float>> findShortestPathWithinRegion(string startRegion, string endRegion) {
		int startIndex = -1, endIndex = -1;

		for (int i = 0; i < region.size(); ++i) {
			if (region[i].first == startRegion) {
				startIndex = i;
			}
			if (region[i].first == endRegion) {
				endIndex = i;
			}
		}

		if (startIndex == -1 || endIndex == -1) {
			cout << "Start or end region not found in the graph." << endl;
			return vector<Pair<string, float>>();
		}

		return findShortestPathWithinRegion(region[startIndex].second, region[endIndex].second);
	}
	void addEdge(string start, string end, float weight)
	{
		int startIndex = -1, endIndex = -1;

		for (int i = 0; i < region.size(); ++i) {
			if (region[i].first == start) {
				startIndex = i;
			}
			if (region[i].first == end) {
				endIndex = i;
			}
		}

		if (startIndex == -1 || endIndex == -1) {
			cout << endl;
			cout << endl;
			cout << "\t\t\tStart or end state not found in the graph." << endl;
			return;
		}

		coordinate[startIndex][endIndex].second = weight;
		coordinate[endIndex][startIndex].second = weight;
	}
	void DeleteEdge(string start, string end)
	{
		int startIndex = -1, endIndex = -1;

		for (int i = 0; i < region.size(); ++i) {
			if (region[i].first == start) {
				startIndex = i;
			}
			if (region[i].first == end) {
				endIndex = i;
			}
		}

		if (startIndex == -1 || endIndex == -1) {
			cout << endl;
			cout << endl;
			cout << "\t\t\tStart or end state not found in the graph." << endl;
			return;
		}

		coordinate[startIndex][endIndex].second = INFINITY;
		coordinate[endIndex][startIndex].second = INFINITY;
	}
	void AddBin(string name, float fillLevel, string location, string region)
	{
		Bin temp;
		temp.name = name;
		temp.fillLevel = fillLevel;
		temp.location = location;
		temp.region = region;
		temp.Collected = false;
		bins.push_back(temp);
	}
	void DeleteBin(string name)
	{
		for (int i = 0; i < bins.size(); i++)
		{
			if (bins[i].name == name)
			{
				bins.erase(bins.begin() + i);
				break;
			}
		}
	}
	~Graph()
	{
		fstream file;
		file.open("Data.csv", ios::out);
		file << "Time,";
		for (int i = 0; i < region.size(); i++)
		{
			file << region[i].first << ",";
		}
		file << endl;
		for (int i = 0; i < coordinate.size(); i++)
		{
			file << region[i].first << ",";
			for (int j = 0; j < coordinate[i].size(); j++)
			{
				if (coordinate[i][j].second != INT_MAX)
					file << coordinate[i][j].second << ",";
				else
					file << ",";
			}
			file << endl;
		}
		file.close();

		file.open("Region.csv", ios::out);
		file << "Region,Name" << endl;
		for (int i = 0; i < region.size(); i++)
		{
			file << region[i].second << "," << region[i].first << endl;
		}
		file.close();

		file.open("Bin.csv", ios::out);
		file << "Name,Fill Level,Location,Region,Collected" << endl;
		for (int i = 0; i < bins.size(); i++)
		{
			file << bins[i].name << "," << bins[i].fillLevel << "," << bins[i].location << "," << bins[i].region << "," << bins[i].Collected << endl;
		}
		file.close();
	}
public:
	int V;
	vector<vector<Pair<string, float>>> coordinate;
	vector<Pair<string, string>> region;
	vector<Bin> bins;
};

class User
{
protected:
	string email;
	string password;
	string name;
	string phone;
	string role;
public:
	User()
	{
		email = "";
		password = "";
		name = "";
		phone = "";
		role = "";
	}
	User(string email, string password, string name, string phone,string role)
	{
		this->email = email;
		this->password = password;
		this->name = name;
		this->phone = phone;
		this->role = role;
	}
	void setEmail(string email)
	{
		this->email = email;
	}
	void setPassword(string password)
	{
		this->password = password;
	}
	void setName(string name)
	{
		this->name = name;
	}
	void setPhone(string phone)
	{
		this->phone = phone;
	}
	string getEmail()
	{
		return email;
	}
	string getPassword()
	{
		return password;
	}
	string getName()
	{
		return name;
	}
	string getPhone()
	{
		return phone;
	}
	void setRole(string role)
	{
		this->role = role;
	}
	string getRole()
	{
		return role;
	}

};

class Controller : public User
{
public:
	Controller()
	{
		email = "";
		password = "";
		name = "";
		phone = "";
	}
	Controller(string email, string password, string name, string phone)
	{
		this->email = email;
		this->password = password;
		this->name = name;
		this->phone = phone;
	}
	int controllerMenu(Graph& g)
	{
		int choice;
		string start, end;
		float weight;
		do
		{
			system("cls");
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\t\t1. View Bin Fill Data" << endl;
			cout << "\t\t\t\t2. Set Collection Threshold" << endl;
			cout << "\t\t\t\t3. Select Truck Departure Location" << endl;
			cout << "\t\t\t\t4. Schedule Collection" << endl;
			cout << "\t\t\t\t5. Allocate Truck" << endl;
			cout << "\t\t\t\t6. Recheck Bin" << endl;
			cout << "\t\t\t\t7. Add vertex" << endl;
			cout << "\t\t\t\t8. View Graph" << endl;
			cout << "\t\t\t\t9. Exit" << endl;
			cout << "\t\t\t\tEnter Choice: ";
			cin >> choice;
			switch (choice)
			{
			case 1:
				ViewBinFillData(g);
				break;
			case 2:
				SetCollectionThreshold(g);
				break;
			case 3:
				SelectTruckDepartureLocation(g);
				break;
			case 4:
				ScheduleCollection(g);
				break;
			case 5:
				AllocateTruck(g);
				break;
			case 6:
				RecheckBin(g);
				break;
			case 7:
				cout << endl;
				cout << endl;
				cout << "\t\t\tEnter the starting vertex : ";
				cin >> start;
				cout << "\t\t\tEnter the ending vertex : ";
				cin >> end;
				cout << "\t\t\tEnter the weight : ";
				cin >> weight;
				g.addEdge(start, end, weight);
				break;
			case 8:
				g.Print();
				break;
			case 9:
				return 0;
				
			default:
				cout << "Invalid Choice" << endl;
				break;
			}
			system("pause");
		} while (choice != 9);
	}
	void ViewBinFillData(Graph& g)
	{
		srand(time(NULL));
		int hour = rand() % 24;
		cout << endl << endl;
		cout << "\t\t\tHour: " << hour << endl;

		cout << endl;
		cout << endl;
		cout << "\t\t\tOverfilled Bins" << endl;

		cout << "\t\t\tName FillLevel Location Region" << endl;
		for (int i = 0; i < g.bins.size(); i++)
		{
			if (g.bins[i].fillLevel > 75)
			{
				cout << "\t\t\t" << i + 1 << ". " << g.bins[i].name << " " << g.bins[i].fillLevel << " " << g.bins[i].location << " " << g.bins[i].region << endl;
			}
		}
	}
	void SetCollectionThreshold(Graph& g)
	{
		int j = 1;
		cout << endl;
		cout << endl;
		cout << "\t\t\tOverfilled Bins Being flagged to be collected" << endl;
		for (int i = 0; i < g.bins.size(); i++)
		{
			if (g.bins[i].fillLevel > 75)
			{
				g.bins[i].Collected = true;
				cout << "\t\t\t" << j << "." << g.bins[i].name << " " << g.bins[i].fillLevel << " " << g.bins[i].location << " " << g.bins[i].region << endl;
				j++;
			}
		}
	}
	void SelectTruckDepartureLocation(Graph& g)
	{
		cout << endl;
		cout << endl;
		srand(time(NULL));
		int index = rand() % 5;
		cout << "\t\t\tTruck Departure Location: " << g.region[index].first << endl;
	}
	void ScheduleCollection(Graph& g)
	{
		srand(time(NULL));
		int hour = rand() % 24;
		int j = 1;
		cout << "\t\t\tHour: " << hour << endl;
		cout << "\t\t\tOverfilled Bins" << endl;
		cout << "\t\t\tName FillLevel Location Region" << endl;
		for (int i = 0; i < g.bins.size(); i++)
		{
			if (g.bins[i].fillLevel > 75)
			{
				cout << "\t\t\t" << j << "." << g.bins[i].name << " " << g.bins[i].fillLevel << " " << g.bins[i].location << " " << g.bins[i].region << endl;
				j++;
			}
		}
	}
	void AllocateTruck(Graph& g)
	{
		srand(time(NULL));
		cout << endl;
		cout << endl;
		int index = rand() % 5;
		cout << "\t\tTruck Departure Location: " << g.region[index].first << endl;
	}
	void RecheckBin(Graph& g)
	{
		cout << endl;
		cout << endl;
		cout << "\t\t\tRechecking Bins " << endl;
		int j = 1;
		for (int i = 0; i < g.bins.size(); i++)
		{
			if (g.bins[i].fillLevel < 75)
			{
				g.bins[i].fillLevel += rand() % 50;
				cout << "\t\t\t" << j << "." << g.bins[i].name << " " << g.bins[i].fillLevel << " " << g.bins[i].location << " " << g.bins[i].region << endl;
				j++;
			}
		}
	}
};

class TruckDriver : public User
{
public:
	TruckDriver()
	{
		email = "";
		password = "";
		name = "";
		phone = "";
	}
	TruckDriver(string email, string password, string name, string phone)
	{
		this->email = email;
		this->password = password;
		this->name = name;
		this->phone = phone;
	}
	void ViewRoute(Graph& g)
	{
		srand(time(NULL));
		cout << endl;
		cout << endl;
		int hour = rand() % 24;
		cout << "\t\t\tHour: " << hour << endl;
		int j = 1;
		cout << "\t\t\tOverfilled Bins" << endl;
		cout << "\t\t\tName FillLevel Location Region" << endl;
		for (int i = 0; i < g.bins.size(); i++)
		{
			if (g.bins[i].fillLevel > 75)
			{
				cout << "\t\t\t" << j << "." << g.bins[i].name << " " << g.bins[i].fillLevel << " " << g.bins[i].location << " " << g.bins[i].region << endl;
				j++;
			}
		}
	}
	void PickUpRoute(Graph& g)
	{
		bool flag = false;
		string regioncheck = "";
		for (int i = 0; i < g.bins.size(); i++)
		{
			if (g.bins[i].fillLevel > 100)
			{
				flag = true;
				regioncheck = g.bins[i].region;
				break;
			}
		}

		if (flag == true)
		{
			cout << endl;
			cout << endl;
			cout<<setw(50)<<setfill('*')<<" "<<endl;
			cout << "\t\t\t\tPICK UP URGENCY" << endl;
			cout << "\t\t\t\tThere are bins that are overfilled" << endl;
			cout << "\t\t\t\tRegion: " << regioncheck << endl;
			cout << setw(50) << setfill('*') << " " << endl;

		}

		cout << "\t\t\t\tThe avaliable regions" << endl;
		cout << endl;

		//finding unique regions
		vector<string> temp;
		for (int i = 0; i < g.region.size(); i++)
		{
			temp.push_back(g.region[i].second);
		}
		Unique(temp);
		//Prinintg all teh regions avaliable
		for (int i = 0; i < temp.size(); i++)
		{
			cout << "\t\t\t\t " << i + 1 << ". " << temp[i] << endl;
		}

		string route;
		cout << "\t\t\t\tYour Seclected Route: ";
		cin >> route;

		for (int i = 0; i < g.region.size(); i++)
		{
			if (g.region[i].first == route)
			{
				cout << "\t\t\t\t" << g.region[i].first << " " << g.region[i].second << endl;
			}
		}
		char op;
		cout << endl;
		cout << endl;
		cout << "\t\t\t\tWould you like to Pick up: (Y,N) ";
		cin >> op;
		if (op == 'y' || op == 'Y')
		{
			//displaying the route for the selected region
			cout << endl;
			cout << endl;
			cout << setw(50) << setfill('*') << " " << endl;
			string start, end;
			cout << "\t\t\tEnter the starting vertex for the route: ";
			cin >> start;
			cout << "\t\t\tEnter the ending vertex for the route: ";
			cin >> end;
			vector<Pair<string, float>> ans = g.findShortestPath(start, end);
			cout << "\t\t\t\tPick up Route:\n\n\n";
			
			float sun = 0.0;
			for (int i = 0; i < ans.size(); i++)
			{
				cout << "\t\t\t";
				cout << ans[i].first << "--> cost " << ans[i].second << " min " << endl;
				sun += ans[i].second;
			}
			cout << endl;
			cout << endl;
			cout << "\t\t\tTotal Time: " << sun << " min" << endl;
		}
		else
		{
			cout << "\t\t\tPick up cancelled" << endl;
		}
	}
	void Menu(Graph& g)
	{
		int choice;
		do
		{
			system("cls");
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\t\t1. View Route" << endl;
			cout << "\t\t\t\t2. Pick Up Route" << endl;
			cout << "\t\t\t\t3. Exit" << endl;
			cout << "\t\t\t\tEnter Choice: ";
			cin >> choice;
			switch (choice)
			{
			case 1:
				ViewRoute(g);
				break;
			case 2:
				PickUpRoute(g);
				break;
			case 3:
				return;
				break;
			default:
				cout << "\t\t\tInvalid Choice" << endl;
				break;
			}
			system("pause");
		} while (choice != 3);
	}
};

class UI
{
public:
	UI()
	{
		fstream file;
		file.open("User.csv");
		string line;
		bool flag = true;
		while (getline(file, line))
		{
			if (flag)
			{
				flag = false;
				continue;
			}
			vector<string> temp = split(line, ',');
			User temp2(temp[0], temp[1], temp[2], temp[3],temp[4]);
			users.push_back(temp2);
		}
		file.close();
	}
	bool Check(string email, string password)
	{
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i].getEmail() == email && users[i].getPassword() == password)
			{
				return true;
			}
		}
		return false;
	}

	bool Login()
	{
		string email, password;
		int tries = 3;
		do {
			cout << "\t\t\t\tEnter Email: ";
			cin >> email;
			cout << "\t\t\t\tEnter Password: ";
			cin >> password;
			if (Check(email, password))
			{
				cout << "\t\t\t\tLogin Successful" << endl;
				system("pause");
				this->email=email;
this->pass=password;
				return true;
			}
			else
			{
				cout << "\t\t\t\tLogin Failed" << endl;
				cout << "\t\t\t\tTries Left: " << tries << endl;
				system("pause");
			}
		} while (tries--);
		return false;
	}

	int CheckNature(string email, string password)
	{
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i].getEmail() == email && users[i].getPassword() == password)
			{
				if (users[i].getRole() == "Controller")
				{
					return 1;
				}
				else
				{
					return 2;
				}
			}
		}
	}

	void Register()
	{
		string email, password, name, phone,role;
		cout << "\t\t\t\tEnter Email: ";
		cin >> email;
		cout << "\t\t\t\tEnter Password: ";
		cin >> password;
		cout << "\t\t\t\tEnter Name: ";
		cin >> name;
		cout << "\t\t\t\tEnter Phone: ";
		cin >> phone;
		cout << "\t\t\t\tEnter Role: ";
		cin >> role;
		User temp(email, password, name, phone,role);
		users.push_back(temp);
		fstream file;
		file.open("Users.csv", ios::out);
		file << "Email,Password,Name,Phone,Role" << endl;
		for (int i = 0; i < users.size(); i++)
		{
			file << users[i].getEmail() << "," << users[i].getPassword() << "," << users[i].getName() << "," << users[i].getPhone()<<","<<users[i].getRole() << endl;
		}
		file.close();
		cout << "\t\t\t\tRegistration Successful" << endl;
		system("pause");
	}

	string getEmail()
	{
		return email;
	}
	
	string getPassword()
	{
		return pass;
	}

private:
	vector<User> users;
	string email;
	string pass;
};
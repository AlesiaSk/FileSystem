#include <iostream>
#include <fstream>
#include<conio.h>
#include<stdio.h>
#include<string>
#include<vector>
#include <bitset>
#include <fstream>

#pragma warning(disable:4996)

using namespace std;

int SIZE_OF_BLOCK = 256;
vector<string> block(SIZE_OF_BLOCK);

struct file {
	string name;
	string type;
	vector<int> index;
};

struct ind {
	string file_name;
	vector<int> index;
};

struct catalog {
	string name;
	vector<file> files;
	vector<catalog> catalogs;
	bool isVisited = false;
};


void DIR(catalog dir) {
	for (int i = 0; i < dir.files.size(); i++) {
		cout << dir.files[i].name << endl;
	}

}

void ADD_TO_DIR(file file, catalog dir) {
	dir.files.push_back(file);
}

void DEL(catalog **dir, string filename) {
	int curr_size = (**dir).files.size();
	for (int i = 0; i < (**dir).files.size(); i++) {
		if ((**dir).files[i].name == filename) {
			(**dir).files.erase((**dir).files.begin() + i);
		}
	}
	if (curr_size == (**dir).files.size()) {
		cout << "Can't find this file";
	}
}

void RMDIR(catalog **dir, string deletable) {
	int curr_size = (**dir).catalogs.size();
	for (int i = 0; i < (**dir).catalogs.size(); i++) {
		catalog* temp = &(**dir).catalogs[i];
		if ((*temp).name == deletable) {
			(**dir).catalogs.erase((**dir).catalogs.begin() + i);
		}
	}
	if (curr_size == (**dir).catalogs.size()) {
		cout << "Can't find this file";
	}
	
}

catalog MD(string name) {
	catalog new_catalog;
	(new_catalog).name = name;
	return new_catalog;
}

file CREATE_FILE(string name, string type) {

	file *my_file = new file;
	(*my_file).name = name;
	(*my_file).type = type;
	return *my_file;
}

void WRITE(catalog **cur_catalog, string filename, string data, vector<ind> *vec) {
	for (int i = 0; i < (**cur_catalog).files.size(); i++) {
		if ((**cur_catalog).files[i].name == filename) {
			if ((**cur_catalog).files[i].type == "txt") {
				for (int k = 0; k < data.size(); k ++) {
					if (k += 7 < data.size()) {
						string r = data.substr(k-1, 8);
						bool isWrite = false;
						for (int j = 0; j < block.size(); j++) {
							if (block[j].empty() && !isWrite) {
								block[j] = r;
								for (int l = 0; l < (*vec).size(); l++) {
									if ((*vec)[l].file_name == filename) {
										(*vec)[l].index.push_back(j);
									}
								}
								isWrite = true;
								
							}
						}
					}
					else {
						string r = data.substr(k, data.size());
						bool isWrite = false;
						for (int j = 0; j < block.size(); j++) {
							if (block[j].empty() && !isWrite) {
								block[j] = r;
								for (int l = 0; l < (*vec).size(); l++) {
									if ((*vec)[l].file_name == filename) {
										(*vec)[l].index.push_back(j);
									}
								}
								isWrite = true;

							}
						}
					}

					k += 6;
				}
			}
			else {
				vector<bitset<8>> bin_data;
				for (int i = 0; i < data.size(); i++)
				{
					bin_data.push_back(data.c_str()[i]);
				}
				data = "";
				for (int i = 0; i < bin_data.size(); i++) {
					data += bin_data[i].to_string();
				}

				for (int k = 0; k < data.size(); k++) {
					if (k += 7 < data.size()) {
						string r = data.substr(k - 1, 8);
						bool isWrite = false;
						for (int j = 0; j < block.size(); j++) {
							if (block[j].empty() && !isWrite) {
								block[j] = r;
								for (int l = 0; l < (*vec).size(); l++) {
									if ((*vec)[l].file_name == filename) {
										(*vec)[l].index.push_back(j);
									}
								}
								isWrite = true;

							}
						}
					}
					else {
						string r = data.substr(k, data.size());
						for (int j = 0; j < block.size(); j++) {
							if (block[j].empty()) {
								block[j] = r;
								for (int l = 0; l < (*vec).size(); l++) {
									if ((*vec)[l].file_name == filename) {
										(*vec)[l].index.push_back(j);
									}
								}
								return;
							}
						}
					}

					k += 6;
				}
			}
			
		}
	}

}

void READ(catalog cur_catalog, string filename, vector<ind> vec) {
	for (int i = 0; i < cur_catalog.files.size(); i++) {
		if (cur_catalog.files[i].name == filename) {
			for (int l = 0; l < vec.size(); l++) {
				if (vec[l].file_name == cur_catalog.files[i].name) {
					for (int j = 0; j < vec[l].index.size(); j++) {
						cout << block[vec[l].index[j]];
						if ((j + 1) == vec[l].index.size()) {
							cout << endl;
						}
					}
				}
			}
		}
	}
}

void COPY(catalog **cur_catalog, string name) {
	int number_of_files = (**cur_catalog).files.size();
	int number_of_catalogs = (**cur_catalog).catalogs.size();

	for (int i = 0; i < (**cur_catalog).files.size(); i++) {
		if ((**cur_catalog).files[i].name == name) {
			string new_name = name + "_COPY";
			file new_file = CREATE_FILE(new_name, (**cur_catalog).files[i].type);
			(**cur_catalog).files.push_back(new_file);
		}

	}

	for (int i = 0; i < (**cur_catalog).catalogs.size(); i++) {
		if ((**cur_catalog).catalogs[i].name == name) {
			string new_name = name + "_COPY";
			catalog new_catalog = MD(new_name);
			(**cur_catalog).catalogs.push_back(new_catalog);
		}

	}

	if (number_of_catalogs == (**cur_catalog).catalogs.size() && number_of_files == (**cur_catalog).files.size()) {
		cout << "File with this name doesn't exist";
	}
}

void MOVE(vector<catalog*> path, string cur_name, string new_name, catalog **cur_catalog) {

	bool isMovable = false;
	for (int i = 0; i < (**cur_catalog).files.size(); i++) {
		if ((**cur_catalog).files[i].name == cur_name) {
			for (int j = 0; j < path.size(); j++) {
				if ((*path[j]).name == new_name) {
					(*path[j]).files.push_back((**cur_catalog).files[i]);
					DEL(cur_catalog, (**cur_catalog).files[i].name);
					isMovable = true;
				}
				else {
					for (int y = 0; y < (*path[j]).catalogs.size(); y++) {
						if ((*path[j]).catalogs[y].name == new_name) {
							(*path[j]).catalogs[y].files.push_back((**cur_catalog).files[i]);
							DEL(cur_catalog, (**cur_catalog).files[i].name);
							isMovable = true;
						}
					}
				}
			}
			if (!isMovable) {
				(**cur_catalog).files[i].name = new_name;
			}
		}
	}



	for (int i = 0; i < (**cur_catalog).catalogs.size(); i++) {
		if ((**cur_catalog).catalogs[i].name == cur_name) {
			for (int j = 0; j < path.size(); j++) {
				if ((*path[j]).name == new_name) {
					catalog temp = (**cur_catalog).catalogs[i];
					(*path[j]).catalogs.push_back(temp);
					RMDIR(cur_catalog, (**cur_catalog).catalogs[i].name);
					isMovable = true;
				}
				else {
					for (int y = 0; y < (*path[j]).catalogs.size(); y++) {
						if ((*path[j]).catalogs[y].name == new_name) {
							(*path[j]).catalogs[y].catalogs.push_back((**cur_catalog).catalogs[i]);
							RMDIR(cur_catalog, (**cur_catalog).catalogs[i].name);
							isMovable = true;
						}
					}
				}
			}
			if (!isMovable) {
				(**cur_catalog).catalogs[i].name = new_name;
			}
		}
	}
	
}


void main() { 
	string cases;
	string filename;
	string type;
	string req;
	catalog dir;
	catalog root = MD("root");
	vector<ind> index_vector;
	vector<catalog*> path;
	catalog* curr_catalog = &root;
	FILE *outfile;
	FILE *infile;
	file f;
	catalog p;

	path.push_back(&root);
	while (true)
	{
		for (int i = 0; i < path.size(); i++) {
			if (i == 0) {
				cout << (*path[i]).name;
			}
			else {
				cout << "\\" << (*path[i]).name;
			}
		}
		cout << ">";
		cin >> cases;
		req = cases.substr(0, cases.find(" "));

		if (req == "cf") {
			cin >> filename;
			cin >> type;
			type = type.substr(1, type.size());
			(*curr_catalog).files.push_back(CREATE_FILE(filename, type));
			ind temp;
			temp.file_name = filename;
			index_vector.push_back(temp);

		}
		else if (req == "md") {
			cin >> filename;
			(*curr_catalog).catalogs.push_back(MD(filename));
		}

		else if (req == "dir") {
			DIR(*curr_catalog);
			for (int i = 0; i < (*curr_catalog).catalogs.size(); i++) {
				catalog *temp = &(*curr_catalog).catalogs[i];
				cout << (*temp).name << endl;
			}
		}
		else if (req == "del") {
			cin >> filename;
			DEL(&curr_catalog, filename);
		}
		else if (req == "cd") {
			cin >> filename;
			for (int i = 0; i < (*curr_catalog).catalogs.size(); i++) {
				if ((*curr_catalog).catalogs[i].name == filename) {
					curr_catalog = &(*curr_catalog).catalogs[i];
					path.push_back(curr_catalog);
				}
				else {
					cout << "Directory is not found" << endl;
				}
			}
		}
		else if (req == "cd--") {
			if ((*curr_catalog).name != root.name) {
				curr_catalog = path[path.size() - 2];
				path.erase(path.begin() + (path.size() - 1));
			}
		}
		else if (req == "rmdir") {
			cin >> filename;
			RMDIR(&curr_catalog, filename);
		}
		else if (req == "move") {
			string new_catalog;
			cin >> filename;
			cin >> new_catalog;
			MOVE(path, filename, new_catalog, &curr_catalog);
		}
		else if (req == "read")
		{
			cin >> filename;
			READ((*curr_catalog), filename, index_vector);
		}
		else if (req == "write")
		{
			string data;
			cin >> filename;
			cout << "Input data to write..." << endl;
			getline(cin >> ws, data);
			WRITE(&curr_catalog, filename, data, &index_vector);
		}

		else if (req == "copy")
		{
			cin >> filename;
			COPY(&curr_catalog, filename);
		}

		else if (req == "save")
		{
			int size;
			string name;
			cin >> name;
			name = name + ".bin";
			ofstream ofs(name, ios::binary);
			size = block.size();
			ofs.write((char *)&size, sizeof(block.size()));
			for (int i = 0; i < block.size(); i++) {
				ofs.write((char *)&block[i], sizeof(block[i]));
			}
			size = root.catalogs.size();
			ofs.write((char *)&root.name, sizeof(root.name));
			ofs.write((char *)&size, sizeof(root.catalogs.size()));
			for (int i = 0; i < root.catalogs.size(); i++) {
				ofs.write((char *)&root.catalogs[i].name, sizeof(root.catalogs[i].name));
			}
			size = root.files.size();
			ofs.write((char *)&size, sizeof(root.files.size()));
			for (int i = 0; i < root.files.size(); i++) {
				ofs.write((char *)&root.files[i].name, sizeof(root.files[i].name));
				ofs.write((char *)&root.files[i].type, sizeof(root.files[i].type));
				size = root.files[i].index.size();
				ofs.write((char *)&size, sizeof(size));
				for (int j = 0; j < size; j++) {
					ofs.write((char *)&root.files[i].index[j], sizeof(root.files[i].index[j]));
				}

			}
			

			
		}

		else if (req == "load") {
			int size;
			file temp;
			string name;
			cin >> name;
			name = name + ".bin";
			ifstream ifs(name, ios::binary);
			ifs.read((char *)&size, sizeof(size));
			for (int i = 0; i < size; i++) {
				ifs.read((char *)&block[i], sizeof(block[i]));
			}
			ifs.read((char *)&root.name, sizeof(root.name));
			ifs.read((char *)&size, sizeof(size));

			for (int i = 0; i < size; i++) {
				ifs.read((char *)&name, sizeof(name));
				root.catalogs.push_back(MD(name));
			}
			ifs.read((char *)&size, sizeof(size)); 
			for (int i = 0; i < size; i++) {
				ifs.read((char *)&name, sizeof(name));
				temp.name = name;
				ifs.read((char *)&temp.type, sizeof(temp.type));
				int temp_size;
				ifs.read((char *)&temp_size, sizeof(temp_size));
				int ind;
				for (int j = 0; j < temp_size; j++) {
					ifs.read((char *)&ind, sizeof(ind));
					temp.index.push_back(ind);
				}
				root.files.push_back(temp);
			}

		}

		else if (req == "help") {
			cout << "md     create directory" << endl;
			cout << "cf     create file" << endl;
			cout << "cd     change directory" << endl;
			cout << "back   come back to parent directory" << endl;
			cout << "del    delete file" << endl;
			cout << "rmdir  delete directory" << endl;
			cout << "copy   copy file or directory" << endl;
			cout << "move   move or rename file or directory" << endl;
			cout << "write  write data to file" << endl;
			cout << "read   read data from file" << endl;
			cout << "save   save file system" << endl;
			cout << "dump   download file system" << endl;
			cout << endl;
		}
	}

	system("pause");
	getchar();
}